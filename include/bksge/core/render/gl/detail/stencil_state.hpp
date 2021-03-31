/**
 *	@file	stencil_state.hpp
 *
 *	@brief	StencilState クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_STENCIL_STATE_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_STENCIL_STATE_HPP

#include <bksge/core/render/fwd/stencil_state_fwd.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

class StencilState
{
public:
	explicit StencilState(bksge::StencilState const& state);

	void Apply(void);

private:
	bool     const	m_enable;
	::GLenum const	m_func;
	::GLint  const	m_reference;
	::GLuint const	m_read_mask;
	::GLuint const	m_write_mask;
	::GLenum const	m_fail_operation;
	::GLenum const	m_depth_fail_operation;
	::GLenum const	m_pass_operation;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/stencil_state_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_STENCIL_STATE_HPP
