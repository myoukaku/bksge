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
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename In, typename Out>
concept indirectly_copyable =
	bksge::indirectly_readable<In> &&
	bksge::indirectly_writable<Out, bksge::iter_reference_t<In>>;

#endif

namespace detail
{

template <typename In, typename Out>
struct indirectly_copyable_t_impl
{
private:
	template <typename I, typename O>
	static auto test(int) -> bksge::conjunction<
		bksge::indirectly_readable_t<I>,
		bksge::indirectly_writable_t<O, bksge::iter_reference_t<I>>
	>;

	template <typename I, typename O>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<In, Out>(0));
};

}	// namespace detail

template <typename In, typename Out>
using indirectly_copyable_t =
	typename detail::indirectly_copyable_t_impl<In, Out>::type;

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_INDIRECTLY_COPYABLE_HPP
