/**
 *	@file	clear_flag_inl.hpp
 *
 *	@brief	ClearFlag の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_CLEAR_FLAG_INL_HPP
#define BKSGE_CORE_RENDER_INL_CLEAR_FLAG_INL_HPP

#include <bksge/core/render/clear_flag.hpp>
#include <bksge/fnd/type_traits/underlying_type.hpp>
#include <bksge/fnd/config.hpp>
#include <unordered_map>
#include <string>

namespace bksge
{

namespace render
{

inline BKSGE_CONSTEXPR ClearFlag
operator|(ClearFlag lhs, ClearFlag rhs) BKSGE_NOEXCEPT
{
	using type = bksge::underlying_type_t<ClearFlag>;
	return ClearFlag(
		static_cast<type>(lhs) |
		static_cast<type>(rhs));
}

inline BKSGE_CONSTEXPR ClearFlag
operator&(ClearFlag lhs, ClearFlag rhs) BKSGE_NOEXCEPT
{
	using type = bksge::underlying_type_t<ClearFlag>;
	return ClearFlag(
		static_cast<type>(lhs) &
		static_cast<type>(rhs));
}

inline BKSGE_CONSTEXPR ClearFlag
operator^(ClearFlag lhs, ClearFlag rhs) BKSGE_NOEXCEPT
{
	using type = bksge::underlying_type_t<ClearFlag>;
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

inline BKSGE_CONSTEXPR bool
Test(ClearFlag lhs, ClearFlag rhs) BKSGE_NOEXCEPT
{
	return (lhs & rhs) != ClearFlag::kNone;
}

inline std::string
to_string(ClearFlag const& clear_flag)
{
#define BKSGE_CORE_RENDER_MAKE_CLEAR_FLAG_KVP(x)	{ x, #x }

	static std::unordered_map<ClearFlag, std::string> const m =
	{
		BKSGE_CORE_RENDER_MAKE_CLEAR_FLAG_KVP(ClearFlag::kNone),
		BKSGE_CORE_RENDER_MAKE_CLEAR_FLAG_KVP(ClearFlag::kColor),
		BKSGE_CORE_RENDER_MAKE_CLEAR_FLAG_KVP(ClearFlag::kDepth),
		BKSGE_CORE_RENDER_MAKE_CLEAR_FLAG_KVP(ClearFlag::kStencil),
		BKSGE_CORE_RENDER_MAKE_CLEAR_FLAG_KVP(ClearFlag::kColor | ClearFlag::kDepth),
		BKSGE_CORE_RENDER_MAKE_CLEAR_FLAG_KVP(ClearFlag::kDepth | ClearFlag::kStencil),
		BKSGE_CORE_RENDER_MAKE_CLEAR_FLAG_KVP(ClearFlag::kColor | ClearFlag::kStencil),
		BKSGE_CORE_RENDER_MAKE_CLEAR_FLAG_KVP(ClearFlag::kAll),
	};

	return m.at(clear_flag);

#undef BKSGE_CORE_RENDER_MAKE_CLEAR_FLAG_KVP
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_CLEAR_FLAG_INL_HPP
