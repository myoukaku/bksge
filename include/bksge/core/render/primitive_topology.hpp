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
#include <ostream>
#include <string>

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
std::string to_string(PrimitiveTopology const& primitive_topology);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, PrimitiveTopology const& rhs)
{
	return os << to_string(rhs).c_str();
}

}	// namespace render

}	// namespace bksge

#if BKSGE_CXX_STANDARD <= 11

#include <bksge/fnd/type_traits/underlying_type.hpp>
#include <cstddef>
#include <functional>

namespace std
{

template<>
struct hash<bksge::render::PrimitiveTopology>
{
	std::size_t operator()(bksge::render::PrimitiveTopology const& arg) const
	{
		using type = bksge::underlying_type_t<bksge::render::PrimitiveTopology>;
		return std::hash<type>{}(static_cast<type>(arg));
	}
};

}	// namespace std

#endif // BKSGE_CXX_STANDARD <= 11

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/primitive_topology_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_PRIMITIVE_TOPOLOGY_HPP
