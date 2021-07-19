/**
 *	@file	identity.hpp
 *
 *	@brief	identity クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FUNCTIONAL_IDENTITY_HPP
#define BKSGE_FND_FUNCTIONAL_IDENTITY_HPP

#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

struct identity
{
	template <typename T>
	BKSGE_CONSTEXPR T&& operator()(T&& t) const BKSGE_NOEXCEPT
	{
		return std::forward<T>(t);
	}

	using is_transparent = void;
};

}	// namespace bksge

#endif // BKSGE_FND_FUNCTIONAL_IDENTITY_HPP
