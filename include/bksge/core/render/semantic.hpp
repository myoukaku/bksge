/**
 *	@file	semantic.hpp
 *
 *	@brief	Semantic の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_SEMANTIC_HPP
#define BKSGE_CORE_RENDER_SEMANTIC_HPP

#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/ostream/basic_ostream.hpp>

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
Semantic ToSemantic(bksge::string const& semantic_str);

/**
 *	@brief	文字列への変換
 */
char const* ToSemanticName(Semantic const& semantic);

/**
 *	@brief	文字列への変換
 */
bksge::string to_string(Semantic const& semantic);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline bksge::basic_ostream<CharT, Traits>&
operator<<(bksge::basic_ostream<CharT, Traits>& os, Semantic const& rhs)
{
	return os << to_string(rhs).c_str();
}

}	// namespace render

using render::Semantic;

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/semantic_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_SEMANTIC_HPP
