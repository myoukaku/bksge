﻿/**
 *	@file	shader_fwd.hpp
 *
 *	@brief	Shader クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_SHADER_FWD_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_SHADER_FWD_HPP

#include <bksge/core/render/detail/identifier.hpp>
#include <bksge/fnd/memory/shared_ptr.hpp>
#include <bksge/fnd/map/map.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class Shader;

using ShaderSharedPtr = bksge::shared_ptr<Shader>;
using ShaderSharedPtrMap = bksge::map<Identifier, ShaderSharedPtr>;

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_SHADER_FWD_HPP
