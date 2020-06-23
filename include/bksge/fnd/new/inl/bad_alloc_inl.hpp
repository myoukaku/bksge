/**
 *	@file	bad_alloc_inl.hpp
 *
 *	@brief	bad_alloc の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_NEW_INL_BAD_ALLOC_INL_HPP
#define BKSGE_FND_NEW_INL_BAD_ALLOC_INL_HPP

#include <bksge/fnd/new/bad_alloc.hpp>
#include <bksge/fnd/config.hpp>
#include <cstdlib>

namespace bksge
{

BKSGE_NORETURN BKSGE_INLINE
void throw_bad_alloc(void)
{
#if !defined(BKSGE_NO_EXCEPTIONS)
	throw bksge::bad_alloc();
#else
	std::abort();
#endif
}

}	// namespace bksge

#endif // BKSGE_FND_NEW_INL_BAD_ALLOC_INL_HPP
