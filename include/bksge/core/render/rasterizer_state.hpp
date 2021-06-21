/**
 *	@file	rasterizer_state.hpp
 *
 *	@brief	RasterizerState の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_RASTERIZER_STATE_HPP
#define BKSGE_CORE_RENDER_RASTERIZER_STATE_HPP

#include <bksge/core/render/fwd/rasterizer_state_fwd.hpp>
#include <bksge/core/render/fill_mode.hpp>
#include <bksge/core/render/cull_mode.hpp>
#include <bksge/core/render/front_face.hpp>
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

private:
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, bksge::serialization::version_t /*version*/)
	{
		ar & BKSGE_SERIALIZATION_NVP(m_fill_mode);
		ar & BKSGE_SERIALIZATION_NVP(m_cull_mode);
		ar & BKSGE_SERIALIZATION_NVP(m_front_face);
	}
};

bool operator==(RasterizerState const& lhs, RasterizerState const& rhs);
bool operator!=(RasterizerState const& lhs, RasterizerState const& rhs);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, RasterizerState const& rhs)
{
	return os << "{ "
		<< rhs.fill_mode() << ", "
		<< rhs.cull_mode() << ", "
		<< rhs.front_face() << " }";
}

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/rasterizer_state_inl.hpp>
#endif

#include <bksge/fnd/functional/hash.hpp>
#include <bksge/fnd/functional/hash_combine.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

namespace BKSGE_HASH_NAMESPACE
{

template<>
struct hash<bksge::render::RasterizerState>
{
	bksge::size_t operator()(bksge::render::RasterizerState const& arg) const
	{
		return bksge::hash_combine(
			arg.fill_mode(),
			arg.cull_mode(),
			arg.front_face());
	}
};

}	// namespace BKSGE_HASH_NAMESPACE

#endif // BKSGE_CORE_RENDER_RASTERIZER_STATE_HPP
