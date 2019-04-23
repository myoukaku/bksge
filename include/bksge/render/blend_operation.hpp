/**
 *	@file	blend_operation.hpp
 *
 *	@brief	BlendOperation の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_BLEND_OPERATION_HPP
#define BKSGE_RENDER_BLEND_OPERATION_HPP

#include <bksge/render/fwd/blend_operation_fwd.hpp>
#include <cstdint>
#include <string>
#include <ostream>

namespace bksge
{

namespace render
{

/**
 *	@brief	ブレンド方法
 */
enum class BlendOperation : std::uint32_t
{
	kAdd,
	kSubtract,
	kReverseSubtract,
	kMin,
	kMax,
};

/**
 *	@brief	文字列への変換
 */
std::string to_string(BlendOperation const& blend_operation);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, BlendOperation const& rhs)
{
	return os << to_string(rhs).c_str();
}

}	// namespace render

}	// namespace bksge

#if BKSGE_STD_VER <= 11

#include <functional>
#include <type_traits>

namespace std
{

template<>
struct hash<bksge::render::BlendOperation>
{
	std::size_t operator()(bksge::render::BlendOperation const& arg) const
	{
		using underlying_type =
			typename std::underlying_type<bksge::render::BlendOperation>::type;
		return std::hash<underlying_type>{}(static_cast<underlying_type>(arg));
	}
};

}	// namespace std

#endif // BKSGE_STD_VER <= 11

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/inl/blend_operation_inl.hpp>
#endif

#endif // BKSGE_RENDER_BLEND_OPERATION_HPP
