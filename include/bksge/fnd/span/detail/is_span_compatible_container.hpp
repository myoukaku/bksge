/**
 *	@file	is_span_compatible_container.hpp
 *
 *	@brief	is_span_compatible_container の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SPAN_DETAIL_IS_SPAN_COMPATIBLE_CONTAINER_HPP
#define BKSGE_FND_SPAN_DETAIL_IS_SPAN_COMPATIBLE_CONTAINER_HPP

#include <bksge/fnd/span/fwd/span_fwd.hpp>
#include <bksge/fnd/iterator/data.hpp>
#include <bksge/fnd/iterator/size.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_array.hpp>
#include <bksge/fnd/type_traits/is_convertible.hpp>
#include <bksge/fnd/type_traits/remove_cv.hpp>
#include <bksge/fnd/type_traits/remove_pointer.hpp>
#include <bksge/fnd/type_traits/void_t.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <array>
#include <cstddef>

namespace bksge
{

namespace span_detail
{

// is_span
template <typename T>
struct is_span_impl
	: public bksge::false_type {};

template <typename T, std::size_t Extent>
struct is_span_impl<span<T, Extent>>
	: public bksge::true_type {};

template <typename T>
struct is_span
	: public is_span_impl<bksge::remove_cv_t<T>> {};

// is_std_array
template <typename T>
struct is_std_array_impl
	: public bksge::false_type {};

template <typename T, std::size_t N>
struct is_std_array_impl<std::array<T, N>>
	: public bksge::true_type {};

template <typename T>
struct is_std_array
	: public is_std_array_impl<bksge::remove_cv_t<T>> {};

// is_span_compatible_container
template <typename T, typename ElementType, typename = void>
struct is_span_compatible_container
	: public bksge::false_type {};

template <typename T, typename ElementType>
struct is_span_compatible_container<
	T,
	ElementType,
	bksge::void_t<
		bksge::enable_if_t<!is_span<T>::value>,
		bksge::enable_if_t<!is_std_array<T>::value>,
		bksge::enable_if_t<!bksge::is_array<T>::value>,
		decltype(bksge::data(bksge::declval<T>())),
		decltype(bksge::size(bksge::declval<T>())),
		bksge::enable_if_t<
			bksge::is_convertible<
				bksge::remove_pointer_t<decltype(bksge::data(bksge::declval<T&>()))>(*)[], ElementType(*)[]
			>::value
		>
	>
> : public bksge::true_type{};

}	// namespace span_detail

}	// namespace bksge

#endif // BKSGE_FND_SPAN_DETAIL_IS_SPAN_COMPATIBLE_CONTAINER_HPP
