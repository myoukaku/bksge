/**
 *	@file	address_mode_inl.hpp
 *
 *	@brief	AddressMode クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_ADDRESS_MODE_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_ADDRESS_MODE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/address_mode.hpp>
#include <bksge/core/render/address_mode.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

namespace detail
{

inline ::GLint
ToGlAddressMode(bksge::AddressMode address_mode)
{
	switch (address_mode)
	{
	case bksge::AddressMode::kRepeat: return GL_REPEAT;
	case bksge::AddressMode::kMirror: return GL_MIRRORED_REPEAT;
	case bksge::AddressMode::kClamp:  return GL_CLAMP_TO_EDGE;
	case bksge::AddressMode::kBorder: return GL_CLAMP_TO_BORDER;
	}
	return GL_REPEAT;
}

}	// namespace detail

BKSGE_INLINE
AddressMode::AddressMode(bksge::AddressMode address_mode)
	: m_address_mode(detail::ToGlAddressMode(address_mode))
{}

BKSGE_INLINE
AddressMode::operator ::GLint() const
{
	return m_address_mode;
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_ADDRESS_MODE_INL_HPP
