/**
 *	@file	stencil_state.hpp
 *
 *	@brief	StencilState の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_STENCIL_STATE_HPP
#define BKSGE_RENDER_STENCIL_STATE_HPP

#include <bksge/render/fwd/stencil_state_fwd.hpp>
#include <bksge/render/comparison_function.hpp>
#include <bksge/render/stencil_operation.hpp>
#include <cstdint>

namespace bksge
{

namespace render
{

/**
 *	@brief	ステンシルテストの設定
 */
class StencilState
{
public:
	StencilState(void);

private:
	bool				m_enable;
	std::uint8_t		m_read_mask;
	std::uint8_t		m_write_mask;
	ComparisonFunction	m_func;
	StencilOperation	m_fail_op;
	StencilOperation	m_depth_fail_op;
	StencilOperation	m_pass_op;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/inl/stencil_state_inl.hpp>
#endif

#endif // BKSGE_RENDER_STENCIL_STATE_HPP
