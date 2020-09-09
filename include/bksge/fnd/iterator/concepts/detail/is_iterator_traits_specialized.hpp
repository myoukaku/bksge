/**
 *	@file	is_iterator_traits_specialized.hpp
 *
 *	@brief	is_iterator_traits_specialized の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_IS_ITERATOR_TRAITS_SPECIALIZED_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_IS_ITERATOR_TRAITS_SPECIALIZED_HPP

namespace bksge
{

namespace detail
{

template <typename Iter>
struct is_iterator_traits_specialized
{
	static const bool value = false;
};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_IS_ITERATOR_TRAITS_SPECIALIZED_HPP
