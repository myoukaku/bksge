/**
 *	@file	stencil_operation_fwd.hpp
 *
 *	@brief	StencilOperation の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_FWD_STENCIL_OPERATION_FWD_HPP
#define BKSGE_CORE_RENDER_FWD_STENCIL_OPERATION_FWD_HPP

#include <cstdint>

namespace bksge
{

namespace render
{

enum class StencilOperation : std::uint32_t;

}	// namespace render

using render::StencilOperation;

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_FWD_STENCIL_OPERATION_FWD_HPP
