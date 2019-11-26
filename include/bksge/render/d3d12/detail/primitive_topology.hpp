/**
 *	@file	primitive_topology.hpp
 *
 *	@brief	PrimitiveTopology クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_PRIMITIVE_TOPOLOGY_HPP
#define BKSGE_RENDER_D3D12_DETAIL_PRIMITIVE_TOPOLOGY_HPP

#include <bksge/render/fwd/primitive_fwd.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

/**
 *	@brief
 */
class PrimitiveTopology
{
public:
	explicit PrimitiveTopology(bksge::Primitive primitive);

	operator ::D3D12_PRIMITIVE_TOPOLOGY() const;

private:
	::D3D12_PRIMITIVE_TOPOLOGY	m_primitive_topology;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/detail/inl/primitive_topology_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_DETAIL_PRIMITIVE_TOPOLOGY_HPP
