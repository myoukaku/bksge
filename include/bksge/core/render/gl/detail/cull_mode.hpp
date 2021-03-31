/**
 *	@file	cull_mode.hpp
 *
 *	@brief	CullMode クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_CULL_MODE_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_CULL_MODE_HPP

#include <bksge/core/render/fwd/cull_mode_fwd.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>

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
	explicit CullMode(bksge::CullMode cull_mode);

	operator ::GLenum() const;

private:
	::GLenum const	m_cull_mode;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/cull_mode_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_CULL_MODE_HPP
