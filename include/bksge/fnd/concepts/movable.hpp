/**
 *	@file	movable.hpp
 *
 *	@brief	movable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_MOVABLE_HPP
#define BKSGE_FND_CONCEPTS_MOVABLE_HPP

#include <bksge/fnd/concepts/move_constructible.hpp>
#include <bksge/fnd/concepts/assignable_from.hpp>
#include <bksge/fnd/concepts/swappable.hpp>
#include <bksge/fnd/type_traits/is_object.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept movable =
	bksge::is_object<T>::value &&
	bksge::move_constructible<T> &&
	bksge::assignable_from<T&, T> &&
	bksge::swappable<T>;

#endif

namespace detail
{

template <typename T>
struct movable_t_impl
{
private:
	template <typename U>
	static auto test(int) -> bksge::conjunction<
		bksge::is_object<U>,
		bksge::move_constructible_t<U>,
		bksge::assignable_from_t<U&, U>,
		bksge::swappable_t<U>>;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

template <typename T>
struct movable_t
	: public detail::movable_t_impl<T>::type
{};

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_MOVABLE_HPP
