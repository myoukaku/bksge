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
		const_cast<bksge::iter_reference_t<Out> const&&>(*o) = bksge::forward<T>(t);
		const_cast<bksge::iter_reference_t<Out> const&&>(*bksge::forward<Out>(o)) = bksge::forward<T>(t);
	};

#else

namespace detail
{

template <typename Out, typename T>
struct indirectly_writable_impl
{
private:
	template <typename Out2, typename T2,
		typename R = bksge::iter_reference_t<Out2> const&&,
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
using indirectly_writable =
	typename detail::indirectly_writable_impl<Out, T>::type;

#endif

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_INDIRECTLY_WRITABLE_HPP
