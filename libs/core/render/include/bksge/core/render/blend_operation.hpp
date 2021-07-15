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
#include <bksge/fnd/string/string.hpp>
#include <ostream>
#include <cstdint>

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
bksge::string to_string(BlendOperation const& blend_operation);

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

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/blend_operation_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_BLEND_OPERATION_HPP
