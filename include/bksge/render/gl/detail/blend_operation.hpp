/**
 *	@file	blend_operation.hpp
 *
 *	@brief	BlendOperation クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_BLEND_OPERATION_HPP
#define BKSGE_RENDER_GL_DETAIL_BLEND_OPERATION_HPP

#include <bksge/render/fwd/blend_operation_fwd.hpp>
#include <bksge/render/gl/detail/gl_h.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief	BlendOperation を OpenGL の enum に変換
 */
class BlendOperation
{
public:
	explicit BlendOperation(bksge::BlendOperation blend_operation);

	operator ::GLenum() const;

private:
	::GLenum	m_blend_operation;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/detail/inl/blend_operation_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_DETAIL_BLEND_OPERATION_HPP
