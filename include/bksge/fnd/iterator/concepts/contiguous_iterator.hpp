/**
 *	@file	contiguous_iterator.hpp
 *
 *	@brief	contiguous_iterator の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_CONTIGUOUS_ITERATOR_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_CONTIGUOUS_ITERATOR_HPP

#include <bksge/fnd/iterator/concepts/random_access_iterator.hpp>
#include <bksge/fnd/iterator/concepts/detail/iter_concept.hpp>
#include <bksge/fnd/iterator/iter_reference_t.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/iterator/tag.hpp>
#include <bksge/fnd/concepts/derived_from.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/type_traits/is_lvalue_reference.hpp>
#include <bksge/fnd/type_traits/remove_cvref.hpp>
#include <bksge/fnd/type_traits/add_pointer.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/memory/to_address.hpp>
#include <bksge/fnd/config.hpp>
#include <memory>	// to_address

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept contiguous_iterator =
	bksge::random_access_iterator<Iter> &&
	bksge::derived_from<bksge::detail::iter_concept<Iter>, bksge::contiguous_iterator_tag> &&
	bksge::is_lvalue_reference<bksge::iter_reference_t<Iter>>::value &&
	bksge::same_as<bksge::iter_value_t<Iter>, bksge::remove_cvref_t<bksge::iter_reference_t<Iter>>> &&
	requires(Iter const& i)
	{
		{ bksge::to_address(i) } -> bksge::same_as<bksge::add_pointer_t<bksge::iter_reference_t<Iter>>>;
	};

#endif

namespace detail
{

template <typename Iter>
struct contiguous_iterator_t_impl
{
private:
	template <typename I2,
		typename R = bksge::iter_reference_t<I2>,
		typename = bksge::enable_if_t<
			bksge::derived_from_t<
				bksge::detail::iter_concept<I2>,
				bksge::contiguous_iterator_tag
			>::value
		>
	>
	static auto test(int) -> bksge::conjunction<
		bksge::random_access_iterator_t<I2>,
		bksge::is_lvalue_reference<R>,
		bksge::same_as_t<bksge::iter_value_t<I2>, bksge::remove_cvref_t<R>>,
		bksge::same_as_t<
			decltype(bksge::to_address(bksge::declval<I2 const&>())),
			bksge::add_pointer_t<R>
		>
	>;

	template <typename I2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace detail

template <typename Iter>
using contiguous_iterator_t =
	typename detail::contiguous_iterator_t_impl<Iter>::type;

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_CONTIGUOUS_ITERATOR_HPP
