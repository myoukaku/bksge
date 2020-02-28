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
#include <cstdint>
#include <string>
#include <ostream>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
enum class StencilOperation : std::uint32_t
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
std::string to_string(StencilOperation const& stencil_operation);

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

#if BKSGE_CXX_STANDARD <= 11

#include <bksge/fnd/type_traits/underlying_type.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <functional>

namespace std
{

template<>
struct hash<bksge::render::StencilOperation>
{
	bksge::size_t operator()(bksge::render::StencilOperation const& arg) const
	{
		using type = bksge::underlying_type_t<bksge::render::StencilOperation>;
		return std::hash<type>{}(static_cast<type>(arg));
	}
};

}	// namespace std

#endif // BKSGE_CXX_STANDARD <= 11

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/stencil_operation_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_STENCIL_OPERATION_HPP
