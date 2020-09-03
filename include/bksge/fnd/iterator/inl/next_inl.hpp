﻿/**
 *	@file	next_inl.hpp
 *
 *	@brief	next 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_INL_NEXT_INL_HPP
#define BKSGE_FND_ITERATOR_INL_NEXT_INL_HPP

#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/iterator/advance.hpp>
#include <bksge/fnd/iterator/iterator_category.hpp>
#include <bksge/fnd/iterator/tag.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename InputIterator, typename Distance>
inline BKSGE_CXX14_CONSTEXPR InputIterator
next_impl(InputIterator it, Distance n, bksge::input_iterator_tag*)
{
	bksge::advance(it, n);
	return it;
}

template <typename RandomAccessIterator, typename Distance>
inline BKSGE_CONSTEXPR RandomAccessIterator
next_impl(RandomAccessIterator const& it, Distance n, bksge::random_access_iterator_tag*)
{
	return it + n;
}

}	// namespace detail

template <typename InputIterator, typename Distance>
inline BKSGE_CONSTEXPR InputIterator
next(InputIterator const& it, Distance n)
{
	using Category = bksge::iterator_category<InputIterator>*;
	return detail::next_impl(it, n, Category());
}

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_INL_NEXT_INL_HPP
