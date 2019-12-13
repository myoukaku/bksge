/**
 *	@file	stencil_operation_inl.hpp
 *
 *	@brief	StencilOperation の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_STENCIL_OPERATION_INL_HPP
#define BKSGE_CORE_RENDER_INL_STENCIL_OPERATION_INL_HPP

#include <bksge/core/render/stencil_operation.hpp>
#include <unordered_map>
#include <string>

namespace bksge
{

namespace render
{

BKSGE_INLINE
std::string to_string(StencilOperation const& stencil_operation)
{
#define BKSGE_CORE_RENDER_MAKE_STENCIL_OPERATION_KVP(x)	{ x, #x }

	static std::unordered_map<StencilOperation, std::string> const m =
	{
		BKSGE_CORE_RENDER_MAKE_STENCIL_OPERATION_KVP(StencilOperation::kKeep),
		BKSGE_CORE_RENDER_MAKE_STENCIL_OPERATION_KVP(StencilOperation::kZero),
		BKSGE_CORE_RENDER_MAKE_STENCIL_OPERATION_KVP(StencilOperation::kReplace),
		BKSGE_CORE_RENDER_MAKE_STENCIL_OPERATION_KVP(StencilOperation::kIncrSaturate),
		BKSGE_CORE_RENDER_MAKE_STENCIL_OPERATION_KVP(StencilOperation::kDecrSaturate),
		BKSGE_CORE_RENDER_MAKE_STENCIL_OPERATION_KVP(StencilOperation::kInvert),
		BKSGE_CORE_RENDER_MAKE_STENCIL_OPERATION_KVP(StencilOperation::kIncr),
		BKSGE_CORE_RENDER_MAKE_STENCIL_OPERATION_KVP(StencilOperation::kDecr),
	};

	return m.at(stencil_operation);

#undef BKSGE_CORE_RENDER_MAKE_STENCIL_OPERATION_KVP
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_STENCIL_OPERATION_INL_HPP
