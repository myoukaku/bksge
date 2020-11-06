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
#include <bksge/fnd/type_traits/enable_if.hpp>
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
		typename V   = bksge::iter_value_t<U>,
		typename R   = bksge::iter_reference_t<U>,
		typename RR  = bksge::iter_rvalue_reference_t<U>,
		typename RC  = bksge::iter_reference_t<U const>,
		typename RRC = bksge::iter_rvalue_reference_t<U const>,
		typename = bksge::enable_if_t<bksge::same_as<RC, R>::value>,
		typename = bksge::enable_if_t<bksge::same_as<RRC, RR>::value>,
		typename = bksge::enable_if_t<bksge::common_reference_with<R&&, V&>::value>,
		typename = bksge::enable_if_t<bksge::common_reference_with<R&&, RR&&>::value>,
		typename = bksge::enable_if_t<bksge::common_reference_with<RR&&, V const&>::value>
	>
	static auto test(int) -> bksge::true_type;

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
