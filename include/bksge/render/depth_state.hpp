﻿/**
 *	@file	depth_state.hpp
 *
 *	@brief	DepthState の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_DEPTH_STATE_HPP
#define BKSGE_RENDER_DEPTH_STATE_HPP

#include <bksge/render/fwd/depth_state_fwd.hpp>
#include <bksge/render/comparison_function.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	デプステストの設定
 */
class DepthState
{
public:
	DepthState(void);

	bool				enable(void) const;
	bool				write(void) const;
	ComparisonFunction	func(void) const;

	void SetEnable(bool enable);
	void SetWrite(bool write);
	void SetFunc(ComparisonFunction func);

private:
	bool				m_enable;
	bool				m_write;
	ComparisonFunction	m_func;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/inl/depth_state_inl.hpp>
#endif

#include <functional>
#include <cstddef>
#include <bksge/functional/hash_combine.hpp>

namespace std
{

template<>
struct hash<bksge::render::DepthState>
{
	std::size_t operator()(bksge::render::DepthState const& arg) const
	{
		return bksge::hash_combine(
			arg.enable(),
			arg.write(),
			arg.func());
	}
};

}	// namespace std

#endif // BKSGE_RENDER_DEPTH_STATE_HPP
