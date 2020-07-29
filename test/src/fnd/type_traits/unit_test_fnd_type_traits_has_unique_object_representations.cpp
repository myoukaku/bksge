/**
 *	@file	unit_test_fnd_type_traits_has_unique_object_representations.cpp
 *
 *	@brief	has_unique_object_representations のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/has_unique_object_representations.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

namespace bksge_type_traits_test
{

namespace has_unique_object_representations_test
{

#define BKSGE_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST_IMPL(b, T)	\
	static_assert(bksge::has_unique_object_representations<T>::value == b, #T);	\
	static_assert(bksge::has_unique_object_representations<T>()      == b, #T)

#define BKSGE_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST(b, T)	\
	BKSGE_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST_IMPL(b,                T);	\
	BKSGE_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST_IMPL(b, const          T);	\
	BKSGE_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST_IMPL(b,       volatile T);	\
	BKSGE_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST_IMPL(b, const volatile T)

class Empty
{
};

class NotEmpty
{
	virtual ~NotEmpty();
};

union EmptyUnion {};

struct NonEmptyUnion { int x; unsigned y; };

struct bit_zero
{
	int : 0;
};

class Abstract
{
	virtual ~Abstract() = 0;
};

struct A
{
	~A();
	unsigned foo;
};

struct B
{
	char bar;
	int foo;
};

#if defined(BKSGE_HAS_CXX17_HAS_UNIQUE_OBJECT_REPRESENTATIONS)

BKSGE_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST(false, void);
BKSGE_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST(false, Empty);
BKSGE_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST(false, EmptyUnion);
BKSGE_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST(false, NotEmpty);
BKSGE_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST(false, bit_zero);
BKSGE_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST(false, Abstract);
BKSGE_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST(false, B);

BKSGE_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST(true, unsigned);
BKSGE_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST(true, NonEmptyUnion);
BKSGE_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST(true, char[3]);
BKSGE_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST(true, char[]);

#endif

#undef BKSGE_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST_IMPL
#undef BKSGE_HAS_UNIQUE_OBJECT_REPRESENTATIONS_TEST

}	// namespace has_unique_object_representations_test

}	// namespace bksge_type_traits_test
