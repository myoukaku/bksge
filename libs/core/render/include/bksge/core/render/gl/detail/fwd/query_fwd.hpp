/**
 *	@file	query_fwd.hpp
 *
 *	@brief	Query クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_FWD_QUERY_FWD_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_FWD_QUERY_FWD_HPP

#include <bksge/fnd/memory/unique_ptr.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

class Query;
using QueryUnique = bksge::unique_ptr<Query>;

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_GL_DETAIL_FWD_QUERY_FWD_HPP
