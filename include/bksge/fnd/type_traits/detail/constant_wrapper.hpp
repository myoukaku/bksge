/**
 *	@file	constant_wrapper.hpp
 *
 *	@brief	constant_wrapper の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_DETAIL_CONSTANT_WRAPPER_HPP
#define BKSGE_FND_TYPE_TRAITS_DETAIL_CONSTANT_WRAPPER_HPP

#include <bksge/fnd/type_traits/integral_constant.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
struct constant_wrapper
	: public bksge::integral_constant<typename T::value_type, T::value>
{};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_DETAIL_CONSTANT_WRAPPER_HPP
