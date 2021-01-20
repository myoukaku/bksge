/**
 *	@file	bad_any_cast.hpp
 *
 *	@brief	bad_any_cast クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ANY_BAD_ANY_CAST_HPP
#define BKSGE_FND_ANY_BAD_ANY_CAST_HPP

#include <bksge/fnd/any/config.hpp>

#if defined(BKSGE_USE_STD_ANY)

namespace bksge
{

using std::bad_any_cast;

}	// namespace bksge

#else

#include <bksge/fnd/config.hpp>
#include <typeinfo>	// bad_cast

namespace bksge
{

class bad_any_cast : public std::bad_cast
{
public:
	virtual char const* what() const BKSGE_NOEXCEPT;
};

BKSGE_NORETURN void throw_bad_any_cast();

}	// namespace bksge

#include <bksge/fnd/any/inl/bad_any_cast_inl.hpp>

#endif

#endif // BKSGE_FND_ANY_BAD_ANY_CAST_HPP
