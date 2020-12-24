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
#include <ostream>

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
bksge::string to_string(ShaderType const& shader_type);

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

#include <bksge/fnd/type_traits/underlying_type.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <functional>

namespace std
{

template<>
struct hash<bksge::render::ShaderType>
{
	bksge::size_t operator()(bksge::render::ShaderType const& arg) const
	{
		using type = bksge::underlying_type_t<bksge::render::ShaderType>;
		return std::hash<type>{}(static_cast<type>(arg));
	}
};

}	// namespace std

#endif // BKSGE_CXX_STANDARD <= 11

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/shader_type_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_SHADER_TYPE_HPP
