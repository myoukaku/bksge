/**
 *	@file	mipmap_mode.hpp
 *
 *	@brief	MipmapMode の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_MIPMAP_MODE_HPP
#define BKSGE_CORE_RENDER_MIPMAP_MODE_HPP

#include <bksge/core/render/fwd/mipmap_mode_fwd.hpp>
#include <bksge/fnd/string/string.hpp>
#include <ostream>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
enum class MipmapMode : bksge::uint32_t
{
	kDisable,
	kNearest,
	kLinear,
};

/**
 *	@brief	文字列への変換
 */
bksge::string to_string(MipmapMode const& mipmap_mode);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, MipmapMode const& rhs)
{
	return os << to_string(rhs).c_str();
}

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/mipmap_mode_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_MIPMAP_MODE_HPP
