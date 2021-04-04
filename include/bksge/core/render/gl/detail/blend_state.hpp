/**
 *	@file	blend_state.hpp
 *
 *	@brief	BlendState クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_BLEND_STATE_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_BLEND_STATE_HPP

#include <bksge/core/render/fwd/blend_state_fwd.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

class BlendState
{
public:
	explicit BlendState(bksge::BlendState const& state);

	void Apply(void);

private:
	bool        const	m_enable;
	::GLenum    const	m_color_src_factor;
	::GLenum    const	m_color_dst_factor;
	::GLenum    const	m_alpha_src_factor;
	::GLenum    const	m_alpha_dst_factor;
	::GLenum    const	m_color_operation;
	::GLenum    const	m_alpha_operation;
	::GLboolean const	m_color_mask_red;
	::GLboolean const	m_color_mask_green;
	::GLboolean const	m_color_mask_blue;
	::GLboolean const	m_color_mask_alpha;
	bool        const	m_logic_op_enable;
	::GLenum    const	m_logic_op;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/blend_state_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_BLEND_STATE_HPP
