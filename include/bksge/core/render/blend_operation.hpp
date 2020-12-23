/**
 *	@file	blend_operation.hpp
 *
 *	@brief	BlendOperation の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_BLEND_OPERATION_HPP
#define BKSGE_CORE_RENDER_BLEND_OPERATION_HPP

#include <bksge/core/render/fwd/blend_operation_fwd.hpp>
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

#if BKSGE_CXX_STANDARD <= 11

#include <bksge/fnd/type_traits/underlying_type.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <functional>

namespace std
{

template<>
struct hash<bksge::render::BlendOperation>
{
	bksge::size_t operator()(bksge::render::BlendOperation const& arg) const
	{
		using type = bksge::underlying_type_t<bksge::render::BlendOperation>;
		return std::hash<type>{}(static_cast<type>(arg));
	}
};

}	// namespace std

#endif // BKSGE_CXX_STANDARD <= 11

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/blend_operation_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_BLEND_OPERATION_HPP
