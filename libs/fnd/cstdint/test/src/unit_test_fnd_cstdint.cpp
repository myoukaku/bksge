/**
 *	@file	unit_test_fnd_cstdint.cpp
 *
 *	@brief	cstdint のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cstdint.hpp>
#include <type_traits>

static_assert( std::is_signed<bksge::int8_t>::value, "");
static_assert( std::is_signed<bksge::int16_t>::value, "");
static_assert( std::is_signed<bksge::int32_t>::value, "");
static_assert( std::is_signed<bksge::int64_t>::value, "");
static_assert( std::is_signed<bksge::int_fast8_t>::value, "");
static_assert( std::is_signed<bksge::int_fast16_t>::value, "");
static_assert( std::is_signed<bksge::int_fast32_t>::value, "");
static_assert( std::is_signed<bksge::int_fast64_t>::value, "");
static_assert( std::is_signed<bksge::int_least8_t>::value, "");
static_assert( std::is_signed<bksge::int_least16_t>::value, "");
static_assert( std::is_signed<bksge::int_least32_t>::value, "");
static_assert( std::is_signed<bksge::int_least64_t>::value, "");
static_assert( std::is_signed<bksge::intmax_t>::value, "");
static_assert( std::is_signed<bksge::intptr_t>::value, "");
static_assert(!std::is_signed<bksge::uint8_t>::value, "");
static_assert(!std::is_signed<bksge::uint16_t>::value, "");
static_assert(!std::is_signed<bksge::uint32_t>::value, "");
static_assert(!std::is_signed<bksge::uint64_t>::value, "");
static_assert(!std::is_signed<bksge::uint_fast8_t>::value, "");
static_assert(!std::is_signed<bksge::uint_fast16_t>::value, "");
static_assert(!std::is_signed<bksge::uint_fast32_t>::value, "");
static_assert(!std::is_signed<bksge::uint_fast64_t>::value, "");
static_assert(!std::is_signed<bksge::uint_least8_t>::value, "");
static_assert(!std::is_signed<bksge::uint_least16_t>::value, "");
static_assert(!std::is_signed<bksge::uint_least32_t>::value, "");
static_assert(!std::is_signed<bksge::uint_least64_t>::value, "");
static_assert(!std::is_signed<bksge::uintmax_t>::value, "");
static_assert(!std::is_signed<bksge::uintptr_t>::value, "");

static_assert(!std::is_unsigned<bksge::int8_t>::value, "");
static_assert(!std::is_unsigned<bksge::int16_t>::value, "");
static_assert(!std::is_unsigned<bksge::int32_t>::value, "");
static_assert(!std::is_unsigned<bksge::int64_t>::value, "");
static_assert(!std::is_unsigned<bksge::int_fast8_t>::value, "");
static_assert(!std::is_unsigned<bksge::int_fast16_t>::value, "");
static_assert(!std::is_unsigned<bksge::int_fast32_t>::value, "");
static_assert(!std::is_unsigned<bksge::int_fast64_t>::value, "");
static_assert(!std::is_unsigned<bksge::int_least8_t>::value, "");
static_assert(!std::is_unsigned<bksge::int_least16_t>::value, "");
static_assert(!std::is_unsigned<bksge::int_least32_t>::value, "");
static_assert(!std::is_unsigned<bksge::int_least64_t>::value, "");
static_assert(!std::is_unsigned<bksge::intmax_t>::value, "");
static_assert(!std::is_unsigned<bksge::intptr_t>::value, "");
static_assert( std::is_unsigned<bksge::uint8_t>::value, "");
static_assert( std::is_unsigned<bksge::uint16_t>::value, "");
static_assert( std::is_unsigned<bksge::uint32_t>::value, "");
static_assert( std::is_unsigned<bksge::uint64_t>::value, "");
static_assert( std::is_unsigned<bksge::uint_fast8_t>::value, "");
static_assert( std::is_unsigned<bksge::uint_fast16_t>::value, "");
static_assert( std::is_unsigned<bksge::uint_fast32_t>::value, "");
static_assert( std::is_unsigned<bksge::uint_fast64_t>::value, "");
static_assert( std::is_unsigned<bksge::uint_least8_t>::value, "");
static_assert( std::is_unsigned<bksge::uint_least16_t>::value, "");
static_assert( std::is_unsigned<bksge::uint_least32_t>::value, "");
static_assert( std::is_unsigned<bksge::uint_least64_t>::value, "");
static_assert( std::is_unsigned<bksge::uintmax_t>::value, "");
static_assert( std::is_unsigned<bksge::uintptr_t>::value, "");

static_assert(sizeof(bksge::int8_t)         == 1, "");
static_assert(sizeof(bksge::int16_t)        == 2, "");
static_assert(sizeof(bksge::int32_t)        == 4, "");
static_assert(sizeof(bksge::int64_t)        == 8, "");
static_assert(sizeof(bksge::int_fast8_t)    >= 1, "");
static_assert(sizeof(bksge::int_fast16_t)   >= 2, "");
static_assert(sizeof(bksge::int_fast32_t)   >= 4, "");
static_assert(sizeof(bksge::int_fast64_t)   >= 8, "");
static_assert(sizeof(bksge::int_least8_t)   >= 1, "");
static_assert(sizeof(bksge::int_least16_t)  >= 2, "");
static_assert(sizeof(bksge::int_least32_t)  >= 4, "");
static_assert(sizeof(bksge::int_least64_t)  >= 8, "");
static_assert(sizeof(bksge::intmax_t)       >= 8, "");
static_assert(sizeof(bksge::intptr_t)       == sizeof(void*), "");
static_assert(sizeof(bksge::uint8_t)        == 1, "");
static_assert(sizeof(bksge::uint16_t)       == 2, "");
static_assert(sizeof(bksge::uint32_t)       == 4, "");
static_assert(sizeof(bksge::uint64_t)       == 8, "");
static_assert(sizeof(bksge::uint_fast8_t)   >= 1, "");
static_assert(sizeof(bksge::uint_fast16_t)  >= 2, "");
static_assert(sizeof(bksge::uint_fast32_t)  >= 4, "");
static_assert(sizeof(bksge::uint_fast64_t)  >= 8, "");
static_assert(sizeof(bksge::uint_least8_t)  >= 1, "");
static_assert(sizeof(bksge::uint_least16_t) >= 2, "");
static_assert(sizeof(bksge::uint_least32_t) >= 4, "");
static_assert(sizeof(bksge::uint_least64_t) >= 8, "");
static_assert(sizeof(bksge::uintmax_t)      >= 8, "");
static_assert(sizeof(bksge::uintptr_t)      == sizeof(void*), "");
