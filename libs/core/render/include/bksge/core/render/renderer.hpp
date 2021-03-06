﻿/**
 *	@file	renderer.hpp
 *
 *	@brief	Renderer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_RENDERER_HPP
#define BKSGE_CORE_RENDER_RENDERER_HPP

#include <bksge/core/render/fwd/renderer_fwd.hpp>
#include <bksge/core/render/fwd/geometry_fwd.hpp>
#include <bksge/core/render/fwd/shader_fwd.hpp>
#include <bksge/core/render/fwd/shader_parameter_map_fwd.hpp>
#include <bksge/core/render/fwd/render_state_fwd.hpp>
#include <bksge/core/render/fwd/render_pass_info_fwd.hpp>
#include <bksge/fnd/vector.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	レンダラーの基底クラス
 */
class Renderer
{
public:
	Renderer(void);

	virtual ~Renderer();

	/**
	 *	@brief	レンダリングを開始します
	 */
	void Begin(void);

	/**
	 *	@brief	レンダリングを終了します
	 */
	void End(void);

	/**
	 *	@brief	レンダリングパスを開始します
	 */
	void BeginRenderPass(RenderPassInfo const& render_pass_info);

	/**
	 *	@brief	レンダリングパスを終了します
	 */
	void EndRenderPass(void);

	/**
	 *	@brief	Geometryを1つ描画します
	 *
	 *	@param	geometry				描画するジオメトリ
	 *	@param	shader					描画に使用するシェーダ
	 *	@param	shader_parameter_map	シェーダのパラメータ
	 *	@param	render_state			レンダリングステート
	 */
	bool Render(
		Geometry const& geometry,
		Shader const& shader,
		ShaderParameterMap const& shader_parameter_map,
		RenderState const& render_state);

private:
	virtual void VBegin(void) = 0;

	virtual void VEnd(void) = 0;

	virtual void VBeginRenderPass(RenderPassInfo const& render_pass_info) = 0;

	virtual void VEndRenderPass(void) = 0;

	virtual bool VRender(
		Geometry const& geometry,
		Shader const& shader,
		ShaderParameterMap const& shader_parameter_map,
		RenderState const& render_state) = 0;
};

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/renderer_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_RENDERER_HPP
