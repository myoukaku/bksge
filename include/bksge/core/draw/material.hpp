/**
 *	@file	material.hpp
 *
 *	@brief	Material クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_DRAW_MATERIAL_HPP
#define BKSGE_CORE_DRAW_MATERIAL_HPP

#include <bksge/core/draw/fwd/material_fwd.hpp>
#include <bksge/core/draw/fwd/mesh_fwd.hpp>
#include <bksge/core/draw/fwd/camera_fwd.hpp>
#include <bksge/core/draw/fwd/node_fwd.hpp>
#include <bksge/core/draw/fwd/light_fwd.hpp>
#include <bksge/core/render/fwd/shader_fwd.hpp>
#include <bksge/core/render/fwd/renderer_fwd.hpp>
#include <bksge/core/render/fwd/geometry_fwd.hpp>
//#include <bksge/fnd/serialization/access.hpp>
//#include <bksge/fnd/serialization/nvp.hpp>

namespace bksge
{

namespace draw
{

/**
 *	@brief	マテリアルの基底となるクラス
 */
class Material
{
public:
	/**
	 *	@brief
	 */
	Material(void);

	/**
	 *	@brief
	 */
	virtual ~Material();

	/**
	 *	@brief
	 */
	void SetShader(ShaderPtr const& shader);

	/**
	 *	@brief
	 */
	void Render(
		Renderer* renderer,
		Node const& node,
		Geometry const& geometry,
		Camera const& camera,
		LightSharedPtrList const& light_list);

private:
	virtual void VOnRender(
		Renderer* renderer,
		Shader* shader,
		Node const& node,
		Geometry const& geometry,
		Camera const& camera,
		LightSharedPtrList const& light_list);

	ShaderPtr	m_shader;

private:
#if 0
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, unsigned int version)
	{
		ar & BKSGE_SERIALIZATION_NVP(m_shader);
	}
#endif
};

}	// namespace draw

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/draw/inl/material_inl.hpp>
#endif

#endif // BKSGE_CORE_DRAW_MATERIAL_HPP
