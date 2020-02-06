/**
 *	@file	stencil_operation_inl.hpp
 *
 *	@brief	StencilOperation の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_INL_STENCIL_OPERATION_INL_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_INL_STENCIL_OPERATION_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#include <bksge/core/render/d3d12/detail/stencil_operation.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/stencil_operation.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

namespace detail
{

inline ::D3D12_STENCIL_OP
Tod3d12StencilOperation(bksge::StencilOperation stencil_operation)
{
	switch (stencil_operation)
	{
	case bksge::StencilOperation::kKeep:         return D3D12_STENCIL_OP_KEEP;
	case bksge::StencilOperation::kZero:         return D3D12_STENCIL_OP_ZERO;
	case bksge::StencilOperation::kReplace:      return D3D12_STENCIL_OP_REPLACE;
	case bksge::StencilOperation::kIncrSaturate: return D3D12_STENCIL_OP_INCR_SAT;
	case bksge::StencilOperation::kDecrSaturate: return D3D12_STENCIL_OP_DECR_SAT;
	case bksge::StencilOperation::kInvert:       return D3D12_STENCIL_OP_INVERT;
	case bksge::StencilOperation::kIncr:         return D3D12_STENCIL_OP_INCR;
	case bksge::StencilOperation::kDecr:         return D3D12_STENCIL_OP_DECR;
	}
	return D3D12_STENCIL_OP_KEEP;
}

}	// namespace detail

BKSGE_INLINE
StencilOperation::StencilOperation(bksge::StencilOperation stencil_operation)
	: m_stencil_operation(detail::Tod3d12StencilOperation(stencil_operation))
{}

BKSGE_INLINE
StencilOperation::operator ::D3D12_STENCIL_OP() const
{
	return m_stencil_operation;
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_INL_STENCIL_OPERATION_INL_HPP
