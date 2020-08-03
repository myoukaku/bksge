/**
 *	@file	default_initializable.hpp
 *
 *	@brief	default_initializable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_DEFAULT_INITIALIZABLE_HPP
#define BKSGE_FND_CONCEPTS_DEFAULT_INITIALIZABLE_HPP

#include <bksge/fnd/concepts/constructible_from.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept default_initializable =
	bksge::constructible_from<T> &&
	requires
	{
		T{};
		(void) ::new T;
	};

#else

namespace detail
{

template <typename T>
struct default_initializable_impl
{
private:
	template <typename U,
		typename = decltype(U{}),
		typename = decltype((void) ::new U)
	>
	static auto test(int) -> bksge::constructible_from<U>;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

template <typename T>
using default_initializable =
	typename detail::default_initializable_impl<T>::type;

#endif

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_DEFAULT_INITIALIZABLE_HPP
