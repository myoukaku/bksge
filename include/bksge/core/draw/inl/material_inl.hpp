/**
 *	@file	material_inl.hpp
 *
 *	@brief	Material クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_DRAW_INL_MATERIAL_INL_HPP
#define BKSGE_CORE_DRAW_INL_MATERIAL_INL_HPP

#include <bksge/core/draw/material.hpp>
#include <bksge/core/draw/node.hpp>
#include <bksge/core/render/shader.hpp>
#include <bksge/core/render/renderer.hpp>

namespace bksge
{

namespace draw
{

BKSGE_INLINE
Material::Material(void)
	: m_shader(nullptr)
{}

BKSGE_INLINE
Material::~Material(void)
{}

BKSGE_INLINE
void Material::SetShader(ShaderPtr const& shader)
{
	m_shader = shader;
}

BKSGE_INLINE
void Material::Render(
	Renderer* renderer,
	Node const& node,
	Geometry const& geometry,
	Camera const& camera,
	LightSharedPtrList const& light_list)
{
	if (!m_shader)
	{
		return;
	}

	VOnRender(renderer, m_shader.get(), node, geometry, camera, light_list);

	renderer->Render(geometry, *m_shader);
}

BKSGE_INLINE
void Material::VOnRender(
	Renderer* /*renderer*/,
	Shader* /*shader*/,
	Node const& /*node*/,
	Geometry const& /*geometry*/,
	Camera const& /*camera*/,
	LightSharedPtrList const& /*light_list*/)
{
}

}	// namespace draw

}	// namespace bksge

#endif // BKSGE_CORE_DRAW_INL_MATERIAL_INL_HPP
