/**
 *	@file	unit_test_fnd_memory_shared_ptr.cpp
 *
 *	@brief	shared_ptr のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/memory/shared_ptr.hpp>
#include <bksge/fnd/memory/weak_ptr.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/memory/allocator.hpp>
#include <bksge/fnd/memory/default_delete.hpp>
#include <bksge/fnd/memory/get_deleter.hpp>
#include <bksge/fnd/utility/move.hpp>
//#include <bksge/fnd/sstream.hpp>
#include <sstream>
//#include <bksge/fnd/functional/hash.hpp>
#include <functional>	// hash
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_memory_test
{

namespace shared_ptr_test
{

static int s_x_dtor_count = 0;
static int s_y_dtor_count = 0;

struct X
{
	int i;
	int j;

	X(int i = 0)
		: i(i)
		, j()
	{}

	virtual ~X()
	{
		++s_x_dtor_count;
	}

	virtual int func() const { return 10; }
};

struct Y : public X
{
	Y(int i = 0)
		: X(i)
	{}

	virtual ~Y()
	{
		++s_y_dtor_count;
	}

	virtual int func() const { return 20; }
};

struct Deleter
{
	template <typename T>
	void operator()(T* p) const
	{
		delete p;
	}
};

GTEST_TEST(SharedPtrTest, ConstructTest)
{
	{
		// (1)
		// デフォルト構築。
		// 空のshared_ptrオブジェクトを構築する
		bksge::shared_ptr<int> p1;
		EXPECT_EQ(nullptr, p1.get());
		EXPECT_EQ(0,       p1.use_count());
	}
	{
		// (2)
		// ポインタの所有権を受け取る。
		bksge::shared_ptr<int> p2(new int(3));
		EXPECT_EQ(3, *p2.get());
		EXPECT_EQ(1, p2.use_count());
	}
	{
		// (3)
		// ポインタの所有権と、デリータを受け取る。
		// リソース解放時に、delete pの代わりにデリータが呼ばれる。
		bksge::shared_ptr<int> p3(new int(3), bksge::default_delete<int>());
		EXPECT_EQ(3, *p3.get());
		EXPECT_EQ(1, p3.use_count());
	}
	{
		// (4)
		// ポインタの所有権、デリータ、アロケータを受け取る。
		// アロケータは内部的にrebindされるので、要素型はなんでもいい。
		bksge::shared_ptr<int> p4(new int(3),
			bksge::default_delete<int>(),
			bksge::allocator<void>());
		EXPECT_EQ(3, *p4.get());
		EXPECT_EQ(1, p4.use_count());
	}
	{
		// (5)
		// デリータを受け取り、
		// ヌルポインタを所有するshared_ptrオブジェクトを構築する。
		bksge::shared_ptr<int> p5(nullptr, bksge::default_delete<int>());
		EXPECT_EQ(nullptr, p5.get());
		EXPECT_EQ(1,       p5.use_count());
	}
	{
		// (6)
		// デリータとアロケータを受け取り、
		// ヌルポインタを所有するshared_ptrオブジェクトを構築する。
		bksge::shared_ptr<int> p6(nullptr,
			bksge::default_delete<int>(),
			bksge::allocator<void>());
		EXPECT_EQ(nullptr, p6.get());
		EXPECT_EQ(1,       p6.use_count());
	}
	{
		// (7)
		// 要素型のメンバへのポインタを共有する。
		bksge::shared_ptr<X> p7_org(new X(3));
		bksge::shared_ptr<int> p7(p7_org, &(p7_org->i));
		EXPECT_EQ(3, *p7.get()); // p7はiへのポインタを所有する
		EXPECT_EQ(p7.use_count(), p7_org.use_count()); // 所有権はコピー元のshared_ptrと共有する
	}
	{
		// (8)
		// 他のshared_ptrとリソースを共有する
		bksge::shared_ptr<int> p8_org(new int(3));
		bksge::shared_ptr<int> p8 = p8_org;
		EXPECT_EQ(p8.get(), p8_org.get()); // p8_orgとo8はリソースを共有する
		EXPECT_EQ(2, p8.use_count()); // 所有者は2人
	}
	{
		// (9)
		bksge::shared_ptr<Y> p9_1(new Y(3));
		bksge::shared_ptr<X> p9_2(p9_1);
		EXPECT_EQ(p9_1.get(), p9_2.get());
		EXPECT_EQ(3, p9_2->i);
		EXPECT_EQ(2, p9_1.use_count());
	}
	{
		// (10)
		// 他のshared_ptrからリソースを移動する
		bksge::shared_ptr<int> p10_org(new int(3));
		bksge::shared_ptr<int> p10 = bksge::move(p10_org);
		EXPECT_EQ(3, *p10.get());
		EXPECT_EQ(1, p10.use_count());
		EXPECT_EQ(0, p10_org.use_count());
	}
	{
		// (11)
		bksge::shared_ptr<Y> p11_1(new Y(3));
		bksge::shared_ptr<X> p11_2(bksge::move(p11_1));
		EXPECT_EQ(nullptr, p11_1.get());
		EXPECT_EQ(3, p11_2->i);
		EXPECT_EQ(0, p11_1.use_count());
		EXPECT_EQ(1, p11_2.use_count());
	}
	{
		// (12)
		// weak_ptrから構築
		bksge::shared_ptr<int> p12_org(new int(3));
		bksge::weak_ptr<int> w12(p12_org);
		bksge::shared_ptr<int> p12(w12);
		EXPECT_TRUE(!!p12);
		EXPECT_EQ(3, *p12.get());
		EXPECT_EQ(2, p12.use_count());
	}

	// (13)
	// auto_ptr は対応しない

	// (14)
	// unique_ptrからリソースを移動する
	{
		bksge::unique_ptr<int> p14_org(new int(3));
		bksge::shared_ptr<int> p14 = bksge::move(p14_org);
		EXPECT_EQ(3, *p14.get());
		EXPECT_EQ(1, p14.use_count());
		EXPECT_EQ(nullptr, p14_org.get());
	}
	{
		bksge::unique_ptr<int, Deleter> p14_org(new int(3), Deleter());
		bksge::shared_ptr<int> p14 = bksge::move(p14_org);
		EXPECT_EQ(3, *p14.get());
		EXPECT_EQ(1, p14.use_count());
		EXPECT_EQ(nullptr, p14_org.get());
	}
	{
		Deleter d;
		bksge::unique_ptr<int, Deleter&> p14_org(new int(3), d);
		bksge::shared_ptr<int> p14 = bksge::move(p14_org);
		EXPECT_EQ(3, *p14.get());
		EXPECT_EQ(1, p14.use_count());
		EXPECT_EQ(nullptr, p14_org.get());
	}

	// (15)
	// 空のshared_ptrを構築する
	{
		bksge::shared_ptr<int> p15 = nullptr;
		EXPECT_EQ(nullptr, p15.get());
		EXPECT_EQ(0,       p15.use_count());
	}
}

GTEST_TEST(SharedPtrTest, DestructTest)
{
	s_x_dtor_count = 0;
	s_y_dtor_count = 0;
	{
		bksge::shared_ptr<X> p(new X());
	}
	EXPECT_EQ(1, s_x_dtor_count);
	EXPECT_EQ(0, s_y_dtor_count);

	s_x_dtor_count = 0;
	s_y_dtor_count = 0;
	{
		bksge::shared_ptr<X> p(new Y());
	}
	EXPECT_EQ(1, s_x_dtor_count);
	EXPECT_EQ(1, s_y_dtor_count);

	s_x_dtor_count = 0;
	s_y_dtor_count = 0;
	{
		bksge::shared_ptr<void> p(new X());
	}
	EXPECT_EQ(1, s_x_dtor_count);
	EXPECT_EQ(0, s_y_dtor_count);

	s_x_dtor_count = 0;
	s_y_dtor_count = 0;
	{
		bksge::shared_ptr<void> p(new Y());
	}
	EXPECT_EQ(1, s_x_dtor_count);
	EXPECT_EQ(1, s_y_dtor_count);
}

GTEST_TEST(SharedPtrTest, AssignTest)
{
	// (1)
	// 自身の所有権を放棄し、
	// 他のshared_ptrオブジェクトとリソースを共有する。
	{
		bksge::shared_ptr<int> p(new int(3));
		bksge::shared_ptr<int> q;
		q = p;

		EXPECT_EQ(3, *p.get());
		EXPECT_EQ(2, p.use_count());

		EXPECT_EQ(3, *q.get());
		EXPECT_EQ(2, q.use_count());
	}

	// (2)
	// 自身の所有権を放棄し、
	// 変換可能なshared_ptrオブジェクトとリソースを共有する。
	{
		bksge::shared_ptr<int> p(new int(3));
		bksge::shared_ptr<void> q;
		q = p;

		EXPECT_EQ(3, *p.get());
		EXPECT_EQ(2, p.use_count());

		EXPECT_EQ(3, *static_cast<int*>(q.get()));
		EXPECT_EQ(2, q.use_count());
	}

	// (3)
	// 自身の所有権を放棄し、
	// 他のshared_ptrから所有権を移動する
	{
		bksge::shared_ptr<int> p(new int(3));
		bksge::shared_ptr<int> q;
		q = bksge::move(p);

		// 移動元は空の状態になる
		EXPECT_EQ(nullptr, p.get());
		EXPECT_EQ(0, p.use_count());

		EXPECT_EQ(3, *q.get());
		EXPECT_EQ(1, q.use_count());
	}

	// (4)
	{
		bksge::shared_ptr<Y> p(new Y(3));
		bksge::shared_ptr<X> q;
		q = bksge::move(p);

		// 移動元は空の状態になる
		EXPECT_EQ(nullptr, p.get());
		EXPECT_EQ(0, p.use_count());

		EXPECT_EQ(3, q.get()->i);
		EXPECT_EQ(1, q.use_count());
	}

	// (5)
	// auto_ptr は対応しない

	// (6)
	// 自身の所有権を放棄し、
	// unique_ptrオブジェクトから所有権を移動する
	{
		bksge::unique_ptr<int> p(new int(3));
		bksge::shared_ptr<int> q;
		q = bksge::move(p);

		// 移動元は空の状態になる
		EXPECT_EQ(nullptr, p.get());

		EXPECT_EQ(3, *q.get());
		EXPECT_EQ(1, q.use_count());
	}
}

GTEST_TEST(SharedPtrTest, ResetTest)
{
	s_x_dtor_count = 0;
	s_y_dtor_count = 0;
	{
		bksge::shared_ptr<X> p1(new X(3));
		bksge::shared_ptr<X> p2 = p1;
		EXPECT_EQ(0, s_x_dtor_count);
		EXPECT_EQ(0, s_y_dtor_count);
		EXPECT_EQ(2, p1.use_count());
		EXPECT_EQ(2, p2.use_count());

		// (1)
		p1.reset();
		EXPECT_EQ(0, s_x_dtor_count);
		EXPECT_EQ(0, s_y_dtor_count);
		EXPECT_EQ(0, p1.use_count());
		EXPECT_EQ(1, p2.use_count());

		p2.reset();
		EXPECT_EQ(1, s_x_dtor_count);
		EXPECT_EQ(0, s_y_dtor_count);
		EXPECT_EQ(0, p1.use_count());
		EXPECT_EQ(0, p2.use_count());
	}
	EXPECT_EQ(1, s_x_dtor_count);
	EXPECT_EQ(0, s_y_dtor_count);

	s_x_dtor_count = 0;
	s_y_dtor_count = 0;
	{
		bksge::shared_ptr<X> p1(new X(3));
		bksge::shared_ptr<X> p2 = p1;
		EXPECT_EQ(0, s_x_dtor_count);
		EXPECT_EQ(0, s_y_dtor_count);
		EXPECT_EQ(2, p1.use_count());
		EXPECT_EQ(2, p2.use_count());
		EXPECT_EQ(3, p1->i);
		EXPECT_EQ(3, p2->i);

		// (2)
		p1.reset(new Y(4));
		EXPECT_EQ(0, s_x_dtor_count);
		EXPECT_EQ(0, s_y_dtor_count);
		EXPECT_EQ(1, p1.use_count());
		EXPECT_EQ(1, p2.use_count());
		EXPECT_EQ(4, p1->i);
		EXPECT_EQ(3, p2->i);

		// (3)
		p2.reset(new X(5), bksge::default_delete<X>());
		EXPECT_EQ(1, s_x_dtor_count);
		EXPECT_EQ(0, s_y_dtor_count);
		EXPECT_EQ(1, p1.use_count());
		EXPECT_EQ(1, p2.use_count());
		EXPECT_EQ(4, p1->i);
		EXPECT_EQ(5, p2->i);

		// (4)
		p1.reset(new X(6), bksge::default_delete<X>(), bksge::allocator<void>());
		EXPECT_EQ(2, s_x_dtor_count);
		EXPECT_EQ(1, s_y_dtor_count);
		EXPECT_EQ(1, p1.use_count());
		EXPECT_EQ(1, p2.use_count());
		EXPECT_EQ(6, p1->i);
		EXPECT_EQ(5, p2->i);
	}
	EXPECT_EQ(4, s_x_dtor_count);
	EXPECT_EQ(1, s_y_dtor_count);
}

GTEST_TEST(SharedPtrTest, SwapTest)
{
	bksge::shared_ptr<int> p1(new int(2));
	bksge::shared_ptr<int> p2(new int(3));

	EXPECT_EQ(2, *p1);
	EXPECT_EQ(3, *p2);

	p1.swap(p2);

	EXPECT_EQ(3, *p1);
	EXPECT_EQ(2, *p2);

	swap(p1, p2);

	EXPECT_EQ(2, *p1);
	EXPECT_EQ(3, *p2);
}

GTEST_TEST(SharedPtrTest, GetTest)
{
	bksge::shared_ptr<int> p(new int(3));

	int* raw_pointer = p.get();

	EXPECT_EQ(3, *raw_pointer);
}

GTEST_TEST(SharedPtrTest, DereferenceTest)
{
	bksge::shared_ptr<int> p(new int(3));

	int& r = *p;

	EXPECT_EQ(3, r);
}

GTEST_TEST(SharedPtrTest, OperatorArrowTest)
{
	bksge::shared_ptr<X> p(new X(3));

	EXPECT_EQ(3, p->i);
}

GTEST_TEST(SharedPtrTest, UseCountTest)
{
	bksge::shared_ptr<int> p1(new int(3));
	bksge::shared_ptr<int> p2;

	EXPECT_EQ(1, p1.use_count());
	EXPECT_EQ(0, p2.use_count());

	p2 = p1;

	EXPECT_EQ(2, p1.use_count());
	EXPECT_EQ(2, p2.use_count());

	{
		bksge::shared_ptr<int> p3 = p2;
		EXPECT_EQ(3, p1.use_count());
		EXPECT_EQ(3, p2.use_count());
		EXPECT_EQ(3, p3.use_count());

		p2.reset();
		EXPECT_EQ(2, p1.use_count());
		EXPECT_EQ(0, p2.use_count());
		EXPECT_EQ(2, p3.use_count());
	}

	EXPECT_EQ(1, p1.use_count());
	EXPECT_EQ(0, p2.use_count());

	p1.reset();

	EXPECT_EQ(0, p1.use_count());
	EXPECT_EQ(0, p2.use_count());
}

#if 0
GTEST_TEST(SharedPtrTest, UniqueTest)
{
	bksge::shared_ptr<int> p1(new int(3));
	bksge::shared_ptr<int> p2;

	EXPECT_TRUE (p1.unique());
	EXPECT_FALSE(p2.unique());

	p2 = p1;

	EXPECT_FALSE(p1.unique());
	EXPECT_FALSE(p2.unique());

	p1.reset();

	EXPECT_FALSE(p1.unique());
	EXPECT_TRUE (p2.unique());

	p2.reset();

	EXPECT_FALSE(p1.unique());
	EXPECT_FALSE(p2.unique());
}
#endif

GTEST_TEST(SharedPtrTest, OperatorBoolTest)
{
	{
		bksge::shared_ptr<int> p(new int(3));

		if (p)
		{
		}
		else
		{
			GTEST_FAIL();
		}

		EXPECT_FALSE(!p);
		EXPECT_TRUE (!!p);
	}
	{
		bksge::shared_ptr<int> p;

		if (p)
		{
			GTEST_FAIL();
		}
		else
		{
		}

		EXPECT_TRUE (!p);
		EXPECT_FALSE(!!p);
	}
}

GTEST_TEST(SharedPtrTest, OwnerBeforeTest)
{
	bksge::shared_ptr<X> org(new X());

	bksge::shared_ptr<int> a(org, &(org->i));
	bksge::shared_ptr<int> b(org, &(org->j));

	EXPECT_TRUE (a < b);
	EXPECT_FALSE(b < a);
	EXPECT_FALSE(a.owner_before(b));
	EXPECT_FALSE(b.owner_before(a));

	bksge::weak_ptr<int> c(a);
	bksge::weak_ptr<int> d(b);
	EXPECT_FALSE(a.owner_before(c));
	EXPECT_FALSE(a.owner_before(d));
	EXPECT_FALSE(b.owner_before(c));
	EXPECT_FALSE(b.owner_before(d));
}

GTEST_TEST(SharedPtrTest, CompareTest)
{
	bksge::shared_ptr<int> p1(new int(3));
	bksge::shared_ptr<int> p2(p1);
	bksge::shared_ptr<int> p3(new int(3));
	bksge::shared_ptr<int> p4;

	EXPECT_TRUE (p1      == p1);
	EXPECT_TRUE (p1      == p2);
	EXPECT_FALSE(p1      == p3);
	EXPECT_FALSE(p1      == p4);
	EXPECT_FALSE(p1      == nullptr);
	EXPECT_FALSE(nullptr == p1);
	EXPECT_TRUE (p4      == nullptr);
	EXPECT_TRUE (nullptr == p4);

	EXPECT_FALSE(p1      != p1);
	EXPECT_FALSE(p1      != p2);
	EXPECT_TRUE (p1      != p3);
	EXPECT_TRUE (p1      != p4);
	EXPECT_TRUE (p1      != nullptr);
	EXPECT_TRUE (nullptr != p1);
	EXPECT_FALSE(p4      != nullptr);
	EXPECT_FALSE(nullptr != p4);

	EXPECT_FALSE(p1      <  p1);
	EXPECT_FALSE(p1      <  p2);
	EXPECT_EQ(p1.get() < p3.get(), p1 < p3);
	EXPECT_FALSE(p1      <  p4);
	EXPECT_FALSE(p1      <  nullptr);
	EXPECT_TRUE (nullptr <  p1);
	EXPECT_FALSE(p4      <  nullptr);
	EXPECT_FALSE(nullptr <  p4);

	EXPECT_FALSE(p1      >  p1);
	EXPECT_FALSE(p1      >  p2);
	EXPECT_EQ(p1.get() > p3.get(), p1 > p3);
	EXPECT_TRUE (p1      >  p4);
	EXPECT_TRUE (p1      >  nullptr);
	EXPECT_FALSE(nullptr >  p1);
	EXPECT_FALSE(p4      >  nullptr);
	EXPECT_FALSE(nullptr >  p4);

	EXPECT_TRUE (p1      <= p1);
	EXPECT_TRUE (p1      <= p2);
	EXPECT_EQ(p1.get() <= p3.get(), p1 <= p3);
	EXPECT_FALSE(p1      <= p4);
	EXPECT_FALSE(p1      <= nullptr);
	EXPECT_TRUE (nullptr <= p1);
	EXPECT_TRUE (p4      <= nullptr);
	EXPECT_TRUE (nullptr <= p4);

	EXPECT_TRUE (p1      >= p1);
	EXPECT_TRUE (p1      >= p2);
	EXPECT_EQ(p1.get() >= p3.get(), p1 >= p3);
	EXPECT_TRUE (p1      >= p4);
	EXPECT_TRUE (p1      >= nullptr);
	EXPECT_FALSE(nullptr >= p1);
	EXPECT_TRUE (p4      >= nullptr);
	EXPECT_TRUE (nullptr >= p4);
}

GTEST_TEST(SharedPtrTest, GetDeleterTest)
{
	bksge::shared_ptr<int> p(new int(3), bksge::default_delete<int>());
	bksge::default_delete<int>* deleter = bksge::get_deleter<bksge::default_delete<int>>(p);
	(void)deleter;
}

GTEST_TEST(SharedPtrTest, OutputStreamTest)
{
	{
		bksge::shared_ptr<int> p(new int(3));
		std::stringstream ss1;
		ss1 << p;
		std::stringstream ss2;
		ss2 << p.get();
		EXPECT_EQ(ss2.str(), ss1.str());
	}
	{
		bksge::shared_ptr<int> p(new int(3));
		std::wstringstream ss1;
		ss1 << p;
		std::wstringstream ss2;
		ss2 << p.get();
		EXPECT_EQ(ss2.str(), ss1.str());
	}
}

GTEST_TEST(SharedPtrTest, HashTest)
{
	{
		const bksge::shared_ptr<int> sp1;
		const bksge::shared_ptr<int> sp2;
		EXPECT_EQ(
			std::hash<bksge::shared_ptr<int>>()(sp1),
			std::hash<bksge::shared_ptr<int>>()(sp2));
	}
	{
		const bksge::shared_ptr<int> sp1(new int(42));
		const bksge::shared_ptr<int> sp2(new int(42));
		EXPECT_NE(
			std::hash<bksge::shared_ptr<int>>()(sp1),
			std::hash<bksge::shared_ptr<int>>()(sp2));
	}
	{
		const bksge::shared_ptr<int> sp1(new int(42));
		const bksge::shared_ptr<int> sp2(sp1);
		EXPECT_EQ(
			std::hash<bksge::shared_ptr<int>>()(sp1),
			std::hash<bksge::shared_ptr<int>>()(sp2));
	}
}

}	// namespace shared_ptr_test

}	// namespace bksge_memory_test
