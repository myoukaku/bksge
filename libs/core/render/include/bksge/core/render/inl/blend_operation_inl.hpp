/**
 *	@file	blend_operation_inl.hpp
 *
 *	@brief	BlendOperation の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_BLEND_OPERATION_INL_HPP
#define BKSGE_CORE_RENDER_INL_BLEND_OPERATION_INL_HPP

#include <bksge/core/render/blend_operation.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE bksge::string
to_string(BlendOperation const& blend_operation)
{
#define BKSGE_CORE_RENDER_BLEND_OPERATION_KVP(x)	case x: return #x

	switch (blend_operation)
	{
		BKSGE_CORE_RENDER_BLEND_OPERATION_KVP(BlendOperation::kAdd);
		BKSGE_CORE_RENDER_BLEND_OPERATION_KVP(BlendOperation::kSubtract);
		BKSGE_CORE_RENDER_BLEND_OPERATION_KVP(BlendOperation::kReverseSubtract);
		BKSGE_CORE_RENDER_BLEND_OPERATION_KVP(BlendOperation::kMin);
		BKSGE_CORE_RENDER_BLEND_OPERATION_KVP(BlendOperation::kMax);
	}

	return "";

#undef BKSGE_CORE_RENDER_BLEND_OPERATION_KVP
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_BLEND_OPERATION_INL_HPP
