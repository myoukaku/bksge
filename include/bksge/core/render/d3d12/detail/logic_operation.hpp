/**
 *	@file	logic_operation.hpp
 *
 *	@brief	LogicOperation クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_LOGIC_OPERATION_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_LOGIC_OPERATION_HPP

#include <bksge/core/render/fwd/logic_operation_fwd.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

/**
 *	@brief
 */
class LogicOperation
{
public:
	explicit LogicOperation(bksge::LogicOperation logic_operation);

	operator ::D3D12_LOGIC_OP() const;

private:
	::D3D12_LOGIC_OP	m_logic_operation;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d12/detail/inl/logic_operation_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_LOGIC_OPERATION_HPP
