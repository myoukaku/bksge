/**
 *	@file	generic_category.hpp
 *
 *	@brief	generic_category の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SYSTEM_ERROR_GENERIC_CATEGORY_HPP
#define BKSGE_FND_SYSTEM_ERROR_GENERIC_CATEGORY_HPP

#include <bksge/fnd/system_error/config.hpp>

#if defined(BKSGE_USE_STD_SYSTEM_ERROR)

#include <system_error>

namespace bksge
{

using std::generic_category;

}	// namespace bksge

#else

#include <bksge/fnd/config.hpp>

namespace bksge
{

class error_category;
error_category const& generic_category() BKSGE_NOEXCEPT;

}	// namespace bksge

#include <bksge/fnd/system_error/inl/generic_category_inl.hpp>

#endif

#endif // BKSGE_FND_SYSTEM_ERROR_GENERIC_CATEGORY_HPP
