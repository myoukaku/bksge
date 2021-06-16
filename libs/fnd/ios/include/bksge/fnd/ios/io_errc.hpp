/**
 *	@file	io_errc.hpp
 *
 *	@brief	io_errc の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_IOS_IO_ERRC_HPP
#define BKSGE_FND_IOS_IO_ERRC_HPP

#include <bksge/fnd/system_error/config.hpp>

#if defined(BKSGE_USE_STD_SYSTEM_ERROR)

#include <ios>

namespace bksge
{

using std::io_errc;

}	// namespace bksge

#else

namespace bksge
{

enum class io_errc
{
	stream = 1
};

}	// namespace bksge

#include <bksge/fnd/ios/iostream_category.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/system_error/is_error_code_enum.hpp>
#include <bksge/fnd/system_error/error_code.hpp>
#include <bksge/fnd/system_error/error_condition.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <>
struct is_error_code_enum<io_errc> : public bksge::true_type {};

BKSGE_NODISCARD inline bksge::error_code
make_error_code(io_errc e) noexcept
{
	return bksge::error_code(
		static_cast<int>(e), bksge::iostream_category());
}

BKSGE_NODISCARD inline bksge::error_condition
make_error_condition(io_errc e) noexcept
{
	return bksge::error_condition(
		static_cast<int>(e), bksge::iostream_category());
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_IOS_IO_ERRC_HPP
