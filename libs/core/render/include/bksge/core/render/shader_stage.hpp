/**
 *	@file	shader_stage.hpp
 *
 *	@brief	ShaderStage の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_SHADER_STAGE_HPP
#define BKSGE_CORE_RENDER_SHADER_STAGE_HPP

#include <bksge/fnd/string/string.hpp>
#include <ostream>

namespace bksge
{

namespace render
{

enum class ShaderStage : bksge::uint32_t
{
	kVertex,
	kGeometry,
	kFragment,
	kTessellationControl,
	kTessellationEvaluation,
};

/**
 *	@brief	文字列への変換
 */
bksge::string to_string(ShaderStage const& shader_stage);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, ShaderStage const& rhs)
{
	return os << to_string(rhs).c_str();
}

}	// namespace render

using render::ShaderStage;

}	// namespace bksge

#if BKSGE_CXX_STANDARD <= 11

#include <bksge/fnd/functional/hash.hpp>
#include <bksge/fnd/type_traits/underlying_type.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

namespace BKSGE_HASH_NAMESPACE
{

template<>
struct hash<bksge::render::ShaderStage>
{
	bksge::size_t operator()(bksge::render::ShaderStage const& arg) const
	{
		using type = bksge::underlying_type_t<bksge::render::ShaderStage>;
		return bksge::hash<type>{}(static_cast<type>(arg));
	}
};

}	// namespace BKSGE_HASH_NAMESPACE

#endif // BKSGE_CXX_STANDARD <= 11

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/shader_stage_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_SHADER_STAGE_HPP
