/**
 *	@file	render_state.hpp
 *
 *	@brief	RenderState の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_RENDER_STATE_HPP
#define BKSGE_RENDER_RENDER_STATE_HPP

#include <bksge/render/fwd/render_state_fwd.hpp>
#include <bksge/render/rasterizer_state.hpp>
#include <bksge/render/blend_state.hpp>
#include <bksge/render/depth_state.hpp>
#include <bksge/render/stencil_state.hpp>
#include <bksge/render/scissor_state.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
class RenderState
{
public:
	RenderState(void);

	RasterizerState const&	rasterizer_state(void) const;
	BlendState const&		blend_state(void) const;
	DepthState const&		depth_state(void) const;
	StencilState const&		stencil_state(void) const;
	ScissorState const&		scissor_state(void) const;

	RasterizerState&	rasterizer_state(void);
	BlendState&			blend_state(void);
	DepthState&			depth_state(void);
	StencilState&		stencil_state(void);
	ScissorState&		scissor_state(void);

private:
	RasterizerState		m_rasterizer_state;
	BlendState			m_blend_state;
	DepthState			m_depth_state;
	StencilState		m_stencil_state;
	ScissorState		m_scissor_state;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/inl/render_state_inl.hpp>
#endif

#include <cstddef>
#include <functional>
#include <bksge/functional/hash_combine.hpp>

namespace std
{

template<>
struct hash<bksge::render::RenderState>
{
	std::size_t operator()(bksge::render::RenderState const& arg) const
	{
		return bksge::hash_combine(
			arg.rasterizer_state(),
			arg.blend_state(),
			arg.depth_state(),
			arg.stencil_state(),
			arg.scissor_state());
	}
};

}	// namespace std

#endif // BKSGE_RENDER_RENDER_STATE_HPP
