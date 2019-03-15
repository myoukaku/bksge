/**
 *	@file	clear_flag_inl.hpp
 *
 *	@brief	ClearFlag の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_INL_CLEAR_FLAG_INL_HPP
#define BKSGE_RENDER_INL_CLEAR_FLAG_INL_HPP

#include <bksge/render/clear_flag.hpp>
#include <bksge/config.hpp>
#include <type_traits>

namespace bksge
{

namespace render
{

inline BKSGE_CONSTEXPR ClearFlag
operator|(ClearFlag lhs, ClearFlag rhs) BKSGE_NOEXCEPT
{
	using type =
		typename std::underlying_type<ClearFlag>::type;
	return ClearFlag(
		static_cast<type>(lhs) |
		static_cast<type>(rhs));
}

inline BKSGE_CONSTEXPR ClearFlag
operator&(ClearFlag lhs, ClearFlag rhs) BKSGE_NOEXCEPT
{
	using type =
		typename std::underlying_type<ClearFlag>::type;
	return ClearFlag(
		static_cast<type>(lhs) &
		static_cast<type>(rhs));
}

inline BKSGE_CONSTEXPR ClearFlag
operator^(ClearFlag lhs, ClearFlag rhs) BKSGE_NOEXCEPT
{
	using type =
		typename std::underlying_type<ClearFlag>::type;
	return ClearFlag(
		static_cast<type>(lhs) ^
		static_cast<type>(rhs));
}

inline BKSGE_CXX14_CONSTEXPR ClearFlag&
operator|=(ClearFlag& lhs, ClearFlag rhs) BKSGE_NOEXCEPT
{
	return lhs = lhs | rhs;
}

inline BKSGE_CXX14_CONSTEXPR ClearFlag&
operator&=(ClearFlag& lhs, ClearFlag rhs) BKSGE_NOEXCEPT
{
	return lhs = lhs & rhs;
}

inline BKSGE_CXX14_CONSTEXPR ClearFlag&
operator^=(ClearFlag& lhs, ClearFlag rhs) BKSGE_NOEXCEPT
{
	return lhs = lhs ^ rhs;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_INL_CLEAR_FLAG_INL_HPP
