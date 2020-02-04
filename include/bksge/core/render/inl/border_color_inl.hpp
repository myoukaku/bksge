/**
 *	@file	border_color_inl.hpp
 *
 *	@brief	BorderColor の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_BORDER_COLOR_INL_HPP
#define BKSGE_CORE_RENDER_INL_BORDER_COLOR_INL_HPP

#include <bksge/core/render/border_color.hpp>
#include <unordered_map>
#include <string>

namespace bksge
{

namespace render
{

BKSGE_INLINE
std::string to_string(BorderColor const& border_color)
{
#define BKSGE_CORE_RENDER_MAKE_BORDER_COLOR_KVP(x)	{ x, #x }

	static std::unordered_map<BorderColor, std::string> const m =
	{
		BKSGE_CORE_RENDER_MAKE_BORDER_COLOR_KVP(BorderColor::kTransparentBlack),
		BKSGE_CORE_RENDER_MAKE_BORDER_COLOR_KVP(BorderColor::kOpaqueBlack),
		BKSGE_CORE_RENDER_MAKE_BORDER_COLOR_KVP(BorderColor::kOpaqueWhite)
	};

	return m.at(border_color);

#undef BKSGE_CORE_RENDER_MAKE_BORDER_COLOR_KVP
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_BORDER_COLOR_INL_HPP
