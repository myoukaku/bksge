/**
 *	@file	simple_material.hpp
 *
 *	@brief	SimpleMaterial クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_DRAW_SIMPLE_MATERIAL_HPP
#define BKSGE_CORE_DRAW_SIMPLE_MATERIAL_HPP

#include <bksge/core/draw/material.hpp>
#include <bksge/core/math/color3.hpp>

namespace bksge
{

namespace draw
{

/**
 *	@brief	
 */
class SimpleMaterial : public Material
{
public:
	using ColorType = Color3f;
	using OpacityType = float;

	/**
	 *	@brief
	 */
	SimpleMaterial(void);

	/**
	 *	@brief
	 */
	virtual ~SimpleMaterial() override;

	/**
	 *	@brief
	 */
	void SetDiffuseColor(ColorType const& diffuse);

	/**
	 *	@brief
	 */
	void SetOpacity(OpacityType opacity);

private:
	virtual void VOnRender(
		Renderer* renderer,
		Shader* shader,
		Node const& node,
		Geometry const& geometry,
		Camera const& camera,
		LightSharedPtrList const& light_list) override;

	ColorType		m_diffuse_color;
	OpacityType		m_opacity;

private:
	/**
	 *	@brief	シリアライズ
	 */
	//friend class bksge::serialization::access;
	//template <typename Archive>
	//void serialize(Archive& ar, unsigned int version)
	//{
	//	ar & BKSGE_SERIALIZATION_BASE_OBJECT_NVP(Material);
	//	ar & BKSGE_SERIALIZATION_NVP(m_shader);
	//}
};

}	// namespace draw

using draw::SimpleMaterial;

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/draw/inl/simple_material_inl.hpp>
#endif

#endif // BKSGE_CORE_DRAW_SIMPLE_MATERIAL_HPP
