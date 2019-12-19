﻿/**
 *	@file	shader_stage.hpp
 *
 *	@brief	ShaderStage の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_SHADER_STAGE_HPP
#define BKSGE_CORE_RENDER_SHADER_STAGE_HPP

#include <ostream>
#include <string>

namespace bksge
{

namespace render
{

enum class ShaderStage
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
std::string to_string(ShaderStage const& shader_stage);

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

#include <functional>
#include <type_traits>

namespace std
{

template<>
struct hash<bksge::render::ShaderStage>
{
	std::size_t operator()(bksge::render::ShaderStage const& arg) const
	{
		using underlying_type = typename std::underlying_type<bksge::render::ShaderStage>::type;
		return std::hash<underlying_type>{}(static_cast<underlying_type>(arg));
	}
};

}	// namespace std

#endif // BKSGE_CXX_STANDARD <= 11

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/shader_stage_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_SHADER_STAGE_HPP