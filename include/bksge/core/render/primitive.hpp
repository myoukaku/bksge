/**
 *	@file	primitive.hpp
 *
 *	@brief	Primitive の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_PRIMITIVE_HPP
#define BKSGE_CORE_RENDER_PRIMITIVE_HPP

#include <bksge/core/render/fwd/primitive_fwd.hpp>
#include <ostream>
#include <string>

namespace bksge
{

namespace render
{

/**
 *	@brief	描画プリミティブの種類
 */
enum class Primitive
{
	kPoints,
	kLines,
	kTriangles,
};

/**
 *	@brief	文字列への変換
 */
std::string to_string(Primitive const& primitive);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, Primitive const& rhs)
{
	return os << to_string(rhs).c_str();
}

}	// namespace render

}	// namespace bksge

#if BKSGE_CXX_STANDARD <= 11

#include <functional>
#include <type_traits>

namespace std
{

template<>
struct hash<bksge::render::Primitive>
{
	std::size_t operator()(bksge::render::Primitive const& arg) const
	{
		using underlying_type = typename std::underlying_type<bksge::render::Primitive>::type;
		return std::hash<underlying_type>{}(static_cast<underlying_type>(arg));
	}
};

}	// namespace std

#endif // BKSGE_CXX_STANDARD <= 11

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/primitive_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_PRIMITIVE_HPP
