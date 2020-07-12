/**
 *	@file	class_or_enum.hpp
 *
 *	@brief	class_or_enum の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_DETAIL_CLASS_OR_ENUM_HPP
#define BKSGE_FND_CONCEPTS_DETAIL_CLASS_OR_ENUM_HPP

#include <bksge/fnd/type_traits/is_class.hpp>
#include <bksge/fnd/type_traits/is_union.hpp>
#include <bksge/fnd/type_traits/is_enum.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept class_or_enum =
	bksge::is_class<T>::value ||
	bksge::is_union<T>::value ||
	bksge::is_enum<T>::value;

#endif

template <typename T>
struct class_or_enum_t
	: public bksge::bool_constant<
		bksge::is_class<T>::value ||
		bksge::is_union<T>::value ||
		bksge::is_enum<T>::value
	>
{};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_DETAIL_CLASS_OR_ENUM_HPP
