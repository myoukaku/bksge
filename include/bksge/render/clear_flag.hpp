﻿/**
 *	@file	clear_flag.hpp
 *
 *	@brief	ClearFlag の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_CLEAR_FLAG_HPP
#define BKSGE_RENDER_CLEAR_FLAG_HPP

#include <bksge/config.hpp>
#include <cstdint>

namespace bksge
{

namespace render
{

/**
 *	@brief	バッファのクリアに指定するフラグ
 */
enum class ClearFlag : std::uint32_t
{
	/// クリアしない
	kNone    = 0,

	/// 色バッファをクリアする
	kColor   = (1 << 0),

	/// デプスバッファをクリアする
	kDepth   = (1 << 1),

	/// ステンシルバッファをクリアする
	kStencil = (1 << 2),

	/// 全てのバッファをクリアする
	kAll = kColor | kDepth | kStencil,
};

BKSGE_CONSTEXPR ClearFlag
operator|(ClearFlag lhs, ClearFlag rhs) BKSGE_NOEXCEPT;

BKSGE_CONSTEXPR ClearFlag
operator&(ClearFlag lhs, ClearFlag rhs) BKSGE_NOEXCEPT;

BKSGE_CONSTEXPR ClearFlag
operator^(ClearFlag lhs, ClearFlag rhs) BKSGE_NOEXCEPT;

BKSGE_CXX14_CONSTEXPR ClearFlag&
operator|=(ClearFlag& lhs, ClearFlag rhs) BKSGE_NOEXCEPT;

BKSGE_CXX14_CONSTEXPR ClearFlag&
operator&=(ClearFlag& lhs, ClearFlag rhs) BKSGE_NOEXCEPT;

BKSGE_CXX14_CONSTEXPR ClearFlag&
operator^=(ClearFlag& lhs, ClearFlag rhs) BKSGE_NOEXCEPT;

}	// namespace render

using render::ClearFlag;

}	// namespace bksge

#include <bksge/render/inl/clear_flag_inl.hpp>

#endif // BKSGE_RENDER_CLEAR_FLAG_HPP
