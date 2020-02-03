/**
 *	@file	clear_state.hpp
 *
 *	@brief	ClearState の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_CLEAR_STATE_HPP
#define BKSGE_CORE_RENDER_CLEAR_STATE_HPP

#include <bksge/core/render/fwd/clear_state_fwd.hpp>
#include <bksge/core/render/clear_flag.hpp>
#include <bksge/core/math/color4.hpp>
#include <cstdint>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
class ClearState
{
public:
	ClearState(void);

	ClearFlag const&	flag(void) const;
	Color4f const&		color(void) const;
	float				depth(void) const;
	std::uint8_t		stencil(void) const;

	void SetFlag(ClearFlag const& flag);
	void SetColor(Color4f const& color);
	void SetDepth(float depth);
	void SetStencil(std::uint8_t stencil);

private:
	ClearFlag			m_flag;
	Color4f				m_color;
	float				m_depth;
	std::uint8_t		m_stencil;
};

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/clear_state_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_CLEAR_STATE_HPP
