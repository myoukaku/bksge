/**
 *	@file	to_underlying.hpp
 *
 *	@brief	to_underlying を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UTILITY_TO_UNDERLYING_HPP
#define BKSGE_FND_UTILITY_TO_UNDERLYING_HPP

#include <utility>

#if defined(__cpp_lib_to_underlying) && (__cpp_lib_to_underlying >= 202102)

namespace bksge
{

using std::to_underlying;

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/underlying_type.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@biref	列挙型Tの値を基底型に変換する。
 */
template <typename T>
inline BKSGE_CONSTEXPR bksge::underlying_type_t<T>
to_underlying(T value) BKSGE_NOEXCEPT
{
	return static_cast<bksge::underlying_type_t<T>>(value);
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_UTILITY_TO_UNDERLYING_HPP
