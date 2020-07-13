/**
 *	@file	unit_test_fnd_iterator_tag.cpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator.hpp>
#include <bksge/fnd/type_traits/is_empty.hpp>
#include <bksge/fnd/type_traits/is_trivially_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_base_of.hpp>
#include <bksge/fnd/type_traits/is_convertible.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>

static_assert( bksge::is_empty<bksge::bidirectional_iterator_tag>::value, "");
static_assert( bksge::is_empty<bksge::contiguous_iterator_tag>::value, "");
static_assert( bksge::is_empty<bksge::forward_iterator_tag>::value, "");
static_assert( bksge::is_empty<bksge::input_iterator_tag>::value, "");
static_assert( bksge::is_empty<bksge::output_iterator_tag>::value, "");
static_assert( bksge::is_empty<bksge::random_access_iterator_tag>::value, "");

static_assert( bksge::is_trivially_copy_constructible<bksge::bidirectional_iterator_tag>::value, "");
static_assert( bksge::is_trivially_copy_constructible<bksge::contiguous_iterator_tag>::value, "");
static_assert( bksge::is_trivially_copy_constructible<bksge::forward_iterator_tag>::value, "");
static_assert( bksge::is_trivially_copy_constructible<bksge::input_iterator_tag>::value, "");
static_assert( bksge::is_trivially_copy_constructible<bksge::output_iterator_tag>::value, "");
static_assert( bksge::is_trivially_copy_constructible<bksge::random_access_iterator_tag>::value, "");

static_assert( bksge::is_base_of<bksge::forward_iterator_tag,       bksge::bidirectional_iterator_tag>::value, "");
static_assert( bksge::is_base_of<bksge::random_access_iterator_tag, bksge::contiguous_iterator_tag>::value, "");
static_assert( bksge::is_base_of<bksge::input_iterator_tag,         bksge::forward_iterator_tag>::value, "");
static_assert(!bksge::is_base_of<bksge::output_iterator_tag,        bksge::input_iterator_tag>::value, "");
static_assert(!bksge::is_base_of<bksge::input_iterator_tag,         bksge::output_iterator_tag>::value, "");
static_assert( bksge::is_base_of<bksge::bidirectional_iterator_tag, bksge::random_access_iterator_tag>::value, "");

static_assert( bksge::is_convertible<bksge::bidirectional_iterator_tag*, bksge::forward_iterator_tag*>::value, "");
static_assert( bksge::is_convertible<bksge::contiguous_iterator_tag*,    bksge::random_access_iterator_tag*>::value, "");
static_assert( bksge::is_convertible<bksge::forward_iterator_tag*,       bksge::input_iterator_tag*>::value, "");
static_assert(!bksge::is_convertible<bksge::input_iterator_tag*,         bksge::output_iterator_tag*>::value, "");
static_assert(!bksge::is_convertible<bksge::output_iterator_tag*,        bksge::input_iterator_tag*>::value, "");
static_assert( bksge::is_convertible<bksge::random_access_iterator_tag*, bksge::bidirectional_iterator_tag*>::value, "");

static_assert(!bksge::is_same<bksge::iterator_traits<int*>::iterator_category, bksge::contiguous_iterator_tag>::value, "");
static_assert( bksge::is_same<bksge::iterator_traits<int*>::iterator_concept,  bksge::contiguous_iterator_tag>::value, "");
static_assert( bksge::is_same<bksge::iterator_traits<int*>::iterator_category, bksge::random_access_iterator_tag>::value, "");
