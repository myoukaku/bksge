/**
 *	@file	unit_test_fnd_span_as_writable_bytes.cpp
 *
 *	@brief	bksge::as_writable_bytes() のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/span.hpp>
#include <bksge/fnd/cstddef/byte.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>
#include <string>
#include <gtest/gtest.h>
#include "noexcept_test.hpp"

#define ASSERT_SAME_TYPE(...) \
    static_assert((bksge::is_same<__VA_ARGS__>::value), \
                 "Types differ unexpectedly")

namespace bksge_span_test
{

namespace as_writable_bytes_test
{

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4307);	// 整数定数がオーバーフローしました。

template <typename Span>
void test(Span sp)
{
	BKSGE_ASSERT_NOEXCEPT(bksge::as_writable_bytes(sp));

	auto sp_bytes = bksge::as_writable_bytes(sp);
	using SB = decltype(sp_bytes);
	ASSERT_SAME_TYPE(bksge::byte, typename SB::element_type);

	auto const e =
		(sp.extent == bksge::dynamic_extent) ?
		bksge::dynamic_extent :
		sizeof(typename Span::element_type) * sp.extent;
	EXPECT_TRUE(sp_bytes.extent == e);

	EXPECT_TRUE(static_cast<void*>(sp_bytes.data()) == static_cast<void*>(sp.data()));
	EXPECT_TRUE(sp_bytes.size() == sp.size_bytes());
}

BKSGE_WARNING_POP();

struct A {};

GTEST_TEST(SpanTest, AsWritableBytesTest)
{
	test(bksge::span<int>        ());
	test(bksge::span<long>       ());
	test(bksge::span<double>     ());
	test(bksge::span<A>          ());
	test(bksge::span<std::string>());

	test(bksge::span<int,         0>());
	test(bksge::span<long,        0>());
	test(bksge::span<double,      0>());
	test(bksge::span<A,           0>());
	test(bksge::span<std::string, 0>());

	int arr[] ={0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	test(bksge::span<int>(arr, 1));
	test(bksge::span<int>(arr, 2));
	test(bksge::span<int>(arr, 3));
	test(bksge::span<int>(arr, 4));
	test(bksge::span<int>(arr, 5));

	test(bksge::span<int, 1>(arr + 5, 1));
	test(bksge::span<int, 2>(arr + 4, 2));
	test(bksge::span<int, 3>(arr + 3, 3));
	test(bksge::span<int, 4>(arr + 2, 4));
	test(bksge::span<int, 5>(arr + 1, 5));

	std::string s;
	test(bksge::span<std::string>(&s, static_cast<std::size_t>(0)));
	test(bksge::span<std::string>(&s, 1));
}

}	// namespace as_writable_bytes_test

}	// namespace bksge_span_test

#undef ASSERT_SAME_TYPE
