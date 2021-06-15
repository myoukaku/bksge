/**
 *	@file	unit_test_fnd_utility_pair_tuple_element.cpp
 *
 *	@brief	tuple_element のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/utility/pair.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/tuple/tuple_element.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_pair_test
{

namespace tuple_element_test
{

static_assert(bksge::is_same<
	bksge::tuple_element_t<0, bksge::pair<int, float>>,
	int>::value, "");
static_assert(bksge::is_same<
	bksge::tuple_element_t<0, bksge::pair<int, float> const>,
	int const>::value, "");
static_assert(bksge::is_same<
	bksge::tuple_element_t<0, bksge::pair<int, float> volatile>,
	int volatile>::value, "");
static_assert(bksge::is_same<
	bksge::tuple_element_t<0, bksge::pair<int, float> const volatile>,
	int const volatile>::value, "");

static_assert(bksge::is_same<
	bksge::tuple_element_t<1, bksge::pair<int, float>>,
	float>::value, "");
static_assert(bksge::is_same<
	bksge::tuple_element_t<1, bksge::pair<int, float> const>,
	float const>::value, "");
static_assert(bksge::is_same<
	bksge::tuple_element_t<1, bksge::pair<int, float> volatile>,
	float volatile>::value, "");
static_assert(bksge::is_same<
	bksge::tuple_element_t<1, bksge::pair<int, float> const volatile>,
	float const volatile>::value, "");

static_assert(bksge::is_same<
	bksge::tuple_element_t<0, bksge::pair<long&, char*>>,
	long&>::value, "");
static_assert(bksge::is_same<
	bksge::tuple_element_t<0, bksge::pair<long&, char*> const>,
	long&>::value, "");
static_assert(bksge::is_same<
	bksge::tuple_element_t<0, bksge::pair<long&, char*> volatile>,
	long&>::value, "");
static_assert(bksge::is_same<
	bksge::tuple_element_t<0, bksge::pair<long&, char*> const volatile>,
	long&>::value, "");

static_assert(bksge::is_same<
	bksge::tuple_element_t<1, bksge::pair<long&, char*>>,
	char*>::value, "");
static_assert(bksge::is_same<
	bksge::tuple_element_t<1, bksge::pair<long&, char*> const>,
	char* const>::value, "");
static_assert(bksge::is_same<
	bksge::tuple_element_t<1, bksge::pair<long&, char*> volatile>,
	char* volatile>::value, "");
static_assert(bksge::is_same<
	bksge::tuple_element_t<1, bksge::pair<long&, char*> const volatile>,
	char* const volatile>::value, "");

static_assert(bksge::is_same<
	bksge::tuple_element_t<0, bksge::pair<int const&, int const&&>>,
	int const&>::value, "");
static_assert(bksge::is_same<
	bksge::tuple_element_t<0, bksge::pair<int const&, int const&&> const>,
	int const&>::value, "");
static_assert(bksge::is_same<
	bksge::tuple_element_t<0, bksge::pair<int const&, int const&&> volatile>,
	int const&>::value, "");
static_assert(bksge::is_same<
	bksge::tuple_element_t<0, bksge::pair<int const&, int const&&> const volatile>,
	int const&>::value, "");

static_assert(bksge::is_same<
	bksge::tuple_element_t<1, bksge::pair<int const&, int const&&>>,
	int const&&>::value, "");
static_assert(bksge::is_same<
	bksge::tuple_element_t<1, bksge::pair<int const&, int const&&> const>,
	int const&&>::value, "");
static_assert(bksge::is_same<
	bksge::tuple_element_t<1, bksge::pair<int const&, int const&&> volatile>,
	int const&&>::value, "");
static_assert(bksge::is_same<
	bksge::tuple_element_t<1, bksge::pair<int const&, int const&&> const volatile>,
	int const&&>::value, "");

}	// namespace tuple_element_test

}	// namespace bksge_pair_test
