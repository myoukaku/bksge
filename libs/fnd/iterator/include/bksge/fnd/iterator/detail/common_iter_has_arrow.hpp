/**
 *	@file	common_iter_has_arrow.hpp
 *
 *	@brief	common_iter_has_arrow の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_DETAIL_COMMON_ITER_HAS_ARROW_HPP
#define BKSGE_FND_ITERATOR_DETAIL_COMMON_ITER_HAS_ARROW_HPP

#include <bksge/fnd/iterator/concepts/indirectly_readable.hpp>
#include <bksge/fnd/iterator/iter_reference_t.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/concepts/constructible_from.hpp>
#include <bksge/fnd/type_traits/is_reference.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/disjunction.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename It>
concept common_iter_has_arrow =
	bksge::indirectly_readable<It const> &&
	(
		requires(It const& it) { it.operator->(); } ||
		bksge::is_reference<bksge::iter_reference_t<It>>::value ||
		bksge::constructible_from<bksge::iter_value_t<It>, bksge::iter_reference_t<It>>
	);

template <typename It>
using is_common_iter_has_arrow = bksge::bool_constant<common_iter_has_arrow<It>>;

#else

template <typename It>
struct common_iter_has_arrow_impl
{
private:
	template <typename U,
		typename = decltype(std::declval<U const&>().operator->())
	>
	static auto test(int) -> bksge::true_type;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = bksge::conjunction<
		bksge::indirectly_readable<It const>,
		bksge::disjunction<
			decltype(test<It>(0)),
			bksge::is_reference<bksge::iter_reference_t<It>>,
			bksge::constructible_from<bksge::iter_value_t<It>, bksge::iter_reference_t<It>>
		>
	>;
};

template <typename It>
using common_iter_has_arrow = typename common_iter_has_arrow_impl<It>::type;

template <typename It>
using is_common_iter_has_arrow = common_iter_has_arrow<It>;

#endif

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_DETAIL_COMMON_ITER_HAS_ARROW_HPP
