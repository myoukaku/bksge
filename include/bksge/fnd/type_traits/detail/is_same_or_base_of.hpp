/**
 *	@file	is_same_or_base_of.hpp
 *
 *	@brief	is_same_or_base_of の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_DETAIL_IS_SAME_OR_BASE_OF_HPP
#define BKSGE_FND_TYPE_TRAITS_DETAIL_IS_SAME_OR_BASE_OF_HPP

#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/is_base_of.hpp>

namespace bksge
{

namespace detail
{

template <typename T0, typename T1>
struct is_same_or_base_of
	: public bksge::bool_constant<
		bksge::is_same<T0, T1>::value ||
		bksge::is_base_of<T0, T1>::value
	>
{};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_DETAIL_IS_SAME_OR_BASE_OF_HPP
