/**
 *	@file	unit_test_fnd_functional_hash.cpp
 *
 *	@brief	hash のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/functional/hash.hpp>
#include <bksge/fnd/cstddef/nullptr_t.hpp>
#include <bksge/fnd/type_traits/is_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_copy_assignable.hpp>
#include <bksge/fnd/type_traits/is_move_assignable.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/is_nothrow_invocable.hpp>
#include <bksge/fnd/type_traits/is_invocable.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4307);	// integral constant overflow

namespace bksge_functional_test
{

namespace hash_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
inline BKSGE_CXX14_CONSTEXPR void test_common()
{
	static_assert(bksge::is_default_constructible<bksge::hash<T>>::value, "");
	static_assert(bksge::is_copy_constructible<bksge::hash<T>>::value, "");
	static_assert(bksge::is_move_constructible<bksge::hash<T>>::value, "");
	static_assert(bksge::is_copy_assignable<bksge::hash<T>>::value, "");
	static_assert(bksge::is_move_assignable<bksge::hash<T>>::value, "");

	static_assert(bksge::is_same<decltype(bksge::hash<T>{}(bksge::declval<T>())), std::size_t>::value, "");

	static_assert(bksge::is_nothrow_invocable<bksge::hash<T>      ,   T>::value, "");
	static_assert(bksge::is_nothrow_invocable<bksge::hash<T> const,   T>::value, "");
	static_assert(bksge::is_nothrow_invocable<bksge::hash<T>      &,  T>::value, "");
	static_assert(bksge::is_nothrow_invocable<bksge::hash<T> const&,  T>::value, "");
	static_assert(bksge::is_nothrow_invocable<bksge::hash<T>      &&, T>::value, "");
	static_assert(bksge::is_nothrow_invocable<bksge::hash<T> const&&, T>::value, "");
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool test_signed()
{
	test_common<T>();

	auto h1 = bksge::hash<T>{}( 0);
	auto h2 = bksge::hash<T>{}( 0);
	auto h3 = bksge::hash<T>{}(-1);
	auto h4 = bksge::hash<T>{}(-1);
	auto h5 = bksge::hash<T>{}( 1);
	auto h6 = bksge::hash<T>{}( 1);
	auto h7 = bksge::hash<T>{}(-2);
	auto h8 = bksge::hash<T>{}(-2);
	auto h9 = bksge::hash<T>{}( 2);
	auto h10= bksge::hash<T>{}( 2);

	VERIFY(h1 == h2);
	VERIFY(h1 != h3);
	VERIFY(h1 != h5);
	VERIFY(h1 != h7);
	VERIFY(h1 != h9);

	VERIFY(h3 == h4);
	VERIFY(h3 != h5);
	VERIFY(h3 != h7);
	VERIFY(h3 != h9);

	VERIFY(h5 == h6);
	VERIFY(h5 != h7);
	VERIFY(h5 != h9);

	VERIFY(h7 == h8);
	VERIFY(h7 != h9);

	VERIFY(h9 == h10);

	return true;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool test_unsigned()
{
	test_common<T>();

	auto h1 = bksge::hash<T>{}( 0);
	auto h2 = bksge::hash<T>{}( 0);
	auto h3 = bksge::hash<T>{}( 1);
	auto h4 = bksge::hash<T>{}( 1);
	auto h5 = bksge::hash<T>{}( 2);
	auto h6 = bksge::hash<T>{}( 2);
	auto h7 = bksge::hash<T>{}( 3);
	auto h8 = bksge::hash<T>{}( 3);
	auto h9 = bksge::hash<T>{}( 4);
	auto h10= bksge::hash<T>{}( 4);

	VERIFY(h1 == h2);
	VERIFY(h1 != h3);
	VERIFY(h1 != h5);
	VERIFY(h1 != h7);
	VERIFY(h1 != h9);

	VERIFY(h3 == h4);
	VERIFY(h3 != h5);
	VERIFY(h3 != h7);
	VERIFY(h3 != h9);

	VERIFY(h5 == h6);
	VERIFY(h5 != h7);
	VERIFY(h5 != h9);

	VERIFY(h7 == h8);
	VERIFY(h7 != h9);

	VERIFY(h9 == h10);

	return true;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool test_float()
{
	test_common<T>();

	auto h1 = bksge::hash<T>{}(T( 0.0));
	auto h2 = bksge::hash<T>{}(T(-0.0));
	auto h3 = bksge::hash<T>{}(T( 0.1));
	auto h4 = bksge::hash<T>{}(T( 0.1));
	auto h5 = bksge::hash<T>{}(T(-0.5));
	auto h6 = bksge::hash<T>{}(T(-0.5));
	auto h7 = bksge::hash<T>{}(T( 0.5));
	auto h8 = bksge::hash<T>{}(T( 0.5));
	auto h9 = bksge::hash<T>{}(T( 1.0));
	auto h10= bksge::hash<T>{}(T( 1.0));

	VERIFY(h1 == h2);
	VERIFY(h1 != h3);
	VERIFY(h1 != h5);
	VERIFY(h1 != h7);
	VERIFY(h1 != h9);

	VERIFY(h3 == h4);
	VERIFY(h3 != h5);
	VERIFY(h3 != h7);
	VERIFY(h3 != h9);

	VERIFY(h5 == h6);
	VERIFY(h5 != h7);
	VERIFY(h5 != h9);

	VERIFY(h7 == h8);
	VERIFY(h7 != h9);

	VERIFY(h9 == h10);

	return true;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool test_char()
{
	test_common<T>();

	auto h1 = bksge::hash<T>{}( 0);
	auto h2 = bksge::hash<T>{}( 0);
	auto h3 = bksge::hash<T>{}(10);
	auto h4 = bksge::hash<T>{}(10);
	auto h5 = bksge::hash<T>{}(20);
	auto h6 = bksge::hash<T>{}(20);
	auto h7 = bksge::hash<T>{}(30);
	auto h8 = bksge::hash<T>{}(30);
	auto h9 = bksge::hash<T>{}(40);
	auto h10= bksge::hash<T>{}(40);

	VERIFY(h1 == h2);
	VERIFY(h1 != h3);
	VERIFY(h1 != h5);
	VERIFY(h1 != h7);
	VERIFY(h1 != h9);

	VERIFY(h3 == h4);
	VERIFY(h3 != h5);
	VERIFY(h3 != h7);
	VERIFY(h3 != h9);

	VERIFY(h5 == h6);
	VERIFY(h5 != h7);
	VERIFY(h5 != h9);

	VERIFY(h7 == h8);
	VERIFY(h7 != h9);

	VERIFY(h9 == h10);

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test_bool()
{
	test_common<bool>();

	auto h1 = bksge::hash<bool>{}(true);
	auto h2 = bksge::hash<bool>{}(true);
	auto h3 = bksge::hash<bool>{}(false);
	auto h4 = bksge::hash<bool>{}(false);
	VERIFY(h1 == h2);
	VERIFY(h1 != h3);
	VERIFY(h1 != h4);
	VERIFY(h3 == h4);

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test_nullptr()
{
	test_common<bksge::nullptr_t>();

	auto h1 = bksge::hash<bksge::nullptr_t>{}(nullptr);
	auto h2 = bksge::hash<bksge::nullptr_t>{}(nullptr);
	VERIFY(h1 == h2);

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test_enum()
{
	enum Enum1 : int
	{
		ONE = 1,
		TWO = 2,
	};

	enum class Enum2 : unsigned int
	{
		THREE = 3,
		FOUR  = 4,
	};

	test_common<Enum1>();
	test_common<Enum2>();

	VERIFY(bksge::hash<int>{}(1) == bksge::hash<Enum1>{}(ONE));
	VERIFY(bksge::hash<int>{}(2) == bksge::hash<Enum1>{}(TWO));
	VERIFY(bksge::hash<unsigned int>{}(3) == bksge::hash<Enum2>{}(Enum2::THREE));
	VERIFY(bksge::hash<unsigned int>{}(4) == bksge::hash<Enum2>{}(Enum2::FOUR));

	return true;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool test_ptr()
{
	test_common<T*>();

	T x1{};
	T x2{};
	T x3{};

	T* p1 = &x1;
	T* p2 = &x1;
	T* p3 = &x2;
	T* p4 = &x2;
	T* p5 = &x3;
	T* p6 = &x3;

	auto h1 = bksge::hash<T*>{}(p1);
	auto h2 = bksge::hash<T*>{}(p2);
	auto h3 = bksge::hash<T*>{}(p3);
	auto h4 = bksge::hash<T*>{}(p4);
	auto h5 = bksge::hash<T*>{}(p5);
	auto h6 = bksge::hash<T*>{}(p6);

	VERIFY(h1 == h2);
	VERIFY(h1 != h3);
	VERIFY(h1 != h5);
	VERIFY(h3 == h4);
	VERIFY(h3 != h5);
	VERIFY(h5 == h6);

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test_poisoned()
{
	struct NonHashable {};

	static_assert(!bksge::is_default_constructible<bksge::hash<NonHashable>>::value, "");
	static_assert(!bksge::is_copy_constructible<bksge::hash<NonHashable>>::value, "");
	static_assert(!bksge::is_move_constructible<bksge::hash<NonHashable>>::value, "");
	static_assert(!bksge::is_copy_assignable<bksge::hash<NonHashable>>::value, "");
	static_assert(!bksge::is_move_assignable<bksge::hash<NonHashable>>::value, "");

	static_assert(!bksge::is_invocable<bksge::hash<NonHashable>      ,   NonHashable>::value, "");
	static_assert(!bksge::is_invocable<bksge::hash<NonHashable> const,   NonHashable>::value, "");
	static_assert(!bksge::is_invocable<bksge::hash<NonHashable>      &,  NonHashable>::value, "");
	static_assert(!bksge::is_invocable<bksge::hash<NonHashable> const&,  NonHashable>::value, "");
	static_assert(!bksge::is_invocable<bksge::hash<NonHashable>      &&, NonHashable>::value, "");
	static_assert(!bksge::is_invocable<bksge::hash<NonHashable> const&&, NonHashable>::value, "");

	return true;
}

GTEST_TEST(FunctionalTest, HashTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test_signed<signed char>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test_signed<signed short>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test_signed<signed int>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test_signed<signed long>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test_signed<signed long long>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test_unsigned<unsigned char>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test_unsigned<unsigned short>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test_unsigned<unsigned int>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test_unsigned<unsigned long>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test_unsigned<unsigned long long>());

	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(test_float<float>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(test_float<double>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(test_float<long double>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test_char<char>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test_char<wchar_t>());
#if defined(BKSGE_HAS_CXX20_CHAR8_T)
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test_char<char8_t>());
#endif
#if defined(BKSGE_HAS_CXX11_CHAR16_T)
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test_char<char16_t>());
#endif
#if defined(BKSGE_HAS_CXX11_CHAR32_T)
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test_char<char32_t>());
#endif

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test_bool());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test_nullptr());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test_enum());

	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(test_ptr<int>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(test_ptr<unsigned int>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(test_ptr<long long>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(test_ptr<float>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(test_ptr<double>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(test_ptr<long double>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test_poisoned());
}

#undef VERIFY

}	// namespace hash_test

}	// namespace bksge_functional_test

BKSGE_WARNING_POP();
