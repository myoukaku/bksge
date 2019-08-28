/**
 *	@file	fill_mode.hpp
 *
 *	@brief	FillMode クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_FILL_MODE_HPP
#define BKSGE_RENDER_GL_DETAIL_FILL_MODE_HPP

#include <bksge/render/fwd/fill_mode_fwd.hpp>
#include <bksge/render/gl/detail/gl_h.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief	FillMode を OpenGL の enum に変換
 */
class FillMode
{
public:
	FillMode(bksge::FillMode fill_mode);

	operator ::GLenum() const;

private:
	::GLenum	m_fill_mode;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/detail/inl/fill_mode_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_DETAIL_FILL_MODE_HPP
