/**
 *	@file	indirectly_writable.hpp
 *
 *	@brief	indirectly_writable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_INDIRECTLY_WRITABLE_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_INDIRECTLY_WRITABLE_HPP

#include <bksge/fnd/iterator/iter_reference_t.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Out, typename T>
concept indirectly_writable =
	requires(Out&& o, T&& t)
	{
		*o = bksge::forward<T>(t);
		*bksge::forward<Out>(o) = bksge::forward<T>(t);
		const_cast<const bksge::iter_reference_t<Out>&&>(*o) = bksge::forward<T>(t);
		const_cast<const bksge::iter_reference_t<Out>&&>(*bksge::forward<Out>(o)) = bksge::forward<T>(t);
	};

#endif

namespace detail
{

template <typename Out, typename T>
struct indirectly_writable_t_impl
{
private:
	template <typename Out2, typename T2,
		typename R = const bksge::iter_reference_t<Out2>&&,
		typename = decltype(*bksge::declval<Out2&>()  = bksge::declval<T2&&>()),
		typename = decltype(*bksge::declval<Out2&&>() = bksge::declval<T2&&>()),
		typename = decltype(const_cast<R>(*bksge::declval<Out2&>())  = bksge::declval<T2&&>()),
		typename = decltype(const_cast<R>(*bksge::declval<Out2&&>()) = bksge::declval<T2&&>())
	>
	static auto test(int) -> bksge::true_type;

	template <typename Out2, typename T2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<Out, T>(0));
};

}	// namespace detail

template <typename Out, typename T>
using indirectly_writable_t =
	typename detail::indirectly_writable_t_impl<Out, T>::type;

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_INDIRECTLY_WRITABLE_HPP
