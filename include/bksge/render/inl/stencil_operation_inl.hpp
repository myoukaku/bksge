/**
 *	@file	stencil_operation_inl.hpp
 *
 *	@brief	StencilOperation の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_INL_STENCIL_OPERATION_INL_HPP
#define BKSGE_RENDER_INL_STENCIL_OPERATION_INL_HPP

#include <bksge/render/stencil_operation.hpp>
#include <unordered_map>
#include <string>

namespace bksge
{

namespace render
{

BKSGE_INLINE
std::string to_string(StencilOperation const& stencil_operation)
{
#define BKSGE_RENDER_MAKE_STENCIL_OPERATION_KVP(x)	{ x, #x }

	static std::unordered_map<StencilOperation, std::string> const m =
	{
		BKSGE_RENDER_MAKE_STENCIL_OPERATION_KVP(StencilOperation::kKeep),
		BKSGE_RENDER_MAKE_STENCIL_OPERATION_KVP(StencilOperation::kZero),
		BKSGE_RENDER_MAKE_STENCIL_OPERATION_KVP(StencilOperation::kReplace),
		BKSGE_RENDER_MAKE_STENCIL_OPERATION_KVP(StencilOperation::kIncrSaturate),
		BKSGE_RENDER_MAKE_STENCIL_OPERATION_KVP(StencilOperation::kDecrSaturate),
		BKSGE_RENDER_MAKE_STENCIL_OPERATION_KVP(StencilOperation::kInvert),
		BKSGE_RENDER_MAKE_STENCIL_OPERATION_KVP(StencilOperation::kIncr),
		BKSGE_RENDER_MAKE_STENCIL_OPERATION_KVP(StencilOperation::kDecr),
	};

	return m.at(stencil_operation);

#undef BKSGE_RENDER_MAKE_STENCIL_OPERATION_KVP
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_INL_STENCIL_OPERATION_INL_HPP
