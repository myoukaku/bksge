/**
 *	@file	cull_mode.hpp
 *
 *	@brief	CullMode クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_CULL_MODE_HPP
#define BKSGE_RENDER_GL_DETAIL_CULL_MODE_HPP

#include <bksge/render/fwd/cull_mode_fwd.hpp>
#include <bksge/render/gl/detail/gl_h.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief	CullMode を OpenGL の enum に変換
 */
class CullMode
{
public:
	CullMode(bksge::CullMode cull_mode);

	operator ::GLenum() const;

private:
	::GLenum	m_cull_mode;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/detail/inl/cull_mode_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_DETAIL_CULL_MODE_HPP
