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

	bool				enable(void) const;
	std::uint8_t		read_mask(void) const;
	std::uint8_t		write_mask(void) const;
	ComparisonFunction	func(void) const;
	StencilOperation	fail_operation(void) const;
	StencilOperation	depth_fail_operation(void) const;
	StencilOperation	pass_operation(void) const;

	void SetEnable(bool enable);
	void SetReadMask(std::uint8_t mask);
	void SetWriteMask(std::uint8_t mask);
	void SetFunc(ComparisonFunction func);
	void SetFailOperation(StencilOperation op);
	void SetDepthFailOperation(StencilOperation op);
	void SetPassOperation(StencilOperation op);

private:
	bool				m_enable;
	std::uint8_t		m_read_mask;
	std::uint8_t		m_write_mask;
	ComparisonFunction	m_func;
	StencilOperation	m_fail_operation;
	StencilOperation	m_depth_fail_operation;
	StencilOperation	m_pass_operation;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/inl/stencil_state_inl.hpp>
#endif

#include <cstddef>
#include <functional>
#include <bksge/functional/hash_combine.hpp>

namespace std
{

template<>
struct hash<bksge::render::StencilState>
{
	std::size_t operator()(bksge::render::StencilState const& arg) const
	{
		return bksge::hash_combine(
			arg.enable(),
			arg.read_mask(),
			arg.write_mask(),
			arg.func(),
			arg.fail_operation(),
			arg.depth_fail_operation(),
			arg.pass_operation());
	}
};

}	// namespace std

#endif // BKSGE_RENDER_STENCIL_STATE_HPP
