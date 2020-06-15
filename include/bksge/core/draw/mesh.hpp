/**
 *	@file	mesh.hpp
 *
 *	@brief	Mesh クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_DRAW_MESH_HPP
#define BKSGE_CORE_DRAW_MESH_HPP

#include <bksge/core/draw/fwd/mesh_fwd.hpp>
#include <bksge/core/draw/fwd/material_fwd.hpp>
#include <bksge/core/draw/fwd/camera_fwd.hpp>
#include <bksge/core/draw/fwd/light_fwd.hpp>
#include <bksge/core/draw/node.hpp>
#include <bksge/core/render/fwd/geometry_fwd.hpp>
#include <bksge/core/render/fwd/renderer_fwd.hpp>
//#include <bksge/fnd/serialization/access.hpp>
//#include <bksge/fnd/serialization/nvp.hpp>
//#include <bksge/fnd/serialization/shared_ptr.hpp>

namespace bksge
{

namespace draw
{

/**
 *	@brief	描画する物の基底クラス
 */
class Mesh : public Node
{
public:
	/**
	 *	@brief
	 */
	Mesh(void);

	/**
	 *	@brief
	 */
	Mesh(GeometryPtr const& geometry, MaterialSharedPtr const& material);

	/**
	 *	@brief
	 */
	void Render(Renderer* renderer, Camera const& camera, LightSharedPtrList const& light_list) const;

private:
	GeometryPtr m_geometry;
	MaterialSharedPtr m_material;

private:
#if 0
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, unsigned int /*version*/)
	{
		ar & BKSGE_SERIALIZATION_BASE_OBJECT_NVP(Node);
		ar & BKSGE_SERIALIZATION_NVP(m_geometry);
		ar & BKSGE_SERIALIZATION_NVP(m_material);
	}
#endif
};

}	// namespace draw

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/draw/inl/mesh_inl.hpp>
#endif

#endif // BKSGE_CORE_DRAW_MESH_HPP
