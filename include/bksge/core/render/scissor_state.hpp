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
#include <bksge/fnd/serialization/access.hpp>
#include <bksge/fnd/serialization/nvp.hpp>
#include <bksge/fnd/serialization/version.hpp>
#include <bksge/fnd/ios/flags_saver.hpp>
#include <bksge/fnd/ostream/basic_ostream.hpp>
#include <ios>

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

private:
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, bksge::serialization::version_t /*version*/)
	{
		ar & BKSGE_SERIALIZATION_NVP(m_enable);
		ar & BKSGE_SERIALIZATION_NVP(m_rect);
	}
};

bool operator==(ScissorState const& lhs, ScissorState const& rhs);
bool operator!=(ScissorState const& lhs, ScissorState const& rhs);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline bksge::basic_ostream<CharT, Traits>&
operator<<(bksge::basic_ostream<CharT, Traits>& os, ScissorState const& rhs)
{
	bksge::ios::flags_saver ifs(os);
	return os << std::boolalpha << "{ "
		<< rhs.enable() << ", "
		<< rhs.rect() << " }";
}

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/scissor_state_inl.hpp>
#endif

#include <bksge/fnd/functional/hash_combine.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <functional>

namespace std
{

template<>
struct hash<bksge::render::ScissorState>
{
	bksge::size_t operator()(bksge::render::ScissorState const& arg) const
	{
		return bksge::hash_combine(
			arg.enable(),
			arg.rect());
	}
};

}	// namespace std

#endif // BKSGE_CORE_RENDER_SCISSOR_STATE_HPP
