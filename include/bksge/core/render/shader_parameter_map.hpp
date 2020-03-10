/**
 *	@file	shader_parameter_map.hpp
 *
 *	@brief	ShaderParameterMap の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_SHADER_PARAMETER_MAP_HPP
#define BKSGE_CORE_RENDER_SHADER_PARAMETER_MAP_HPP

#include <bksge/core/render/fwd/shader_parameter_map_fwd.hpp>
#include <bksge/core/render/detail/fwd/shader_parameter_base_fwd.hpp>
#include <bksge/core/render/detail/identifiable.hpp>
//#include <bksge/fnd/serialization/access.hpp>
//#include <bksge/fnd/serialization/nvp.hpp>
//#include <bksge/fnd/serialization/map.hpp>
//#include <bksge/fnd/serialization/string.hpp>
//#include <bksge/fnd/serialization/shared_ptr.hpp>
//#include <bksge/fnd/serialization/version.hpp>
#include <map>
#include <bksge/fnd/memory/shared_ptr.hpp>
#include <string>

namespace bksge
{

namespace render
{

/**
 *	@brief	シェーダパラメータのmap
 */
class ShaderParameterMap : public Identifiable
{
public:
	using key_type = std::string;
	using mapped_type = bksge::shared_ptr<ShaderParameterBase>;

	ShaderParameterMap(void);

	// コピー禁止
	ShaderParameterMap(ShaderParameterMap const&) = delete;
	ShaderParameterMap& operator=(ShaderParameterMap const&) = delete;

	// ムーブ可能
	ShaderParameterMap(ShaderParameterMap&& rhs);
	ShaderParameterMap& operator=(ShaderParameterMap&& rhs);

	mapped_type const& operator[](key_type const& key) const;

	template <typename T>
	void SetParameter(key_type const& key, T const& value);

private:
	std::map<key_type, mapped_type>	m_parameters;

private:
#if 0
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, bksge::serialization::version_t /*version*/)
	{
		ar & BKSGE_SERIALIZATION_NVP(m_parameters);
	}
#endif
};

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/shader_parameter_map_inl.hpp>
#endif

#include <bksge/core/render/detail/shader_parameter.hpp>
#include <bksge/fnd/memory/make_shared.hpp>

namespace bksge
{

namespace render
{

template <typename T>
inline void ShaderParameterMap::SetParameter(key_type const& key, T const& value)
{
	using ParamType = ShaderParameter<T>;

	if (auto const& t = (*this)[key])
	{
		if (t->class_id() == ParamType::StaticClassId())
		{
			static_cast<ParamType*>(t.get())->SetValue(value);
			return;
		}
	}

	m_parameters[key] = bksge::make_shared<ParamType>(value);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_SHADER_PARAMETER_MAP_HPP
