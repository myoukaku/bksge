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
#include <bksge/render/detail/shader_program_map.hpp>
#include <bksge/render/detail/shader_parameter_map.hpp>
//#include <bksge/serialization/access.hpp>
//#include <bksge/serialization/nvp.hpp>
//#include <bksge/serialization/string.hpp>
#include <string>

namespace bksge
{

namespace render
{

/**
 *	@brief	シェーダの基底クラス
 */
class Shader : public Identifiable
{
	using Base = Identifiable;

public:
	Shader(void);

	explicit Shader(std::string type);

	// コピー禁止
	Shader(Shader const&) = delete;
	Shader& operator=(Shader const&) = delete;

	// ムーブ可能
	Shader(Shader&& rhs);
	Shader& operator=(Shader&& rhs);

	~Shader() = default;

	/**
	 *	@brief	シェーダプログラムを設定します
	 */
	void SetProgram(ShaderStage stage, std::string source);

	/**
	 *	@brief	パラメータの値を設定します
	 */
	template <typename T>
	void SetParameter(char const* name, T const& value)
	{
		m_parameter_map.SetParameter(name, value);
	}

	/**
	 *	@brief	シェーダの種類を取得します
	 */
	std::string const& type(void) const;

	/**
	 *	@brief	シェーダプログラムのマップを取得します
	 */
	ShaderProgramMap const& program_map(void) const;

	/**
	 *	@brief	シェーダパラメータのマップを取得します
	 */
	ShaderParameterMap const& parameter_map(void) const;

private:
	std::string         m_type;
	ShaderProgramMap    m_program_map;
	ShaderParameterMap  m_parameter_map;

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
		ar & BKSGE_SERIALIZATION_NVP(m_program_map);
		ar & BKSGE_SERIALIZATION_NVP(m_parameter_map);
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
