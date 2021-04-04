/**
 *	@file	logic_operation_inl.hpp
 *
 *	@brief	LogicOperation の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_LOGIC_OPERATION_INL_HPP
#define BKSGE_CORE_RENDER_INL_LOGIC_OPERATION_INL_HPP

#include <bksge/core/render/logic_operation.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE bksge::string
to_string(LogicOperation const& logic_operation)
{
#define BKSGE_CORE_RENDER_LOGIC_OPERATION_KVP(x)	case x: return #x

	switch (logic_operation)
	{
	BKSGE_CORE_RENDER_LOGIC_OPERATION_KVP(LogicOperation::kClear);
	BKSGE_CORE_RENDER_LOGIC_OPERATION_KVP(LogicOperation::kSet);
	BKSGE_CORE_RENDER_LOGIC_OPERATION_KVP(LogicOperation::kCopy);
	BKSGE_CORE_RENDER_LOGIC_OPERATION_KVP(LogicOperation::kCopyInverted);
	BKSGE_CORE_RENDER_LOGIC_OPERATION_KVP(LogicOperation::kNoop);
	BKSGE_CORE_RENDER_LOGIC_OPERATION_KVP(LogicOperation::kInvert);
	BKSGE_CORE_RENDER_LOGIC_OPERATION_KVP(LogicOperation::kAnd);
	BKSGE_CORE_RENDER_LOGIC_OPERATION_KVP(LogicOperation::kNand);
	BKSGE_CORE_RENDER_LOGIC_OPERATION_KVP(LogicOperation::kOr);
	BKSGE_CORE_RENDER_LOGIC_OPERATION_KVP(LogicOperation::kNor);
	BKSGE_CORE_RENDER_LOGIC_OPERATION_KVP(LogicOperation::kXor);
	BKSGE_CORE_RENDER_LOGIC_OPERATION_KVP(LogicOperation::kEquiv);
	BKSGE_CORE_RENDER_LOGIC_OPERATION_KVP(LogicOperation::kAndReverse);
	BKSGE_CORE_RENDER_LOGIC_OPERATION_KVP(LogicOperation::kAndInverted);
	BKSGE_CORE_RENDER_LOGIC_OPERATION_KVP(LogicOperation::kOrReverse);
	BKSGE_CORE_RENDER_LOGIC_OPERATION_KVP(LogicOperation::kOrInverted);
	}

	return "";

#undef BKSGE_CORE_RENDER_LOGIC_OPERATION_KVP
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_LOGIC_OPERATION_INL_HPP
