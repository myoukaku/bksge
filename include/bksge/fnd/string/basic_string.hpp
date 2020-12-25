/**
 *	@file	basic_string.hpp
 *
 *	@brief	basic_string の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STRING_BASIC_STRING_HPP
#define BKSGE_FND_STRING_BASIC_STRING_HPP

#include <bksge/fnd/string/config.hpp>

#if defined(BKSGE_USE_STD_STRING)

#include <string>

namespace bksge
{

using std::basic_string;

}	// namespace bksge

#else

// TODO

#endif

#include <bksge/fnd/functional/config.hpp>

#if !defined(BKSGE_USE_STD_STRING) || !defined(BKSGE_USE_STD_HASH)

#include <bksge/fnd/functional/hash.hpp>
#include <bksge/fnd/hash_functions/murmur_hash_3.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>

namespace BKSGE_HASH_NAMESPACE
{

template <typename T>
struct hash<bksge::basic_string<T>>
{
	BKSGE_CXX14_CONSTEXPR bksge::size_t
	operator()(bksge::basic_string<T> const& arg) const BKSGE_NOEXCEPT
	{
		return bksge::murmur_hash_3{}(arg.data(), arg.length());
	}
};

}	// namespace BKSGE_HASH_NAMESPACE

#endif

#endif // BKSGE_FND_STRING_BASIC_STRING_HPP
