/**
 *	@file	comparison_function.hpp
 *
 *	@brief	ComparisonFunction クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_comparison_function_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_comparison_function_HPP

#include <bksge/core/render/fwd/comparison_function_fwd.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief	ComparisonFunction を OpenGL の enum に変換
 */
class ComparisonFunction
{
public:
	explicit ComparisonFunction(bksge::ComparisonFunction comparison_function);

	operator ::GLenum() const;

private:
	::GLenum	m_comparison_function;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/comparison_function_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_comparison_function_HPP
