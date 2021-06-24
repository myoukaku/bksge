/**
 *	@file	filter_mode.hpp
 *
 *	@brief	FilterMode クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_FILTER_MODE_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_FILTER_MODE_HPP

#include <bksge/core/render/fwd/filter_mode_fwd.hpp>
#include <bksge/core/render/fwd/mipmap_mode_fwd.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief	FilterMode を OpenGL の enum に変換
 */
class FilterMode
{
public:
	explicit FilterMode(bksge::FilterMode mag_filter);

	explicit FilterMode(
		bksge::FilterMode min_filter,
		bksge::MipmapMode mip_filter);

	operator ::GLint() const;

private:
	::GLint const	m_mode;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/filter_mode_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_FILTER_MODE_HPP
