/**
 *	@file	unit_test_fnd_concepts_floating_point.cpp
 *
 *	@brief	floating_point のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/concepts/floating_point.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_FLOATING_POINT_TEST(B, T)	\
	static_assert(B == bksge::floating_point<T>, " ");	\
	static_assert(B == bksge::floating_point_t<T>::value, " ")
#else
#  define BKSGE_FLOATING_POINT_TEST(B, T)	\
	static_assert(B == bksge::floating_point_t<T>::value, " ")
#endif

namespace bksge_concepts_test
{

namespace floating_point_test
{

BKSGE_FLOATING_POINT_TEST(true,  float);
BKSGE_FLOATING_POINT_TEST(true,  double);
BKSGE_FLOATING_POINT_TEST(true,  long double);

BKSGE_FLOATING_POINT_TEST(false, char);
BKSGE_FLOATING_POINT_TEST(false, signed char);
BKSGE_FLOATING_POINT_TEST(false, bool);
BKSGE_FLOATING_POINT_TEST(false, int);
BKSGE_FLOATING_POINT_TEST(false, char32_t);

BKSGE_FLOATING_POINT_TEST(false, void);
BKSGE_FLOATING_POINT_TEST(false, float*);
BKSGE_FLOATING_POINT_TEST(false, float&);
BKSGE_FLOATING_POINT_TEST(false, float&&);
BKSGE_FLOATING_POINT_TEST(false, const float&);
BKSGE_FLOATING_POINT_TEST(false, float[]);
BKSGE_FLOATING_POINT_TEST(false, float[2]);
BKSGE_FLOATING_POINT_TEST(false, float());
BKSGE_FLOATING_POINT_TEST(false, float(*)());
BKSGE_FLOATING_POINT_TEST(false, float(&)());

enum E { };
BKSGE_FLOATING_POINT_TEST(false, E);
enum class CE { };
BKSGE_FLOATING_POINT_TEST(false, CE);
struct A { };
BKSGE_FLOATING_POINT_TEST(false, A);
union B { };
BKSGE_FLOATING_POINT_TEST(false, B);

}	// namespace floating_point_test

}	// namespace bksge_concepts_test

#undef BKSGE_FLOATING_POINT_TEST
