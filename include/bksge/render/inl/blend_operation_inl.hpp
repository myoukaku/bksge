/**
 *	@file	blend_operation_inl.hpp
 *
 *	@brief	BlendOperation の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_INL_BLEND_OPERATION_INL_HPP
#define BKSGE_RENDER_INL_BLEND_OPERATION_INL_HPP

#include <bksge/render/blend_operation.hpp>
#include <unordered_map>
#include <string>

namespace bksge
{

namespace render
{

BKSGE_INLINE
std::string to_string(BlendOperation const& blend_operation)
{
#define BKSGE_RENDER_MAKE_BLEND_OPERATION_KVP(x)	{ x, #x }

	static std::unordered_map<BlendOperation, std::string> const m =
	{
		BKSGE_RENDER_MAKE_BLEND_OPERATION_KVP(BlendOperation::kAdd),
		BKSGE_RENDER_MAKE_BLEND_OPERATION_KVP(BlendOperation::kSubtract),
		BKSGE_RENDER_MAKE_BLEND_OPERATION_KVP(BlendOperation::kReverseSubtract),
		BKSGE_RENDER_MAKE_BLEND_OPERATION_KVP(BlendOperation::kMin),
		BKSGE_RENDER_MAKE_BLEND_OPERATION_KVP(BlendOperation::kMax),
	};

	return m.at(blend_operation);

#undef BKSGE_RENDER_MAKE_BLEND_OPERATION_KVP
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_INL_BLEND_OPERATION_INL_HPP
