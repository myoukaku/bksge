/**
 *	@file	unit_test_fnd_memory_weak_ptr.cpp
 *
 *	@brief	weak_ptr のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/memory/weak_ptr.hpp>
#include <bksge/fnd/memory/shared_ptr.hpp>
#include <bksge/fnd/memory/static_pointer_cast.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <gtest/gtest.h>

namespace bksge_memory_test
{

namespace weak_ptr_test
{

struct X
{
	int i;
	int j;
};

GTEST_TEST(WeakPtrTest, ConstructTest)
{
	// (1)
	// 監視対象を持たない、空のweak_ptrオブジェクトを構築する。
	{
		bksge::weak_ptr<int> wp;
		EXPECT_EQ(0, wp.use_count());
	}

	// (2)
	// 他のweak_ptrオブジェクトの監視対象をコピーする
	{
		bksge::shared_ptr<int> sp(new int(3));
		{
			bksge::weak_ptr<int> wp_org = sp; // wp_orgはspを監視する
			bksge::weak_ptr<int> wp = wp_org; // wp_orgの監視対象をコピーする
			EXPECT_EQ(1, sp.use_count());
			EXPECT_EQ(1, wp_org.use_count());
			EXPECT_EQ(1, wp.use_count());

			if (bksge::shared_ptr<int> r = wp.lock())
			{
				EXPECT_EQ(2, sp.use_count());
				EXPECT_EQ(2, wp_org.use_count());
				EXPECT_EQ(2, wp.use_count());
				EXPECT_EQ(2, r.use_count());
				EXPECT_EQ(3, *r);
			}
			EXPECT_EQ(1, sp.use_count());
		}
		EXPECT_EQ(1, sp.use_count());
	}

	// (3)
	// 変換可能なweak_ptrオブジェクトの監視対象をコピーする
	{
		bksge::shared_ptr<int> sp(new int(3));
		{
			bksge::weak_ptr<int> wp_org = sp;
			bksge::weak_ptr<void> wp = wp_org;
			EXPECT_EQ(1, sp.use_count());
			EXPECT_EQ(1, wp_org.use_count());
			EXPECT_EQ(1, wp.use_count());

			if (bksge::shared_ptr<int> r = bksge::static_pointer_cast<int>(wp.lock()))
			{
				EXPECT_EQ(2, sp.use_count());
				EXPECT_EQ(2, wp_org.use_count());
				EXPECT_EQ(2, wp.use_count());
				EXPECT_EQ(2, r.use_count());
				EXPECT_EQ(3, *r);
			}
			EXPECT_EQ(1, sp.use_count());
		}
		EXPECT_EQ(1, sp.use_count());
	}

	// (4)
	// shared_ptrオブジェクトを監視する
	{
		bksge::shared_ptr<int> sp(new int(3));
		{
			bksge::weak_ptr<int> wp = sp;
			EXPECT_EQ(1, sp.use_count());
			EXPECT_EQ(1, wp.use_count());

			if (bksge::shared_ptr<int> r = wp.lock())
			{
				EXPECT_EQ(2, sp.use_count());
				EXPECT_EQ(2, wp.use_count());
				EXPECT_EQ(2, r.use_count());
				EXPECT_EQ(3, *r);
			}
			EXPECT_EQ(1, sp.use_count());
		}
		EXPECT_EQ(1, sp.use_count());
	}

	// (5)
	// weak_ptrオブジェクトの監視対象を移動する
	{
		bksge::shared_ptr<int> sp(new int(3));
		{
			bksge::weak_ptr<int> wp_org = sp;
			bksge::weak_ptr<int> wp = bksge::move(wp_org);
			EXPECT_EQ(1, sp.use_count());
			EXPECT_EQ(0, wp_org.use_count());
			EXPECT_EQ(1, wp.use_count());

			if (bksge::shared_ptr<int> r = wp.lock())
			{
				EXPECT_EQ(2, sp.use_count());
				EXPECT_EQ(0, wp_org.use_count());
				EXPECT_EQ(2, wp.use_count());
				EXPECT_EQ(2, r.use_count());
				EXPECT_EQ(3, *r);
			}
			EXPECT_EQ(1, sp.use_count());
		}
		EXPECT_EQ(1, sp.use_count());
	}

	// (6)
	// 変換可能なweak_ptrオブジェクトの監視対象を移動する
	{
		bksge::shared_ptr<int> sp(new int(3));
		{
			bksge::weak_ptr<int> wp_org = sp;
			bksge::weak_ptr<void> wp = bksge::move(wp_org);
			EXPECT_EQ(1, sp.use_count());
			EXPECT_EQ(0, wp_org.use_count());
			EXPECT_EQ(1, wp.use_count());

			if (bksge::shared_ptr<int> r = bksge::static_pointer_cast<int>(wp.lock()))
			{
				EXPECT_EQ(2, sp.use_count());
				EXPECT_EQ(0, wp_org.use_count());
				EXPECT_EQ(2, wp.use_count());
				EXPECT_EQ(2, r.use_count());
				EXPECT_EQ(3, *r);
			}
			EXPECT_EQ(1, sp.use_count());
		}
		EXPECT_EQ(1, sp.use_count());
	}
}

GTEST_TEST(WeakPtrTest, AssignTest)
{
	{
		// (1)
		// 他のweak_ptrオブジェクトの監視対象を、新たに監視する
		bksge::shared_ptr<int> sp(new int(3));
		bksge::weak_ptr<int> wp_org = sp; // wp_orgはspを監視する
		bksge::weak_ptr<int> wp;
		wp = wp_org; // wpはwp_orgの監視対象を監視する

		bksge::shared_ptr<int> r = wp.lock();
		EXPECT_EQ(3, *r);
	}

	// (2)
	// 他の変換可能なweak_ptrオブジェクトの監視対象を、新たに監視する
	{
		bksge::shared_ptr<int> sp(new int(3));
		bksge::weak_ptr<int> wp_org = sp;
		bksge::weak_ptr<void> wp;
		wp = wp_org;

		bksge::shared_ptr<int> r = bksge::static_pointer_cast<int>(wp.lock());
		EXPECT_EQ(3, *r);
	}

	// (3)
	// shared_ptrオブジェクトを新たに監視する
	{
		bksge::shared_ptr<int> sp(new int(3));
		bksge::weak_ptr<int> wp;
		wp = sp;

		bksge::shared_ptr<int> r = wp.lock();
		EXPECT_EQ(3, *r);
	}

	// (4)
	// weak_ptrオブジェクトの監視対象を移動する
	{
		bksge::shared_ptr<int> sp(new int(3));
		bksge::weak_ptr<int> wp_org = sp;
		bksge::weak_ptr<int> wp;
		wp = bksge::move(wp_org);

		bksge::shared_ptr<int> r = wp.lock();
		EXPECT_EQ(3, *r);
	}

	// (5)
	// 変換可能なweak_ptrオブジェクトの監視対象を移動する
	{
		bksge::shared_ptr<int> sp(new int(3));
		bksge::weak_ptr<int> wp_org = sp;
		bksge::weak_ptr<void> wp;
		wp = bksge::move(wp_org);

		bksge::shared_ptr<int> r = bksge::static_pointer_cast<int>(wp.lock());
		EXPECT_EQ(3, *r);
	}
}

GTEST_TEST(WeakPtrTest, ResetTest)
{
	// wpはspを監視する
	bksge::shared_ptr<int> sp(new int(3));
	bksge::weak_ptr<int> wp = sp;

	EXPECT_EQ(1, wp.use_count());

	// spの監視をやめる
	wp.reset();

	EXPECT_EQ(0, wp.use_count());
}

GTEST_TEST(WeakPtrTest, SwapTest)
{
	bksge::shared_ptr<int> sp1(new int(1));
	bksge::weak_ptr<int> wp1 = sp1;

	bksge::shared_ptr<int> sp2(new int(2));
	bksge::weak_ptr<int> wp2 = sp2;

	EXPECT_EQ(1, *wp1.lock());
	EXPECT_EQ(2, *wp2.lock());

	// wp1とwp2を入れ替える
	wp1.swap(wp2);

	EXPECT_EQ(2, *wp1.lock());
	EXPECT_EQ(1, *wp2.lock());

	swap(wp1, wp2);

	EXPECT_EQ(1, *wp1.lock());
	EXPECT_EQ(2, *wp2.lock());
}

GTEST_TEST(WeakPtrTest, UseCountTest)
{
	bksge::weak_ptr<int> wp;
	EXPECT_EQ(0, wp.use_count());
	{
		bksge::shared_ptr<int> sp1(new int(1));
		wp = sp1;
		EXPECT_EQ(1, wp.use_count());

		{
			bksge::shared_ptr<int> sp2(sp1);
			EXPECT_EQ(2, wp.use_count());
		}
		EXPECT_EQ(1, wp.use_count());
	}
	EXPECT_EQ(0, wp.use_count());
}

GTEST_TEST(WeakPtrTest, ExpiredTest)
{
	bksge::weak_ptr<int> wp;
	EXPECT_TRUE(wp.expired());
	{
		bksge::shared_ptr<int> sp1(new int(1));
		wp = sp1;
		EXPECT_FALSE(wp.expired());

		{
			bksge::shared_ptr<int> sp2(sp1);
			EXPECT_FALSE(wp.expired());
		}
		EXPECT_FALSE(wp.expired());
	}
	EXPECT_TRUE(wp.expired());
}

GTEST_TEST(WeakPtrTest, LockTest)
{
	bksge::weak_ptr<int> wp;
	{
		auto r = wp.lock();
		EXPECT_TRUE(!r);
	}

	{
		bksge::shared_ptr<int> sp(new int(42));
		wp = sp;
		{
			auto r = wp.lock();
			EXPECT_TRUE(!!r);
			EXPECT_EQ(42, *r);
		}
	}

	{
		auto r = wp.lock();
		EXPECT_TRUE(!r);
	}
}

GTEST_TEST(WeakPtrTest, OwnerBeforeTest)
{
	bksge::shared_ptr<X> org(new X());

	bksge::shared_ptr<int> a(org, &(org->i));
	bksge::shared_ptr<int> b(org, &(org->j));

	bksge::weak_ptr<int> c(a);
	bksge::weak_ptr<int> d(b);
	EXPECT_FALSE(c.owner_before(a));
	EXPECT_FALSE(c.owner_before(b));
	EXPECT_FALSE(c.owner_before(c));
	EXPECT_FALSE(c.owner_before(d));
	EXPECT_FALSE(d.owner_before(a));
	EXPECT_FALSE(d.owner_before(b));
	EXPECT_FALSE(d.owner_before(c));
	EXPECT_FALSE(d.owner_before(d));
}

GTEST_TEST(WeakPtrTest, BadWeakPtrTest)
{
	bksge::shared_ptr<int> sp(new int(42));
	bksge::weak_ptr<int> wp(sp);

	sp.reset();
	EXPECT_THROW(bksge::shared_ptr<int> i(wp), std::bad_weak_ptr);
}

}	// namespace weak_ptr_test

}	// namespace bksge_memory_test
