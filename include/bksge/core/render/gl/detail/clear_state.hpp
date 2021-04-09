/**
 *	@file	clear_state.hpp
 *
 *	@brief	ClearState クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_CLEAR_STATE_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_CLEAR_STATE_HPP

#include <bksge/core/render/fwd/clear_state_fwd.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

class ClearState
{
public:
	static void Apply(bksge::ClearState const& state);
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/clear_state_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_CLEAR_STATE_HPP
