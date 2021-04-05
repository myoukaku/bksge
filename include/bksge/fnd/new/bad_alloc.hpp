/**
 *	@file	bad_alloc.hpp
 *
 *	@brief	bad_alloc の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_NEW_BAD_ALLOC_HPP
#define BKSGE_FND_NEW_BAD_ALLOC_HPP

#include <bksge/fnd/config.hpp>
#include <new>

namespace bksge
{

using std::bad_alloc;

BKSGE_NORETURN
void throw_bad_alloc(void);

}	// namespace bksge

#if defined(BKSGE_HEADER_ONLY)
#include <bksge/fnd/new/inl/bad_alloc_inl.hpp>
#endif

#endif // BKSGE_FND_NEW_BAD_ALLOC_HPP
