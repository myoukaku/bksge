/**
 *	@file	unit_test_fnd_iterator_unreachable_sentinel.cpp
 *
 *	@brief	unreachable_sentinel のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/unreachable_sentinel.hpp>

namespace bksge_iterator_test
{

namespace unreachable_sentinel_test
{

constexpr bksge::unreachable_sentinel_t const* unreachable_sentinel = &bksge::unreachable_sentinel;

}	// namespace unreachable_sentinel_test

}	// namespace bksge_iterator_test
