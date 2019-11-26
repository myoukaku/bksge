/**
 *	@file	cull_mode.hpp
 *
 *	@brief	CullMode クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_CULL_MODE_HPP
#define BKSGE_RENDER_D3D12_DETAIL_CULL_MODE_HPP

#include <bksge/render/fwd/cull_mode_fwd.hpp>
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
class CullMode
{
public:
	explicit CullMode(bksge::CullMode cull_mode);

	operator ::D3D12_CULL_MODE() const;

private:
	::D3D12_CULL_MODE	m_cull_mode;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/detail/inl/cull_mode_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_DETAIL_CULL_MODE_HPP
