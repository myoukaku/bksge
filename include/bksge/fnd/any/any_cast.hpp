/**
 *	@file	any_cast.hpp
 *
 *	@brief	any_cast 関数テンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ANY_ANY_CAST_HPP
#define BKSGE_FND_ANY_ANY_CAST_HPP

#include <bksge/fnd/any/config.hpp>

#if defined(BKSGE_USE_STD_ANY)

namespace bksge
{

using std::any_cast;

}	// namespace bksge

#else

#include <bksge/fnd/any/any.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename ValueType>
BKSGE_NODISCARD ValueType any_cast(any const& a);

template <typename ValueType>
BKSGE_NODISCARD ValueType any_cast(any& a);

template <typename ValueType>
BKSGE_NODISCARD ValueType any_cast(any&& a);

template <typename ValueType>
BKSGE_NODISCARD ValueType const* any_cast(any const* a) BKSGE_NOEXCEPT;

template <typename ValueType>
BKSGE_NODISCARD ValueType* any_cast(any* a) BKSGE_NOEXCEPT;

}	// namespace bksge

#include <bksge/fnd/any/inl/any_cast_inl.hpp>

#endif

#endif // BKSGE_FND_ANY_ANY_CAST_HPP
