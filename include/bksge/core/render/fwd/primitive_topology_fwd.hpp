/**
 *	@file	primitive_topology_fwd.hpp
 *
 *	@brief	PrimitiveTopology の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_FWD_PRIMITIVE_TOPOLOGY_FWD_HPP
#define BKSGE_CORE_RENDER_FWD_PRIMITIVE_TOPOLOGY_FWD_HPP

#include <bksge/fnd/cstdint/uint32_t.hpp>

namespace bksge
{

namespace render
{

enum class PrimitiveTopology : bksge::uint32_t;

}	// namespace render

using render::PrimitiveTopology;

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_FWD_PRIMITIVE_TOPOLOGY_FWD_HPP
