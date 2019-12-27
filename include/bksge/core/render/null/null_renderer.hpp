/**
 *	@file	null_renderer.hpp
 *
 *	@brief	NullRenderer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_NULL_NULL_RENDERER_HPP
#define BKSGE_CORE_RENDER_NULL_NULL_RENDERER_HPP

#include <bksge/core/render/renderer.hpp>
#include <bksge/core/window/fwd/window_fwd.hpp>

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
	void VBegin(void) override;
	void VEnd(void) override;
	bool VRender(
		Geometry const& geometry,
		Shader const& shader,
		ShaderParameterMap const& shader_parameter_map,
		RenderState const& render_state) override;
};

}	// namespace render

using render::NullRenderer;

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/null/inl/null_renderer_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_NULL_NULL_RENDERER_HPP
