/**
 *	@file	bool_constant.hpp
 *
 *	@brief	bool_constant の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_BOOL_CONSTANT_HPP
#define BKSGE_FND_TYPE_TRAITS_BOOL_CONSTANT_HPP

#include <bksge/fnd/type_traits/integral_constant.hpp>

namespace bksge
{

template <bool B>
using bool_constant = bksge::integral_constant<bool, B>;

using true_type  = bool_constant<true>;
using false_type = bool_constant<false>;

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_BOOL_CONSTANT_HPP
