/**
 *	@file	unit_test_fnd_iterator_concepts_sized_sentinel_for.cpp
 *
 *	@brief	sized_sentinel_for のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/concepts/sized_sentinel_for.hpp>
#include <bksge/fnd/config.hpp>
#include <iterator>
#include <memory>
#include <vector>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_SIZED_SENTINEL_FOR_TEST(B, ...)	\
	static_assert(B == bksge::sized_sentinel_for<__VA_ARGS__>, "")
#else
#  define BKSGE_SIZED_SENTINEL_FOR_TEST(B, ...)	\
	static_assert(B == bksge::sized_sentinel_for<__VA_ARGS__>::value, "")
#endif

namespace bksge_iterator_test
{

namespace sized_sentinel_for_test
{

BKSGE_SIZED_SENTINEL_FOR_TEST(true,  int*,                             int      *);
BKSGE_SIZED_SENTINEL_FOR_TEST(true,  int const*,                       int      *);
BKSGE_SIZED_SENTINEL_FOR_TEST(true,  int*,                             int const*);
BKSGE_SIZED_SENTINEL_FOR_TEST(true,  int const*,                       int const*);
BKSGE_SIZED_SENTINEL_FOR_TEST(false, int*,                             int      * const);
BKSGE_SIZED_SENTINEL_FOR_TEST(false, int*,                             int const* const);
BKSGE_SIZED_SENTINEL_FOR_TEST(false, int*,                             void*);
BKSGE_SIZED_SENTINEL_FOR_TEST(false, int*,                             std::unique_ptr<int>);
BKSGE_SIZED_SENTINEL_FOR_TEST(false, int*,                             std::shared_ptr<int>);
BKSGE_SIZED_SENTINEL_FOR_TEST(false, int*,                             std::vector<int>::iterator);
BKSGE_SIZED_SENTINEL_FOR_TEST(true,  std::vector<int>::iterator,       std::vector<int>::iterator);
BKSGE_SIZED_SENTINEL_FOR_TEST(false, int*,                             std::vector<int>::const_iterator);
BKSGE_SIZED_SENTINEL_FOR_TEST(true,  std::vector<int>::const_iterator, std::vector<int>::const_iterator);
BKSGE_SIZED_SENTINEL_FOR_TEST(false, int*,                             std::istream_iterator<int>);
BKSGE_SIZED_SENTINEL_FOR_TEST(false, std::istream_iterator<int>,       std::istream_iterator<int>);
BKSGE_SIZED_SENTINEL_FOR_TEST(false, int*,                             std::ostream_iterator<int>);
BKSGE_SIZED_SENTINEL_FOR_TEST(false, std::ostream_iterator<int>,       std::ostream_iterator<int>);

BKSGE_SIZED_SENTINEL_FOR_TEST(false, int const, int*);
BKSGE_SIZED_SENTINEL_FOR_TEST(false, float*,    int*);
BKSGE_SIZED_SENTINEL_FOR_TEST(false, bool*,     int*);
BKSGE_SIZED_SENTINEL_FOR_TEST(false, void*,     int*);

BKSGE_SIZED_SENTINEL_FOR_TEST(false, int*, int[]);
BKSGE_SIZED_SENTINEL_FOR_TEST(false, int*, int[2]);
BKSGE_SIZED_SENTINEL_FOR_TEST(false, int*, int&);
BKSGE_SIZED_SENTINEL_FOR_TEST(false, int*, int const&);
BKSGE_SIZED_SENTINEL_FOR_TEST(false, int*, int&&);
BKSGE_SIZED_SENTINEL_FOR_TEST(false, int*, int const&&);

BKSGE_SIZED_SENTINEL_FOR_TEST(false, int[],       int*);
BKSGE_SIZED_SENTINEL_FOR_TEST(false, int[2],      int*);
BKSGE_SIZED_SENTINEL_FOR_TEST(false, int&,        int*);
BKSGE_SIZED_SENTINEL_FOR_TEST(false, int const&,  int*);
BKSGE_SIZED_SENTINEL_FOR_TEST(false, int&&,       int*);
BKSGE_SIZED_SENTINEL_FOR_TEST(false, int const&&, int*);

struct Sentinel {};

struct X
{
	friend auto operator++(X&)->X&;
	friend auto operator++(X&, int)->X;
	friend auto operator*(X&) -> int;
	friend bool operator==(const X&, Sentinel);
	friend bool operator!=(const X&, Sentinel);
	friend bool operator==(Sentinel, const X&);
	friend bool operator!=(Sentinel, const X&);
	friend auto operator-(const X&, Sentinel) -> int;
	friend auto operator-(Sentinel, const X&) -> int;
	using difference_type = int;
};
struct Y
{
	friend auto operator++(Y&)->Y&;
	friend auto operator++(Y&, int)->Y;
	friend auto operator*(Y&) -> int;
	friend bool operator==(const Y&, Sentinel);
	friend bool operator!=(const Y&, Sentinel);
	friend bool operator==(Sentinel, const Y&);
	friend bool operator!=(Sentinel, const Y&);
//	friend auto operator-(const Y&, Sentinel) -> int;
	friend auto operator-(Sentinel, const Y&) -> int;
	using difference_type = int;
};
struct Z
{
	friend auto operator++(Z&)->Z&;
	friend auto operator++(Z&, int)->Z;
	friend auto operator*(Z&) -> int;
	friend bool operator==(const Z&, Sentinel);
	friend bool operator!=(const Z&, Sentinel);
	friend bool operator==(Sentinel, const Z&);
	friend bool operator!=(Sentinel, const Z&);
	friend auto operator-(const Z&, Sentinel) -> int;
	friend auto operator-(Sentinel, const Z&) -> int;
	using difference_type = int;
};

}	// namespace sized_sentinel_for_test

}	// namespace bksge_iterator_test

BKSGE_SPECIALIZE_DISABLE_SIZED_SENTINEL_FOR(true,
	bksge_iterator_test::sized_sentinel_for_test::Sentinel,
	bksge_iterator_test::sized_sentinel_for_test::Z);

namespace bksge_iterator_test
{

namespace sized_sentinel_for_test
{

BKSGE_SIZED_SENTINEL_FOR_TEST(true,  Sentinel, X);
BKSGE_SIZED_SENTINEL_FOR_TEST(false, X,        X);
BKSGE_SIZED_SENTINEL_FOR_TEST(false, int,      X);
BKSGE_SIZED_SENTINEL_FOR_TEST(false, Sentinel, Y);
BKSGE_SIZED_SENTINEL_FOR_TEST(false, Y,        Y);
BKSGE_SIZED_SENTINEL_FOR_TEST(false, int,      Y);
BKSGE_SIZED_SENTINEL_FOR_TEST(false, Sentinel, Z);
BKSGE_SIZED_SENTINEL_FOR_TEST(false, Z,        Z);
BKSGE_SIZED_SENTINEL_FOR_TEST(false, int,      Z);

}	// namespace sized_sentinel_for_test

}	// namespace bksge_iterator_test

#undef BKSGE_SIZED_SENTINEL_FOR_TEST
