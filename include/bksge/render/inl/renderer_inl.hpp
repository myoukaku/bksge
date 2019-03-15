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

namespace bksge
{

namespace render
{

BKSGE_INLINE
Renderer::Renderer(void)
	: m_clear_flag(ClearFlag::kAll)
	, m_clear_color(0, 0, 0, 0)
{}

BKSGE_INLINE
Renderer::~Renderer()
{}

BKSGE_INLINE
void Renderer::SetRenderTarget(Window const& window)
{
	VSetRenderTarget(window);
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
void Renderer::Render(Geometry const& geometry, Shader const& shader)
{
	VRender(geometry, shader);
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
