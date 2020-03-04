/**
 *	@file	scene_inl.hpp
 *
 *	@brief	Scene クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_DRAW_INL_SCENE_INL_HPP
#define BKSGE_CORE_DRAW_INL_SCENE_INL_HPP

#include <bksge/core/draw/scene.hpp>
#include <bksge/core/render/renderer.hpp>
#include <bksge/core/render/render_pass_info.hpp>

namespace bksge
{

namespace draw
{

struct Scene::Impl
{
	bksge::RenderPassInfo	render_pass_info;
};

BKSGE_INLINE
Scene::Scene(void)
	: m_impl(new Scene::Impl())
{
}

BKSGE_INLINE
Scene::~Scene()
{
}

BKSGE_INLINE void
Scene::Add(NodeSharedPtr const& node)
{
	(void)node;
}

BKSGE_INLINE void
Scene::Render(bksge::Renderer* renderer) const
{
	m_impl->render_pass_info.clear_state().SetColor({0.5f, 0.0f, 0.5f, 1.0f});
	renderer->BeginRenderPass(m_impl->render_pass_info);
	renderer->EndRenderPass();
}

}	// namespace draw

}	// namespace bksge

#endif // BKSGE_CORE_DRAW_INL_SCENE_INL_HPP
