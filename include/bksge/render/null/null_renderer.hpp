/**
 *	@file	null_renderer.hpp
 *
 *	@brief	NullRenderer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_NULL_NULL_RENDERER_HPP
#define BKSGE_RENDER_NULL_NULL_RENDERER_HPP

#include <bksge/render/renderer.hpp>
#include <bksge/window/fwd/window_fwd.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
class NullRenderer : public Renderer
{
public:
	NullRenderer(void);

	virtual ~NullRenderer();

private:
	void VSetRenderTarget(Window const& window) override;
	void VBegin(void) override;
	void VEnd(void) override;
	void VClear(ClearFlag clear_flag, Color4f const& clear_color) override;
	void VRender(Geometry const& geometry, Shader const& shader) override;
};

}	// namespace render

using render::NullRenderer;

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/null/inl/null_renderer_inl.hpp>
#endif

#endif // BKSGE_RENDER_NULL_NULL_RENDERER_HPP
