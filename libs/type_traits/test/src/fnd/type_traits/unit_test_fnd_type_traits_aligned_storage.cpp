/**
 *	@file	unit_test_fnd_type_traits_aligned_storage.cpp
 *
 *	@brief	aligned_storage のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/aligned_storage.hpp>
#include <bksge/fnd/type_traits/alignment_of.hpp>
#include <bksge/fnd/type_traits/is_standard_layout.hpp>
#include <bksge/fnd/type_traits/is_trivial.hpp>
#include <bksge/fnd/cstddef/max_align_t.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

namespace type_traits_test
{

namespace aligned_storage_test
{

static auto const default_alignment = bksge::alignment_of<bksge::max_align_t>::value;

#define BKSGE_ALIGNED_STORAGE_TEST_IMPL(T, Len, Align)	\
	static_assert(bksge::is_standard_layout<T>::value, "bksge::is_standard_layout<" #T ">");	\
	static_assert(bksge::is_trivial<T>::value, "bksge::is_trivial<" #T ">");	\
	static_assert(sizeof(T) >= Len, "sizeof(" #T ")");	\
	static_assert(bksge::alignment_of<T>::value <= Align, "alignment_of<" #T ">")

#define BKSGE_ALIGNED_STORAGE_TEST(Len)	\
	BKSGE_ALIGNED_STORAGE_TEST_IMPL(bksge::aligned_storage<Len>::type, Len, default_alignment);	\
	BKSGE_ALIGNED_STORAGE_TEST_IMPL(bksge::aligned_storage_t<Len>,     Len, default_alignment);	\
	using storage_ ## Len = bksge::aligned_storage<Len, Len>::type;	\
	BKSGE_ALIGNED_STORAGE_TEST_IMPL(storage_ ## Len, Len, Len)

BKSGE_ALIGNED_STORAGE_TEST(1);
BKSGE_ALIGNED_STORAGE_TEST(2);
BKSGE_ALIGNED_STORAGE_TEST(4);
BKSGE_ALIGNED_STORAGE_TEST(8);
#if !defined(_MSC_VER)
BKSGE_ALIGNED_STORAGE_TEST(16);
BKSGE_ALIGNED_STORAGE_TEST(32);
BKSGE_ALIGNED_STORAGE_TEST(64);
BKSGE_ALIGNED_STORAGE_TEST(128);
#endif

#undef BKSGE_ALIGNED_STORAGE_TEST
#undef BKSGE_ALIGNED_STORAGE_TEST_IMPL

}	// namespace aligned_storage_test

}	// namespace type_traits_test
