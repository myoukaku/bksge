/**
 *	@file	is_std_array.hpp
 *
 *	@brief	is_std_array の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SPAN_DETAIL_IS_STD_ARRAY_HPP
#define BKSGE_FND_SPAN_DETAIL_IS_STD_ARRAY_HPP

#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/remove_cv.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <array>

namespace bksge
{

namespace detail
{

// is_std_array
template <typename T>
struct is_std_array_impl
	: public bksge::false_type {};

template <typename T, bksge::size_t N>
struct is_std_array_impl<std::array<T, N>>
	: public bksge::true_type {};

template <typename T>
struct is_std_array
	: public is_std_array_impl<bksge::remove_cv_t<T>> {};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_SPAN_DETAIL_IS_STD_ARRAY_HPP
