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
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE bksge::string
to_string(BorderColor const& border_color)
{
#define BKSGE_CORE_RENDER_BORDER_COLOR_KVP(x)	case x: return #x

	switch (border_color)
	{
		BKSGE_CORE_RENDER_BORDER_COLOR_KVP(BorderColor::kTransparentBlack);
		BKSGE_CORE_RENDER_BORDER_COLOR_KVP(BorderColor::kOpaqueBlack);
		BKSGE_CORE_RENDER_BORDER_COLOR_KVP(BorderColor::kOpaqueWhite);
	}

	return "";

#undef BKSGE_CORE_RENDER_BORDER_COLOR_KVP
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_BORDER_COLOR_INL_HPP
