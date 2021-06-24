/**
 *	@file	blend_operation.hpp
 *
 *	@brief	BlendOperation クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_BLEND_OPERATION_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_BLEND_OPERATION_HPP

#include <bksge/core/render/fwd/blend_operation_fwd.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>

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
	::GLenum const	m_blend_operation;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/blend_operation_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_BLEND_OPERATION_HPP
