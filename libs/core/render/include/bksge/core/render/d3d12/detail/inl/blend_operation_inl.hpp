/**
 *	@file	blend_operation_inl.hpp
 *
 *	@brief	BlendOperation の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_INL_BLEND_OPERATION_INL_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_INL_BLEND_OPERATION_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#include <bksge/core/render/d3d12/detail/blend_operation.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/blend_operation.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

namespace detail
{

inline ::D3D12_BLEND_OP
ToD3D12BlendOperation(bksge::BlendOperation blend_operation)
{
	switch (blend_operation)
	{
	case bksge::BlendOperation::kAdd:             return D3D12_BLEND_OP_ADD;
	case bksge::BlendOperation::kSubtract:        return D3D12_BLEND_OP_SUBTRACT;
	case bksge::BlendOperation::kReverseSubtract: return D3D12_BLEND_OP_REV_SUBTRACT;
	case bksge::BlendOperation::kMin:             return D3D12_BLEND_OP_MIN;
	case bksge::BlendOperation::kMax:             return D3D12_BLEND_OP_MAX;
	}
	return D3D12_BLEND_OP_ADD;
}

}	// namespace detail

BKSGE_INLINE
BlendOperation::BlendOperation(bksge::BlendOperation blend_operation)
	: m_blend_operation(detail::ToD3D12BlendOperation(blend_operation))
{}

BKSGE_INLINE
BlendOperation::operator D3D12_BLEND_OP() const
{
	return m_blend_operation;
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_INL_BLEND_OPERATION_INL_HPP
