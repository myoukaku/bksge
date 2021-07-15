/**
 *	@file	unit_test_fnd_span_types.cpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/span.hpp>
#include <bksge/fnd/cstddef/ptrdiff_t.hpp>
#include <bksge/fnd/iterator/iterator_traits.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/remove_cv.hpp>
#include <gtest/gtest.h>
#include <cstddef>

#define ASSERT_SAME_TYPE(...) \
    static_assert((bksge::is_same<__VA_ARGS__>::value), \
                 "Types differ unexpectedly")

namespace bksge_span_test
{

namespace types_test
{

template <typename S, typename Iter>
void testIterator()
{
	typedef bksge::iterator_traits<Iter> ItT;

	ASSERT_SAME_TYPE(typename ItT::iterator_category, bksge::random_access_iterator_tag);
	ASSERT_SAME_TYPE(typename ItT::value_type,        typename S::value_type);
	ASSERT_SAME_TYPE(typename ItT::reference,         typename S::reference);
	ASSERT_SAME_TYPE(typename ItT::pointer,           typename S::pointer);
	ASSERT_SAME_TYPE(typename ItT::difference_type,   typename S::difference_type);
}

template <typename S, typename ElementType, std::size_t Size>
void testSpan()
{
	ASSERT_SAME_TYPE(typename S::element_type,    ElementType);
	ASSERT_SAME_TYPE(typename S::value_type,      bksge::remove_cv_t<ElementType>);
	ASSERT_SAME_TYPE(typename S::size_type,       std::size_t);
	ASSERT_SAME_TYPE(typename S::difference_type, bksge::ptrdiff_t);
	ASSERT_SAME_TYPE(typename S::pointer,         ElementType*);
	ASSERT_SAME_TYPE(typename S::const_pointer,   const ElementType*);
	ASSERT_SAME_TYPE(typename S::reference,       ElementType&);
	ASSERT_SAME_TYPE(typename S::const_reference, const ElementType&);

	static_assert(S::extent == Size, ""); // check that it exists

	testIterator<S, typename S::iterator>();
	//testIterator<S, typename S::reverse_iterator>();
}


template <typename T>
void test()
{
	testSpan<bksge::span<               T>,                T, bksge::dynamic_extent>();
	testSpan<bksge::span<const          T>, const          T, bksge::dynamic_extent>();
	testSpan<bksge::span<      volatile T>,       volatile T, bksge::dynamic_extent>();
	testSpan<bksge::span<const volatile T>, const volatile T, bksge::dynamic_extent>();

	testSpan<bksge::span<               T, 5>,                T, 5>();
	testSpan<bksge::span<const          T, 5>, const          T, 5>();
	testSpan<bksge::span<      volatile T, 5>,       volatile T, 5>();
	testSpan<bksge::span<const volatile T, 5>, const volatile T, 5>();
}

struct A {};

GTEST_TEST(SpanTest, TypesTest)
{
	test<int>();
	test<long>();
	test<double>();
	test<bksge::string>();
	test<A>();
}

}	// namespace types_test

}	// namespace bksge_span_test

#undef ASSERT_SAME_TYPE
