/**
 *	@file	render_pass_info.hpp
 *
 *	@brief	RenderPassInfo の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_RENDER_PASS_INFO_HPP
#define BKSGE_CORE_RENDER_RENDER_PASS_INFO_HPP

#include <bksge/core/render/fwd/render_pass_info_fwd.hpp>
#include <bksge/core/render/clear_state.hpp>
#include <bksge/core/render/scissor_state.hpp>
#include <bksge/core/render/viewport.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	
 */
class RenderPassInfo
{
public:
	RenderPassInfo(void);

	ClearState const&		clear_state(void) const;
	ScissorState const&		scissor_state(void) const;
	Viewport const&			viewport(void) const;

	ClearState&				clear_state(void);
	ScissorState&			scissor_state(void);
	Viewport&				viewport(void);

private:
	ClearState			m_clear_state;
	ScissorState		m_scissor_state;
	Viewport			m_viewport;
};

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/render_pass_info_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_RENDER_PASS_INFO_HPP
