﻿/**
 *	@file	unit_test_fnd_iterator_concepts_sentinel_for.cpp
 *
 *	@brief	sentinel_for のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/config.hpp>
#include <iterator>
#include <memory>
#include <vector>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_SENTINEL_FOR_TEST(B, ...)	\
	static_assert(B == bksge::sentinel_for<__VA_ARGS__>, "")
#else
#  define BKSGE_SENTINEL_FOR_TEST(B, ...)	\
	static_assert(B == bksge::sentinel_for<__VA_ARGS__>::value, "")
#endif

namespace bksge_iterator_test
{

namespace sentinel_for_test
{

BKSGE_SENTINEL_FOR_TEST(true,  int*,                             int      *);
BKSGE_SENTINEL_FOR_TEST(true,  int const*,                       int      *);
BKSGE_SENTINEL_FOR_TEST(true,  int*,                             int const*);
BKSGE_SENTINEL_FOR_TEST(true,  int const*,                       int const*);
BKSGE_SENTINEL_FOR_TEST(false, int*,                             int      * const);
BKSGE_SENTINEL_FOR_TEST(false, int*,                             int const* const);
BKSGE_SENTINEL_FOR_TEST(false, int*,                             void*);
BKSGE_SENTINEL_FOR_TEST(false, int*,                             std::unique_ptr<int>);
BKSGE_SENTINEL_FOR_TEST(false, int*,                             std::shared_ptr<int>);
BKSGE_SENTINEL_FOR_TEST(false, int*,                             std::vector<int>::iterator);
BKSGE_SENTINEL_FOR_TEST(true,  std::vector<int>::iterator,       std::vector<int>::iterator);
BKSGE_SENTINEL_FOR_TEST(false, int*,                             std::vector<int>::const_iterator);
BKSGE_SENTINEL_FOR_TEST(true,  std::vector<int>::const_iterator, std::vector<int>::const_iterator);
BKSGE_SENTINEL_FOR_TEST(false, int*,                             std::istream_iterator<int>);
BKSGE_SENTINEL_FOR_TEST(true,  std::istream_iterator<int>,       std::istream_iterator<int>);
BKSGE_SENTINEL_FOR_TEST(false, int*,                             std::ostream_iterator<int>);
BKSGE_SENTINEL_FOR_TEST(false, std::ostream_iterator<int>,       std::ostream_iterator<int>);

BKSGE_SENTINEL_FOR_TEST(false, int const, int*);
BKSGE_SENTINEL_FOR_TEST(false, float*,    int*);
BKSGE_SENTINEL_FOR_TEST(false, bool*,     int*);
BKSGE_SENTINEL_FOR_TEST(true,  void*,     int*);

BKSGE_SENTINEL_FOR_TEST(false, int*, int[]);
BKSGE_SENTINEL_FOR_TEST(false, int*, int[2]);
BKSGE_SENTINEL_FOR_TEST(false, int*, int&);
BKSGE_SENTINEL_FOR_TEST(false, int*, int const&);
BKSGE_SENTINEL_FOR_TEST(false, int*, int&&);
BKSGE_SENTINEL_FOR_TEST(false, int*, int const&&);

BKSGE_SENTINEL_FOR_TEST(false, int[],       int*);
BKSGE_SENTINEL_FOR_TEST(false, int[2],      int*);
BKSGE_SENTINEL_FOR_TEST(false, int&,        int*);
BKSGE_SENTINEL_FOR_TEST(false, int const&,  int*);
BKSGE_SENTINEL_FOR_TEST(false, int&&,       int*);
BKSGE_SENTINEL_FOR_TEST(false, int const&&, int*);

struct Sentinel {};

struct X
{
	friend auto operator++(X&) -> X&;
	friend auto operator++(X&, int) -> X;
	friend auto operator*(X&) -> int;
	friend bool operator==(const X&, Sentinel);
	friend bool operator!=(const X&, Sentinel);
	friend bool operator==(Sentinel, const X&);
	friend bool operator!=(Sentinel, const X&);
	using difference_type = int;
};
struct Y
{
	friend auto operator++(Y&) -> Y&;
	friend auto operator++(Y&, int) -> Y;
	friend auto operator*(Y&) -> int;
//	friend bool operator==(const Y&, Sentinel);
	using difference_type = int;
};

BKSGE_SENTINEL_FOR_TEST(true,  Sentinel, X);
BKSGE_SENTINEL_FOR_TEST(false, X,        X);
BKSGE_SENTINEL_FOR_TEST(false, int,      X);
BKSGE_SENTINEL_FOR_TEST(false, Sentinel, Y);
BKSGE_SENTINEL_FOR_TEST(false, Y,        Y);
BKSGE_SENTINEL_FOR_TEST(false, int,      Y);

}	// namespace sentinel_for_test

}	// namespace bksge_iterator_test

#undef BKSGE_SENTINEL_FOR_TEST
