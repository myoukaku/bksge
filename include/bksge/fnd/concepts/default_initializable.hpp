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

#endif

namespace detail
{

template <typename T>
struct default_initializable_t_impl
{
private:
	template <typename U,
		typename = decltype(U{}),
		typename = decltype((void) ::new U)
	>
	static auto test(int) -> bksge::constructible_from_t<U>;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

template <typename T>
struct default_initializable_t
	: public detail::default_initializable_t_impl<T>::type
{};

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_DEFAULT_INITIALIZABLE_HPP
