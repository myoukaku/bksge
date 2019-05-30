/**
 *	@file	shader.hpp
 *
 *	@brief	Shader クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_SHADER_HPP
#define BKSGE_RENDER_SHADER_HPP

#include <bksge/render/fwd/shader_fwd.hpp>
#include <bksge/render/detail/identifiable.hpp>
#include <bksge/render/shader_type.hpp>
#include <bksge/render/shader_stage.hpp>
//#include <bksge/serialization/access.hpp>
//#include <bksge/serialization/nvp.hpp>
//#include <bksge/serialization/string.hpp>
#include <string>
#include <initializer_list>
#include <utility>	// pair
#include <unordered_map>

namespace bksge
{

namespace render
{

/**
 *	@brief	シェーダの基底クラス
 */
class Shader : public Identifiable
{
private:
	using Base = Identifiable;
	using ContainerType = std::unordered_map<ShaderStage, std::string>;

public:
	using const_iterator = ContainerType::const_iterator;

	Shader(ShaderType type, std::initializer_list<std::pair<ShaderStage, char const*>> il);

	// コピー禁止
	Shader(Shader const&) = delete;
	Shader& operator=(Shader const&) = delete;

	// ムーブ可能
	Shader(Shader&& rhs);
	Shader& operator=(Shader&& rhs);

	~Shader() = default;

	ShaderType type(void) const;

	const_iterator begin(void) const;
	const_iterator end(void) const;

private:
	ShaderType			m_type;
	ContainerType		m_shaders;

private:
#if 0
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, unsigned int /*version*/)
	{
		ar & BKSGE_SERIALIZATION_NVP(m_type);
		ar & BKSGE_SERIALIZATION_NVP(m_shaders);
	}
#endif
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/inl/shader_inl.hpp>
#endif

#endif // BKSGE_RENDER_SHADER_HPP
