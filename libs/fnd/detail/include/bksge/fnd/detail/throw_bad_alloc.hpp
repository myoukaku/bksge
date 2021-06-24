/**
 *	@file	throw_bad_alloc.hpp
 *
 *	@brief	throw_bad_alloc の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_DETAIL_THROW_BAD_ALLOC_HPP
#define BKSGE_FND_DETAIL_THROW_BAD_ALLOC_HPP

#include <bksge/fnd/config.hpp>
#include <cstdlib>
#include <new>

namespace bksge
{

namespace detail
{

BKSGE_NORETURN inline
void throw_bad_alloc(void)
{
#if !defined(BKSGE_NO_EXCEPTIONS)
	throw std::bad_alloc();
#else
	std::abort();
#endif
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_DETAIL_THROW_BAD_ALLOC_HPP
