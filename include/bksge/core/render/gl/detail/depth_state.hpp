/**
 *	@file	depth_state.hpp
 *
 *	@brief	DepthState クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_DEPTH_STATE_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_DEPTH_STATE_HPP

#include <bksge/core/render/fwd/depth_state_fwd.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

class DepthState
{
public:
	explicit DepthState(bksge::DepthState const& state);

	void Apply(void);

private:
	bool        const	m_enable;
	::GLboolean const	m_write;
	::GLenum    const	m_func;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/depth_state_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_DEPTH_STATE_HPP
