/**
 *	@file	logic_operation.hpp
 *
 *	@brief	LogicOperation の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_LOGIC_OPERATION_HPP
#define BKSGE_CORE_RENDER_LOGIC_OPERATION_HPP

#include <bksge/core/render/fwd/logic_operation_fwd.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/ostream/basic_ostream.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	ブレンド方法
 */
enum class LogicOperation : bksge::uint32_t
{
	kClear,
	kSet,
	kCopy,
	kCopyInverted,
	kNoop,
	kInvert,
	kAnd,
	kNand,
	kOr,
	kNor,
	kXor,
	kEquiv,
	kAndReverse,
	kAndInverted,
	kOrReverse,
	kOrInverted,
};

/**
 *	@brief	文字列への変換
 */
bksge::string to_string(LogicOperation const& logic_operation);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline bksge::basic_ostream<CharT, Traits>&
operator<<(bksge::basic_ostream<CharT, Traits>& os, LogicOperation const& rhs)
{
	return os << to_string(rhs).c_str();
}

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/logic_operation_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_LOGIC_OPERATION_HPP
