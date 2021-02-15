﻿/**
 *	@file	forward_list.hpp
 *
 *	@brief	forward_list の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FORWARD_LIST_FORWARD_LIST_HPP
#define BKSGE_FND_FORWARD_LIST_FORWARD_LIST_HPP

#include <forward_list>

namespace bksge
{

using std::forward_list;

}	// namespace bksge

#if defined(__cpp_lib_erase_if) && (__cpp_lib_erase_if >= 202002)

namespace bksge
{

using std::erase;
using std::erase_if;

}	// namespace bksge

#else	// __cpp_lib_erase_if

#include <bksge/fnd/iterator/distance.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename T, typename Alloc, typename Predicate>
inline BKSGE_CXX14_CONSTEXPR
typename forward_list<T, Alloc>::size_type
erase_if(forward_list<T, Alloc>& c, Predicate pred)
{
#if defined(__cpp_lib_list_remove_return_type) && (__cpp_lib_list_remove_return_type >= 201806)
	return c.remove_if(pred);
#else
	auto const sz = bksge::distance(c.begin(), c.end());
	c.remove_if(pred);
	return sz - bksge::distance(c.begin(), c.end());
#endif
}

template <typename T, typename Alloc, typename U>
inline BKSGE_CXX14_CONSTEXPR
typename forward_list<T, Alloc>::size_type
erase(forward_list<T, Alloc>& c, U const& value)
{
	using elem_type = typename forward_list<T, Alloc>::value_type;
	return bksge::erase_if(c, [&](elem_type& elem) { return elem == value; });
}

}	// namespace bksge

#endif	// __cpp_lib_erase_if

#endif // BKSGE_FND_FORWARD_LIST_FORWARD_LIST_HPP
