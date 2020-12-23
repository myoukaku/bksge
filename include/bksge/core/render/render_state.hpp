/**
 *	@file	render_state.hpp
 *
 *	@brief	RenderState の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_RENDER_STATE_HPP
#define BKSGE_CORE_RENDER_RENDER_STATE_HPP

#include <bksge/core/render/fwd/render_state_fwd.hpp>
#include <bksge/core/render/rasterizer_state.hpp>
#include <bksge/core/render/blend_state.hpp>
#include <bksge/core/render/depth_state.hpp>
#include <bksge/core/render/stencil_state.hpp>
#include <bksge/fnd/serialization/access.hpp>
#include <bksge/fnd/serialization/nvp.hpp>
#include <bksge/fnd/serialization/version.hpp>
#include <ostream>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
class RenderState
{
public:
	RenderState(void);

	RasterizerState const&	rasterizer_state(void) const;
	BlendState const&		blend_state(void) const;
	DepthState const&		depth_state(void) const;
	StencilState const&		stencil_state(void) const;

	RasterizerState&	rasterizer_state(void);
	BlendState&			blend_state(void);
	DepthState&			depth_state(void);
	StencilState&		stencil_state(void);

private:
	RasterizerState		m_rasterizer_state;
	BlendState			m_blend_state;
	DepthState			m_depth_state;
	StencilState		m_stencil_state;

private:
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, bksge::serialization::version_t /*version*/)
	{
		ar & BKSGE_SERIALIZATION_NVP(m_rasterizer_state);
		ar & BKSGE_SERIALIZATION_NVP(m_blend_state);
		ar & BKSGE_SERIALIZATION_NVP(m_depth_state);
		ar & BKSGE_SERIALIZATION_NVP(m_stencil_state);
	}
};

bool operator==(RenderState const& lhs, RenderState const& rhs);
bool operator!=(RenderState const& lhs, RenderState const& rhs);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, RenderState const& rhs)
{
	return os << "{ "
		<< rhs.rasterizer_state() << ", "
		<< rhs.blend_state() << ", "
		<< rhs.depth_state() << ", "
		<< rhs.stencil_state() << " }";
}

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/render_state_inl.hpp>
#endif

#include <bksge/fnd/functional/hash_combine.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <functional>

namespace std
{

template<>
struct hash<bksge::render::RenderState>
{
	bksge::size_t operator()(bksge::render::RenderState const& arg) const
	{
		return bksge::hash_combine(
			arg.rasterizer_state(),
			arg.blend_state(),
			arg.depth_state(),
			arg.stencil_state());
	}
};

}	// namespace std

#endif // BKSGE_CORE_RENDER_RENDER_STATE_HPP
