/**
 *	@file	render_pass_info.hpp
 *
 *	@brief	RenderPassInfo の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_RENDER_PASS_INFO_HPP
#define BKSGE_CORE_RENDER_RENDER_PASS_INFO_HPP

#include <bksge/core/render/fwd/render_pass_info_fwd.hpp>
#include <bksge/core/render/clear_state.hpp>
#include <bksge/core/render/scissor_state.hpp>
#include <bksge/core/render/viewport.hpp>
#include <bksge/fnd/serialization/access.hpp>
#include <bksge/fnd/serialization/nvp.hpp>
#include <bksge/fnd/serialization/version.hpp>
#include <bksge/fnd/ostream/basic_ostream.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	
 */
class RenderPassInfo
{
public:
	RenderPassInfo(void);

	ClearState const&		clear_state(void) const;
	ScissorState const&		scissor_state(void) const;
	Viewport const&			viewport(void) const;

	ClearState&				clear_state(void);
	ScissorState&			scissor_state(void);
	Viewport&				viewport(void);

private:
	ClearState			m_clear_state;
	ScissorState		m_scissor_state;
	Viewport			m_viewport;

private:
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, bksge::serialization::version_t /*version*/)
	{
		ar & BKSGE_SERIALIZATION_NVP(m_clear_state);
		ar & BKSGE_SERIALIZATION_NVP(m_scissor_state);
		ar & BKSGE_SERIALIZATION_NVP(m_viewport);
	}
};

bool operator==(RenderPassInfo const& lhs, RenderPassInfo const& rhs);
bool operator!=(RenderPassInfo const& lhs, RenderPassInfo const& rhs);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline bksge::basic_ostream<CharT, Traits>&
operator<<(bksge::basic_ostream<CharT, Traits>& os, RenderPassInfo const& rhs)
{
	return os << "{ "
		<< rhs.clear_state() << ", "
		<< rhs.scissor_state() << ", "
		<< rhs.viewport() << " }";
}

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/render_pass_info_inl.hpp>
#endif

#include <bksge/fnd/functional/hash_combine.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <functional>

namespace std
{

template<>
struct hash<bksge::render::RenderPassInfo>
{
	bksge::size_t operator()(bksge::render::RenderPassInfo const& arg) const
	{
		return bksge::hash_combine(
			arg.clear_state(),
			arg.scissor_state(),
			arg.viewport());
	}
};

}	// namespace std

#endif // BKSGE_CORE_RENDER_RENDER_PASS_INFO_HPP
