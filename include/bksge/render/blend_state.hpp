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

	bool			enable(void) const;
	BlendOperation	operation(void) const;
	BlendFactor		src_factor(void) const;
	BlendFactor		dst_factor(void) const;
	BlendOperation	alpha_operation(void) const;
	BlendFactor		alpha_src_factor(void) const;
	BlendFactor		alpha_dst_factor(void) const;

	void SetEnable(bool enable);
	void SetOperation(BlendOperation op);
	void SetOperation(BlendOperation rgb_op, BlendOperation alpha_op);
	void SetFactor(BlendFactor src, BlendFactor dst);
	void SetFactor(
		BlendFactor rgb_src, BlendFactor rgb_dst,
		BlendFactor alpha_src, BlendFactor alpha_dst);

private:
	bool			m_enable;
	BlendOperation	m_operation;
	BlendFactor		m_src_factor;
	BlendFactor		m_dst_factor;
	BlendOperation	m_alpha_operation;
	BlendFactor		m_alpha_src_factor;
	BlendFactor		m_alpha_dst_factor;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/inl/blend_state_inl.hpp>
#endif

#endif // BKSGE_RENDER_BLEND_STATE_HPP
