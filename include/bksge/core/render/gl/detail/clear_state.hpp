/**
 *	@file	clear_state.hpp
 *
 *	@brief	ClearState クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_CLEAR_STATE_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_CLEAR_STATE_HPP

#include <bksge/core/render/fwd/clear_state_fwd.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

class ClearState
{
public:
	explicit ClearState(bksge::ClearState const& state);

	void Apply(void);

private:
	::GLbitfield const	m_mask;
	::GLfloat    const	m_red;
	::GLfloat    const	m_green;
	::GLfloat    const	m_blue;
	::GLfloat    const	m_alpha;
	::GLdouble   const	m_depth;
	::GLint      const	m_stencil;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/clear_state_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_CLEAR_STATE_HPP
