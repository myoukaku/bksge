/**
 *	@file	blend_operation.hpp
 *
 *	@brief	BlendOperation の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_BLEND_OPERATION_HPP
#define BKSGE_RENDER_BLEND_OPERATION_HPP

#include <bksge/render/fwd/blend_operation_fwd.hpp>
#include <cstdint>

namespace bksge
{

namespace render
{

/**
 *	@brief	ブレンド方法
 */
enum class BlendOperation : std::uint32_t
{
	kAdd,
	kSubtract,
	kReverseSubtract,
	kMin,
	kMax,
};

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_BLEND_OPERATION_HPP
