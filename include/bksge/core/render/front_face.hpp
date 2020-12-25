/**
 *	@file	front_face.hpp
 *
 *	@brief	FrontFace の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_FRONT_FACE_HPP
#define BKSGE_CORE_RENDER_FRONT_FACE_HPP

#include <bksge/core/render/fwd/front_face_fwd.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/ostream/basic_ostream.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	ポリゴンの表面
 */
enum class FrontFace : bksge::uint32_t
{
	kClockwise,
	kCounterClockwise,
};

/**
 *	@brief	文字列への変換
 */
bksge::string to_string(FrontFace const& front_face);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline bksge::basic_ostream<CharT, Traits>&
operator<<(bksge::basic_ostream<CharT, Traits>& os, FrontFace const& rhs)
{
	return os << to_string(rhs).c_str();
}

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/front_face_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_FRONT_FACE_HPP
