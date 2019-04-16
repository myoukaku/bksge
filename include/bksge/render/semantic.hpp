/**
 *	@file	semantic.hpp
 *
 *	@brief	Semantic の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_SEMANTIC_HPP
#define BKSGE_RENDER_SEMANTIC_HPP

#include <ostream>
#include <string>

namespace bksge
{

namespace render
{

/**
 *	@brief	頂点データの意味
 */
enum class Semantic
{
	kPosition,
	kNormal,
	kColor,
	kTexCoord,
	kFogCoord,
	kPointSize,
	kBlendWeight,
	kBlendIndices,
	kTangent,
	kBinormal,

	kUnknown,
};

/**
 *	@brief	文字列からの変換
 */
Semantic ToSemantic(std::string const& semantic_str);

/**
 *	@brief	文字列への変換
 */
char const* ToSemanticName(Semantic const& semantic);

/**
 *	@brief	文字列への変換
 */
std::string to_string(Semantic const& semantic);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, Semantic const& rhs)
{
	return os << to_string(rhs).c_str();
}

}	// namespace render

using render::Semantic;

}	// namespace bksge

#if BKSGE_STD_VER <= 11

#include <functional>
#include <type_traits>

namespace std
{

template<>
struct hash<bksge::render::Semantic>
{
	std::size_t operator()(bksge::render::Semantic const& arg) const
	{
		using underlying_type = typename std::underlying_type<bksge::render::Semantic>::type;
		return std::hash<underlying_type>{}(static_cast<underlying_type>(arg));
	}
};

}	// namespace std

#endif // BKSGE_STD_VER <= 11

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/inl/semantic_inl.hpp>
#endif

#endif // BKSGE_RENDER_SEMANTIC_HPP
