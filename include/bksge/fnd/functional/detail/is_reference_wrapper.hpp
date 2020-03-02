/**
 *	@file	is_reference_wrapper.hpp
 *
 *	@brief	is_reference_wrapper クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FUNCTIONAL_DETAIL_IS_REFERENCE_WRAPPER_HPP
#define BKSGE_FND_FUNCTIONAL_DETAIL_IS_REFERENCE_WRAPPER_HPP

#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/functional/reference_wrapper.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
struct is_reference_wrapper
	: public bksge::false_type
{};

template <typename T>
struct is_reference_wrapper<bksge::reference_wrapper<T>>
	: public bksge::true_type
{};

template <typename T>
struct is_reference_wrapper<T const>
	: public is_reference_wrapper<T>
{};

template <typename T>
struct is_reference_wrapper<T volatile>
	: public is_reference_wrapper<T>
{};

template <typename T>
struct is_reference_wrapper<T const volatile>
	: public is_reference_wrapper<T>
{};

template <typename T>
struct is_reference_wrapper<T&>
	: public is_reference_wrapper<T>
{};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_FUNCTIONAL_DETAIL_IS_REFERENCE_WRAPPER_HPP
