/**
 *	@file	erase_if.hpp
 *
 *	@brief	erase_if の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STRING_ERASE_IF_HPP
#define BKSGE_FND_STRING_ERASE_IF_HPP

#include <bksge/fnd/string/basic_string.hpp>
#include <bksge/fnd/string/config.hpp>

#if defined(BKSGE_USE_STD_STRING)

#include <string>

namespace bksge
{

using std::erase_if;

}	// namespace bksge

#else

#include <bksge/fnd/algorithm/remove_if.hpp>

namespace bksge
{

template <typename CharT, typename Traits, typename Allocator, typename Predicate>
inline BKSGE_CXX14_CONSTEXPR
typename bksge::basic_string<CharT, Traits, Allocator>::size_type
erase_if(bksge::basic_string<CharT, Traits, Allocator>& str, Predicate pred)
{
	auto const osz = str.size();
	str.erase(bksge::remove_if(str.begin(), str.end(), pred), str.end());
	return osz - str.size();
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_STRING_ERASE_IF_HPP
