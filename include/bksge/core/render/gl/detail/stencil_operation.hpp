/**
 *	@file	stencil_operation.hpp
 *
 *	@brief	StencilOperation クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_STENCIL_OPERATION_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_STENCIL_OPERATION_HPP

#include <bksge/core/render/fwd/stencil_operation_fwd.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief	StencilOperation を OpenGL の enum に変換
 */
class StencilOperation
{
public:
	explicit StencilOperation(bksge::StencilOperation stencil_operation);

	operator ::GLenum() const;

private:
	::GLenum	m_stencil_operation;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/stencil_operation_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_STENCIL_OPERATION_HPP
