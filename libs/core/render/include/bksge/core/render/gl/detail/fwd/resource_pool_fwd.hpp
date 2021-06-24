/**
 *	@file	resource_pool_fwd.hpp
 *
 *	@brief	ResourcePool クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_FWD_RESOURCE_POOL_FWD_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_FWD_RESOURCE_POOL_FWD_HPP

#include <bksge/fnd/memory/unique_ptr.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

class ResourcePool;
using ResourcePoolUnique = bksge::unique_ptr<ResourcePool>;

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_GL_DETAIL_FWD_RESOURCE_POOL_FWD_HPP
