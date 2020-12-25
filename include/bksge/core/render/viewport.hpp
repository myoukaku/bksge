/**
 *	@file	viewport.hpp
 *
 *	@brief	Viewport の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VIEWPORT_HPP
#define BKSGE_CORE_RENDER_VIEWPORT_HPP

#include <bksge/core/render/fwd/viewport_fwd.hpp>
#include <bksge/core/math/rect.hpp>
#include <bksge/fnd/serialization/access.hpp>
#include <bksge/fnd/serialization/nvp.hpp>
#include <bksge/fnd/serialization/version.hpp>
#include <bksge/fnd/ostream/basic_ostream.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	ビューポートの設定
 */
class Viewport
{
public:
	Viewport(void);

	Rectf const&	rect(void) const;
	float			min_depth(void) const;
	float			max_depth(void) const;

	void SetRect(Rectf const& rect);
	void SetMinDepth(float min_depth);
	void SetMaxDepth(float max_depth);

private:
	Rectf		m_rect;
	float		m_min_depth;
	float		m_max_depth;

private:
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, bksge::serialization::version_t /*version*/)
	{
		ar & BKSGE_SERIALIZATION_NVP(m_rect);
		ar & BKSGE_SERIALIZATION_NVP(m_min_depth);
		ar & BKSGE_SERIALIZATION_NVP(m_max_depth);
	}
};

bool operator==(Viewport const& lhs, Viewport const& rhs);
bool operator!=(Viewport const& lhs, Viewport const& rhs);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline bksge::basic_ostream<CharT, Traits>&
operator<<(bksge::basic_ostream<CharT, Traits>& os, Viewport const& rhs)
{
	return os << "{ "
		<< rhs.rect() << ", "
		<< rhs.min_depth() << ", "
		<< rhs.max_depth() << " }";
}

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/viewport_inl.hpp>
#endif

#include <bksge/fnd/functional/hash.hpp>
#include <bksge/fnd/functional/hash_combine.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

namespace BKSGE_HASH_NAMESPACE
{

template<>
struct hash<bksge::render::Viewport>
{
	bksge::size_t operator()(bksge::render::Viewport const& arg) const
	{
		return bksge::hash_combine(
			arg.rect(),
			arg.min_depth(),
			arg.max_depth());
	}
};

}	// namespace BKSGE_HASH_NAMESPACE

#endif // BKSGE_CORE_RENDER_VIEWPORT_HPP
