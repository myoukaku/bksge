/**
 *	@file	has_unique_object_representations_inl.hpp
 *
 *	@brief	has_unique_object_representations の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_INL_HAS_UNIQUE_OBJECT_REPRESENTATIONS_INL_HPP
#define BKSGE_FND_TYPE_TRAITS_INL_HAS_UNIQUE_OBJECT_REPRESENTATIONS_INL_HPP

#include <bksge/fnd/type_traits/has_unique_object_representations.hpp>
#include <type_traits>

#if defined(__cpp_lib_has_unique_object_representations) && (__cpp_lib_has_unique_object_representations >= 201606)

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>

namespace bksge
{

template <typename T>
struct has_unique_object_representations
	: public detail::constant_wrapper<
		std::has_unique_object_representations<T>
	>
{};

}	// namespace bksge

#define BKSGE_HAS_CXX17_HAS_UNIQUE_OBJECT_REPRESENTATIONS

#endif

#endif // BKSGE_FND_TYPE_TRAITS_INL_HAS_UNIQUE_OBJECT_REPRESENTATIONS_INL_HPP
