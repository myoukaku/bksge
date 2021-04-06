/**
 *	@file	shader_type.hpp
 *
 *	@brief	ShaderType の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_SHADER_TYPE_HPP
#define BKSGE_CORE_RENDER_SHADER_TYPE_HPP

#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/ostream/basic_ostream.hpp>

namespace bksge
{

namespace render
{

enum class ShaderType : bksge::uint32_t
{
	kHLSL,
	kGLSL,
};

/**
 *	@brief	文字列への変換
 */
bksge::string to_string(ShaderType const& shader_type);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline bksge::basic_ostream<CharT, Traits>&
operator<<(bksge::basic_ostream<CharT, Traits>& os, ShaderType const& rhs)
{
	return os << to_string(rhs).c_str();
}

}	// namespace render

using render::ShaderType;

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/shader_type_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_SHADER_TYPE_HPP
