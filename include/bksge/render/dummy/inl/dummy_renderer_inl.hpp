/**
 *	@file	dummy_renderer_inl.hpp
 *
 *	@brief	DummyRenderer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_DUMMY_INL_DUMMY_RENDERER_INL_HPP
#define BKSGE_RENDER_DUMMY_INL_DUMMY_RENDERER_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_DUMMY_RENDERER

#include <bksge/render/dummy/dummy_renderer.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE DummyRenderer::DummyRenderer(void)
{}

BKSGE_INLINE DummyRenderer::~DummyRenderer()
{}

BKSGE_INLINE void DummyRenderer::VSetRenderTarget(Window const& /*window*/)
{}

BKSGE_INLINE void DummyRenderer::VBegin(void)
{}

BKSGE_INLINE void DummyRenderer::VEnd(void)
{}

BKSGE_INLINE void DummyRenderer::VClear(ClearFlag /*clear_flag*/, Color4f const& /*clear_color*/)
{}

BKSGE_INLINE void DummyRenderer::VRender(Geometry const& /*geometry*/, Shader const& /*shader*/)
{}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_DUMMY_RENDERER

#endif // BKSGE_RENDER_DUMMY_INL_DUMMY_RENDERER_INL_HPP
