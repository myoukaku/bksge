/**
 *	@file	unit_test_fnd_compare_three_way_comparable_with.cpp
 *
 *	@brief	three_way_comparable_with のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/compare/concepts/three_way_comparable_with.hpp>
#include <bksge/fnd/type_traits/basic_common_reference.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

#if defined(BKSGE_HAS_STD_COMPARE) && defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)

namespace bksge_compare_test
{

namespace three_way_comparable_with_test
{

#if !defined(_MSC_VER)
static_assert(bksge::three_way_comparable_with<int, int>, "");
static_assert(bksge::three_way_comparable_with<int, char>, "");
static_assert(bksge::three_way_comparable_with<int, float>, "");
static_assert(bksge::three_way_comparable_with<char, int>, "");
static_assert(bksge::three_way_comparable_with<char, char>, "");
static_assert(bksge::three_way_comparable_with<char, float>, "");
static_assert(bksge::three_way_comparable_with<float, int>, "");
static_assert(bksge::three_way_comparable_with<float, char>, "");
static_assert(bksge::three_way_comparable_with<float, float>, "");
#endif

struct B
{
	friend auto operator<=>(const B&, const B&) = default;
};

struct S1 : B
{
	std::size_t s;

	friend auto operator<=>(const S1&, const S1&) = default;
};

struct S2 : B
{
	std::size_t s;

	friend auto operator<=>(const S2&, const S2&) = default;
	friend bool operator== (const S2&, const S2&) = default;

	friend auto operator<=>(const S1& a, const S2& b) { return a.s <=> b.s; }
	friend bool operator== (const S1& a, const S2& b) { return a.s ==  b.s; }
};

}	// namespace three_way_comparable_with_test

}	// namespace bksge_compare_test

namespace BKSGE_BASIC_COMMON_REFERENCE_NAMESPACE
{

template <template <typename> class Qual1, template <typename> class Qual2>
struct basic_common_reference<
	bksge_compare_test::three_way_comparable_with_test::S1,
	bksge_compare_test::three_way_comparable_with_test::S2,
	Qual1, Qual2>
{
	using type = const bksge_compare_test::three_way_comparable_with_test::B&;
};

template <template <typename> class Qual1, template <typename> class Qual2>
struct basic_common_reference<
	bksge_compare_test::three_way_comparable_with_test::S2,
	bksge_compare_test::three_way_comparable_with_test::S1,
	Qual1, Qual2>
{
	using type = const bksge_compare_test::three_way_comparable_with_test::B&;
};

}	// namespace BKSGE_BASIC_COMMON_REFERENCE_NAMESPACE

namespace bksge_compare_test
{

namespace three_way_comparable_with_test
{

static_assert( bksge::three_way_comparable_with<S1, S1>, "");
//static_assert( bksge::three_way_comparable_with<S1, S2>, "");	// TODO:	MSVCでエラー
static_assert( bksge::three_way_comparable_with<S1, B>, "");
//static_assert( bksge::three_way_comparable_with<S2, S1>, "");	// TODO:	MSVCでエラー
static_assert( bksge::three_way_comparable_with<S2, S2>, "");
static_assert( bksge::three_way_comparable_with<S2, B>, "");
static_assert( bksge::three_way_comparable_with<B, S1>, "");
static_assert( bksge::three_way_comparable_with<B, S2>, "");
static_assert( bksge::three_way_comparable_with<B, B>, "");
static_assert(!bksge::three_way_comparable_with<S1, int>, "");
static_assert(!bksge::three_way_comparable_with<S2, int>, "");
static_assert(!bksge::three_way_comparable_with<int, S1>, "");
static_assert(!bksge::three_way_comparable_with<int, S2>, "");

}	// namespace three_way_comparable_with_test

}	// namespace bksge_compare_test

#endif
