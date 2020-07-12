/**
 *	@file	unit_test_fnd_concepts_same_as.cpp
 *
 *	@brief	same_as のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/type_traits/is_const.hpp>
#include <bksge/fnd/type_traits/is_volatile.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_SAME_AS_TEST(B, T1, T2)	\
	static_assert(B == bksge::same_as<T1, T2>, " ");	\
	static_assert(B == bksge::same_as_t<T1, T2>::value, " ")
#else
#  define BKSGE_SAME_AS_TEST(B, T1, T2)	\
	static_assert(B == bksge::same_as_t<T1, T2>::value, " ")
#endif

namespace bksge_concepts_test
{

namespace same_as_test
{

BKSGE_SAME_AS_TEST(true,  int, int);
BKSGE_SAME_AS_TEST(false, int&, int);
BKSGE_SAME_AS_TEST(false, int, int&);
BKSGE_SAME_AS_TEST(false, int&&, int&);
BKSGE_SAME_AS_TEST(false, const int, int);
BKSGE_SAME_AS_TEST(true,  const int, const int);

struct A { };
BKSGE_SAME_AS_TEST(true,  A, A);
BKSGE_SAME_AS_TEST(false, A, const A);
BKSGE_SAME_AS_TEST(true,  A const, const A);
BKSGE_SAME_AS_TEST(false, volatile A, const A);

struct B : A { };
BKSGE_SAME_AS_TEST(false, A, B);

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T, typename U>
constexpr int
check_subsumption()
{
	return 0;
}

template <typename T, typename U>
requires bksge::same_as<T, U>
constexpr int
check_subsumption()
{
	return 1;
}

template <typename T, typename U>
requires bksge::same_as<U, T>&& bksge::is_const<T>::value
constexpr int
check_subsumption()
{
	return 2;
}

template <typename T, typename U>
requires bksge::same_as<U, T>&& bksge::is_volatile<T>::value
constexpr int
check_subsumption()
{
	return 3;
}

static_assert( check_subsumption<short, long>() == 0, "");
static_assert( check_subsumption<unsigned, unsigned>() == 1, "");
// These will be ambiguous if same_as<T,U> doesn't subsume same_as<U,T>:
static_assert( check_subsumption<const char, const char>() == 2, "");
static_assert( check_subsumption<volatile int, volatile int>() == 3, "");

#endif

}	// namespace same_as_test

}	// namespace bksge_concepts_test

#undef BKSGE_SAME_AS_TEST
