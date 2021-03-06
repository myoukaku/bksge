﻿/**
 *	@file	stencil_operation.hpp
 *
 *	@brief	StencilOperation クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_STENCIL_OPERATION_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_STENCIL_OPERATION_HPP

#include <bksge/core/render/stencil_operation.hpp>
#include <bksge/core/render/d3d_common/d3d11.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

/**
 *	@brief
 */
class StencilOperation
{
public:
	explicit StencilOperation(bksge::StencilOperation stencil_operation);

	operator ::D3D11_STENCIL_OP() const;

private:
	::D3D11_STENCIL_OP	m_stencil_operation;
};

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d11/detail/inl/stencil_operation_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_STENCIL_OPERATION_HPP
