/**
 *	@file	convertible_to.hpp
 *
 *	@brief	convertible_to の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_CONVERTIBLE_TO_HPP
#define BKSGE_FND_CONCEPTS_CONVERTIBLE_TO_HPP

#include <bksge/fnd/type_traits/is_convertible.hpp>
#include <bksge/fnd/type_traits/add_rvalue_reference.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename From, typename To>
concept convertible_to =
	bksge::is_convertible<From, To>::value &&
	requires(bksge::add_rvalue_reference_t<From> (&f)())
	{
		static_cast<To>(f());
	};

template <typename From, typename To>
using is_convertible_to = bksge::bool_constant<convertible_to<From, To>>;

#else

namespace detail
{

template <typename From, typename To>
struct convertible_to_impl
{
private:
	template <typename F, typename T,
		typename Func = bksge::add_rvalue_reference_t<F> (&)(),
		typename = decltype(static_cast<T>(bksge::declval<Func>()()))
	>
	static auto test(int) -> bksge::is_convertible<F, T>;

	template <typename F, typename T>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<From, To>(0));
};

}	// namespace detail

template <typename From, typename To>
using convertible_to =
	typename detail::convertible_to_impl<From, To>::type;

template <typename From, typename To>
using is_convertible_to = convertible_to<From, To>;

#endif

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_CONVERTIBLE_TO_HPP
