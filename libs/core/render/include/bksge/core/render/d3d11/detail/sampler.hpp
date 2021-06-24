/**
 *	@file	sampler.hpp
 *
 *	@brief	Sampler クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_SAMPLER_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_SAMPLER_HPP

#include <bksge/core/render/d3d11/detail/fwd/sampler_fwd.hpp>
#include <bksge/core/render/d3d11/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/d3d_common/d3d11.hpp>
#include <bksge/core/render/d3d_common/com_ptr.hpp>
#include <bksge/core/render/fwd/sampler_fwd.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

/**
 *	@brief
 */
class Sampler
{
public:
	explicit Sampler(Device* device, bksge::Sampler const& sampler);

	~Sampler();

	ComPtr<::ID3D11SamplerState> const& state(void) const;

private:
	// noncopyable
	Sampler(Sampler const&) = delete;
	Sampler& operator=(Sampler const&) = delete;

private:
	ComPtr<::ID3D11SamplerState>	m_state;
};

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d11/detail/inl/sampler_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_SAMPLER_HPP
