/**
 *	@file	d3d11_sampler.hpp
 *
 *	@brief	D3D11Sampler クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_D3D11_SAMPLER_HPP
#define BKSGE_RENDER_D3D11_D3D11_SAMPLER_HPP

#include <bksge/render/d3d11/fwd/d3d11_sampler_fwd.hpp>
#include <bksge/render/d3d11/fwd/d3d11_texture_fwd.hpp>
#include <bksge/render/d3d11/fwd/d3d11_renderer_fwd.hpp>
#include <bksge/render/d3d11/d3d11.hpp>
#include <bksge/render/d3d11/com_ptr.hpp>
#include <bksge/render/fwd/sampler_fwd.hpp>
#include <memory>

namespace bksge
{

namespace render
{

/**
 *	@brief	SamplerをD3D11で使えるように変換したクラス
 */
class D3D11Sampler
{
public:
	D3D11Sampler(D3D11Renderer* renderer, Sampler const& sampler);

	~D3D11Sampler();

	std::shared_ptr<D3D11Texture> const& texture(void) const;
	ID3D11SamplerState* state(void) const;

private:
	std::shared_ptr<D3D11Texture> m_texture;
	ComPtr<ID3D11SamplerState> m_state;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d11/inl/d3d11_sampler_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D11_D3D11_SAMPLER_HPP
