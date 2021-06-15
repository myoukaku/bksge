/**
 *	@file	unit_test_fnd_iterator_unreachable_sentinel.cpp
 *
 *	@brief	unreachable_sentinel のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/unreachable_sentinel.hpp>
#include <bksge/fnd/config.hpp>

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_CLANG("-Wunused-const-variable");

namespace bksge_iterator_test
{

namespace unreachable_sentinel_test
{

constexpr bksge::unreachable_sentinel_t const* unreachable_sentinel = &bksge::unreachable_sentinel;

}	// namespace unreachable_sentinel_test

}	// namespace bksge_iterator_test

BKSGE_WARNING_POP();
