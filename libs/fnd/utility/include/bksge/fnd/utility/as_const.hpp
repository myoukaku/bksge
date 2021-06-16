/**
 *	@file	as_const.hpp
 *
 *	@brief	as_const を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UTILITY_AS_CONST_HPP
#define BKSGE_FND_UTILITY_AS_CONST_HPP

#include <utility>

#if defined(__cpp_lib_as_const) && (__cpp_lib_as_const >= 201510)

namespace bksge
{

using std::as_const;

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/add_const.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *
 */
template <typename T>
inline BKSGE_CONSTEXPR add_const_t<T>&
as_const(T& t) BKSGE_NOEXCEPT
{
	return t;
}

/**
 *
 */
template <typename T>
void as_const(T const&&) = delete;

}	// namespace bksge

#endif

#endif // BKSGE_FND_UTILITY_AS_CONST_HPP
