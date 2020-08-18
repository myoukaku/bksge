/**
 *	@file	incrementable.hpp
 *
 *	@brief	incrementable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_INCREMENTABLE_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_INCREMENTABLE_HPP

#include <bksge/fnd/iterator/concepts/weakly_incrementable.hpp>
#include <bksge/fnd/concepts/regular.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept incrementable =
	bksge::regular<Iter> &&
	bksge::weakly_incrementable<Iter> &&
	requires(Iter i) { { i++ } -> bksge::same_as<Iter>; };

template <typename Iter>
using is_incrementable = bksge::bool_constant<incrementable<Iter>>;

#else

namespace detail
{

template <typename Iter>
struct incrementable_impl
{
private:
	template <typename I2>
	static auto test(int) -> bksge::conjunction<
		bksge::regular<I2>,
		bksge::weakly_incrementable<I2>,
		bksge::same_as<decltype(bksge::declval<I2&>()++), I2>
	>;

	template <typename I2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace detail

template <typename Iter>
using incrementable =
	typename detail::incrementable_impl<Iter>::type;

template <typename Iter>
using is_incrementable = incrementable<Iter>;

#endif

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_INCREMENTABLE_HPP
