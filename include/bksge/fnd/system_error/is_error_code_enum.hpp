/**
 *	@file	is_error_code_enum.hpp
 *
 *	@brief	is_error_code_enum の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SYSTEM_ERROR_IS_ERROR_CODE_ENUM_HPP
#define BKSGE_FND_SYSTEM_ERROR_IS_ERROR_CODE_ENUM_HPP

#include <bksge/fnd/system_error/config.hpp>

#if defined(BKSGE_USE_STD_SYSTEM_ERROR)

#include <system_error>

namespace bksge
{

#define BKSGE_IS_ERROR_CODE_ENUM_NAMESPACE std

using std::is_error_code_enum;

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/bool_constant.hpp>

namespace bksge
{

#define BKSGE_IS_ERROR_CODE_ENUM_NAMESPACE bksge

template <typename T>
struct is_error_code_enum
	: public bksge::false_type {};

}	// namespace bksge

#endif

#endif // BKSGE_FND_SYSTEM_ERROR_IS_ERROR_CODE_ENUM_HPP
