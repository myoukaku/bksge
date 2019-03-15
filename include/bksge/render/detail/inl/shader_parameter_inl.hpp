/**
 *	@file	shader_parameter_inl.hpp
 *
 *	@brief	ShaderParameter の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_DETAIL_INL_SHADER_PARAMETER_INL_HPP
#define BKSGE_RENDER_DETAIL_INL_SHADER_PARAMETER_INL_HPP

#include <bksge/render/detail/shader_parameter.hpp>
#include <bksge/render/detail/class_id.hpp>

namespace bksge
{

namespace render
{

template <typename T>
inline ShaderParameter<T>::ShaderParameter(void)
	: m_value()
{}

template <typename T>
inline ShaderParameter<T>::ShaderParameter(T const& value)
	: m_value(value)
{}

template <typename T>
inline T const& ShaderParameter<T>::value(void) const
{
	return m_value;
}

template <typename T>
inline void ShaderParameter<T>::SetValue(T const& value)
{
	m_value = value;
}

template <typename T>
inline void const* ShaderParameter<T>::data(void) const
{
	return &m_value;
}

template <typename T>
inline bool ShaderParameter<T>::Equals(ShaderParameterBase const& rhs) const
{
	if (rhs.class_id() != class_id())
	{
		return false;
	}

	auto const* t = static_cast<ShaderParameter<T> const*>(&rhs);
	return m_value == t->m_value;
}

template <typename T>
inline ClassId const& ShaderParameter<T>::class_id(void) const
{
	return StaticClassId();
}

template <typename T>
inline ClassId const& ShaderParameter<T>::StaticClassId(void)
{
	static ClassId const id = make_class_id<ShaderParameter<T>>();
	return id;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_DETAIL_INL_SHADER_PARAMETER_INL_HPP
