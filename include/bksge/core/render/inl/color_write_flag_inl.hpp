/**
 *	@file	color_write_flag_inl.hpp
 *
 *	@brief	ColorWriteFlag の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_COLOR_WRITE_FLAG_INL_HPP
#define BKSGE_CORE_RENDER_INL_COLOR_WRITE_FLAG_INL_HPP

#include <bksge/core/render/color_write_flag.hpp>
#include <bksge/fnd/type_traits/underlying_type.hpp>
#include <bksge/fnd/config.hpp>
#include <string>
#include <utility>

namespace bksge
{

namespace render
{

inline BKSGE_CONSTEXPR ColorWriteFlag
operator|(ColorWriteFlag lhs, ColorWriteFlag rhs) BKSGE_NOEXCEPT
{
	using type = bksge::underlying_type_t<ColorWriteFlag>;
	return ColorWriteFlag(
		static_cast<type>(lhs) |
		static_cast<type>(rhs));
}

inline BKSGE_CONSTEXPR ColorWriteFlag
operator&(ColorWriteFlag lhs, ColorWriteFlag rhs) BKSGE_NOEXCEPT
{
	using type = bksge::underlying_type_t<ColorWriteFlag>;
	return ColorWriteFlag(
		static_cast<type>(lhs) &
		static_cast<type>(rhs));
}

inline BKSGE_CONSTEXPR ColorWriteFlag
operator^(ColorWriteFlag lhs, ColorWriteFlag rhs) BKSGE_NOEXCEPT
{
	using type = bksge::underlying_type_t<ColorWriteFlag>;
	return ColorWriteFlag(
		static_cast<type>(lhs) ^
		static_cast<type>(rhs));
}

inline BKSGE_CXX14_CONSTEXPR ColorWriteFlag&
operator|=(ColorWriteFlag& lhs, ColorWriteFlag rhs) BKSGE_NOEXCEPT
{
	return lhs = lhs | rhs;
}

inline BKSGE_CXX14_CONSTEXPR ColorWriteFlag&
operator&=(ColorWriteFlag& lhs, ColorWriteFlag rhs) BKSGE_NOEXCEPT
{
	return lhs = lhs & rhs;
}

inline BKSGE_CXX14_CONSTEXPR ColorWriteFlag&
operator^=(ColorWriteFlag& lhs, ColorWriteFlag rhs) BKSGE_NOEXCEPT
{
	return lhs = lhs ^ rhs;
}

inline BKSGE_CONSTEXPR bool
Test(ColorWriteFlag lhs, ColorWriteFlag rhs) BKSGE_NOEXCEPT
{
	return (lhs & rhs) != ColorWriteFlag::kNone;
}

inline std::string
to_string(ColorWriteFlag const& color_write_flag)
{
	if (color_write_flag == ColorWriteFlag::kAll)
	{
		return "ColorWriteFlag::kAll";
	}
	if (color_write_flag == ColorWriteFlag::kNone)
	{
		return "ColorWriteFlag::kNone";
	}

#define BKSGE_CORE_RENDER_MAKE_COLOR_WRITE_FLAG_KVP(x)	{ x, #x }

	static std::pair<ColorWriteFlag, std::string> const tbl[] =
	{
		BKSGE_CORE_RENDER_MAKE_COLOR_WRITE_FLAG_KVP(ColorWriteFlag::kRed),
		BKSGE_CORE_RENDER_MAKE_COLOR_WRITE_FLAG_KVP(ColorWriteFlag::kGreen),
		BKSGE_CORE_RENDER_MAKE_COLOR_WRITE_FLAG_KVP(ColorWriteFlag::kBlue),
		BKSGE_CORE_RENDER_MAKE_COLOR_WRITE_FLAG_KVP(ColorWriteFlag::kAlpha),
	};

#undef BKSGE_CORE_RENDER_MAKE_COLOR_WRITE_FLAG_KVP

	std::string result;
	for (auto p : tbl)
	{
		if ((color_write_flag & p.first) != ColorWriteFlag::kNone)
		{
			if (!result.empty())
			{
				result += " | ";
			}

			result += p.second;
		}
	}

	return result;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_COLOR_WRITE_FLAG_INL_HPP
