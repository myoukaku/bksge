/**
 *	@file	front_face.hpp
 *
 *	@brief	FrontFace の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_FRONT_FACE_HPP
#define BKSGE_RENDER_FRONT_FACE_HPP

#include <bksge/render/fwd/front_face_fwd.hpp>
#include <cstdint>
#include <string>
#include <ostream>

namespace bksge
{

namespace render
{

/**
 *	@brief	ポリゴンの表面
 */
enum class FrontFace : std::uint32_t
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

#include <functional>
#include <type_traits>

namespace std
{

template<>
struct hash<bksge::render::FrontFace>
{
	std::size_t operator()(bksge::render::FrontFace const& arg) const
	{
		using underlying_type =
			typename std::underlying_type<bksge::render::FrontFace>::type;
		return std::hash<underlying_type>{}(static_cast<underlying_type>(arg));
	}
};

}	// namespace std

#endif // BKSGE_CXX_STANDARD <= 11

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/inl/front_face_inl.hpp>
#endif

#endif // BKSGE_RENDER_FRONT_FACE_HPP
