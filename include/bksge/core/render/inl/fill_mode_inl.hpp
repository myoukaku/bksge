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
#include <unordered_map>
#include <string>

namespace bksge
{

namespace render
{

BKSGE_INLINE
std::string to_string(FillMode const& fill_mode)
{
#define BKSGE_CORE_RENDER_MAKE_FILL_MODE_KVP(x)	{ x, #x }

	static std::unordered_map<FillMode, std::string> const m =
	{
		BKSGE_CORE_RENDER_MAKE_FILL_MODE_KVP(FillMode::kSolid),
		BKSGE_CORE_RENDER_MAKE_FILL_MODE_KVP(FillMode::kWireframe),
	};

	return m.at(fill_mode);

#undef BKSGE_CORE_RENDER_MAKE_FILL_MODE_KVP
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_FILL_MODE_INL_HPP
