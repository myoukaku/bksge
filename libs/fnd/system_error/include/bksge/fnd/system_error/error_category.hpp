/**
 *	@file	error_category.hpp
 *
 *	@brief	error_category の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SYSTEM_ERROR_ERROR_CATEGORY_HPP
#define BKSGE_FND_SYSTEM_ERROR_ERROR_CATEGORY_HPP

#include <bksge/fnd/system_error/config.hpp>

#if defined(BKSGE_USE_STD_SYSTEM_ERROR)

#include <system_error>

namespace bksge
{

using std::error_category;

}	// namespace bksge

#else

#include <bksge/fnd/compare/strong_ordering.hpp>
#include <bksge/fnd/string.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

class error_condition;
class error_code;

class error_category
{
public:
	BKSGE_CXX14_CONSTEXPR error_category() BKSGE_NOEXCEPT = default;

	virtual ~error_category() BKSGE_NOEXCEPT;

private:
	error_category(error_category const&);// = delete;
	error_category& operator=(error_category const&);// = delete;

public:
	virtual char const* name() const BKSGE_NOEXCEPT = 0;
	virtual error_condition default_error_condition(int ev) const BKSGE_NOEXCEPT;
	virtual bool equivalent(int code, error_condition const& condition) const BKSGE_NOEXCEPT;
	virtual bool equivalent(error_code const& code, int condition) const BKSGE_NOEXCEPT;
	virtual bksge::string message(int ev) const = 0;

	bool operator==(error_category const& rhs) const BKSGE_NOEXCEPT;
#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	bksge::strong_ordering operator<=>(error_category const& rhs) const BKSGE_NOEXCEPT;
#else
	bool operator!=(error_category const& rhs) const BKSGE_NOEXCEPT;
	bool operator< (error_category const& rhs) const BKSGE_NOEXCEPT;
#endif
};

}	// namespace bksge

#include <bksge/fnd/system_error/inl/error_category_inl.hpp>

#endif

#endif // BKSGE_FND_SYSTEM_ERROR_ERROR_CATEGORY_HPP
