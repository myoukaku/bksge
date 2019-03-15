/**
 *	@file	wrap_mode_inl.hpp
 *
 *	@brief	WrapMode の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_INL_WRAP_MODE_INL_HPP
#define BKSGE_RENDER_INL_WRAP_MODE_INL_HPP

#include <bksge/render/wrap_mode.hpp>
#include <unordered_map>
#include <string>

namespace bksge
{

namespace render
{

BKSGE_INLINE
std::string to_string(WrapMode const& wrap_mode)
{
#define BKSGE_RENDER_MAKE_WRAP_MODE_KVP(x)	{ x, #x }

	static std::unordered_map<WrapMode, std::string> const m =
	{
		BKSGE_RENDER_MAKE_WRAP_MODE_KVP(WrapMode::kRepeat),
		BKSGE_RENDER_MAKE_WRAP_MODE_KVP(WrapMode::kClamp),
		BKSGE_RENDER_MAKE_WRAP_MODE_KVP(WrapMode::kBorder)
	};

	return m.at(wrap_mode);

#undef BKSGE_RENDER_MAKE_WRAP_MODE_KVP
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_INL_WRAP_MODE_INL_HPP
