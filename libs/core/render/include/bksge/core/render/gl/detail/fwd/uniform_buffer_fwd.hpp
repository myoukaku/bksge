﻿/**
 *	@file	uniform_buffer_fwd.hpp
 *
 *	@brief	UniformBuffer クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_FWD_UNIFORM_BUFFER_FWD_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_FWD_UNIFORM_BUFFER_FWD_HPP

#include <bksge/fnd/memory/unique_ptr.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

class UniformBuffer;
using UniformBufferUnique = bksge::unique_ptr<UniformBuffer>;

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_GL_DETAIL_FWD_UNIFORM_BUFFER_FWD_HPP
