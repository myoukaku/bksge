/**
 *	@file	blend_operation_inl.hpp
 *
 *	@brief	BlendOperation クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_DETAIL_INL_BLEND_OPERATION_INL_HPP
#define BKSGE_RENDER_D3D11_DETAIL_INL_BLEND_OPERATION_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D11_RENDERER

#include <bksge/render/d3d11/detail/blend_operation.hpp>
#include <bksge/render/d3d_common/d3d11.hpp>
#include <bksge/render/blend_operation.hpp>
#include <unordered_map>

namespace bksge
{

namespace render
{

namespace d3d11
{

namespace detail
{

inline ::D3D11_BLEND_OP
D3D11BlendOperation(bksge::BlendOperation blend_operation)
{
	static std::unordered_map<bksge::BlendOperation, ::D3D11_BLEND_OP> const m =
	{
		{ bksge::BlendOperation::kAdd,             D3D11_BLEND_OP_ADD },
		{ bksge::BlendOperation::kSubtract,        D3D11_BLEND_OP_SUBTRACT },
		{ bksge::BlendOperation::kReverseSubtract, D3D11_BLEND_OP_REV_SUBTRACT },
		{ bksge::BlendOperation::kMin,             D3D11_BLEND_OP_MIN },
		{ bksge::BlendOperation::kMax,             D3D11_BLEND_OP_MAX },
	};

	return m.at(blend_operation);
}

}	// namespace detail

BKSGE_INLINE
BlendOperation::BlendOperation(bksge::BlendOperation blend_operation)
	: m_blend_operation(detail::D3D11BlendOperation(blend_operation))
{}

BKSGE_INLINE
BlendOperation::operator ::D3D11_BLEND_OP() const
{
	return m_blend_operation;
}

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_DETAIL_INL_BLEND_OPERATION_INL_HPP
