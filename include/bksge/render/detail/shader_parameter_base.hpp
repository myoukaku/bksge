/**
 *	@file	shader_parameter_base.hpp
 *
 *	@brief	ShaderParameterBase の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_DETAIL_SHADER_PARAMETER_BASE_HPP
#define BKSGE_RENDER_DETAIL_SHADER_PARAMETER_BASE_HPP

#include <bksge/render/detail/fwd/shader_parameter_base_fwd.hpp>
#include <bksge/render/detail/fwd/class_id_fwd.hpp>
//#include <bksge/serialization/access.hpp>
//#include <bksge/serialization/nvp.hpp>
//#include <bksge/serialization/polymorphic_serializable.hpp>

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

	virtual bool Equals(ShaderParameterBase const& rhs) const = 0;

	virtual ClassId const& class_id(void) const = 0;

private:
#if 0
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& /*ar*/, unsigned int /*version*/)
	{
	}
#endif
};

bool operator==(ShaderParameterBase const& lhs, ShaderParameterBase const& rhs);
bool operator!=(ShaderParameterBase const& lhs, ShaderParameterBase const& rhs);

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/detail/inl/shader_parameter_base_inl.hpp>
#endif

#endif // BKSGE_RENDER_DETAIL_SHADER_PARAMETER_BASE_HPP
