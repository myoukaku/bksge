/**
 *	@file	shader_parameter_map.hpp
 *
 *	@brief	ShaderParameterMap の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_SHADER_PARAMETER_MAP_HPP
#define BKSGE_RENDER_SHADER_PARAMETER_MAP_HPP

#include <bksge/render/fwd/shader_parameter_map_fwd.hpp>
#include <bksge/render/detail/fwd/shader_parameter_base_fwd.hpp>
#include <bksge/render/detail/identifiable.hpp>
//#include <bksge/serialization/access.hpp>
//#include <bksge/serialization/nvp.hpp>
//#include <bksge/serialization/map.hpp>
//#include <bksge/serialization/string.hpp>
//#include <bksge/serialization/shared_ptr.hpp>
#include <map>
#include <memory>
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
	using mapped_type = std::shared_ptr<ShaderParameterBase>;

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
	void serialize(Archive& ar, unsigned int /*version*/)
	{
		ar & BKSGE_SERIALIZATION_NVP(m_parameters);
	}
#endif
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/inl/shader_parameter_map_inl.hpp>
#endif

#include <bksge/render/detail/shader_parameter.hpp>

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

	m_parameters[key] = std::make_shared<ParamType>(value);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_SHADER_PARAMETER_MAP_HPP
