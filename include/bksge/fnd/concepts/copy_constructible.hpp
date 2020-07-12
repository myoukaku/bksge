/**
 *	@file	copy_constructible.hpp
 *
 *	@brief	copy_constructible の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_COPY_CONSTRUCTIBLE_HPP
#define BKSGE_FND_CONCEPTS_COPY_CONSTRUCTIBLE_HPP

#include <bksge/fnd/concepts/move_constructible.hpp>
#include <bksge/fnd/concepts/constructible_from.hpp>
#include <bksge/fnd/concepts/convertible_to.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept copy_constructible =
	bksge::move_constructible<T> &&
	bksge::constructible_from<T, T&>       && bksge::convertible_to<T&, T> &&
	bksge::constructible_from<T, const T&> && bksge::convertible_to<const T&, T> &&
	bksge::constructible_from<T, const T>  && bksge::convertible_to<const T, T>;

#endif

namespace detail
{

template <typename T>
struct copy_constructible_t_impl
{
private:
	template <typename U>
	static auto test(int) -> bksge::conjunction<
		bksge::move_constructible_t<U>,
		bksge::constructible_from_t<U, U&>,       bksge::convertible_to_t<U&, U>,
		bksge::constructible_from_t<U, const U&>, bksge::convertible_to_t<const U&, U>,
		bksge::constructible_from_t<U, const U>,  bksge::convertible_to_t<const U, U>>;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

template <typename T>
struct copy_constructible_t
	: public detail::copy_constructible_t_impl<T>::type
{};

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_COPY_CONSTRUCTIBLE_HPP
