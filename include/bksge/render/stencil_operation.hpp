/**
 *	@file	stencil_operation.hpp
 *
 *	@brief	StencilOperation の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_STENCIL_OPERATION_HPP
#define BKSGE_RENDER_STENCIL_OPERATION_HPP

#include <bksge/render/fwd/stencil_operation_fwd.hpp>
#include <cstdint>

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

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_STENCIL_OPERATION_HPP
