﻿/**
 *	@file	blend_operation_fwd.hpp
 *
 *	@brief	BlendOperation の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_FWD_BLEND_OPERATION_FWD_HPP
#define BKSGE_CORE_RENDER_FWD_BLEND_OPERATION_FWD_HPP

#include <bksge/fnd/cstdint/uint32_t.hpp>

namespace bksge
{

namespace render
{

enum class BlendOperation : bksge::uint32_t;

}	// namespace render

using render::BlendOperation;

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_FWD_BLEND_OPERATION_FWD_HPP
