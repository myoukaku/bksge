/**
 *	@file	deque.hpp
 *
 *	@brief	deque の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_DEQUE_DEQUE_HPP
#define BKSGE_FND_DEQUE_DEQUE_HPP

#include <deque>

namespace bksge
{

using std::deque;

}	// namespace bksge

#if defined(__cpp_lib_erase_if) && (__cpp_lib_erase_if >= 202002)

namespace bksge
{

using std::erase;
using std::erase_if;

}	// namespace bksge

#else	// __cpp_lib_erase_if

#include <bksge/fnd/algorithm/remove.hpp>
#include <bksge/fnd/algorithm/remove_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename T, typename Alloc, typename Predicate>
inline BKSGE_CXX14_CONSTEXPR
typename deque<T, Alloc>::size_type
erase_if(deque<T, Alloc>& c, Predicate pred)
{
	auto const sz = c.size();
	c.erase(bksge::remove_if(c.begin(), c.end(), pred), c.end());
	return sz - c.size();
}

template <typename T, typename Alloc, typename U>
inline BKSGE_CXX14_CONSTEXPR
typename deque<T, Alloc>::size_type
erase(deque<T, Alloc>& c, const U& value)
{
	auto const sz = c.size();
	c.erase(bksge::remove(c.begin(), c.end(), value), c.end());
	return sz - c.size();
}

}	// namespace bksge

#endif	// __cpp_lib_erase_if

#endif // BKSGE_FND_DEQUE_DEQUE_HPP
