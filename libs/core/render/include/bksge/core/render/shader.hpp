/**
 *	@file	shader.hpp
 *
 *	@brief	Shader クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_SHADER_HPP
#define BKSGE_CORE_RENDER_SHADER_HPP

#include <bksge/core/render/fwd/shader_fwd.hpp>
#include <bksge/core/render/detail/identifiable.hpp>
#include <bksge/core/render/shader_stage.hpp>
//#include <bksge/fnd/serialization/access.hpp>
//#include <bksge/fnd/serialization/nvp.hpp>
//#include <bksge/fnd/serialization/string.hpp>
//#include <bksge/fnd/serialization/version.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/utility/pair.hpp>
#include <bksge/fnd/unordered_map/unordered_map.hpp>
#include <initializer_list>

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
	using ContainerType = bksge::unordered_map<ShaderStage, std::string>;

public:
	using const_iterator = ContainerType::const_iterator;

	explicit Shader(std::initializer_list<bksge::pair<ShaderStage, char const*>> il);

private:
	// コピー禁止
	Shader(Shader const&) = delete;
	Shader& operator=(Shader const&) = delete;

public:
	// ムーブ可能
	Shader(Shader&& rhs);
	Shader& operator=(Shader&& rhs);

	~Shader() = default;

	const_iterator begin(void) const;
	const_iterator end(void) const;

private:
	ContainerType		m_shaders;

private:
#if 0
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, bksge::serialization::version_t /*version*/)
	{
		ar & BKSGE_SERIALIZATION_NVP(m_shaders);
	}
#endif
};

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/shader_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_SHADER_HPP
