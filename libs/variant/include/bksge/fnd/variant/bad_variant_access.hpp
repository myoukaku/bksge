/**
 *	@file	bad_variant_access.hpp
 *
 *	@brief	bad_variant_access の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_BAD_VARIANT_ACCESS_HPP
#define BKSGE_FND_VARIANT_BAD_VARIANT_ACCESS_HPP

#include <bksge/fnd/variant/config.hpp>

#if defined(BKSGE_USE_STD_VARIANT)

namespace bksge
{

using std::bad_variant_access;

}	// namespace bksge

#else

#include <bksge/fnd/exception/exception.hpp>
#include <bksge/fnd/config.hpp>
#if defined(BKSGE_NO_EXCEPTIONS)
#include <bksge/fnd/cstdlib/abort.hpp>
#endif

namespace bksge
{

/**
 *	@brief	variantの無効な値にアクセスしたときに投げられる例外
 *
 *	bad_variant_access は以下の状況の時に投げられる例外である
 *	・get(variant)を有効でないインデックスや型で呼び出した
 *	・valueless_by_exception が true の variant に対して visit を呼び出した
 */
class bad_variant_access : public bksge::exception
{
public:
	bad_variant_access() BKSGE_NOEXCEPT {}

	char const* what() const BKSGE_NOEXCEPT override
	{
		return m_reason;
	}

private:
	bad_variant_access(char const* reason) BKSGE_NOEXCEPT
		: m_reason(reason) {}

	// Must point to a string with static storage duration:
	char const* m_reason = "bad variant access";

	friend void throw_bad_variant_access(char const* what);
};

/*BKSGE_NORETURN*/ inline void
throw_bad_variant_access(char const* what)
{
#if !defined(BKSGE_NO_EXCEPTIONS)
	throw bksge::bad_variant_access(what);
#else
	bksge::abort();
#endif
}

/*BKSGE_NORETURN*/ inline void
throw_bad_variant_access(bool valueless)
{
	if (valueless) /*[[__unlikely__]]*/
	{
		throw_bad_variant_access("bksge::get: variant is valueless");
	}
	else
	{
		throw_bad_variant_access("bksge::get: wrong index for variant");
	}
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_VARIANT_BAD_VARIANT_ACCESS_HPP
