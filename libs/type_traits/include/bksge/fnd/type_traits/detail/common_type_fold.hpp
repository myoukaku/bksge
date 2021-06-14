/**
 *	@file	common_type_fold.hpp
 *
 *	@brief	common_type_fold の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_DETAIL_COMMON_TYPE_FOLD_HPP
#define BKSGE_FND_TYPE_TRAITS_DETAIL_COMMON_TYPE_FOLD_HPP

#include <bksge/fnd/type_traits/void_t.hpp>

namespace bksge
{

namespace detail
{

template <typename, typename, typename = bksge::void_t<>>
struct common_type_fold
{};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_DETAIL_COMMON_TYPE_FOLD_HPP
