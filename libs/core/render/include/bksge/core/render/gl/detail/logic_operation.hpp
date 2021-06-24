/**
 *	@file	logic_operation.hpp
 *
 *	@brief	LogicOperation クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_LOGIC_OPERATION_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_LOGIC_OPERATION_HPP

#include <bksge/core/render/fwd/logic_operation_fwd.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief	LogicOperation を OpenGL の enum に変換
 */
class LogicOperation
{
public:
	explicit LogicOperation(bksge::LogicOperation logic_operation);

	operator ::GLenum() const;

private:
	::GLenum const	m_logic_operation;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/logic_operation_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_LOGIC_OPERATION_HPP
