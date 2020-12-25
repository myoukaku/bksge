/**
 *	@file	cull_mode.hpp
 *
 *	@brief	CullMode の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_CULL_MODE_HPP
#define BKSGE_CORE_RENDER_CULL_MODE_HPP

#include <bksge/core/render/fwd/cull_mode_fwd.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/ostream/basic_ostream.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	ポリゴンのカリングモード
 */
enum class CullMode : bksge::uint32_t
{
	kNone,
	kFront,
	kBack,
};

/**
 *	@brief	文字列への変換
 */
bksge::string to_string(CullMode const& cull_mode);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline bksge::basic_ostream<CharT, Traits>&
operator<<(bksge::basic_ostream<CharT, Traits>& os, CullMode const& rhs)
{
	return os << to_string(rhs).c_str();
}

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/cull_mode_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_CULL_MODE_HPP
