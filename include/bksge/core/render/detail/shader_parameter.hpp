/**
 *	@file	shader_parameter.hpp
 *
 *	@brief	ShaderParameter の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_DETAIL_SHADER_PARAMETER_HPP
#define BKSGE_CORE_RENDER_DETAIL_SHADER_PARAMETER_HPP

#include <bksge/core/render/detail/fwd/shader_parameter_fwd.hpp>
#include <bksge/core/render/detail/fwd/class_id_fwd.hpp>
#include <bksge/core/render/detail/shader_parameter_base.hpp>
//#include <bksge/fnd/serialization/access.hpp>
//#include <bksge/fnd/serialization/nvp.hpp>
//#include <bksge/fnd/serialization/polymorphic_serializable.hpp>

namespace bksge
{

namespace render
{

template <typename T>
class ShaderParameter
	: public ShaderParameterBase
	/*, private bksge::serialization::polymorphic_serializable<ShaderParameter<T>>*/
{
public:
	ShaderParameter(void);

	explicit ShaderParameter(T const& value);

	T const& value(void) const;

	void SetValue(T const& value);

	void const* data(void) const override;

	bool Equals(ShaderParameterBase const& rhs) const override;

	ClassId const& class_id(void) const override;

	static ClassId const& StaticClassId(void);

private:
	T	m_value;

#if 0
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, unsigned int /*version*/)
	{
		ar & BKSGE_SERIALIZATION_BASE_OBJECT_NVP(ShaderParameterBase);
		ar & BKSGE_SERIALIZATION_NVP(m_value);
	}
#endif
};

}	// namespace render

}	// namespace bksge

#include <bksge/core/render/detail/inl/shader_parameter_inl.hpp>

#endif // BKSGE_CORE_RENDER_DETAIL_SHADER_PARAMETER_HPP
