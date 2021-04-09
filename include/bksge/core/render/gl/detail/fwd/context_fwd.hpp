/**
 *	@file	context_fwd.hpp
 *
 *	@brief	Context クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_FWD_CONTEXT_FWD_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_FWD_CONTEXT_FWD_HPP

#include <bksge/fnd/memory/unique_ptr.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

class Context;
using ContextUnique = bksge::unique_ptr<Context>;

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_GL_DETAIL_FWD_CONTEXT_FWD_HPP
