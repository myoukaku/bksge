/**
 *	@file	copyable.hpp
 *
 *	@brief	copyable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_COPYABLE_HPP
#define BKSGE_FND_CONCEPTS_COPYABLE_HPP

#include <bksge/fnd/concepts/copy_constructible.hpp>
#include <bksge/fnd/concepts/movable.hpp>
#include <bksge/fnd/concepts/assignable_from.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept copyable =
	bksge::copy_constructible<T> &&
	bksge::movable<T> &&
	bksge::assignable_from<T&, T&> &&
	bksge::assignable_from<T&, const T&> &&
	bksge::assignable_from<T&, const T>;

#else

namespace detail
{

template <typename T>
struct copyable_impl
{
private:
	template <typename U>
	static auto test(int) -> bksge::conjunction<
		bksge::copy_constructible<U>,
		bksge::movable<U>,
		bksge::assignable_from<U&, U&>,
		bksge::assignable_from<U&, const U&>,
		bksge::assignable_from<U&, const U>>;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

template <typename T>
using copyable =
	typename detail::copyable_impl<T>::type;

#endif

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_COPYABLE_HPP
