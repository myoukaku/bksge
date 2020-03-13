/**
 *	@file	unit_test_fnd_type_traits_aligned_storage.cpp
 *
 *	@brief	aligned_storage のテスト
 *
 *	@author	myoukaku
 */

//#if defined(_MSC_VER)
//#define _ENABLE_EXTENDED_ALIGNED_STORAGE
//#endif

#include <bksge/fnd/type_traits/aligned_storage.hpp>
#include <bksge/fnd/type_traits/alignment_of.hpp>
#include <bksge/fnd/type_traits/is_pod.hpp>
#include <cstddef>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

GTEST_TEST(TypeTraitsTest, AlignedStorageTest)
{
	static auto const default_alignment = bksge::alignment_of<std::max_align_t>::value;

#define BKSGE_ALIGNED_STORAGE_TEST_IMPL(T, Len, Align)	\
	static_assert(bksge::is_pod<T>::value, "bksge::is_pod<" #T ">");	\
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
}

//#if defined(_MSC_VER)
//#undef _ENABLE_EXTENDED_ALIGNED_STORAGE
//#endif
