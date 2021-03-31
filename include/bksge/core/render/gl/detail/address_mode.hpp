/**
 *	@file	address_mode.hpp
 *
 *	@brief	AddressMode クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_ADDRESS_MODE_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_ADDRESS_MODE_HPP

#include <bksge/core/render/fwd/address_mode_fwd.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief	AddressModeをOpenGLのenumに変換
 */
class AddressMode
{
public:
	explicit AddressMode(bksge::AddressMode address_mode);

	operator ::GLint() const;

private:
	::GLint	const m_address_mode;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/address_mode_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_ADDRESS_MODE_HPP
