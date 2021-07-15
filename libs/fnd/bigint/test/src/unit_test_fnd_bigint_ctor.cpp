/**
 *	@file	unit_test_fnd_bigint_ctor.cpp
 *
 *	@brief	bigint のコンストラクタのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/bigint.hpp>
#include <bksge/fnd/type_traits/is_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_trivially_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_constructible.hpp>
#include <bksge/fnd/type_traits/is_trivially_constructible.hpp>
#include <bksge/fnd/type_traits/is_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_trivially_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_trivially_move_constructible.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/string.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include <limits>
#include <cstdint>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_CLANG("-Wsign-compare");
BKSGE_WARNING_DISABLE_CLANG("-Wliteral-conversion");
BKSGE_WARNING_DISABLE_MSVC(4127);	// conditional expression is constant
BKSGE_WARNING_DISABLE_MSVC(4244);	// conversion from '...' to '...', possible loss of data
BKSGE_WARNING_DISABLE_MSVC(4245);	// conversion from '...' to '...', signed/unsigned mismatch
BKSGE_WARNING_DISABLE_MSVC(4389);	// '==': signed/unsigned mismatch

namespace bksge_bigint_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline BKSGE_CXX14_CONSTEXPR bool CtorDefaultTest()
{
	static_assert( bksge::is_default_constructible<BigInt>::value, "");
	static_assert( bksge::is_nothrow_default_constructible<BigInt>::value, "");
	static_assert( bksge::is_implicitly_default_constructible<BigInt>::value, "");
	static_assert(!bksge::is_trivially_default_constructible<BigInt>::value, "");

	{
		BigInt x {};
		VERIFY(x == 0);
	}
	{
		BigInt x = {};
		VERIFY(x == 0);
	}

	return true;
}

template <typename BigInt>
inline BKSGE_CXX14_CONSTEXPR bool CtorIntTest()
{
	constexpr bool is_bounded = std::numeric_limits<BigInt>::is_bounded;
	static_assert(bksge::is_constructible<BigInt, int>::value            == true, "");
	static_assert(bksge::is_nothrow_constructible<BigInt, int>::value    == is_bounded, "");
	static_assert(bksge::is_implicitly_constructible<BigInt, int>::value == true, "");
	static_assert(bksge::is_trivially_constructible<BigInt, int>::value  == false, "");

	{
		BigInt x = {1};
		VERIFY(x == 1);
	}
	{
		BigInt x(-2);
		VERIFY(x == -2);
	}
	{
		BigInt x = 3;
		VERIFY(x == 3);
	}
	{
		BigInt x = {std::numeric_limits<std::int8_t>::min()};
		VERIFY(x == std::numeric_limits<std::int8_t>::min());
	}
	{
		BigInt x = {std::numeric_limits<std::int8_t>::max()};
		VERIFY(x == std::numeric_limits<std::int8_t>::max());
	}
	{
		BigInt x = {std::numeric_limits<std::int16_t>::min()};
		VERIFY(x == std::numeric_limits<std::int16_t>::min());
	}
	{
		BigInt x = {std::numeric_limits<std::int16_t>::max()};
		VERIFY(x == std::numeric_limits<std::int16_t>::max());
	}
	{
		BigInt x = {std::numeric_limits<std::int32_t>::min()};
		VERIFY(x == std::numeric_limits<std::int32_t>::min());
	}
	{
		BigInt x = {std::numeric_limits<std::int32_t>::max()};
		VERIFY(x == std::numeric_limits<std::int32_t>::max());
	}
	{
		BigInt x = {std::numeric_limits<std::int64_t>::min()};
		VERIFY(x == std::numeric_limits<std::int64_t>::min());
	}
	{
		BigInt x = {std::numeric_limits<std::int64_t>::max()};
		VERIFY(x == std::numeric_limits<std::int64_t>::max());
	}
	{
		BigInt x = {std::numeric_limits<std::uint8_t>::max()};
		VERIFY(x == std::numeric_limits<std::uint8_t>::max());
	}
	{
		BigInt x = {std::numeric_limits<std::uint16_t>::max()};
		VERIFY(x == std::numeric_limits<std::uint16_t>::max());
	}
	{
		BigInt x = {std::numeric_limits<std::uint32_t>::max()};
		VERIFY(x == std::numeric_limits<std::uint32_t>::max());
	}
	{
		BigInt x = {std::numeric_limits<std::uint64_t>::max()};
		VERIFY(x == std::numeric_limits<std::uint64_t>::max());
	}

	return true;
}

template <typename BigInt>
inline BKSGE_CXX14_CONSTEXPR bool CtorFloatTest()
{
	constexpr bool is_bounded = std::numeric_limits<BigInt>::is_bounded;
	static_assert(bksge::is_constructible<BigInt, float>::value            == true, "");
	static_assert(bksge::is_nothrow_constructible<BigInt, float>::value    == is_bounded, "");
	static_assert(bksge::is_implicitly_constructible<BigInt, float>::value == true, "");
//	static_assert(bksge::is_trivially_constructible<BigInt, float>::value  == true, "");
	{
		BigInt x(0.0f);
		VERIFY(x == 0);
	}
	{
		BigInt x(0.0);
		VERIFY(x == 0);
	}
	{
		BigInt x(0.0L);
		VERIFY(x == 0);
	}
	{
		BigInt x(-0.0f);
		VERIFY(x == 0);
	}
	{
		BigInt x(-0.0);
		VERIFY(x == 0);
	}
	{
		BigInt x(-0.0L);
		VERIFY(x == 0);
	}
	{
		BigInt x(0.5f);
		VERIFY(x == 0);
	}
	{
		BigInt x(1.5);
		VERIFY(x == 1);
	}
	{
		BigInt x(2.5L);
		VERIFY(x == 2);
	}
	{
		BigInt x(-0.5f);
		VERIFY(x == 0);
	}
	{
		BigInt x(-1.5);
		VERIFY(x == -1);
	}
	{
		BigInt x(-2.5L);
		VERIFY(x == -2);
	}
	{
		BigInt x(123.456f);
		VERIFY(x == 123);
	}
	{
		BigInt x(1234.567);
		VERIFY(x == 1234);
	}
	{
		BigInt x(12345.6789L);
		VERIFY(x == 12345);
	}
	{
		BigInt x(-123.456f);
		VERIFY(x == -123);
	}
	{
		BigInt x(-1234.567);
		VERIFY(x == -1234);
	}
	{
		BigInt x(-12345.6789L);
		VERIFY(x == -12345);
	}
	return true;
}

template <typename BigInt>
inline BKSGE_CXX14_CONSTEXPR bool CtorFloatLargeTest()
{
	{
		BigInt x((float)std::numeric_limits<std::int32_t>::max());
		VERIFY(x == BigInt("2147483648"));
	}
	{
		BigInt x((float)std::numeric_limits<std::int32_t>::min());
		VERIFY(x == BigInt("-2147483648"));
	}
	{
		BigInt x((float)std::numeric_limits<std::uint32_t>::max());
		VERIFY(x == BigInt("4294967296"));
	}
	{
		BigInt x((float)std::numeric_limits<std::uint32_t>::min());
		VERIFY(x == BigInt("0"));
	}
	{
		BigInt x((float)std::numeric_limits<std::int64_t>::max());
		VERIFY(x == BigInt("9223372036854775808"));
	}
	{
		BigInt x((float)std::numeric_limits<std::int64_t>::min());
		VERIFY(x == BigInt("-9223372036854775808"));
	}
	{
		BigInt x((float)std::numeric_limits<std::uint64_t>::max());
		VERIFY(x == BigInt("18446744073709551616"));
	}
	{
		BigInt x((float)std::numeric_limits<std::uint64_t>::min());
		VERIFY(x == BigInt("0"));
	}
	{
		BigInt x((double)std::numeric_limits<std::int32_t>::max());
		VERIFY(x == BigInt("2147483647"));
	}
	{
		BigInt x((double)std::numeric_limits<std::int32_t>::min());
		VERIFY(x == BigInt("-2147483648"));
	}
	{
		BigInt x((double)std::numeric_limits<std::uint32_t>::max());
		VERIFY(x == BigInt("4294967295"));
	}
	{
		BigInt x((double)std::numeric_limits<std::uint32_t>::min());
		VERIFY(x == BigInt("0"));
	}
	{
		BigInt x((double)std::numeric_limits<std::int64_t>::max());
		VERIFY(x == BigInt("9223372036854775808"));
	}
	{
		BigInt x((double)std::numeric_limits<std::int64_t>::min());
		VERIFY(x == BigInt("-9223372036854775808"));
	}
	{
		BigInt x((double)std::numeric_limits<std::uint64_t>::max());
		VERIFY(x == BigInt("18446744073709551616"));
	}
	{
		BigInt x((double)std::numeric_limits<std::uint64_t>::min());
		VERIFY(x == BigInt("0"));
	}
	{
		BigInt x(std::numeric_limits<float>::max());
		VERIFY(x == BigInt("340282346638528859811704183484516925440"));
	}
	{
		BigInt x(std::numeric_limits<float>::lowest());
		VERIFY(x == BigInt("-340282346638528859811704183484516925440"));
	}
	{
		BigInt x(std::numeric_limits<double>::max());
		VERIFY(x == BigInt("179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368"));
	}
	{
		BigInt x(std::numeric_limits<double>::lowest());
		VERIFY(x == BigInt("-179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368"));
	}
	return true;
}

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool CtorConvTest()
{
	{
		BigInt1 x1{};
		BigInt2 x2(x1);
		VERIFY(x2 == 0);
		VERIFY(x1 == x2);
	}
	{
		BigInt1 x1(1);
		BigInt2 x2(x1);
		VERIFY(x2 == 1);
		VERIFY(x1 == x2);
	}
	{
		BigInt1 x1(-1);
		BigInt2 x2(x1);
		if (std::numeric_limits<BigInt1>::is_signed &&
			std::numeric_limits<BigInt2>::is_signed)
		{
			VERIFY(x2 == -1);
			VERIFY(x1 == x2);
		}
	}
	{
		BigInt1 x1(123);
		BigInt2 x2(x1);
		VERIFY(x2 == 123);
		VERIFY(x1 == x2);
	}
	{
		BigInt1 x1(-123);
		BigInt2 x2(x1);
		if (std::numeric_limits<BigInt1>::is_signed &&
			std::numeric_limits<BigInt2>::is_signed)
		{
			VERIFY(x2 == -123);
			VERIFY(x1 == x2);
		}
	}
	return true;
}

template <typename BigInt>
inline BKSGE_CXX14_CONSTEXPR bool CtorStringTest()
{
	static_assert( bksge::is_constructible<BigInt, const char*>::value, "");
	static_assert(!bksge::is_nothrow_constructible<BigInt, const char*>::value, "");
	static_assert(!bksge::is_implicitly_constructible<BigInt, const char*>::value, "");
	static_assert(!bksge::is_trivially_constructible<BigInt, const char*>::value, "");

	static_assert( bksge::is_constructible<BigInt, bksge::string const&>::value, "");
	static_assert(!bksge::is_nothrow_constructible<BigInt, bksge::string const&>::value, "");
	static_assert(!bksge::is_implicitly_constructible<BigInt, bksge::string const&>::value, "");
	static_assert(!bksge::is_trivially_constructible<BigInt, bksge::string const&>::value, "");

	static_assert( bksge::is_constructible<BigInt, const wchar_t*>::value, "");
	static_assert(!bksge::is_nothrow_constructible<BigInt, const wchar_t*>::value, "");
	static_assert(!bksge::is_implicitly_constructible<BigInt, const wchar_t*>::value, "");
	static_assert(!bksge::is_trivially_constructible<BigInt, const wchar_t*>::value, "");

	static_assert( bksge::is_constructible<BigInt, bksge::wstring const&>::value, "");
	static_assert(!bksge::is_nothrow_constructible<BigInt, bksge::wstring const&>::value, "");
	static_assert(!bksge::is_implicitly_constructible<BigInt, bksge::wstring const&>::value, "");
	static_assert(!bksge::is_trivially_constructible<BigInt, bksge::wstring const&>::value, "");

#if defined(BKSGE_HAS_CXX20_CHAR8_T)
	static_assert( bksge::is_constructible<BigInt, const char8_t*>::value, "");
	static_assert(!bksge::is_nothrow_constructible<BigInt, const char8_t*>::value, "");
	static_assert(!bksge::is_implicitly_constructible<BigInt, const char8_t*>::value, "");
	static_assert(!bksge::is_trivially_constructible<BigInt, const char8_t*>::value, "");

	static_assert( bksge::is_constructible<BigInt, bksge::u8string const&>::value, "");
	static_assert(!bksge::is_nothrow_constructible<BigInt, bksge::u8string const&>::value, "");
	static_assert(!bksge::is_implicitly_constructible<BigInt, bksge::u8string const&>::value, "");
	static_assert(!bksge::is_trivially_constructible<BigInt, bksge::u8string const&>::value, "");
#endif

#if defined(BKSGE_HAS_CXX11_CHAR16_T)
	static_assert( bksge::is_constructible<BigInt, const char16_t*>::value, "");
	static_assert(!bksge::is_nothrow_constructible<BigInt, const char16_t*>::value, "");
	static_assert(!bksge::is_implicitly_constructible<BigInt, const char16_t*>::value, "");
	static_assert(!bksge::is_trivially_constructible<BigInt, const char16_t*>::value, "");

	static_assert( bksge::is_constructible<BigInt, bksge::u16string const&>::value, "");
	static_assert(!bksge::is_nothrow_constructible<BigInt, bksge::u16string const&>::value, "");
	static_assert(!bksge::is_implicitly_constructible<BigInt, bksge::u16string const&>::value, "");
	static_assert(!bksge::is_trivially_constructible<BigInt, bksge::u16string const&>::value, "");
#endif

#if defined(BKSGE_HAS_CXX11_CHAR32_T)
	static_assert( bksge::is_constructible<BigInt, const char32_t*>::value, "");
	static_assert(!bksge::is_nothrow_constructible<BigInt, const char32_t*>::value, "");
	static_assert(!bksge::is_implicitly_constructible<BigInt, const char32_t*>::value, "");
	static_assert(!bksge::is_trivially_constructible<BigInt, const char32_t*>::value, "");

	static_assert( bksge::is_constructible<BigInt, bksge::u32string const&>::value, "");
	static_assert(!bksge::is_nothrow_constructible<BigInt, bksge::u32string const&>::value, "");
	static_assert(!bksge::is_implicitly_constructible<BigInt, bksge::u32string const&>::value, "");
	static_assert(!bksge::is_trivially_constructible<BigInt, bksge::u32string const&>::value, "");
#endif

	// empty
	{
		BigInt x {""};
		VERIFY(x == 0);
	}
	{
		BigInt x {L""};
		VERIFY(x == 0);
	}

	// decimal
	{
		BigInt x {"0"};
		VERIFY(x == 0);
	}
	{
		BigInt x {L"1"};
		VERIFY(x == 1);
	}
	{
		BigInt x {"123"};
		VERIFY(x == 123);
	}
	{
		BigInt x {L"-42"};
		VERIFY(x == -42);
	}
	{
		BigInt x {"-4567"};
		VERIFY(x == -4567);
	}
	{
		BigInt x {"123456789"};
		VERIFY(x == 123456789);
	}
	{
		BigInt x {L"123456789"};
		VERIFY(x == 123456789);
	}
	// binary
	{
		BigInt x {"0b1111011"};
		VERIFY(x == 0b1111011);
		VERIFY(x == 123);
	}
	{
		BigInt x {L"-0b01111011"};
		VERIFY(x == -0b1111011);
		VERIFY(x == -123);
	}
	// hex
	{
		BigInt x {"0xffffffff"};
		VERIFY(x == 0xffffffff);
		VERIFY(x == 4294967295);
	}
	{
		BigInt x {L"0xffffffffffffffff"};
		VERIFY(x == 0xffffffffffffffff);
	}
	{
		BigInt x {"-0x007f"};
		VERIFY(x == -0x7f);
		VERIFY(x == -127);
	}
	// oct
	{
		BigInt x {L"02322"};
		VERIFY(x == 02322);
		VERIFY(x == 1234);
	}
	{
		BigInt x {"-02322"};
		VERIFY(x == -02322);
		VERIFY(x == -1234);
	}

#if defined(BKSGE_HAS_CXX20_CHAR8_T)
	{
		BigInt x {u8""};
		VERIFY(x == 0);
	}
	{
		BigInt x {u8"1234"};
		VERIFY(x == 1234);
	}
	{
		BigInt x {u8"0xabcdef"};
		VERIFY(x == 0xabcdef);
	}
#endif

#if defined(BKSGE_HAS_CXX11_CHAR16_T)
	{
		BigInt x {u""};
		VERIFY(x == 0);
	}
	{
		BigInt x {u"1234"};
		VERIFY(x == 1234);
	}
	{
		BigInt x {u"0xabcdef"};
		VERIFY(x == 0xabcdef);
	}
#endif

#if defined(BKSGE_HAS_CXX11_CHAR32_T)
	{
		BigInt x {U""};
		VERIFY(x == 0);
	}
	{
		BigInt x {U"1234"};
		VERIFY(x == 1234);
	}
	{
		BigInt x {U"0xabcdef"};
		VERIFY(x == 0xabcdef);
	}
#endif

	return true;
}

template <typename BigInt>
inline BKSGE_CXX14_CONSTEXPR bool CtorCopyTest()
{
	constexpr bool is_bounded = std::numeric_limits<BigInt>::is_bounded;
	static_assert(bksge::is_copy_constructible<BigInt>::value            == true, "");
	static_assert(bksge::is_nothrow_copy_constructible<BigInt>::value    == is_bounded, "");
	static_assert(bksge::is_implicitly_copy_constructible<BigInt>::value == true, "");
	static_assert(bksge::is_trivially_copy_constructible<BigInt>::value  == is_bounded, "");

	{
		BigInt x1;
		BigInt x2(x1);
		VERIFY(x2 == 0);
	}
	{
		BigInt x1 = 1;
		BigInt x2{x1};
		VERIFY(x2 == 1);
	}
	{
		BigInt x1{"12345"};
		BigInt x2(x1);
		VERIFY(x2 == 12345);
	}
	{
		BigInt x1{"-12345"};
		BigInt x2{x1};
		VERIFY(x2 == -12345);
	}
	return true;
}

template <typename BigInt>
inline BKSGE_CXX14_CONSTEXPR bool CtorMoveTest()
{
	constexpr bool is_bounded = std::numeric_limits<BigInt>::is_bounded;
	static_assert(bksge::is_move_constructible<BigInt>::value            == true, "");
	static_assert(bksge::is_nothrow_move_constructible<BigInt>::value    == true, "");
	static_assert(bksge::is_implicitly_move_constructible<BigInt>::value == true, "");
	static_assert(bksge::is_trivially_move_constructible<BigInt>::value  == is_bounded, "");

	{
		BigInt x1;
		BigInt x2(bksge::move(x1));
		VERIFY(x2 == 0);
	}
	{
		BigInt x1 = 1;
		BigInt x2{bksge::move(x1)};
		VERIFY(x2 == 1);
	}
	{
		BigInt x1{"12345"};
		BigInt x2(bksge::move(x1));
		VERIFY(x2 == 12345);
	}
	{
		BigInt x1{"-12345"};
		BigInt x2{bksge::move(x1)};
		VERIFY(x2 == -12345);
	}
	return true;
}

GTEST_TEST(BigIntTest, CtorTest)
{
	EXPECT_TRUE(CtorDefaultTest<bksge::bigint>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDefaultTest<bksge::int128_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDefaultTest<bksge::int256_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDefaultTest<bksge::int512_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDefaultTest<bksge::int1024_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDefaultTest<bksge::uint128_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDefaultTest<bksge::uint256_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDefaultTest<bksge::uint512_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDefaultTest<bksge::uint1024_t>());

	EXPECT_TRUE(CtorIntTest<bksge::bigint>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorIntTest<bksge::int128_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorIntTest<bksge::int256_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorIntTest<bksge::int512_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorIntTest<bksge::int1024_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorIntTest<bksge::uint128_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorIntTest<bksge::uint256_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorIntTest<bksge::uint512_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorIntTest<bksge::uint1024_t>());

	EXPECT_TRUE(CtorFloatTest<bksge::bigint>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorFloatTest<std::int32_t>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorFloatTest<std::int64_t>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorFloatTest<bksge::int128_t>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorFloatTest<bksge::int256_t>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorFloatTest<bksge::int512_t>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorFloatTest<bksge::int1024_t>());
//	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorFloatTest<std::uint32_t>());
//	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorFloatTest<std::uint64_t>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorFloatTest<bksge::uint128_t>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorFloatTest<bksge::uint256_t>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorFloatTest<bksge::uint512_t>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorFloatTest<bksge::uint1024_t>());

	EXPECT_TRUE(CtorFloatLargeTest<bksge::bigint>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorFloatLargeTest<bksge::int256_t>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorFloatLargeTest<bksge::int512_t>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorFloatLargeTest<bksge::int1024_t>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorFloatLargeTest<bksge::int2048_t>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorFloatLargeTest<bksge::uint256_t>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorFloatLargeTest<bksge::uint512_t>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorFloatLargeTest<bksge::uint1024_t>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorFloatLargeTest<bksge::uint2048_t>());

	static_assert(bksge::is_constructible<bksge::bigint, bksge::bigint>::value         == true, "");
	static_assert(bksge::is_constructible<bksge::bigint, bksge::int128_t>::value       == true, "");
	static_assert(bksge::is_constructible<bksge::bigint, bksge::int256_t>::value       == true, "");
	static_assert(bksge::is_constructible<bksge::bigint, bksge::int512_t>::value       == true, "");
	static_assert(bksge::is_constructible<bksge::bigint, bksge::int1024_t>::value      == true, "");
	static_assert(bksge::is_constructible<bksge::bigint, bksge::uint128_t>::value      == true, "");
	static_assert(bksge::is_constructible<bksge::bigint, bksge::uint256_t>::value      == true, "");
	static_assert(bksge::is_constructible<bksge::bigint, bksge::uint512_t>::value      == true, "");
	static_assert(bksge::is_constructible<bksge::bigint, bksge::uint1024_t>::value     == true, "");
	static_assert(bksge::is_constructible<bksge::int128_t, bksge::bigint>::value       == true, "");
	static_assert(bksge::is_constructible<bksge::int128_t, bksge::int128_t>::value     == true, "");
	static_assert(bksge::is_constructible<bksge::int128_t, bksge::int256_t>::value     == true, "");
	static_assert(bksge::is_constructible<bksge::int128_t, bksge::int512_t>::value     == true, "");
	static_assert(bksge::is_constructible<bksge::int128_t, bksge::int1024_t>::value    == true, "");
	static_assert(bksge::is_constructible<bksge::int128_t, bksge::uint128_t>::value    == true, "");
	static_assert(bksge::is_constructible<bksge::int128_t, bksge::uint256_t>::value    == true, "");
	static_assert(bksge::is_constructible<bksge::int128_t, bksge::uint512_t>::value    == true, "");
	static_assert(bksge::is_constructible<bksge::int128_t, bksge::uint1024_t>::value   == true, "");
	static_assert(bksge::is_constructible<bksge::int256_t, bksge::bigint>::value       == true, "");
	static_assert(bksge::is_constructible<bksge::int256_t, bksge::int128_t>::value     == true, "");
	static_assert(bksge::is_constructible<bksge::int256_t, bksge::int256_t>::value     == true, "");
	static_assert(bksge::is_constructible<bksge::int256_t, bksge::int512_t>::value     == true, "");
	static_assert(bksge::is_constructible<bksge::int256_t, bksge::int1024_t>::value    == true, "");
	static_assert(bksge::is_constructible<bksge::int256_t, bksge::uint128_t>::value    == true, "");
	static_assert(bksge::is_constructible<bksge::int256_t, bksge::uint256_t>::value    == true, "");
	static_assert(bksge::is_constructible<bksge::int256_t, bksge::uint512_t>::value    == true, "");
	static_assert(bksge::is_constructible<bksge::int256_t, bksge::uint1024_t>::value   == true, "");
	static_assert(bksge::is_constructible<bksge::int512_t, bksge::bigint>::value       == true, "");
	static_assert(bksge::is_constructible<bksge::int512_t, bksge::int128_t>::value     == true, "");
	static_assert(bksge::is_constructible<bksge::int512_t, bksge::int256_t>::value     == true, "");
	static_assert(bksge::is_constructible<bksge::int512_t, bksge::int512_t>::value     == true, "");
	static_assert(bksge::is_constructible<bksge::int512_t, bksge::int1024_t>::value    == true, "");
	static_assert(bksge::is_constructible<bksge::int512_t, bksge::uint128_t>::value    == true, "");
	static_assert(bksge::is_constructible<bksge::int512_t, bksge::uint256_t>::value    == true, "");
	static_assert(bksge::is_constructible<bksge::int512_t, bksge::uint512_t>::value    == true, "");
	static_assert(bksge::is_constructible<bksge::int512_t, bksge::uint1024_t>::value   == true, "");
	static_assert(bksge::is_constructible<bksge::int1024_t, bksge::bigint>::value      == true, "");
	static_assert(bksge::is_constructible<bksge::int1024_t, bksge::int128_t>::value    == true, "");
	static_assert(bksge::is_constructible<bksge::int1024_t, bksge::int256_t>::value    == true, "");
	static_assert(bksge::is_constructible<bksge::int1024_t, bksge::int512_t>::value    == true, "");
	static_assert(bksge::is_constructible<bksge::int1024_t, bksge::int1024_t>::value   == true, "");
	static_assert(bksge::is_constructible<bksge::int1024_t, bksge::uint128_t>::value   == true, "");
	static_assert(bksge::is_constructible<bksge::int1024_t, bksge::uint256_t>::value   == true, "");
	static_assert(bksge::is_constructible<bksge::int1024_t, bksge::uint512_t>::value   == true, "");
	static_assert(bksge::is_constructible<bksge::int1024_t, bksge::uint1024_t>::value  == true, "");
	static_assert(bksge::is_constructible<bksge::uint128_t, bksge::bigint>::value      == true, "");
	static_assert(bksge::is_constructible<bksge::uint128_t, bksge::int128_t>::value    == true, "");
	static_assert(bksge::is_constructible<bksge::uint128_t, bksge::int256_t>::value    == true, "");
	static_assert(bksge::is_constructible<bksge::uint128_t, bksge::int512_t>::value    == true, "");
	static_assert(bksge::is_constructible<bksge::uint128_t, bksge::int1024_t>::value   == true, "");
	static_assert(bksge::is_constructible<bksge::uint128_t, bksge::uint128_t>::value   == true, "");
	static_assert(bksge::is_constructible<bksge::uint128_t, bksge::uint256_t>::value   == true, "");
	static_assert(bksge::is_constructible<bksge::uint128_t, bksge::uint512_t>::value   == true, "");
	static_assert(bksge::is_constructible<bksge::uint128_t, bksge::uint1024_t>::value  == true, "");
	static_assert(bksge::is_constructible<bksge::uint256_t, bksge::bigint>::value      == true, "");
	static_assert(bksge::is_constructible<bksge::uint256_t, bksge::int128_t>::value    == true, "");
	static_assert(bksge::is_constructible<bksge::uint256_t, bksge::int256_t>::value    == true, "");
	static_assert(bksge::is_constructible<bksge::uint256_t, bksge::int512_t>::value    == true, "");
	static_assert(bksge::is_constructible<bksge::uint256_t, bksge::int1024_t>::value   == true, "");
	static_assert(bksge::is_constructible<bksge::uint256_t, bksge::uint128_t>::value   == true, "");
	static_assert(bksge::is_constructible<bksge::uint256_t, bksge::uint256_t>::value   == true, "");
	static_assert(bksge::is_constructible<bksge::uint256_t, bksge::uint512_t>::value   == true, "");
	static_assert(bksge::is_constructible<bksge::uint256_t, bksge::uint1024_t>::value  == true, "");
	static_assert(bksge::is_constructible<bksge::uint512_t, bksge::bigint>::value      == true, "");
	static_assert(bksge::is_constructible<bksge::uint512_t, bksge::int128_t>::value    == true, "");
	static_assert(bksge::is_constructible<bksge::uint512_t, bksge::int256_t>::value    == true, "");
	static_assert(bksge::is_constructible<bksge::uint512_t, bksge::int512_t>::value    == true, "");
	static_assert(bksge::is_constructible<bksge::uint512_t, bksge::int1024_t>::value   == true, "");
	static_assert(bksge::is_constructible<bksge::uint512_t, bksge::uint128_t>::value   == true, "");
	static_assert(bksge::is_constructible<bksge::uint512_t, bksge::uint256_t>::value   == true, "");
	static_assert(bksge::is_constructible<bksge::uint512_t, bksge::uint512_t>::value   == true, "");
	static_assert(bksge::is_constructible<bksge::uint512_t, bksge::uint1024_t>::value  == true, "");
	static_assert(bksge::is_constructible<bksge::uint1024_t, bksge::bigint>::value     == true, "");
	static_assert(bksge::is_constructible<bksge::uint1024_t, bksge::int128_t>::value   == true, "");
	static_assert(bksge::is_constructible<bksge::uint1024_t, bksge::int256_t>::value   == true, "");
	static_assert(bksge::is_constructible<bksge::uint1024_t, bksge::int512_t>::value   == true, "");
	static_assert(bksge::is_constructible<bksge::uint1024_t, bksge::int1024_t>::value  == true, "");
	static_assert(bksge::is_constructible<bksge::uint1024_t, bksge::uint128_t>::value  == true, "");
	static_assert(bksge::is_constructible<bksge::uint1024_t, bksge::uint256_t>::value  == true, "");
	static_assert(bksge::is_constructible<bksge::uint1024_t, bksge::uint512_t>::value  == true, "");
	static_assert(bksge::is_constructible<bksge::uint1024_t, bksge::uint1024_t>::value == true, "");

	static_assert(bksge::is_nothrow_constructible<bksge::bigint, bksge::bigint>::value         == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::bigint, bksge::int128_t>::value       == false, "");
	static_assert(bksge::is_nothrow_constructible<bksge::bigint, bksge::int256_t>::value       == false, "");
	static_assert(bksge::is_nothrow_constructible<bksge::bigint, bksge::int512_t>::value       == false, "");
	static_assert(bksge::is_nothrow_constructible<bksge::bigint, bksge::int1024_t>::value      == false, "");
	static_assert(bksge::is_nothrow_constructible<bksge::bigint, bksge::uint128_t>::value      == false, "");
	static_assert(bksge::is_nothrow_constructible<bksge::bigint, bksge::uint256_t>::value      == false, "");
	static_assert(bksge::is_nothrow_constructible<bksge::bigint, bksge::uint512_t>::value      == false, "");
	static_assert(bksge::is_nothrow_constructible<bksge::bigint, bksge::uint1024_t>::value     == false, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int128_t, bksge::bigint>::value       == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int128_t, bksge::int128_t>::value     == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int128_t, bksge::int256_t>::value     == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int128_t, bksge::int512_t>::value     == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int128_t, bksge::int1024_t>::value    == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int128_t, bksge::uint128_t>::value    == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int128_t, bksge::uint256_t>::value    == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int128_t, bksge::uint512_t>::value    == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int128_t, bksge::uint1024_t>::value   == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int256_t, bksge::bigint>::value       == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int256_t, bksge::int128_t>::value     == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int256_t, bksge::int256_t>::value     == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int256_t, bksge::int512_t>::value     == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int256_t, bksge::int1024_t>::value    == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int256_t, bksge::uint128_t>::value    == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int256_t, bksge::uint256_t>::value    == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int256_t, bksge::uint512_t>::value    == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int256_t, bksge::uint1024_t>::value   == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int512_t, bksge::bigint>::value       == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int512_t, bksge::int128_t>::value     == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int512_t, bksge::int256_t>::value     == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int512_t, bksge::int512_t>::value     == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int512_t, bksge::int1024_t>::value    == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int512_t, bksge::uint128_t>::value    == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int512_t, bksge::uint256_t>::value    == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int512_t, bksge::uint512_t>::value    == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int512_t, bksge::uint1024_t>::value   == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int1024_t, bksge::bigint>::value      == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int1024_t, bksge::int128_t>::value    == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int1024_t, bksge::int256_t>::value    == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int1024_t, bksge::int512_t>::value    == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int1024_t, bksge::int1024_t>::value   == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int1024_t, bksge::uint128_t>::value   == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int1024_t, bksge::uint256_t>::value   == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int1024_t, bksge::uint512_t>::value   == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::int1024_t, bksge::uint1024_t>::value  == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint128_t, bksge::bigint>::value      == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint128_t, bksge::int128_t>::value    == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint128_t, bksge::int256_t>::value    == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint128_t, bksge::int512_t>::value    == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint128_t, bksge::int1024_t>::value   == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint128_t, bksge::uint128_t>::value   == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint128_t, bksge::uint256_t>::value   == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint128_t, bksge::uint512_t>::value   == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint128_t, bksge::uint1024_t>::value  == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint256_t, bksge::bigint>::value      == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint256_t, bksge::int128_t>::value    == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint256_t, bksge::int256_t>::value    == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint256_t, bksge::int512_t>::value    == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint256_t, bksge::int1024_t>::value   == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint256_t, bksge::uint128_t>::value   == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint256_t, bksge::uint256_t>::value   == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint256_t, bksge::uint512_t>::value   == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint256_t, bksge::uint1024_t>::value  == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint512_t, bksge::bigint>::value      == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint512_t, bksge::int128_t>::value    == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint512_t, bksge::int256_t>::value    == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint512_t, bksge::int512_t>::value    == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint512_t, bksge::int1024_t>::value   == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint512_t, bksge::uint128_t>::value   == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint512_t, bksge::uint256_t>::value   == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint512_t, bksge::uint512_t>::value   == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint512_t, bksge::uint1024_t>::value  == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint1024_t, bksge::bigint>::value     == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint1024_t, bksge::int128_t>::value   == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint1024_t, bksge::int256_t>::value   == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint1024_t, bksge::int512_t>::value   == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint1024_t, bksge::int1024_t>::value  == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint1024_t, bksge::uint128_t>::value  == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint1024_t, bksge::uint256_t>::value  == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint1024_t, bksge::uint512_t>::value  == true, "");
	static_assert(bksge::is_nothrow_constructible<bksge::uint1024_t, bksge::uint1024_t>::value == true, "");

	static_assert(bksge::is_implicitly_constructible<bksge::bigint, bksge::bigint>::value         == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::bigint, bksge::int128_t>::value       == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::bigint, bksge::int256_t>::value       == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::bigint, bksge::int512_t>::value       == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::bigint, bksge::int1024_t>::value      == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::bigint, bksge::uint128_t>::value      == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::bigint, bksge::uint256_t>::value      == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::bigint, bksge::uint512_t>::value      == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::bigint, bksge::uint1024_t>::value     == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int128_t, bksge::bigint>::value       == false, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int128_t, bksge::int128_t>::value     == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int128_t, bksge::int256_t>::value     == false, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int128_t, bksge::int512_t>::value     == false, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int128_t, bksge::int1024_t>::value    == false, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int128_t, bksge::uint128_t>::value    == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int128_t, bksge::uint256_t>::value    == false, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int128_t, bksge::uint512_t>::value    == false, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int128_t, bksge::uint1024_t>::value   == false, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int256_t, bksge::bigint>::value       == false, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int256_t, bksge::int128_t>::value     == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int256_t, bksge::int256_t>::value     == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int256_t, bksge::int512_t>::value     == false, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int256_t, bksge::int1024_t>::value    == false, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int256_t, bksge::uint128_t>::value    == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int256_t, bksge::uint256_t>::value    == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int256_t, bksge::uint512_t>::value    == false, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int256_t, bksge::uint1024_t>::value   == false, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int512_t, bksge::bigint>::value       == false, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int512_t, bksge::int128_t>::value     == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int512_t, bksge::int256_t>::value     == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int512_t, bksge::int512_t>::value     == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int512_t, bksge::int1024_t>::value    == false, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int512_t, bksge::uint128_t>::value    == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int512_t, bksge::uint256_t>::value    == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int512_t, bksge::uint512_t>::value    == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int512_t, bksge::uint1024_t>::value   == false, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int1024_t, bksge::bigint>::value      == false, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int1024_t, bksge::int128_t>::value    == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int1024_t, bksge::int256_t>::value    == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int1024_t, bksge::int512_t>::value    == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int1024_t, bksge::int1024_t>::value   == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int1024_t, bksge::uint128_t>::value   == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int1024_t, bksge::uint256_t>::value   == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int1024_t, bksge::uint512_t>::value   == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::int1024_t, bksge::uint1024_t>::value  == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint128_t, bksge::bigint>::value      == false, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint128_t, bksge::int128_t>::value    == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint128_t, bksge::int256_t>::value    == false, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint128_t, bksge::int512_t>::value    == false, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint128_t, bksge::int1024_t>::value   == false, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint128_t, bksge::uint128_t>::value   == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint128_t, bksge::uint256_t>::value   == false, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint128_t, bksge::uint512_t>::value   == false, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint128_t, bksge::uint1024_t>::value  == false, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint256_t, bksge::bigint>::value      == false, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint256_t, bksge::int128_t>::value    == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint256_t, bksge::int256_t>::value    == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint256_t, bksge::int512_t>::value    == false, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint256_t, bksge::int1024_t>::value   == false, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint256_t, bksge::uint128_t>::value   == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint256_t, bksge::uint256_t>::value   == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint256_t, bksge::uint512_t>::value   == false, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint256_t, bksge::uint1024_t>::value  == false, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint512_t, bksge::bigint>::value      == false, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint512_t, bksge::int128_t>::value    == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint512_t, bksge::int256_t>::value    == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint512_t, bksge::int512_t>::value    == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint512_t, bksge::int1024_t>::value   == false, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint512_t, bksge::uint128_t>::value   == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint512_t, bksge::uint256_t>::value   == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint512_t, bksge::uint512_t>::value   == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint512_t, bksge::uint1024_t>::value  == false, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint1024_t, bksge::bigint>::value     == false, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint1024_t, bksge::int128_t>::value   == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint1024_t, bksge::int256_t>::value   == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint1024_t, bksge::int512_t>::value   == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint1024_t, bksge::int1024_t>::value  == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint1024_t, bksge::uint128_t>::value  == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint1024_t, bksge::uint256_t>::value  == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint1024_t, bksge::uint512_t>::value  == true, "");
	static_assert(bksge::is_implicitly_constructible<bksge::uint1024_t, bksge::uint1024_t>::value == true, "");

	EXPECT_TRUE((CtorConvTest<std::int32_t,    bksge::bigint>()));
	EXPECT_TRUE((CtorConvTest<std::int64_t,    bksge::bigint>()));
	EXPECT_TRUE((CtorConvTest<bksge::int128_t,   bksge::bigint>()));
	EXPECT_TRUE((CtorConvTest<bksge::int256_t,   bksge::bigint>()));
	EXPECT_TRUE((CtorConvTest<bksge::int512_t,   bksge::bigint>()));
	EXPECT_TRUE((CtorConvTest<bksge::int1024_t,  bksge::bigint>()));
	EXPECT_TRUE((CtorConvTest<std::uint32_t,   bksge::bigint>()));
	EXPECT_TRUE((CtorConvTest<std::uint64_t,   bksge::bigint>()));
	EXPECT_TRUE((CtorConvTest<bksge::uint128_t,  bksge::bigint>()));
	EXPECT_TRUE((CtorConvTest<bksge::uint256_t,  bksge::bigint>()));
	EXPECT_TRUE((CtorConvTest<bksge::uint512_t,  bksge::bigint>()));
	EXPECT_TRUE((CtorConvTest<bksge::uint1024_t, bksge::bigint>()));
//	EXPECT_TRUE((CtorConvTest<bksge::bigint,     std::int32_t>()));
//	EXPECT_TRUE((CtorConvTest<bksge::bigint,     std::int64_t>()));
	EXPECT_TRUE((CtorConvTest<bksge::bigint,     bksge::int128_t>()));
	EXPECT_TRUE((CtorConvTest<bksge::bigint,     bksge::int256_t>()));
	EXPECT_TRUE((CtorConvTest<bksge::bigint,     bksge::int512_t>()));
	EXPECT_TRUE((CtorConvTest<bksge::bigint,     bksge::int1024_t>()));
//	EXPECT_TRUE((CtorConvTest<bksge::bigint,     std::uint32_t>()));
//	EXPECT_TRUE((CtorConvTest<bksge::bigint,     std::uint64_t>()));
	EXPECT_TRUE((CtorConvTest<bksge::bigint,     bksge::uint128_t>()));
	EXPECT_TRUE((CtorConvTest<bksge::bigint,     bksge::uint256_t>()));
	EXPECT_TRUE((CtorConvTest<bksge::bigint,     bksge::uint512_t>()));
	EXPECT_TRUE((CtorConvTest<bksge::bigint,     bksge::uint1024_t>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::int32_t, std::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::int32_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::int32_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::int32_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::int32_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::int32_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::int32_t, std::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::int32_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::int32_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::int32_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::int32_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::int32_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::int64_t, std::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::int64_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::int64_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::int64_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::int64_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::int64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::int64_t, std::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::int64_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::int64_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::int64_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::int64_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::int64_t, bksge::uint1024_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int128_t, std::int32_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int128_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int128_t, bksge::int1024_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int128_t, std::uint32_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int128_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int128_t, bksge::uint1024_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int256_t, std::int32_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int256_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int256_t, bksge::int1024_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int256_t, std::uint32_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int256_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int256_t, bksge::uint1024_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int512_t, std::int32_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int512_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int512_t, bksge::int1024_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int512_t, std::uint32_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int512_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int512_t, bksge::uint1024_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int1024_t, std::int32_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int1024_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int1024_t, bksge::int1024_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int1024_t, std::uint32_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int1024_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::int1024_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::uint32_t, std::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::uint32_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::uint32_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::uint32_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::uint32_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::uint32_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::uint32_t, std::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::uint32_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::uint32_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::uint32_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::uint32_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::uint32_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::uint64_t, std::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::uint64_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::uint64_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::uint64_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::uint64_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::uint64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::uint64_t, std::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::uint64_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::uint64_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::uint64_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::uint64_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<std::uint64_t, bksge::uint1024_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint128_t, std::int32_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint128_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint128_t, bksge::int1024_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint128_t, std::uint32_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint128_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint128_t, bksge::uint1024_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint256_t, std::int32_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint256_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint256_t, bksge::int1024_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint256_t, std::uint32_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint256_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint256_t, bksge::uint1024_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint512_t, std::int32_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint512_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint512_t, bksge::int1024_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint512_t, std::uint32_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint512_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint512_t, bksge::uint1024_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint1024_t, std::int32_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint1024_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint1024_t, bksge::int1024_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint1024_t, std::uint32_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint1024_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorConvTest<bksge::uint1024_t, bksge::uint1024_t>()));

	EXPECT_TRUE(CtorStringTest<bksge::bigint>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorStringTest<bksge::int128_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorStringTest<bksge::int256_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorStringTest<bksge::int512_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorStringTest<bksge::int1024_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorStringTest<bksge::uint128_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorStringTest<bksge::uint256_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorStringTest<bksge::uint512_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorStringTest<bksge::uint1024_t>());

	{
		EXPECT_THROW(bksge::bigint x{"ab"}, bksge::runtime_error);
		EXPECT_THROW(bksge::bigint x{"0b2"}, bksge::runtime_error);
		EXPECT_THROW(bksge::bigint x{"0787"}, bksge::runtime_error);
		EXPECT_THROW(bksge::bigint x{"0xEFG"}, bksge::runtime_error);
		EXPECT_THROW(bksge::int128_t x{"ab"}, bksge::runtime_error);
		EXPECT_THROW(bksge::int128_t x{"0b2"}, bksge::runtime_error);
		EXPECT_THROW(bksge::int128_t x{"0787"}, bksge::runtime_error);
		EXPECT_THROW(bksge::int128_t x{"0xEFG"}, bksge::runtime_error);
		EXPECT_THROW(bksge::int256_t x{"ab"}, bksge::runtime_error);
		EXPECT_THROW(bksge::int256_t x{"0b2"}, bksge::runtime_error);
		EXPECT_THROW(bksge::int256_t x{"0787"}, bksge::runtime_error);
		EXPECT_THROW(bksge::int256_t x{"0xEFG"}, bksge::runtime_error);
		EXPECT_THROW(bksge::int512_t x{"ab"}, bksge::runtime_error);
		EXPECT_THROW(bksge::int512_t x{"0b2"}, bksge::runtime_error);
		EXPECT_THROW(bksge::int512_t x{"0787"}, bksge::runtime_error);
		EXPECT_THROW(bksge::int512_t x{"0xEFG"}, bksge::runtime_error);
		EXPECT_THROW(bksge::int1024_t x{"ab"}, bksge::runtime_error);
		EXPECT_THROW(bksge::int1024_t x{"0b2"}, bksge::runtime_error);
		EXPECT_THROW(bksge::int1024_t x{"0787"}, bksge::runtime_error);
		EXPECT_THROW(bksge::int1024_t x{"0xEFG"}, bksge::runtime_error);
		EXPECT_THROW(bksge::uint128_t x{"ab"}, bksge::runtime_error);
		EXPECT_THROW(bksge::uint128_t x{"0b2"}, bksge::runtime_error);
		EXPECT_THROW(bksge::uint128_t x{"0787"}, bksge::runtime_error);
		EXPECT_THROW(bksge::uint128_t x{"0xEFG"}, bksge::runtime_error);
		EXPECT_THROW(bksge::uint256_t x{"ab"}, bksge::runtime_error);
		EXPECT_THROW(bksge::uint256_t x{"0b2"}, bksge::runtime_error);
		EXPECT_THROW(bksge::uint256_t x{"0787"}, bksge::runtime_error);
		EXPECT_THROW(bksge::uint256_t x{"0xEFG"}, bksge::runtime_error);
		EXPECT_THROW(bksge::uint512_t x{"ab"}, bksge::runtime_error);
		EXPECT_THROW(bksge::uint512_t x{"0b2"}, bksge::runtime_error);
		EXPECT_THROW(bksge::uint512_t x{"0787"}, bksge::runtime_error);
		EXPECT_THROW(bksge::uint512_t x{"0xEFG"}, bksge::runtime_error);
		EXPECT_THROW(bksge::uint1024_t x{"ab"}, bksge::runtime_error);
		EXPECT_THROW(bksge::uint1024_t x{"0b2"}, bksge::runtime_error);
		EXPECT_THROW(bksge::uint1024_t x{"0787"}, bksge::runtime_error);
		EXPECT_THROW(bksge::uint1024_t x{"0xEFG"}, bksge::runtime_error);
	}

	EXPECT_TRUE(CtorCopyTest<bksge::bigint>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorCopyTest<bksge::int128_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorCopyTest<bksge::int256_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorCopyTest<bksge::int512_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorCopyTest<bksge::int1024_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorCopyTest<bksge::uint128_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorCopyTest<bksge::uint256_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorCopyTest<bksge::uint512_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorCopyTest<bksge::uint1024_t>());

	EXPECT_TRUE(CtorMoveTest<bksge::bigint>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorMoveTest<bksge::int128_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorMoveTest<bksge::int256_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorMoveTest<bksge::int512_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorMoveTest<bksge::int1024_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorMoveTest<bksge::uint128_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorMoveTest<bksge::uint256_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorMoveTest<bksge::uint512_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorMoveTest<bksge::uint1024_t>());
}

#undef VERIFY

}	// namespace bksge_bigint_test

BKSGE_WARNING_POP();
