﻿/**
 *	@file	primitive.hpp
 *
 *	@brief	Primitive の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_PRIMITIVE_HPP
#define BKSGE_RENDER_PRIMITIVE_HPP

#include <bksge/render/fwd/primitive_fwd.hpp>
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

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/inl/primitive_inl.hpp>
#endif

#endif // BKSGE_RENDER_PRIMITIVE_HPP
