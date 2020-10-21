/**
 *	@file	compares_as.hpp
 *
 *	@brief	compares_as の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_COMPARE_DETAIL_COMPARES_AS_HPP
#define BKSGE_FND_COMPARE_DETAIL_COMPARES_AS_HPP

#include <bksge/fnd/compare/common_comparison_category.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T, typename Cat>
concept compares_as =
	bksge::same_as<bksge::common_comparison_category_t<T, Cat>, Cat>;

#endif

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_COMPARE_DETAIL_COMPARES_AS_HPP
