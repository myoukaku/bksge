/**
 *	@file	multimap.hpp
 *
 *	@brief	multimap の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_MAP_MULTIMAP_HPP
#define BKSGE_FND_MAP_MULTIMAP_HPP

#include <map>

namespace bksge
{

using std::multimap;

}	// namespace bksge

#if defined(__cpp_lib_erase_if) && (__cpp_lib_erase_if >= 202002)

namespace bksge
{

using std::erase_if;

}	// namespace bksge

#else	// __cpp_lib_erase_if

#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename Key, typename T, typename Compare, typename Alloc, typename Predicate>
inline BKSGE_CXX14_CONSTEXPR
typename multimap<Key, T, Compare, Alloc>::size_type
erase_if(multimap<Key, T, Compare, Alloc>& c, Predicate pred)
{
	auto const sz = c.size();
	for (auto i = c.begin(), last = c.end(); i != last; )
	{
		if (pred(*i))
		{
			i = c.erase(i);
		}
		else
		{
			++i;
		}
	}
	return sz - c.size();
}

}	// namespace bksge

#endif	// __cpp_lib_erase_if

#endif // BKSGE_FND_MAP_MULTIMAP_HPP
