/**
 *	@file	fill_mode_inl.hpp
 *
 *	@brief	FillMode の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_FILL_MODE_INL_HPP
#define BKSGE_CORE_RENDER_INL_FILL_MODE_INL_HPP

#include <bksge/core/render/fill_mode.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE bksge::string
to_string(FillMode const& fill_mode)
{
#define BKSGE_CORE_RENDER_FILL_MODE_KVP(x)	case x: return #x

	switch (fill_mode)
	{
		BKSGE_CORE_RENDER_FILL_MODE_KVP(FillMode::kSolid);
		BKSGE_CORE_RENDER_FILL_MODE_KVP(FillMode::kWireframe);
	}

	return "";

#undef BKSGE_CORE_RENDER_FILL_MODE_KVP
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_FILL_MODE_INL_HPP
