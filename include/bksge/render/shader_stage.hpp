/**
 *	@file	shader_stage.hpp
 *
 *	@brief	ShaderStage の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_SHADER_STAGE_HPP
#define BKSGE_RENDER_SHADER_STAGE_HPP

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

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/inl/shader_stage_inl.hpp>
#endif

#endif // BKSGE_RENDER_SHADER_STAGE_HPP
