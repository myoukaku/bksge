/**
 *	@file	mipmap_mode_inl.hpp
 *
 *	@brief	MipmapMode の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_MIPMAP_MODE_INL_HPP
#define BKSGE_CORE_RENDER_INL_MIPMAP_MODE_INL_HPP

#include <bksge/core/render/mipmap_mode.hpp>
#include <string>

namespace bksge
{

namespace render
{

BKSGE_INLINE
std::string to_string(MipmapMode const& mipmap_mode)
{
#define BKSGE_CORE_RENDER_MAKE_MIPMAP_MODE_KVP(x)	case x: return #x

	switch (mipmap_mode)
	{
	BKSGE_CORE_RENDER_MAKE_MIPMAP_MODE_KVP(MipmapMode::kDisable);
	BKSGE_CORE_RENDER_MAKE_MIPMAP_MODE_KVP(MipmapMode::kNearest);
	BKSGE_CORE_RENDER_MAKE_MIPMAP_MODE_KVP(MipmapMode::kLinear);
	}

	return "";

#undef BKSGE_CORE_RENDER_MAKE_MIPMAP_MODE_KVP
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_MIPMAP_MODE_INL_HPP
