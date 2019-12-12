/**
 *	@file	rasterizer_state.hpp
 *
 *	@brief	RasterizerState の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_RASTERIZER_STATE_HPP
#define BKSGE_RENDER_RASTERIZER_STATE_HPP

#include <bksge/render/fwd/rasterizer_state_fwd.hpp>
#include <bksge/render/fill_mode.hpp>
#include <bksge/render/cull_mode.hpp>
#include <bksge/render/front_face.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
class RasterizerState
{
public:
	RasterizerState(void);

	FillMode	fill_mode(void) const;
	CullMode	cull_mode(void) const;
	FrontFace	front_face(void) const;

	void SetFillMode(FillMode fill_mode);
	void SetCullMode(CullMode cull_mode);
	void SetFrontFace(FrontFace front_face);

private:
	FillMode	m_fill_mode;
	CullMode	m_cull_mode;
	FrontFace	m_front_face;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/inl/rasterizer_state_inl.hpp>
#endif

#include <cstddef>
#include <functional>
#include <bksge/functional/hash_combine.hpp>

namespace std
{

template<>
struct hash<bksge::render::RasterizerState>
{
	std::size_t operator()(bksge::render::RasterizerState const& arg) const
	{
		return bksge::hash_combine(
			arg.fill_mode(),
			arg.cull_mode(),
			arg.front_face());
	}
};

}	// namespace std

#endif // BKSGE_RENDER_RASTERIZER_STATE_HPP
