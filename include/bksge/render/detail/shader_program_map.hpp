/**
 *	@file	shader_program_map.hpp
 *
 *	@brief	ShaderProgramMap クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_DETAIL_SHADER_PROGRAM_MAP_HPP
#define BKSGE_RENDER_DETAIL_SHADER_PROGRAM_MAP_HPP

#include <bksge/render/shader_stage.hpp>
//#include <bksge/serialization/access.hpp>
//#include <bksge/serialization/nvp.hpp>
//#include <bksge/serialization/map.hpp>
//#include <bksge/serialization/string.hpp>
#include <map>
#include <string>

namespace bksge
{

namespace render
{

/**
 *	@brief	シェーダプログラムのマップ
 */
class ShaderProgramMap
{
public:
	using key_type = ShaderStage;
	using mapped_type = std::string;
	using container_type = std::map<key_type, mapped_type>;
	using const_iterator = container_type::const_iterator;

	ShaderProgramMap(void) = default;

	// コピー禁止
	ShaderProgramMap(ShaderProgramMap const&) = delete;
	ShaderProgramMap& operator=(ShaderProgramMap const&) = delete;

	// ムーブ可能
	ShaderProgramMap(ShaderProgramMap&& rhs);
	ShaderProgramMap& operator=(ShaderProgramMap&& rhs);

	~ShaderProgramMap() = default;

	mapped_type& operator[](key_type const& key);

	BKSGE_NODISCARD mapped_type& at(key_type const& key);
	BKSGE_NODISCARD mapped_type const& at(key_type const& key) const;

	const_iterator begin(void) const;

	const_iterator end(void) const;

private:
	container_type	m_value;

private:
#if 0
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, unsigned int /*version*/)
	{
		ar & BKSGE_SERIALIZATION_NVP(m_value);
	}
#endif

private:
	friend bool operator==(ShaderProgramMap const& lhs, ShaderProgramMap const& rhs);
};

bool operator!=(ShaderProgramMap const& lhs, ShaderProgramMap const& rhs);

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/detail/inl/shader_program_map_inl.hpp>
#endif

#endif // BKSGE_RENDER_DETAIL_SHADER_PROGRAM_MAP_HPP
