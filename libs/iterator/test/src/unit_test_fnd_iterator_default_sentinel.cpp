/**
 *	@file	unit_test_fnd_iterator_default_sentinel.cpp
 *
 *	@brief	default_sentinel のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/default_sentinel.hpp>
#include <bksge/fnd/config.hpp>

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_CLANG("-Wunused-const-variable");

namespace bksge_iterator_test
{

namespace default_sentinel_test
{

constexpr bksge::default_sentinel_t const* default_sentinel = &bksge::default_sentinel;

}	// namespace default_sentinel_test

}	// namespace bksge_iterator_test

BKSGE_WARNING_POP();
