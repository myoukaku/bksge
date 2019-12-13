/**
 *	@file	cull_mode_inl.hpp
 *
 *	@brief	CullMode の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_CULL_MODE_INL_HPP
#define BKSGE_CORE_RENDER_INL_CULL_MODE_INL_HPP

#include <bksge/core/render/cull_mode.hpp>
#include <unordered_map>
#include <string>

namespace bksge
{

namespace render
{

BKSGE_INLINE
std::string to_string(CullMode const& cull_mode)
{
#define BKSGE_CORE_RENDER_MAKE_CULL_MODE_KVP(x)	{ x, #x }

	static std::unordered_map<CullMode, std::string> const m =
	{
		BKSGE_CORE_RENDER_MAKE_CULL_MODE_KVP(CullMode::kNone),
		BKSGE_CORE_RENDER_MAKE_CULL_MODE_KVP(CullMode::kFront),
		BKSGE_CORE_RENDER_MAKE_CULL_MODE_KVP(CullMode::kBack),
	};

	return m.at(cull_mode);

#undef BKSGE_CORE_RENDER_MAKE_CULL_MODE_KVP
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_CULL_MODE_INL_HPP
