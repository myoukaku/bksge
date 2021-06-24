/**
 *	@file	bad_any_cast_inl.hpp
 *
 *	@brief	bad_any_cast クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ANY_INL_BAD_ANY_CAST_INL_HPP
#define BKSGE_FND_ANY_INL_BAD_ANY_CAST_INL_HPP

#include <bksge/fnd/any/bad_any_cast.hpp>
#include <bksge/fnd/config.hpp>
#include <cstdlib>

namespace bksge
{

inline char const* bad_any_cast::what() const BKSGE_NOEXCEPT
{
	return "bad any_cast";
}

BKSGE_NORETURN inline void throw_bad_any_cast()
{
#if !defined(BKSGE_NO_EXCEPTIONS)
	throw bksge::bad_any_cast();
#else
	std::abort();
#endif
}

}	// namespace bksge

#endif // BKSGE_FND_ANY_INL_BAD_ANY_CAST_INL_HPP
