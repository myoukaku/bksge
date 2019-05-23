/**
 *	@file	scissor_state.hpp
 *
 *	@brief	ScissorState の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_SCISSOR_STATE_HPP
#define BKSGE_RENDER_SCISSOR_STATE_HPP

#include <bksge/render/fwd/scissor_state_fwd.hpp>
#include <bksge/math/rect.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	シザーテストの設定
 */
class ScissorState
{
public:
	ScissorState(void);

	bool			enable(void) const;
	Rectf const&	rect(void) const;

	void SetEnable(bool enable);
	void SetRect(Rectf const& rect);

private:
	bool		m_enable;
	Rectf		m_rect;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/inl/scissor_state_inl.hpp>
#endif

#endif // BKSGE_RENDER_SCISSOR_STATE_HPP
