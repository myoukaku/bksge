/**
 *	@file	blend_operation.hpp
 *
 *	@brief	BlendOperation クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_DETAIL_BLEND_OPERATION_HPP
#define BKSGE_RENDER_D3D11_DETAIL_BLEND_OPERATION_HPP

#include <bksge/render/fwd/blend_operation_fwd.hpp>
#include <bksge/render/d3d_common/d3d11.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

/**
 *	@brief
 */
class BlendOperation
{
public:
	explicit BlendOperation(bksge::BlendOperation blend_operation);

	operator ::D3D11_BLEND_OP() const;

private:
	::D3D11_BLEND_OP	m_blend_operation;
};

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d11/detail/inl/blend_operation_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D11_DETAIL_BLEND_OPERATION_HPP
