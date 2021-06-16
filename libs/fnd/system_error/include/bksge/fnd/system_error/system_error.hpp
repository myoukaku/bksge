/**
 *	@file	system_error.hpp
 *
 *	@brief	system_error の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SYSTEM_ERROR_SYSTEM_ERROR_HPP
#define BKSGE_FND_SYSTEM_ERROR_SYSTEM_ERROR_HPP

#include <bksge/fnd/system_error/config.hpp>

#if defined(BKSGE_USE_STD_SYSTEM_ERROR)

#include <system_error>

namespace bksge
{

using std::system_error;

}	// namespace bksge

#else

#include <bksge/fnd/stdexcept/runtime_error.hpp>
#include <bksge/fnd/string.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

class error_code;
class error_category;

class system_error
	: public bksge::runtime_error
{
public:
	system_error(error_code ec, bksge::string const& what_arg);
	system_error(error_code ec, char const* what_arg);
	system_error(error_code ec);
	system_error(int ev, error_category const& ecat, bksge::string const& what_arg);
	system_error(int ev, error_category const& ecat, char const* what_arg);
	system_error(int ev, error_category const& ecat);
	~system_error() BKSGE_NOEXCEPT;

	error_code const& code() const BKSGE_NOEXCEPT { return m_ec; }

private:
	static bksge::string init(error_code const&, bksge::string);

	error_code m_ec;
};

BKSGE_NORETURN
void throw_system_error(int ev, char const* what_arg);

}	// namespace bksge

#include <bksge/fnd/system_error/inl/system_error_inl.hpp>

#endif

#endif // BKSGE_FND_SYSTEM_ERROR_SYSTEM_ERROR_HPP
