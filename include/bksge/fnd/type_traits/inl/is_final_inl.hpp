/**
 *	@file	is_final_inl.hpp
 *
 *	@brief	is_final の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_INL_IS_FINAL_INL_HPP
#define BKSGE_FND_TYPE_TRAITS_INL_IS_FINAL_INL_HPP

#include <bksge/fnd/type_traits/is_final.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

template <typename T>
struct is_final
#if defined(__cpp_lib_is_final) && (__cpp_lib_is_final >= 201402)
	: public detail::constant_wrapper<std::is_final<T>>
#elif (defined(_MSC_VER) && (_MSC_VER >= 1500)) || \
	BKSGE_HAS_FEATURE(is_final)
	: public bksge::bool_constant<__is_final(T)>
#else
	: public bksge::false_type
#endif
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_INL_IS_FINAL_INL_HPP
