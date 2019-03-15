/**
 *	@file	dummy_renderer.hpp
 *
 *	@brief	DummyRenderer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_DUMMY_DUMMY_RENDERER_HPP
#define BKSGE_RENDER_DUMMY_DUMMY_RENDERER_HPP

#include <bksge/render/renderer.hpp>
#include <bksge/window/fwd/window_fwd.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
class DummyRenderer : public Renderer
{
public:
	DummyRenderer(void);

	virtual ~DummyRenderer();

private:
	virtual void VSetRenderTarget(Window const& window) override;
	virtual void VBegin(void) override;
	virtual void VEnd(void) override;
	virtual void VClear(ClearFlag clear_flag, Color4f const& clear_color) override;
	virtual void VRender(Geometry const& geometry, Shader const& shader) override;
};

}	// namespace render

using render::DummyRenderer;

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/dummy/inl/dummy_renderer_inl.hpp>
#endif

#endif // BKSGE_RENDER_DUMMY_DUMMY_RENDERER_HPP
