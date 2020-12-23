/**
 *	@file	unit_test_fnd_iterator_counted_iterator.cpp
 *
 *	@brief	counted_iterator のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/counted_iterator.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/ssize.hpp>
#include <bksge/fnd/iterator/default_sentinel.hpp>
#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/iterator/iter_reference_t.hpp>
#include <bksge/fnd/iterator/iter_rvalue_reference_t.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
#include <bksge/fnd/iterator/concepts/forward_iterator.hpp>
#include <bksge/fnd/iterator/concepts/bidirectional_iterator.hpp>
#include <bksge/fnd/iterator/concepts/random_access_iterator.hpp>
#include <bksge/fnd/type_traits/is_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_copy_assignable.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_convertible.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/cstddef/ptrdiff_t.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace bksge_iterator_test
{

namespace counted_iterator_test
{

using I = bksge::counted_iterator<int*>;
static_assert( bksge::is_default_constructible<I>::value, "");
static_assert( bksge::is_copy_constructible<I>::value, "");
static_assert( bksge::is_copy_assignable<I>::value, "");
static_assert(!bksge::is_constructible<I, int*>::value, "");
static_assert( bksge::is_constructible<I, int*, bksge::ptrdiff_t>::value, "");
static_assert( bksge::is_same<bksge::iter_difference_t<I>, bksge::ptrdiff_t>::value, "");
static_assert( bksge::is_same<bksge::iter_reference_t<I>, int&>::value, "");
static_assert( bksge::is_same<bksge::iter_rvalue_reference_t<I>, int&&>::value, "");
static_assert( bksge::is_same<bksge::iter_value_t<I>, int>::value, "");
static_assert( bksge::is_input_iterator<I>::value, "");
static_assert( bksge::is_forward_iterator<I>::value, "");
static_assert( bksge::is_bidirectional_iterator<I>::value, "");
static_assert(!bksge::is_random_access_iterator<I>::value, "");

using J = bksge::counted_iterator<int const*>;
static_assert( bksge::is_constructible<J, I const&>::value, "");
static_assert( bksge::is_convertible<I const&, J>::value, "");
static_assert( bksge::is_same<bksge::iter_difference_t<J>, bksge::ptrdiff_t>::value, "");
static_assert( bksge::is_same<bksge::iter_reference_t<J>, int const&>::value, "");
static_assert( bksge::is_same<bksge::iter_rvalue_reference_t<J>, int const&&>::value, "");
static_assert( bksge::is_same<bksge::iter_value_t<J>, int>::value, "");

using I2 = bksge::counted_iterator<input_iterator_wrapper<char>>;
static_assert( bksge::is_same<bksge::iter_difference_t<I2>, bksge::ptrdiff_t>::value, "");
static_assert( bksge::is_same<bksge::iter_reference_t<I2>, char&>::value, "");
static_assert( bksge::is_same<bksge::iter_rvalue_reference_t<I2>, char&&>::value, "");
static_assert( bksge::is_same<bksge::iter_value_t<I2>, char>::value, "");
static_assert( bksge::is_input_iterator<I2>::value, "");
static_assert(!bksge::is_forward_iterator<I2>::value, "");
static_assert(!bksge::is_bidirectional_iterator<I2>::value, "");
static_assert(!bksge::is_random_access_iterator<I2>::value, "");

using I3 = bksge::counted_iterator<forward_iterator_wrapper<double>>;
static_assert( bksge::is_same<bksge::iter_difference_t<I3>, bksge::ptrdiff_t>::value, "");
static_assert( bksge::is_same<bksge::iter_reference_t<I3>, double&>::value, "");
static_assert( bksge::is_same<bksge::iter_rvalue_reference_t<I3>, double&&>::value, "");
static_assert( bksge::is_same<bksge::iter_value_t<I3>, double>::value, "");
static_assert( bksge::is_input_iterator<I3>::value, "");
static_assert( bksge::is_forward_iterator<I3>::value, "");
static_assert(!bksge::is_bidirectional_iterator<I3>::value, "");
static_assert(!bksge::is_random_access_iterator<I3>::value, "");

using I4 = bksge::counted_iterator<bidirectional_iterator_wrapper<float>>;
static_assert( bksge::is_same<bksge::iter_difference_t<I4>, bksge::ptrdiff_t>::value, "");
static_assert( bksge::is_same<bksge::iter_reference_t<I4>, float&>::value, "");
static_assert( bksge::is_same<bksge::iter_rvalue_reference_t<I4>, float&&>::value, "");
static_assert( bksge::is_same<bksge::iter_value_t<I4>, float>::value, "");
static_assert( bksge::is_input_iterator<I4>::value, "");
static_assert( bksge::is_forward_iterator<I4>::value, "");
static_assert( bksge::is_bidirectional_iterator<I4>::value, "");
static_assert(!bksge::is_random_access_iterator<I4>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	{
		int in[3] = {1, 2, 3};
		bksge::counted_iterator<int const*> in_iter(bksge::begin(in), bksge::ssize(in));
		VERIFY(in_iter.base() == in);
		VERIFY((bksge::default_sentinel - in_iter) == 3);
		VERIFY((in_iter - bksge::default_sentinel) == -3);

		int out[4] = {};
		bksge::counted_iterator<int*> out_iter(bksge::begin(out), bksge::ssize(out));
		VERIFY(out_iter.base() == out);
		VERIFY((bksge::default_sentinel - out_iter) == 4);
		VERIFY((out_iter - bksge::default_sentinel) == -4);

		while (in_iter != bksge::default_sentinel && out_iter != bksge::default_sentinel)
		{
			*out_iter++ = *in_iter++;
		}

		VERIFY(in_iter  == bksge::default_sentinel);
		VERIFY(out_iter != bksge::default_sentinel);
		VERIFY(out[0] == 1);
		VERIFY(out[1] == 2);
		VERIFY(out[2] == 3);
		VERIFY(out[3] == 0);

		auto out2 = out_iter;
		out2 += 1;
		VERIFY(out2 == bksge::default_sentinel);
		//VERIFY((out2 <=> out_iter) == std::strong_ordering::greater);
		out2 -= 3;
		VERIFY((out_iter - out2) == 2);
		//VERIFY((out2 <=> out_iter) == std::strong_ordering::less);
	}
	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test02()
{
	int x[] = {1, 2, 3};
	bksge::counted_iterator<int*> const iter1(bksge::begin(x), bksge::ssize(x));
	bksge::counted_iterator<int const*> iter2(iter1);
	VERIFY(iter1.base() == x);
	VERIFY(iter2.base() == x);
	VERIFY(iter1.count() == 3);
	VERIFY(iter2.count() == 3);
	VERIFY(*iter1 == 1);
	VERIFY(*iter2 == 1);

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test03()
{
	int x[] = {1, 2, 3, 4};
	bksge::counted_iterator<int*> const iter1(bksge::begin(x), bksge::ssize(x));
	bksge::counted_iterator<int const*> iter2;
	iter2 = iter1;
	VERIFY(iter2.base() == x);
	VERIFY(iter2.count() == 4);

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test04()
{
	int x[] = {1, 2, 3, 4};
	input_iterator_wrapper<int> iter1{x};
	bksge::counted_iterator<input_iterator_wrapper<int>> iter2(iter1, bksge::ssize(x));

	VERIFY(iter2.count() == 4);
	++iter2;
	VERIFY(iter2.count() == 3);
	iter2++;
	VERIFY(iter2.count() == 2);

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test05()
{
	int x[] = {1, 2, 3};
	bksge::counted_iterator<int*> iter(bksge::begin(x), bksge::ssize(x));

	VERIFY(iter[0] == 1);
	VERIFY(iter[1] == 2);
	VERIFY(iter[2] == 3);
	
	VERIFY(iter.count() == 3);
	VERIFY(*iter == 1);
	auto p1 = (++iter).base();
	VERIFY(iter.count() == 2);
	VERIFY(*iter == 2);
	VERIFY(p1 == x+1);
	auto p2 = (iter++).base();
	VERIFY(iter.count() == 1);
	VERIFY(*iter == 3);
	VERIFY(p2 == x+1);
	--iter;
	VERIFY(iter.count() == 2);
	VERIFY(*iter == 2);
	iter--;
	VERIFY(iter.count() == 3);
	VERIFY(*iter == 1);

	auto iter2 = iter + 1;
	VERIFY(iter2.count() == 2);
	VERIFY(*iter2 == 2);

	auto iter3 = 2 + iter;
	VERIFY(iter3.count() == 1);
	VERIFY(*iter3 == 3);

	auto iter4 = iter3 - 1;
	VERIFY(iter4.count() == 2);
	VERIFY(*iter4 == 2);

	VERIFY(iter2[0] == 2);
	VERIFY(iter2[1] == 3);
	VERIFY(iter3[0] == 3);

	VERIFY(iter2 - iter == 1);
	VERIFY(iter3 - iter == 2);
	VERIFY(iter4 - iter == 1);

	VERIFY((iter2 == iter3) == false);
	VERIFY((iter2 == iter4) == true);
	VERIFY((iter2 != iter3) == true);
	VERIFY((iter2 != iter4) == false);

	bksge::ranges::iter_swap(iter2, iter3);
	VERIFY(*iter2 == 3);
	VERIFY(*iter3 == 2);

	auto y = bksge::ranges::iter_move(iter2);
	auto z = bksge::ranges::iter_move(iter3);
	VERIFY(y == 3);
	VERIFY(z == 2);

	return true;
}

#if 0
struct X
{
	BKSGE_CXX14_CONSTEXPR X(int i) : i(i) { }
	BKSGE_CXX14_CONSTEXPR X(X&& x) : i(x.i) { x.i = -1; }
	BKSGE_CXX14_CONSTEXPR X& operator=(X&& x) { i = x.i; x.i = 0; return *this; }
	int i;
};

inline BKSGE_CXX14_CONSTEXPR bool test06()
{
	X arr[] ={{1}, {2}};
	bksge::counted_iterator<X*> i(arr, 2), j(arr + 1, 1);
	bksge::ranges::iter_swap(i, j);
	VERIFY(arr[0].i == 2);
	VERIFY(arr[1].i == 1);

	X x = bksge::ranges::iter_move(i);
	VERIFY(arr[0].i == -1);
	VERIFY(x.i == 2);

	return true;
}
#endif

#undef VERIFY

GTEST_TEST(IteratorTest, CountedIteratorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
}

}	// namespace counted_iterator_test

}	// namespace bksge_iterator_test
