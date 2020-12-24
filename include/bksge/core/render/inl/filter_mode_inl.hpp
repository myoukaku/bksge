/**
 *	@file	filter_mode_inl.hpp
 *
 *	@brief	FilterMode の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_FILTER_MODE_INL_HPP
#define BKSGE_CORE_RENDER_INL_FILTER_MODE_INL_HPP

#include <bksge/core/render/filter_mode.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE bksge::string
to_string(FilterMode const& filter_mode)
{
#define BKSGE_CORE_RENDER_FILTER_MODE_KVP(x)	case x: return #x

	switch (filter_mode)
	{
		BKSGE_CORE_RENDER_FILTER_MODE_KVP(FilterMode::kNearest);
		BKSGE_CORE_RENDER_FILTER_MODE_KVP(FilterMode::kLinear);
	}

	return "";

#undef BKSGE_CORE_RENDER_FILTER_MODE_KVP
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_FILTER_MODE_INL_HPP
