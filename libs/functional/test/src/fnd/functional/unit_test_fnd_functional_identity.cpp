/**
 *	@file	unit_test_fnd_functional_identity.cpp
 *
 *	@brief	identity のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/type_traits/is_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_copy_assignable.hpp>
#include <bksge/fnd/type_traits/is_move_assignable.hpp>
#include <bksge/fnd/type_traits/is_invocable.hpp>
#include <bksge/fnd/type_traits/is_nothrow_invocable_r.hpp>
#include <bksge/fnd/memory/addressof.hpp>

namespace bksge_functional_test
{

namespace identity_test
{

static_assert( bksge::is_default_constructible<bksge::identity>::value, "");
static_assert( bksge::is_copy_constructible<bksge::identity>::value, "");
static_assert( bksge::is_move_constructible<bksge::identity>::value, "");
static_assert( bksge::is_copy_assignable<bksge::identity>::value, "");
static_assert( bksge::is_move_assignable<bksge::identity>::value, "");

static_assert(!bksge::is_invocable<bksge::identity>::value, "");
static_assert(!bksge::is_invocable<bksge::identity, int&, int&>::value, "");
static_assert( bksge::is_nothrow_invocable_r<int&, bksge::identity&, int&>::value, "");
static_assert( bksge::is_nothrow_invocable_r<const long&, bksge::identity, const long&>::value, "");
static_assert( bksge::is_nothrow_invocable_r<short&&, const bksge::identity&, short>::value, "");
static_assert( bksge::is_nothrow_invocable_r<const char&&, const bksge::identity, const char>::value, "");

int i;
static_assert( bksge::addressof(bksge::identity{}(i)) == bksge::addressof(i), "");

using T = bksge::identity::is_transparent; // required typedef

}	// namespace identity_test

}	// namespace bksge_functional_test
