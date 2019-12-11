/**
 *	@file	sampler.hpp
 *
 *	@brief	Sampler クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_SAMPLER_HPP
#define BKSGE_RENDER_D3D12_DETAIL_SAMPLER_HPP

#include <bksge/render/d3d12/detail/fwd/sampler_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/device_fwd.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/fwd/sampler_fwd.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

class Sampler
{
public:
	explicit Sampler(bksge::Sampler const& sampler);

	~Sampler();

	void CreateView(Device* device, ::D3D12_CPU_DESCRIPTOR_HANDLE dest);

private:
	::D3D12_SAMPLER_DESC	m_desc;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/detail/inl/sampler_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_DETAIL_SAMPLER_HPP
