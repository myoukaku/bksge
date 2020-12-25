/**
 *	@file	primitive_topology.hpp
 *
 *	@brief	PrimitiveTopology の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_PRIMITIVE_TOPOLOGY_HPP
#define BKSGE_CORE_RENDER_PRIMITIVE_TOPOLOGY_HPP

#include <bksge/core/render/fwd/primitive_topology_fwd.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/ostream/basic_ostream.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	描画プリミティブの種類
 */
enum class PrimitiveTopology
{
	kPoints,
	kLines,
	kTriangles,
};

/**
 *	@brief	文字列への変換
 */
bksge::string to_string(PrimitiveTopology const& primitive_topology);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline bksge::basic_ostream<CharT, Traits>&
operator<<(bksge::basic_ostream<CharT, Traits>& os, PrimitiveTopology const& rhs)
{
	return os << to_string(rhs).c_str();
}

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/primitive_topology_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_PRIMITIVE_TOPOLOGY_HPP
