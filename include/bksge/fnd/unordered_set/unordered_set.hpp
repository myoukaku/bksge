/**
 *	@file	unordered_set.hpp
 *
 *	@brief	unordered_set の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNORDERED_SET_UNORDERED_SET_HPP
#define BKSGE_FND_UNORDERED_SET_UNORDERED_SET_HPP

#include <unordered_set>

namespace bksge
{

using std::unordered_set;

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

template <typename Key, typename Hash, typename CPred, typename Alloc, typename Predicate>
inline BKSGE_CXX14_CONSTEXPR
typename unordered_set<Key, Hash, CPred, Alloc>::size_type
erase_if(unordered_set<Key, Hash, CPred, Alloc>& c, Predicate pred)
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

#endif // BKSGE_FND_UNORDERED_SET_UNORDERED_SET_HPP
