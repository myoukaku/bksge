/**
 *	@file	unordered_map.hpp
 *
 *	@brief	unordered_map の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNORDERED_MAP_UNORDERED_MAP_HPP
#define BKSGE_FND_UNORDERED_MAP_UNORDERED_MAP_HPP

#include <unordered_map>

namespace bksge
{

using std::unordered_map;

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

template <typename Key, typename T, typename Hash, typename CPred, typename Alloc, typename Predicate>
inline BKSGE_CXX14_CONSTEXPR
typename unordered_map<Key, T, Hash, CPred, Alloc>::size_type
erase_if(unordered_map<Key, T, Hash, CPred, Alloc>& c, Predicate pred)
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

#endif // BKSGE_FND_UNORDERED_MAP_UNORDERED_MAP_HPP
