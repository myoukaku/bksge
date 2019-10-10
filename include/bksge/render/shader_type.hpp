/**
 *	@file	shader_type.hpp
 *
 *	@brief	ShaderType の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_SHADER_TYPE_HPP
#define BKSGE_RENDER_SHADER_TYPE_HPP

#include <ostream>
#include <string>

namespace bksge
{

namespace render
{

enum class ShaderType
{
	kHLSL,
	kGLSL,
};

/**
 *	@brief	文字列への変換
 */
std::string to_string(ShaderType const& shader_type);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, ShaderType const& rhs)
{
	return os << to_string(rhs).c_str();
}

}	// namespace render

using render::ShaderType;

}	// namespace bksge

#if BKSGE_CXX_STANDARD <= 11

#include <functional>
#include <type_traits>

namespace std
{

template<>
struct hash<bksge::render::ShaderType>
{
	std::size_t operator()(bksge::render::ShaderType const& arg) const
	{
		using underlying_type = typename std::underlying_type<bksge::render::ShaderType>::type;
		return std::hash<underlying_type>{}(static_cast<underlying_type>(arg));
	}
};

}	// namespace std

#endif // BKSGE_CXX_STANDARD <= 11

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/inl/shader_type_inl.hpp>
#endif

#endif // BKSGE_RENDER_SHADER_TYPE_HPP
