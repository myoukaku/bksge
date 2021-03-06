﻿/**
 *	@file	uniform_buffer_setter_fwd.hpp
 *
 *	@brief	UniformBufferSetter クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_UNIFORM_BUFFER_SETTER_FWD_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_UNIFORM_BUFFER_SETTER_FWD_HPP

#include <bksge/fnd/memory/unique_ptr.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class UniformBufferSetter;
using UniformBufferSetterUniquePtr = bksge::unique_ptr<UniformBufferSetter>;

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_UNIFORM_BUFFER_SETTER_FWD_HPP
