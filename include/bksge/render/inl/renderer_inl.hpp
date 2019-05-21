/**
 *	@file	renderer_inl.hpp
 *
 *	@brief	Renderer の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_INL_RENDERER_INL_HPP
#define BKSGE_RENDER_INL_RENDERER_INL_HPP

#include <bksge/render/renderer.hpp>
#include <bksge/window/window.hpp>
#include <bksge/math/rect.hpp>
#include <bksge/math/vector2.hpp>
#include <bksge/memory/make_unique.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
Renderer::Renderer(void)
	: m_clear_flag(ClearFlag::kAll)
	, m_clear_color(0, 0, 0, 0)
	, m_viewport()
	, m_scissor()
{}

BKSGE_INLINE
Renderer::~Renderer()
{}

BKSGE_INLINE
void Renderer::SetRenderTarget(Window const& window)
{
	VSetRenderTarget(window);

	if (!m_viewport)
	{
		SetViewport(Rectf(Vector2f(0,0), Size2f(window.client_size())));
	}

	if (!m_scissor)
	{
		SetScissor(Rectf(Vector2f(0,0), Size2f(window.client_size())));
	}
}

BKSGE_INLINE void
Renderer::SetViewport(Rectf const& viewport)
{
	if (!m_viewport)
	{
		m_viewport = bksge::make_unique<Rectf>(viewport);
	}
	else
	{
		*m_viewport = viewport;
	}
}

BKSGE_INLINE void
Renderer::SetScissor(Rectf const& scissor)
{
	if (!m_scissor)
	{
		m_scissor = bksge::make_unique<Rectf>(scissor);
	}
	else
	{
		*m_scissor = scissor;
	}
}

BKSGE_INLINE
void Renderer::Begin(void)
{
	VBegin();
}

BKSGE_INLINE
void Renderer::End(void)
{
	VEnd();
}

BKSGE_INLINE
void Renderer::Clear(void)
{
	VClear(m_clear_flag, m_clear_color);
}

BKSGE_INLINE
void Renderer::Render(
	Geometry const& geometry,
	ShaderMap const& shader_map,
	ShaderParameterMap const& shader_parameter_map,
	RenderState const& render_state)
{
	VRender(geometry, shader_map, shader_parameter_map, render_state);
}

BKSGE_INLINE
void Renderer::SetClearFlag(ClearFlag clear_flag)
{
	m_clear_flag = clear_flag;
}

BKSGE_INLINE
void Renderer::SetClearColor(Color4f const& clear_color)
{
	m_clear_color = clear_color;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_INL_RENDERER_INL_HPP
