/**
 *	@file	mesh_inl.hpp
 *
 *	@brief	Mesh クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_DRAW_INL_MESH_INL_HPP
#define BKSGE_CORE_DRAW_INL_MESH_INL_HPP

#include <bksge/core/draw/mesh.hpp>
#include <bksge/core/draw/material.hpp>
#include <bksge/core/render/geometry.hpp>
#include <bksge/core/render/renderer.hpp>

namespace bksge
{

namespace draw
{

BKSGE_INLINE
Mesh::Mesh(void)
	: Mesh(nullptr, nullptr)
{}

BKSGE_INLINE
Mesh::Mesh(GeometryPtr const& geometry, MaterialSharedPtr const& material)
	: m_geometry(geometry)
	, m_material(material)
{}

BKSGE_INLINE
void Mesh::Render(Renderer* renderer, Camera const& camera, LightSharedPtrList const& light_list) const
{
	if (!renderer || !m_geometry || !m_material)
	{
		return;
	}

	m_material->Render(renderer, *this, *m_geometry, camera, light_list);
}

}	// namespace draw

}	// namespace bksge

#endif // BKSGE_CORE_DRAW_INL_MESH_INL_HPP
