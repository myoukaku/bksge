/**
 *	@file	logic_operation_inl.hpp
 *
 *	@brief	LogicOperation クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_LOGIC_OPERATION_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_LOGIC_OPERATION_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/logic_operation.hpp>
#include <bksge/core/render/logic_operation.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

namespace detail
{

inline ::GLenum
ToGlLogicOperation(bksge::LogicOperation logic_operation)
{
	switch (logic_operation)
	{
	case bksge::LogicOperation::kClear:        return GL_CLEAR;
	case bksge::LogicOperation::kSet:          return GL_SET;
	case bksge::LogicOperation::kCopy:         return GL_COPY;
	case bksge::LogicOperation::kCopyInverted: return GL_COPY_INVERTED;
	case bksge::LogicOperation::kNoop:         return GL_NOOP;
	case bksge::LogicOperation::kInvert:       return GL_INVERT;
	case bksge::LogicOperation::kAnd:          return GL_AND;
	case bksge::LogicOperation::kNand:         return GL_NAND;
	case bksge::LogicOperation::kOr:           return GL_OR;
	case bksge::LogicOperation::kNor:          return GL_NOR;
	case bksge::LogicOperation::kXor:          return GL_XOR;
	case bksge::LogicOperation::kEquiv:        return GL_EQUIV;
	case bksge::LogicOperation::kAndReverse:   return GL_AND_REVERSE;
	case bksge::LogicOperation::kAndInverted:  return GL_AND_INVERTED;
	case bksge::LogicOperation::kOrReverse:    return GL_OR_REVERSE;
	case bksge::LogicOperation::kOrInverted:   return GL_OR_INVERTED;
	}
	return GL_COPY;
}

}	// namespace detail

BKSGE_INLINE
LogicOperation::LogicOperation(bksge::LogicOperation logic_operation)
	: m_logic_operation(detail::ToGlLogicOperation(logic_operation))
{}

BKSGE_INLINE
LogicOperation::operator ::GLenum() const
{
	return m_logic_operation;
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_LOGIC_OPERATION_INL_HPP
