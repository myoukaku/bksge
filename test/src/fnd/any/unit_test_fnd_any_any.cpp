/**
 *	@file	unit_test_fnd_any_any.cpp
 *
 *	@brief	any のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/any/any.hpp>
#include <bksge/fnd/any/any_cast.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/type_traits/is_assignable.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_trivially_copyable.hpp>
#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/tuple/get.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/swap.hpp>
#include <bksge/fnd/utility/in_place_type.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/cstdint/uintptr_t.hpp>
#include <bksge/fnd/set/set.hpp>
#include <bksge/fnd/initializer_list.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>

namespace bksge_any_test
{

BKSGE_WARNING_PUSH()
BKSGE_WARNING_DISABLE_MSVC(4324)	// アラインメント指定子のために構造体がパッドされました

namespace ctor_test
{

static bool moved = false;
static bool copied = false;

struct X
{
	X() = default;
	X(const X&) { copied = true; }
	X(X&&) { moved = true; }
};

struct X2
{
	X2() = default;
	X2(const X2&) { copied = true; }
	X2(X2&&) BKSGE_NOEXCEPT { moved = true; }
};

#if !(defined(_MSC_VER) && (_MSC_VER <= 1913))

// Alignment requiremnts of this type prevent it being stored in 'any'
struct alignas(2 * alignof(void*)) Y {};

inline bool
stored_internally(void* obj, const bksge::any& a)
{
	bksge::uintptr_t a_addr = reinterpret_cast<bksge::uintptr_t>(&a);
	bksge::uintptr_t a_end = a_addr + sizeof(a);
	bksge::uintptr_t obj_addr = reinterpret_cast<bksge::uintptr_t>(obj);
	return (a_addr <= obj_addr) && (obj_addr < a_end);
}

#endif

struct combined
{
	bksge::vector<int> v;
	bksge::tuple<int, int> t;
	template <typename... Args>
	combined(bksge::initializer_list<int> il, Args&&... args)
		: v(il), t(bksge::forward<Args>(args)...)
	{}
};

struct LocationAware
{
	LocationAware() {}
	~LocationAware() { EXPECT_TRUE(self == this); }
	LocationAware(const LocationAware&) {}
	LocationAware& operator=(const LocationAware&) { return *this; }
	LocationAware(LocationAware&&) BKSGE_NOEXCEPT {}
	LocationAware& operator=(LocationAware&&) BKSGE_NOEXCEPT { return *this; }

	void* const self = this;
};
//static_assert(bksge::is_nothrow_move_constructible<LocationAware>::value, "");
static_assert(!bksge::is_trivially_copyable<LocationAware>::value, "");

GTEST_TEST(AnyTest, CtorTest)
{
	using std::get;
	{
		bksge::any x;
		EXPECT_TRUE(!x.has_value());

		bksge::any y(x);
		EXPECT_TRUE(!x.has_value());
		EXPECT_TRUE(!y.has_value());

		bksge::any z(bksge::move(y));
		EXPECT_TRUE(!y.has_value());
		EXPECT_TRUE(!z.has_value());
	}
	{
		bksge::any x(1);
		EXPECT_TRUE(x.has_value());

		bksge::any y(x);
		EXPECT_TRUE(x.has_value());
		EXPECT_TRUE(y.has_value());

		bksge::any z(bksge::move(y));
//		EXPECT_TRUE(!y.has_value());
		EXPECT_TRUE(z.has_value());
	}
	{
		moved = false;
		X x;
		bksge::any a1(x);
		EXPECT_FALSE(moved);
		bksge::any a2(bksge::move(x));
		EXPECT_TRUE(moved);
	}
	{
		moved = false;
		X x;
		bksge::any a1(x);
		EXPECT_FALSE(moved);
		copied = false;
		bksge::any a2(bksge::move(a1));
		EXPECT_FALSE(copied);
	}
	{
		moved = false;
		X2 x;
		bksge::any a1(x);
		EXPECT_FALSE(moved);
		copied = false;
		bksge::any a2(bksge::move(a1));
		EXPECT_FALSE(copied);
		EXPECT_TRUE(moved);
	}

	// aligned test
#if 0//!(defined(_MSC_VER) && (_MSC_VER <= 1913))
	{
		bksge::any a = Y{};
		Y& x = bksge::any_cast<Y&>(a);
		EXPECT_TRUE(!stored_internally(&x, a));

		a = 'X';
		char& c = bksge::any_cast<char&>(a);
		EXPECT_TRUE(stored_internally(&c, a));
	}
#endif

	// in_place test
	{
		const int i = 42;
		bksge::any o(bksge::in_place_type_t<int>{}, i);
		int& i2 = bksge::any_cast<int&>(o);
		EXPECT_TRUE(i2 == 42);
		EXPECT_TRUE(&i2 != &i);

		bksge::any o2(bksge::in_place_type_t<bksge::tuple<int, int>>{}, 1, 2);
		bksge::tuple<int, int>& t = bksge::any_cast<bksge::tuple<int, int>&>(o2);
		EXPECT_EQ(get<0>(t), 1);
		EXPECT_EQ(get<1>(t), 2);

		bksge::any o3(bksge::in_place_type_t<bksge::vector<int>>{}, { 42, 666 });
		bksge::vector<int>& v = bksge::any_cast<bksge::vector<int>&>(o3);
		EXPECT_EQ(v[0], 42);
		EXPECT_EQ(v[1], 666);
		EXPECT_EQ(v.size(), 2u);

		bksge::any o4(bksge::in_place_type_t<combined>{}, { 42, 666 });
		combined& c = bksge::any_cast<combined&>(o4);
		EXPECT_EQ(c.v[0], 42);
		EXPECT_EQ(c.v[1], 666);
		EXPECT_EQ(c.v.size(), 2u);
		EXPECT_EQ(get<0>(c.t), 0);
		EXPECT_EQ(get<1>(c.t), 0);

		bksge::any o5(bksge::in_place_type_t<combined>{}, { 1, 2 }, 3, 4);
		combined& c2 = bksge::any_cast<combined&>(o5);
		EXPECT_EQ(c2.v[0], 1);
		EXPECT_EQ(c2.v[1], 2);
		EXPECT_EQ(c2.v.size(), 2u);
		EXPECT_EQ(get<0>(c2.t), 3);
		EXPECT_EQ(get<1>(c2.t), 4);

#if !defined(BKSGE_NO_RTTI)
		bksge::any o6(bksge::in_place_type_t<int&>{}, i);
		EXPECT_TRUE(o6.type() == o.type());

		bksge::any o7(bksge::in_place_type_t<void()>{}, nullptr);
		bksge::any o8(bksge::in_place_type_t<void(*)()>{}, nullptr);
		EXPECT_TRUE(o7.type() == o8.type());

		bksge::any o9(bksge::in_place_type_t<char(&)[42]>{}, nullptr);
		bksge::any o10(bksge::in_place_type_t<char*>{}, nullptr);
		EXPECT_TRUE(o9.type() == o10.type());
#endif
	}

	// nontrivial test
	{

		LocationAware l;
		bksge::any a = l;
	}
	{
		LocationAware l;
		bksge::any a = l;
		bksge::any b = a;
		{
			bksge::any tmp = bksge::move(a);
			a = bksge::move(b);
			b = bksge::move(tmp);
		}
	}
	{
		LocationAware l;
		bksge::any a = l;
		bksge::any b = a;
		swap(a, b);
	}
}

}	// namespace ctor_test

BKSGE_WARNING_POP()

namespace assign_test
{

static bool moved = false;
static bool copied = false;

struct X
{
	X() = default;
	X(const X&) { copied = true; }
	X(X&&) { moved = true; }
};

struct X2
{
	X2() = default;
	X2(const X2&) { copied = true; }
	X2(X2&&) BKSGE_NOEXCEPT { moved = true; }
};

struct combined
{
	bksge::vector<int> v;
	bksge::tuple<int, int> t;
	template <typename... Args>
	combined(bksge::initializer_list<int> il, Args&&... args)
		: v(il), t(bksge::forward<Args>(args)...)
	{}
};


static bool should_throw = false;
struct Bad
{
	Bad() = default;
	Bad(const Bad&) { if (should_throw) throw 666; }
};

struct Bad2
{
	Bad2() = default;
	Bad2(const Bad2&) { if (should_throw) throw 666; }
	Bad2(Bad2&&) BKSGE_NOEXCEPT {}
};

struct Good
{
	Good() = default;
	Good(const Good&) = default;
	Good(Good&&) {}//= default;
	~Good() {}
};


static bksge::set<const void*> live_objects;

struct A
{
	A() { live_objects.insert(this); }
	~A() { live_objects.erase(this); }
	A(const A& a) { EXPECT_TRUE(live_objects.count(&a) != 0); live_objects.insert(this); }
};

BKSGE_WARNING_PUSH()
#if defined(__clang_major__) && (__clang_major__ >= 7) && !defined(__APPLE__)
BKSGE_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
#endif

GTEST_TEST(AnyTest, AssignTest)
{
	using std::get;
	{
		bksge::any x;
		bksge::any y;
		y = x;
		EXPECT_TRUE(!x.has_value());
		EXPECT_TRUE(!y.has_value());

		y = bksge::move(x);
		EXPECT_TRUE(!x.has_value());
		EXPECT_TRUE(!y.has_value());
	}
	{
		bksge::any x(1);
		bksge::any y;
		y = x;
		EXPECT_TRUE(x.has_value());
		EXPECT_TRUE(y.has_value());

		x = bksge::move(y);
		EXPECT_TRUE(x.has_value());
//		EXPECT_TRUE(!y.has_value());
	}

	{
		moved = false;
		X x;
		bksge::any a1;
		a1 = x;
		EXPECT_FALSE(moved);
		bksge::any a2;
		copied = false;
		a2 = bksge::move(x);
		EXPECT_TRUE(moved);
		EXPECT_FALSE(copied);
	}
	{
		moved = false;
		X x;
		bksge::any a1;
		a1 = x;
		EXPECT_FALSE(moved);
		bksge::any a2;
		copied = false;
		a2 = bksge::move(a1);
		EXPECT_FALSE(moved);
		EXPECT_FALSE(copied);
	}
	{
		moved = false;
		X2 x;
		bksge::any a1;
		a1 = x;
		EXPECT_TRUE(copied);
		EXPECT_TRUE(moved);

		bksge::any a2;
		moved = false;
		copied = false;
		a2 = bksge::move(a1);
		EXPECT_TRUE(moved);
		EXPECT_FALSE(copied);
	}

	// emplace test
	{
		const int i = 42;
		bksge::any o;
		o.emplace<int>(i);
		int& i2 = bksge::any_cast<int&>(o);
		EXPECT_TRUE(i2 == 42);
		EXPECT_TRUE(&i2 != &i);

		bksge::any o2;
		o2.emplace<bksge::tuple<int, int>>(1, 2);
		bksge::tuple<int, int>& t = bksge::any_cast<bksge::tuple<int, int>&>(o2);
		EXPECT_EQ(get<0>(t), 1);
		EXPECT_EQ(get<1>(t), 2);

		bksge::any o3;
		o3.emplace<bksge::vector<int>>({ 42, 666 });
		bksge::vector<int>& v = bksge::any_cast<bksge::vector<int>&>(o3);
		EXPECT_EQ(v[0], 42);
		EXPECT_EQ(v[1], 666);
		EXPECT_EQ(v.size(), 2u);

		bksge::any o4;
		o4.emplace<combined>({ 42, 666 });
		combined& c = bksge::any_cast<combined&>(o4);
		EXPECT_EQ(c.v[0], 42);
		EXPECT_EQ(c.v[1], 666);
		EXPECT_EQ(c.v.size(), 2u);
		EXPECT_EQ(get<0>(c.t), 0);
		EXPECT_EQ(get<1>(c.t), 0);

		bksge::any o5;
		o5.emplace<combined>({ 1, 2 }, 3, 4);
		combined& c2 = bksge::any_cast<combined&>(o5);
		EXPECT_EQ(c2.v[0], 1);
		EXPECT_EQ(c2.v[1], 2);
		EXPECT_EQ(c2.v.size(), 2u);
		EXPECT_EQ(get<0>(c2.t), 3);
		EXPECT_EQ(get<1>(c2.t), 4);

#if !defined(BKSGE_NO_RTTI)
		bksge::any o6;
		o6.emplace<const int&>(i);
		EXPECT_TRUE(o6.type() == o.type());

		bksge::any o7;
		o7.emplace<void()>(nullptr);

		bksge::any o8;
		o8.emplace<void(*)()>(nullptr);
		EXPECT_TRUE(o7.type() == o8.type());

		bksge::any o9;
		o9.emplace<char(&)[42]>(nullptr);

		bksge::any o10;
		o10.emplace<char*>(nullptr);
		EXPECT_TRUE(o9.type() == o10.type());
#endif

		bksge::any o11;
		{
			auto t1 = &o11.emplace<int>(42);
			auto t2 = &bksge::any_cast<int&>(o11);
			EXPECT_TRUE(t1 == t2);
		}
		{
			auto t1 = &o11.emplace<bksge::vector<int>>({ 1, 2, 3 });
			auto t2 = &bksge::any_cast<bksge::vector<int>&>(o11);
			EXPECT_TRUE(t1 == t2);
		}
	}

	// exception test
	{
		bksge::any a1 = Good();
		try
		{
			Bad b;
			bksge::any a2 = b;
			should_throw = true;
			a1 = a2;
		}
		catch (...)
		{
			auto x = bksge::any_cast<Good>(a1);
			EXPECT_TRUE(a1.has_value());
			(void)bksge::any_cast<Good>(a1);
		}
		bksge::any a3 = Good();
		try
		{
			Bad2 b;
			bksge::any a4 = b;
			should_throw = true;
			a3 = a4;
		}
		catch (...)
		{
			auto x = bksge::any_cast<Good>(a1);
			EXPECT_TRUE(a1.has_value());
			(void)bksge::any_cast<Good>(a1);
		}
	}

	{
		bksge::any a;
		a = a;
		EXPECT_TRUE(!a.has_value());

		a = A{};
		a = a;
		EXPECT_TRUE(a.has_value());

		a.reset();
		EXPECT_TRUE(live_objects.empty());
	}
	{
		struct X
		{
			bksge::any a;
		};

		X x;
		bksge::swap(x, x); // results in "self-move-assignment" of X::a
		EXPECT_TRUE(!x.a.has_value());

		x.a = A{};
		bksge::swap(x, x); // results in "self-move-assignment" of X::a
		EXPECT_TRUE(x.a.has_value());

		x.a.reset();
		EXPECT_TRUE(live_objects.empty());
	}
	{
		bksge::any a;
		a.swap(a);
		EXPECT_TRUE(!a.has_value());

		a = A{};
		a.swap(a);
		EXPECT_TRUE(a.has_value());

		a.reset();
		EXPECT_TRUE(live_objects.empty());
	}
}

BKSGE_WARNING_POP()

}	// namespace assign_test

namespace requirements_test
{

struct NoDefaultCtor
{
	NoDefaultCtor() = delete;
};

GTEST_TEST(AnyTest, RequirementsTest)
{
	using bksge::any;
	using bksge::unique_ptr;

	static_assert( bksge::is_assignable<any&, int>::value, "");
	static_assert(!bksge::is_assignable<any&, unique_ptr<int>>::value, "");
	static_assert(!bksge::is_assignable<any&, unique_ptr<int> const&>::value, "");
	static_assert(!bksge::is_assignable<any&, unique_ptr<int>&>::value, "");
	static_assert( bksge::is_constructible<any, int>::value, "");
	static_assert(!bksge::is_constructible<any, unique_ptr<int>>::value, "");
	static_assert(!bksge::is_constructible<any&, unique_ptr<int> const&>::value, "");
	static_assert(!bksge::is_constructible<any&, unique_ptr<int>&>::value, "");

	static_assert(!bksge::is_constructible<any, bksge::in_place_type_t<NoDefaultCtor>>::value, "");
	static_assert(!bksge::is_constructible<any, bksge::in_place_type_t<NoDefaultCtor>&>::value, "");
	static_assert(!bksge::is_constructible<any, bksge::in_place_type_t<NoDefaultCtor>&&>::value, "");
	static_assert(!bksge::is_constructible<any, const bksge::in_place_type_t<NoDefaultCtor>&>::value, "");
	static_assert(!bksge::is_constructible<any, const bksge::in_place_type_t<NoDefaultCtor>&&>::value, "");
}

}	// namespace requirements_test

GTEST_TEST(AnyTest, TypeTest)
{
#if !defined(BKSGE_NO_RTTI)
	bksge::any x;
	EXPECT_TRUE(x.type() == typeid(void));
	x = 1;
	EXPECT_TRUE(x.type() == typeid(int));
	x = bksge::vector<int>{1,2,3};
	EXPECT_TRUE(x.type() == typeid(bksge::vector<int>));
	x = bksge::any();
	EXPECT_TRUE(x.type() == typeid(void));
#endif
}

GTEST_TEST(AnyTest, SwapTest)
{
	bksge::any x(1);
	bksge::any y;
	swap(x, y);
	EXPECT_TRUE(!x.has_value());
	EXPECT_TRUE( y.has_value());
}

}	// namespace bksge_any_test
