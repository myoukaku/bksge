/**
 *	@file	make_optional.hpp
 *
 *	@brief	make_optional の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_OPTIONAL_MAKE_OPTIONAL_HPP
#define BKSGE_FND_OPTIONAL_MAKE_OPTIONAL_HPP

#include <bksge/fnd/optional/config.hpp>

#if defined(BKSGE_USE_STD_OPTIONAL)

#include <optional>

namespace bksge
{

using std::make_optional;

}	// namespace bksge

#else

#include <bksge/fnd/optional/optional.hpp>
#include <bksge/fnd/type_traits/decay.hpp>
#include <bksge/fnd/utility/forward.hpp>

namespace bksge
{

template <typename T>
inline BKSGE_CONSTEXPR optional<bksge::decay_t<T>>
make_optional(T&& t)
{
	return optional<bksge::decay_t<T>> { bksge::forward<T>(t) };
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_OPTIONAL_MAKE_OPTIONAL_HPP
