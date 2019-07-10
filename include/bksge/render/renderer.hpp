/**
 *	@file	renderer.hpp
 *
 *	@brief	Renderer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_RENDERER_HPP
#define BKSGE_RENDER_RENDERER_HPP

#include <bksge/render/fwd/renderer_fwd.hpp>
#include <bksge/render/fwd/geometry_fwd.hpp>
#include <bksge/render/fwd/shader_fwd.hpp>
#include <bksge/render/fwd/shader_parameter_map_fwd.hpp>
#include <bksge/render/fwd/render_state_fwd.hpp>
#include <bksge/render/clear_flag.hpp>
#include <bksge/window/fwd/window_fwd.hpp>
#include <bksge/math/color4.hpp>
#include <bksge/math/rect.hpp>
#include <memory>
#include <vector>

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
	 *	@brief	レンダリングターゲットを設定します
	 */
	void SetRenderTarget(Window const& window);

	/**
	 *	@brief	ビューポート矩形を設定します
	 */
	void SetViewport(Rectf const& viewport);

	/**
	 *	@brief	レンダリングターゲットのクリアフラグを設定します。
	 *
	 *	@param	clear_flag	ClearFlagの論理和を設定します
	 */
	void SetClearFlag(ClearFlag clear_flag);

	/**
	 *	@brief	レンダリングターゲットをクリアする色を設定します。
	 *
	 *	@param	clear_color	クリアする色
	 */
	void SetClearColor(Color4f const& clear_color);

	/**
	 *	@brief	レンダリングを開始します
	 */
	void Begin(void);

	/**
	 *	@brief	レンダリングを終了します
	 */
	void End(void);

	/**
	 *	@brief	Geometryを1つ描画します
	 *
	 *	@param	geometry				描画するジオメトリ
	 *	@param	shader_map				描画に使用するシェーダ
	 *	@param	shader_parameter_map	シェーダのパラメータ
	 *	@param	render_state			レンダリングステート
	 */
	void Render(
		Geometry const& geometry,
		std::vector<Shader const*> const& shader_list,
		ShaderParameterMap const& shader_parameter_map,
		RenderState const& render_state);

private:
	virtual void VSetRenderTarget(Window const& window) = 0;

	virtual void VBegin(void) = 0;

	virtual void VEnd(void) = 0;

	virtual bool VRender(
		Geometry const& geometry,
		Shader const& shader,
		ShaderParameterMap const& shader_parameter_map,
		RenderState const& render_state) = 0;

protected:
	ClearFlag					m_clear_flag;
	Color4f						m_clear_color;
	std::unique_ptr<Rectf>		m_viewport;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/inl/renderer_inl.hpp>
#endif

#endif // BKSGE_RENDER_RENDERER_HPP
