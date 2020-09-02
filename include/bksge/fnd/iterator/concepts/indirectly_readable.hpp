/**
 *	@file	indirectly_readable.hpp
 *
 *	@brief	indirectly_readable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_INDIRECTLY_READABLE_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_INDIRECTLY_READABLE_HPP

#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/iterator/iter_reference_t.hpp>
#include <bksge/fnd/iterator/iter_rvalue_reference_t.hpp>
#include <bksge/fnd/iterator/ranges/iter_move.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/concepts/common_reference_with.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/remove_cvref.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

namespace detail
{

template <typename In>
concept indirectly_readable_impl =
	requires
	{
		typename bksge::iter_value_t<In>;
		typename bksge::iter_reference_t<In>;
		typename bksge::iter_rvalue_reference_t<In>;
		requires bksge::same_as<bksge::iter_reference_t<In const>, bksge::iter_reference_t<In>>;
		requires bksge::same_as<bksge::iter_rvalue_reference_t<In const>, bksge::iter_rvalue_reference_t<In>>;
	} &&
	bksge::common_reference_with<bksge::iter_reference_t<In>&&, bksge::iter_value_t<In>&> &&
	bksge::common_reference_with<bksge::iter_reference_t<In>&&, bksge::iter_rvalue_reference_t<In>&&> &&
	bksge::common_reference_with<bksge::iter_rvalue_reference_t<In>&&, bksge::iter_value_t<In> const&>;

}	// namespace detail

template <typename In>
concept indirectly_readable =
	detail::indirectly_readable_impl<bksge::remove_cvref_t<In>>;

template <typename In>
using is_indirectly_readable = bksge::bool_constant<indirectly_readable<In>>;

#else

namespace detail
{

template <typename In>
struct indirectly_readable_impl
{
private:
	template <typename U,
		typename IterValue = bksge::iter_value_t<U>,
		typename IterRef   = bksge::iter_reference_t<U>,
		typename IterRVRef = bksge::iter_rvalue_reference_t<U>
	>
	static auto test(int) -> bksge::conjunction<
		bksge::same_as<bksge::iter_reference_t<U const>, IterRef>,
		bksge::same_as<bksge::iter_rvalue_reference_t<U const>, IterRVRef>,
		bksge::common_reference_with<IterRef&&, IterValue&>,
		bksge::common_reference_with<IterRef&&, IterRVRef&&>,
		bksge::common_reference_with<IterRVRef&&, IterValue const&>
	>;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<In>(0));
};

}	// namespace detail

template <typename In>
using indirectly_readable =
	typename detail::indirectly_readable_impl<bksge::remove_cvref_t<In>>::type;

template <typename In>
using is_indirectly_readable = indirectly_readable<In>;

#endif

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_INDIRECTLY_READABLE_HPP
