/**
 *	@file	copy_cv_inl.hpp
 *
 *	@brief	copy_cv の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_INL_COPY_CV_INL_HPP
#define BKSGE_FND_TYPE_TRAITS_INL_COPY_CV_INL_HPP

#include <bksge/fnd/type_traits/copy_cv.hpp>
#include <bksge/fnd/type_traits/add_const.hpp>
#include <bksge/fnd/type_traits/add_volatile.hpp>
#include <bksge/fnd/type_traits/is_const.hpp>
#include <bksge/fnd/type_traits/is_volatile.hpp>

namespace bksge
{

namespace detail
{

template <typename T, bool, bool>
struct copy_cv_impl
{
	using type = T;
};

template <typename T>
struct copy_cv_impl<T, true, false>
{
	using type = bksge::add_const_t<T>;
};

template <typename T>
struct copy_cv_impl<T, false, true>
{
	using type = bksge::add_volatile_t<T>;
};

template <typename T>
struct copy_cv_impl<T, true, true>
{
	using type = bksge::add_const_t<bksge::add_volatile_t<T>>;
};

} // namespace detail

template <typename T, typename U>
struct copy_cv
{
	using type = typename detail::copy_cv_impl<
		T,
		bksge::is_const<U>::value,
		bksge::is_volatile<U>::value
	>::type;
};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_INL_COPY_CV_INL_HPP
