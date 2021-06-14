/**
 *	@file	indirectly_copyable.hpp
 *
 *	@brief	indirectly_copyable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_INDIRECTLY_COPYABLE_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_INDIRECTLY_COPYABLE_HPP

#include <bksge/fnd/iterator/concepts/indirectly_readable.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_writable.hpp>
#include <bksge/fnd/iterator/iter_reference_t.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename In, typename Out>
concept indirectly_copyable =
	bksge::indirectly_readable<In> &&
	bksge::indirectly_writable<Out, bksge::iter_reference_t<In>>;

#else

namespace detail
{

template <typename In, typename Out>
struct indirectly_copyable_impl
{
private:
	template <typename I, typename O,
		typename = bksge::enable_if_t<bksge::indirectly_readable<I>::value>,
		typename R = bksge::iter_reference_t<I>,
		typename = bksge::enable_if_t<bksge::indirectly_writable<O, R>::value>
	>
	static auto test(int) -> bksge::true_type;

	template <typename I, typename O>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<In, Out>(0));
};

}	// namespace detail

template <typename In, typename Out>
using indirectly_copyable =
	typename detail::indirectly_copyable_impl<In, Out>::type;

#endif

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_INDIRECTLY_COPYABLE_HPP
