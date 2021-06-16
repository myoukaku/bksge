/**
 *	@file	unit_test_fnd_type_traits_negation.cpp
 *
 *	@brief	negation のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/negation.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/is_unsigned.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>

static_assert(bksge::negation<bksge::false_type>::value == true, "");
static_assert(bksge::negation<bksge::true_type>::value  == false, "");
static_assert(bksge::negation<bksge::is_unsigned<signed   int>>::value == true, "");
static_assert(bksge::negation<bksge::is_unsigned<unsigned int>>::value == false, "");

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

static_assert(bksge::negation_v<bksge::false_type> == true, "");
static_assert(bksge::negation_v<bksge::true_type>  == false, "");

#endif
