/**
 *	@file	filter_mode.hpp
 *
 *	@brief	FilterMode の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_FILTER_MODE_HPP
#define BKSGE_CORE_RENDER_FILTER_MODE_HPP

#include <bksge/core/render/fwd/filter_mode_fwd.hpp>
#include <string>
#include <ostream>

namespace bksge
{

namespace render
{

/**
 *	@brief	テクスチャの拡大・縮小時の補間方法
 */
enum class FilterMode
{
	kNearest,	///< テクセル座標に最も近いテクセルの値を読み出してテクスチャ値とする
	kLinear,	///< テクセル座標に最も近い4つのテクセルの値を読み出し、それらの加重平均をテクスチャ値とする
};

/**
 *	@brief	文字列への変換
 */
std::string to_string(FilterMode const& filter_mode);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, FilterMode const& rhs)
{
	return os << to_string(rhs).c_str();
}

}	// namespace render

}	// namespace bksge

#if BKSGE_CXX_STANDARD <= 11

#include <bksge/fnd/type_traits/underlying_type.hpp>
#include <functional>
#include <cstddef>

namespace std
{

template<>
struct hash<bksge::render::FilterMode>
{
	std::size_t operator()(bksge::render::FilterMode const& arg) const
	{
		using type = bksge::underlying_type_t<bksge::render::FilterMode>;
		return std::hash<type>{}(static_cast<type>(arg));
	}
};

}	// namespace std

#endif // BKSGE_CXX_STANDARD <= 11

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/filter_mode_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_FILTER_MODE_HPP
