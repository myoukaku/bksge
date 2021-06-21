/**
 *	@file	make_optional.hpp
 *
 *	@brief	make_optional の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_OPTIONAL_MAKE_OPTIONAL_HPP
#define BKSGE_FND_OPTIONAL_MAKE_OPTIONAL_HPP

#include <bksge/fnd/optional/config.hpp>

#if defined(BKSGE_USE_STD_OPTIONAL)

#include <optional>

namespace bksge
{

using std::make_optional;

}	// namespace bksge

#else

#include <bksge/fnd/optional/optional.hpp>
#include <bksge/fnd/type_traits/decay.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/in_place.hpp>
#include <bksge/fnd/config.hpp>
#include <initializer_list>

namespace bksge
{

template <typename T,
	typename = bksge::enable_if_t<
		bksge::is_constructible<bksge::decay_t<T>, T>::value>>
inline BKSGE_CONSTEXPR optional<bksge::decay_t<T>>
make_optional(T&& t)
	BKSGE_NOEXCEPT_IF((
		bksge::is_nothrow_constructible<optional<bksge::decay_t<T>>, T>::value))
{
	return optional<bksge::decay_t<T>>{ bksge::forward<T>(t) };
}

template <typename T, typename... Args,
	typename = bksge::enable_if_t<
		bksge::is_constructible<T, Args...>::value>>
inline BKSGE_CONSTEXPR optional<T>
make_optional(Args&&... args)
	BKSGE_NOEXCEPT_IF((
		bksge::is_nothrow_constructible<T, Args...>::value))
{
	return optional<T>{ bksge::in_place, bksge::forward<Args>(args)... };
}

template <typename T, typename U, typename... Args,
	typename = bksge::enable_if_t<
		bksge::is_constructible<T, std::initializer_list<U>&, Args...>::value>>
inline BKSGE_CONSTEXPR optional<T>
make_optional(std::initializer_list<U> il, Args&&... args)
	BKSGE_NOEXCEPT_IF((
		bksge::is_nothrow_constructible<T, std::initializer_list<U>&, Args...>::value))
{
	return optional<T>{ bksge::in_place, il, bksge::forward<Args>(args)... };
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_OPTIONAL_MAKE_OPTIONAL_HPP
