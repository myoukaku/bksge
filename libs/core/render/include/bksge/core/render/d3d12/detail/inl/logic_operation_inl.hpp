/**
 *	@file	logic_operation_inl.hpp
 *
 *	@brief	LogicOperation の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_INL_LOGIC_OPERATION_INL_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_INL_LOGIC_OPERATION_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#include <bksge/core/render/d3d12/detail/logic_operation.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/logic_operation.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

namespace detail
{

inline ::D3D12_LOGIC_OP
ToD3D12LogicOperation(bksge::LogicOperation logic_operation)
{
	switch (logic_operation)
	{
	case bksge::LogicOperation::kClear:        return D3D12_LOGIC_OP_CLEAR;
	case bksge::LogicOperation::kSet:          return D3D12_LOGIC_OP_SET;
	case bksge::LogicOperation::kCopy:         return D3D12_LOGIC_OP_COPY;
	case bksge::LogicOperation::kCopyInverted: return D3D12_LOGIC_OP_COPY_INVERTED;
	case bksge::LogicOperation::kNoop:         return D3D12_LOGIC_OP_NOOP;
	case bksge::LogicOperation::kInvert:       return D3D12_LOGIC_OP_INVERT;
	case bksge::LogicOperation::kAnd:          return D3D12_LOGIC_OP_AND;
	case bksge::LogicOperation::kNand:         return D3D12_LOGIC_OP_NAND;
	case bksge::LogicOperation::kOr:           return D3D12_LOGIC_OP_OR;
	case bksge::LogicOperation::kNor:          return D3D12_LOGIC_OP_NOR;
	case bksge::LogicOperation::kXor:          return D3D12_LOGIC_OP_XOR;
	case bksge::LogicOperation::kEquiv:        return D3D12_LOGIC_OP_EQUIV;
	case bksge::LogicOperation::kAndReverse:   return D3D12_LOGIC_OP_AND_REVERSE;
	case bksge::LogicOperation::kAndInverted:  return D3D12_LOGIC_OP_AND_INVERTED;
	case bksge::LogicOperation::kOrReverse:    return D3D12_LOGIC_OP_OR_REVERSE;
	case bksge::LogicOperation::kOrInverted:   return D3D12_LOGIC_OP_OR_INVERTED;
	}
	return D3D12_LOGIC_OP_COPY;
}

}	// namespace detail

BKSGE_INLINE
LogicOperation::LogicOperation(bksge::LogicOperation logic_operation)
	: m_logic_operation(detail::ToD3D12LogicOperation(logic_operation))
{}

BKSGE_INLINE
LogicOperation::operator D3D12_LOGIC_OP() const
{
	return m_logic_operation;
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_INL_LOGIC_OPERATION_INL_HPP
