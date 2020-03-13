/**
 *	@file	semantic.hpp
 *
 *	@brief	Semantic の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_SEMANTIC_HPP
#define BKSGE_CORE_RENDER_SEMANTIC_HPP

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

#if BKSGE_CXX_STANDARD <= 11

#include <bksge/fnd/type_traits/underlying_type.hpp>
#include <cstddef>
#include <functional>

namespace std
{

template<>
struct hash<bksge::render::Semantic>
{
	std::size_t operator()(bksge::render::Semantic const& arg) const
	{
		using type = bksge::underlying_type_t<bksge::render::Semantic>;
		return std::hash<type>{}(static_cast<type>(arg));
	}
};

}	// namespace std

#endif // BKSGE_CXX_STANDARD <= 11

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/semantic_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_SEMANTIC_HPP
