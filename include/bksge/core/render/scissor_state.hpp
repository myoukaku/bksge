/**
 *	@file	scissor_state.hpp
 *
 *	@brief	ScissorState の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_SCISSOR_STATE_HPP
#define BKSGE_CORE_RENDER_SCISSOR_STATE_HPP

#include <bksge/core/render/fwd/scissor_state_fwd.hpp>
#include <bksge/core/math/rect.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	シザーテストの設定
 */
class ScissorState
{
public:
	ScissorState(void);

	bool			enable(void) const;
	Rectf const&	rect(void) const;

	void SetEnable(bool enable);
	void SetRect(Rectf const& rect);

private:
	bool		m_enable;
	Rectf		m_rect;
};

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/scissor_state_inl.hpp>
#endif

#include <cstddef>
#include <functional>
#include <bksge/fnd/functional/hash_combine.hpp>

namespace std
{

template<>
struct hash<bksge::render::ScissorState>
{
	std::size_t operator()(bksge::render::ScissorState const& arg) const
	{
		return bksge::hash_combine(
			arg.enable(),
			arg.rect());
	}
};

}	// namespace std

#endif // BKSGE_CORE_RENDER_SCISSOR_STATE_HPP
