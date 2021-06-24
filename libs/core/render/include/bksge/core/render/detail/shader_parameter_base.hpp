/**
 *	@file	shader_parameter_base.hpp
 *
 *	@brief	ShaderParameterBase の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_DETAIL_SHADER_PARAMETER_BASE_HPP
#define BKSGE_CORE_RENDER_DETAIL_SHADER_PARAMETER_BASE_HPP

#include <bksge/core/render/detail/fwd/shader_parameter_base_fwd.hpp>
#include <bksge/core/render/detail/fwd/class_id_fwd.hpp>
//#include <bksge/fnd/serialization/access.hpp>
//#include <bksge/fnd/serialization/nvp.hpp>
//#include <bksge/fnd/serialization/polymorphic_serializable.hpp>
//#include <bksge/fnd/serialization/version.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	シェーダのパラメータ
 */
class ShaderParameterBase
{
public:
	virtual ~ShaderParameterBase();

	virtual void const* data(void) const = 0;

	virtual ClassId const& class_id(void) const = 0;

private:
#if 0
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& /*ar*/, bksge::serialization::version_t /*version*/)
	{
	}
#endif
};

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/detail/inl/shader_parameter_base_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_DETAIL_SHADER_PARAMETER_BASE_HPP
