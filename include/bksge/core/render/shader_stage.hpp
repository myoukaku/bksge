﻿/**
 *	@file	shader_stage.hpp
 *
 *	@brief	ShaderStage の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_SHADER_STAGE_HPP
#define BKSGE_CORE_RENDER_SHADER_STAGE_HPP

#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/ostream/basic_ostream.hpp>

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
bksge::string to_string(ShaderStage const& shader_stage);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline bksge::basic_ostream<CharT, Traits>&
operator<<(bksge::basic_ostream<CharT, Traits>& os, ShaderStage const& rhs)
{
	return os << to_string(rhs).c_str();
}

}	// namespace render

using render::ShaderStage;

}	// namespace bksge

#if BKSGE_CXX_STANDARD <= 11

#include <bksge/fnd/type_traits/underlying_type.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <functional>

namespace std
{

template<>
struct hash<bksge::render::ShaderStage>
{
	bksge::size_t operator()(bksge::render::ShaderStage const& arg) const
	{
		using type = bksge::underlying_type_t<bksge::render::ShaderStage>;
		return std::hash<type>{}(static_cast<type>(arg));
	}
};

}	// namespace std

#endif // BKSGE_CXX_STANDARD <= 11

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/shader_stage_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_SHADER_STAGE_HPP
