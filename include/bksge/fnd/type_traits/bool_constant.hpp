/**
 *	@file	bool_constant.hpp
 *
 *	@brief	bool_constant の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_BOOL_CONSTANT_HPP
#define BKSGE_FND_TYPE_TRAITS_BOOL_CONSTANT_HPP

#include <type_traits>	// integral_constant

namespace bksge
{

template <bool B>
using bool_constant = std::integral_constant<bool, B>;

using true_type  = bool_constant<true>;
using false_type = bool_constant<false>;

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_BOOL_CONSTANT_HPP
