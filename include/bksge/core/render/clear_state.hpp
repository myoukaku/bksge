/**
 *	@file	clear_state.hpp
 *
 *	@brief	ClearState の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_CLEAR_STATE_HPP
#define BKSGE_CORE_RENDER_CLEAR_STATE_HPP

#include <bksge/core/render/fwd/clear_state_fwd.hpp>
#include <bksge/core/render/clear_flag.hpp>
#include <bksge/core/math/color4.hpp>
#include <bksge/fnd/serialization/access.hpp>
#include <bksge/fnd/serialization/nvp.hpp>
#include <bksge/fnd/serialization/version.hpp>
#include <cstdint>
#include <ostream>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
class ClearState
{
public:
	ClearState(void);

	ClearFlag const&	flag(void) const;
	Color4f const&		color(void) const;
	float				depth(void) const;
	std::uint8_t		stencil(void) const;

	void SetFlag(ClearFlag const& flag);
	void SetColor(Color4f const& color);
	void SetDepth(float depth);
	void SetStencil(std::uint8_t stencil);

private:
	ClearFlag			m_flag;
	Color4f				m_color;
	float				m_depth;
	std::uint8_t		m_stencil;

private:
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, bksge::serialization::version_t /*version*/)
	{
		ar & BKSGE_SERIALIZATION_NVP(m_flag);
		ar & BKSGE_SERIALIZATION_NVP(m_color);
		ar & BKSGE_SERIALIZATION_NVP(m_depth);
		ar & BKSGE_SERIALIZATION_NVP(m_stencil);
	}
};

bool operator==(ClearState const& lhs, ClearState const& rhs);
bool operator!=(ClearState const& lhs, ClearState const& rhs);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, ClearState const& rhs)
{
	return os << "{ "
		<< rhs.flag() << ", "
		<< rhs.color() << ", "
		<< rhs.depth() << ", "
		<< static_cast<std::uint32_t>(rhs.stencil()) << " }";
}

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/clear_state_inl.hpp>
#endif

#include <functional>
#include <cstddef>
#include <bksge/fnd/functional/hash_combine.hpp>

namespace std
{

template<>
struct hash<bksge::render::ClearState>
{
	std::size_t operator()(bksge::render::ClearState const& arg) const
	{
		return bksge::hash_combine(
			arg.flag(),
			arg.color().r(),	// TODO
			arg.color().g(),
			arg.color().b(),
			arg.color().a(),
			arg.depth(),
			arg.stencil());
	}
};

}	// namespace std

#endif // BKSGE_CORE_RENDER_CLEAR_STATE_HPP
