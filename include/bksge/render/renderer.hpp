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
#include <bksge/render/clear_flag.hpp>
#include <bksge/window/fwd/window_fwd.hpp>
#include <bksge/math/color4.hpp>

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
	 *	@brief	レンダリングを開始します
	 */
	void Begin(void);

	/**
	 *	@brief	レンダリングを終了します
	 */
	void End(void);

	/**
	 *	@brief	バッファをクリアします
	 */
	void Clear(void);

	/**
	 *	@brief	Geometryを1つ描画します
	 *
	 *	@param	geometry	描画するジオメトリ
	 *	@param	shader		描画に使うシェーダ
	 *
	 *	geometryによって描画する形状(幾何)が決まり、
	 *	shaderによって描画結果の見た目が決まります。
	 */
	void Render(Geometry const& geometry, Shader const& shader);

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

private:
	virtual void VSetRenderTarget(Window const& window) = 0;

	virtual void VBegin(void) = 0;

	virtual void VEnd(void) = 0;

	virtual void VClear(ClearFlag clear_flag, Color4f const& clear_color) = 0;

	virtual void VRender(Geometry const& geometry, Shader const& shader) = 0;

	ClearFlag  m_clear_flag;
	Color4f    m_clear_color;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/inl/renderer_inl.hpp>
#endif

#endif // BKSGE_RENDER_RENDERER_HPP
