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
#include <string>
#include <ostream>

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
std::string to_string(FrontFace const& front_face);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, FrontFace const& rhs)
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
struct hash<bksge::render::FrontFace>
{
	bksge::size_t operator()(bksge::render::FrontFace const& arg) const
	{
		using type = bksge::underlying_type_t<bksge::render::FrontFace>;
		return std::hash<type>{}(static_cast<type>(arg));
	}
};

}	// namespace std

#endif // BKSGE_CXX_STANDARD <= 11

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/front_face_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_FRONT_FACE_HPP
