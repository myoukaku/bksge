/**
 *	@file	iter_with_nested_types.hpp
 *
 *	@brief	iter_with_nested_types の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_ITER_WITH_NESTED_TYPES_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_ITER_WITH_NESTED_TYPES_HPP

#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept iter_with_nested_types =
	requires
	{
		typename Iter::iterator_category;
		typename Iter::value_type;
		typename Iter::difference_type;
		typename Iter::reference;
	};

#endif

namespace iter_with_nested_types_detail
{

template <typename Iter>
struct iter_with_nested_types_t_impl
{
private:
	template <typename I2,
		typename = typename I2::iterator_category,
		typename = typename I2::value_type,
		typename = typename I2::difference_type,
		typename = typename I2::reference
	>
	static auto test(int) -> bksge::true_type;

	template <typename I2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace iter_with_nested_types_detail

template <typename Iter>
using iter_with_nested_types_t =
	typename iter_with_nested_types_detail::iter_with_nested_types_t_impl<Iter>::type;

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_ITER_WITH_NESTED_TYPES_HPP
