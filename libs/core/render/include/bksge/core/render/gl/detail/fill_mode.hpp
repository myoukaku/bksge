/**
 *	@file	fill_mode.hpp
 *
 *	@brief	FillMode クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_FILL_MODE_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_FILL_MODE_HPP

#include <bksge/core/render/fwd/fill_mode_fwd.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>

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
	explicit FillMode(bksge::FillMode fill_mode);

	operator ::GLenum() const;

private:
	::GLenum const	m_fill_mode;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/fill_mode_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_FILL_MODE_HPP
