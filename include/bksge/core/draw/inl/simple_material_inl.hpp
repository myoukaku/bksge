/**
 *	@file	simple_material_inl.hpp
 *
 *	@brief	SimpleMaterial クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_DRAW_INL_SIMPLE_MATERIAL_INL_HPP
#define BKSGE_CORE_DRAW_INL_SIMPLE_MATERIAL_INL_HPP

#include <bksge/core/draw/simple_material.hpp>
#include <bksge/core/draw/node.hpp>
#include <bksge/core/draw/camera.hpp>
#include <bksge/core/render/shader.hpp>

namespace bksge
{

namespace draw
{

BKSGE_INLINE
SimpleMaterial::SimpleMaterial(void)
	: m_diffuse_color()
	, m_opacity()
{
	char const* vs_source =
		"void main(									"
		"	float4 aPosition : POSITION,			"
		"	uniform float4x4 uModelViewProj,		"
		"	out float4 oPosition : POSITION)		"
		"{											"
		"	oPosition = mul(uModelViewProj, aPosition);	"
		"}											"
	;

	char const* fs_source =
		"void main(									"
		"	uniform float3 uDiffuseColor,			"
		"	out float4 oColor : COLOR)				"
		"{											"
		"	oColor = float4(uDiffuseColor, 1);		"
		"}											"
	;

	auto shader = std::make_shared<Shader>("Cg");
	shader->SetProgram(ShaderStage::kVertex, vs_source);
	shader->SetProgram(ShaderStage::kFragment, fs_source);

	SetShader(shader);
}

BKSGE_INLINE
SimpleMaterial::~SimpleMaterial()
{}

BKSGE_INLINE
void SimpleMaterial::SetDiffuseColor(ColorType const& diffuse)
{
	m_diffuse_color = diffuse;
}

BKSGE_INLINE
void SimpleMaterial::SetOpacity(OpacityType opacity)
{
	m_opacity = opacity;
}

BKSGE_INLINE
void SimpleMaterial::VOnRender(
	Renderer* /*renderer*/,
	Shader* shader,
	Node const& node,
	Geometry const& /*geometry*/,
	Camera const& camera,
	LightSharedPtrList const& /*light_list*/)
{
	auto const model = node.GetWorldMatrix();
	auto const view = camera.GetViewMatrix();
	auto const proj = camera.GetProjectionMatrix();
	shader->SetParameter("uModelViewProj", model * view * proj);
	shader->SetParameter("uDiffuseColor", m_diffuse_color);
}

}	// namespace draw

}	// namespace bksge

#endif // BKSGE_CORE_DRAW_INL_SIMPLE_MATERIAL_INL_HPP
