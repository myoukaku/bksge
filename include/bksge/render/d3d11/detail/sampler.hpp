/**
 *	@file	sampler.hpp
 *
 *	@brief	Sampler クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_DETAIL_SAMPLER_HPP
#define BKSGE_RENDER_D3D11_DETAIL_SAMPLER_HPP

#include <bksge/render/d3d11/detail/fwd/sampler_fwd.hpp>
#include <bksge/render/d3d11/detail/fwd/texture_fwd.hpp>
#include <bksge/render/d3d11/fwd/d3d11_renderer_fwd.hpp>
#include <bksge/render/d3d_common/d3d11.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
#include <bksge/render/fwd/sampler_fwd.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace d3d11
{

#if 0
/**
 *	@brief	SamplerをD3D11で使えるように変換したクラス
 */
class Sampler
{
public:
	Sampler(D3D11Renderer* renderer, bksge::Sampler const& sampler);

	~Sampler();

	std::shared_ptr<Texture> const& texture(void) const;
	::ID3D11SamplerState* state(void) const;

private:
	std::shared_ptr<Texture> m_texture;
	ComPtr<::ID3D11SamplerState> m_state;
};
#endif

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d11/detail/inl/sampler_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D11_DETAIL_SAMPLER_HPP
