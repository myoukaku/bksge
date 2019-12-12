/**
 *	@file	blend_factor.hpp
 *
 *	@brief	BlendFactor クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_BLEND_FACTOR_HPP
#define BKSGE_RENDER_GL_DETAIL_BLEND_FACTOR_HPP

#include <bksge/render/fwd/blend_factor_fwd.hpp>
#include <bksge/render/gl/detail/gl_h.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief	BlendFactor を OpenGL の enum に変換
 */
class BlendFactor
{
public:
	explicit BlendFactor(bksge::BlendFactor blend_factor);

	operator ::GLenum() const;

private:
	::GLenum	m_blend_factor;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/detail/inl/blend_factor_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_DETAIL_BLEND_FACTOR_HPP
