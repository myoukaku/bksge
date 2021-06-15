/**
 *	@file	erase.hpp
 *
 *	@brief	erase の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STRING_ERASE_HPP
#define BKSGE_FND_STRING_ERASE_HPP

#include <bksge/fnd/string/basic_string.hpp>
#include <bksge/fnd/string/config.hpp>

#if defined(BKSGE_USE_STD_STRING)

#include <string>

namespace bksge
{

using std::erase;

}	// namespace bksge

#else

#include <bksge/fnd/algorithm/remove.hpp>

namespace bksge
{

template <typename CharT, typename Traits, typename Allocator, typename U>
inline BKSGE_CXX14_CONSTEXPR
typename bksge::basic_string<CharT, Traits, Allocator>::size_type
erase(bksge::basic_string<CharT, Traits, Allocator>& str, U const& value)
{
	auto const osz = str.size();
	str.erase(bksge::remove(str.begin(), str.end(), value), str.end());
	return osz - str.size();
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_STRING_ERASE_HPP
