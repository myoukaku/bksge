/**
 *	@file	render_pass_info.hpp
 *
 *	@brief	RenderPassInfo クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_RENDER_PASS_INFO_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_RENDER_PASS_INFO_HPP

#include <bksge/core/render/fwd/render_pass_info_fwd.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

class RenderPassInfo
{
public:
	static void Apply(bksge::RenderPassInfo const& info);
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/render_pass_info_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_RENDER_PASS_INFO_HPP
