/**
 *	@file	primitive_topology_inl.hpp
 *
 *	@brief	PrimitiveTopology の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_PRIMITIVE_TOPOLOGY_INL_HPP
#define BKSGE_CORE_RENDER_INL_PRIMITIVE_TOPOLOGY_INL_HPP

#include <bksge/core/render/primitive_topology.hpp>
#include <unordered_map>
#include <string>

namespace bksge
{

namespace render
{

BKSGE_INLINE
std::string to_string(PrimitiveTopology const& primitive_topology)
{
#define BKSGE_CORE_RENDER_MAKE_PRIMITIVE_TOPOLOGY_KVP(x)	{ x, #x }

	static std::unordered_map<PrimitiveTopology, std::string> const m =
	{
		BKSGE_CORE_RENDER_MAKE_PRIMITIVE_TOPOLOGY_KVP(PrimitiveTopology::kPoints),
		BKSGE_CORE_RENDER_MAKE_PRIMITIVE_TOPOLOGY_KVP(PrimitiveTopology::kLines),
		BKSGE_CORE_RENDER_MAKE_PRIMITIVE_TOPOLOGY_KVP(PrimitiveTopology::kTriangles),
	};

	return m.at(primitive_topology);

#undef BKSGE_CORE_RENDER_MAKE_PRIMITIVE_TOPOLOGY_KVP
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_PRIMITIVE_TOPOLOGY_INL_HPP
