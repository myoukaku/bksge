/**
 *	@file	d3d11_shader.hpp
 *
 *	@brief	D3D11Shader クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_D3D11_SHADER_HPP
#define BKSGE_RENDER_D3D11_D3D11_SHADER_HPP

#include <bksge/render/d3d11/fwd/d3d11_shader_fwd.hpp>
#include <bksge/render/d3d11/fwd/d3d11_renderer_fwd.hpp>
#include <bksge/render/fwd/geometry_fwd.hpp>
#include <bksge/render/fwd/shader_fwd.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
class D3D11Shader
{
public:
	D3D11Shader(D3D11Renderer* renderer, Shader const& shader);

	void Render(D3D11Renderer* renderer, Geometry const& geometry, Shader const& shader);

private:
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d11/inl/d3d11_shader_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D11_D3D11_SHADER_HPP
