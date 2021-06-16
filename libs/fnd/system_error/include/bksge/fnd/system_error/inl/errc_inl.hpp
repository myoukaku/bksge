/**
 *	@file	errc_inl.hpp
 *
 *	@brief	errc の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SYSTEM_ERROR_INL_ERRC_INL_HPP
#define BKSGE_FND_SYSTEM_ERROR_INL_ERRC_INL_HPP

#include <bksge/fnd/system_error/errc.hpp>
#include <bksge/fnd/system_error/error_condition.hpp>
#include <bksge/fnd/system_error/error_code.hpp>
#include <bksge/fnd/system_error/generic_category.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

inline error_condition
make_error_condition(errc er) BKSGE_NOEXCEPT
{
	return error_condition(static_cast<int>(er), generic_category());
}

inline error_code
make_error_code(errc er) BKSGE_NOEXCEPT
{
	return error_code(static_cast<int>(er), generic_category());
}

}	// namespace bksge

#endif // BKSGE_FND_SYSTEM_ERROR_INL_ERRC_INL_HPP
