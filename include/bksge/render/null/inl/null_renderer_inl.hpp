/**
 *	@file	null_renderer_inl.hpp
 *
 *	@brief	NullRenderer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_NULL_INL_NULL_RENDERER_INL_HPP
#define BKSGE_RENDER_NULL_INL_NULL_RENDERER_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_NULL_RENDERER

#include <bksge/render/null/null_renderer.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE NullRenderer::NullRenderer(void)
{}

BKSGE_INLINE NullRenderer::~NullRenderer()
{}

BKSGE_INLINE void NullRenderer::VSetRenderTarget(Window const& /*window*/)
{}

BKSGE_INLINE void NullRenderer::VBegin(void)
{}

BKSGE_INLINE void NullRenderer::VEnd(void)
{}

BKSGE_INLINE void NullRenderer::VClear(ClearFlag /*clear_flag*/, Color4f const& /*clear_color*/)
{}

BKSGE_INLINE void NullRenderer::VRender(Geometry const& /*geometry*/, Shader const& /*shader*/)
{}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_NULL_RENDERER

#endif // BKSGE_RENDER_NULL_INL_NULL_RENDERER_INL_HPP
