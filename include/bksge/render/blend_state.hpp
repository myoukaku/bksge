/**
 *	@file	blend_state.hpp
 *
 *	@brief	BlendState の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_BLEND_STATE_HPP
#define BKSGE_RENDER_BLEND_STATE_HPP

#include <bksge/render/fwd/blend_state_fwd.hpp>
#include <bksge/render/blend_operation.hpp>
#include <bksge/render/blend_factor.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	ブレンドの設定
 */
class BlendState
{
public:
	BlendState(void);

private:
	bool			m_enable;
	BlendOperation	m_op;
	BlendFactor		m_src;
	BlendFactor		m_dst;
	BlendOperation	m_alpha_op;
	BlendFactor		m_alpha_src;
	BlendFactor		m_alpha_dst;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/inl/blend_state_inl.hpp>
#endif

#endif // BKSGE_RENDER_BLEND_STATE_HPP
