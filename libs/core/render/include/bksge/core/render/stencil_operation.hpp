/**
 *	@file	stencil_operation.hpp
 *
 *	@brief	StencilOperation の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_STENCIL_OPERATION_HPP
#define BKSGE_CORE_RENDER_STENCIL_OPERATION_HPP

#include <bksge/core/render/fwd/stencil_operation_fwd.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>
#include <bksge/fnd/string/string.hpp>
#include <ostream>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
enum class StencilOperation : bksge::uint32_t
{
	kKeep,
	kZero,
	kReplace,
	kIncrSaturate,
	kDecrSaturate,
	kInvert,
	kIncr,
	kDecr,
};

/**
 *	@brief	文字列への変換
 */
bksge::string to_string(StencilOperation const& stencil_operation);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, StencilOperation const& rhs)
{
	return os << to_string(rhs).c_str();
}

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/stencil_operation_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_STENCIL_OPERATION_HPP
