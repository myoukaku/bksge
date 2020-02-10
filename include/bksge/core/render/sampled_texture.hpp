/**
 *	@file	sampled_texture.hpp
 *
 *	@brief	SampledTexture の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_SAMPLED_TEXTURE_HPP
#define BKSGE_CORE_RENDER_SAMPLED_TEXTURE_HPP

#include <bksge/core/render/fwd/sampled_texture_fwd.hpp>
#include <bksge/core/render/texture.hpp>
#include <bksge/core/render/sampler.hpp>
#include <ostream>
#include <string>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
class SampledTexture
{
public:
	SampledTexture(void);
	explicit SampledTexture(
		Sampler const& sampler,
		Texture const& texture);

	Sampler&	sampler(void);
	Texture&	texture(void);

	Sampler const&	sampler(void) const;
	Texture const&	texture(void) const;

private:
	Sampler			m_sampler;		///< サンプラー
	Texture			m_texture;		///< テクスチャ

private:
	// TODO
#if 0
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, bksge::serialization::version_t /*version*/)
	{
		ar & BKSGE_SERIALIZATION_NVP(m_sampler);
		ar & BKSGE_SERIALIZATION_NVP(m_texture);
	}
#endif
};

/**
 *	@brief	比較演算子
 */
bool operator==(SampledTexture const& lhs, SampledTexture const& rhs);
bool operator!=(SampledTexture const& lhs, SampledTexture const& rhs);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, SampledTexture const& rhs)
{
	return os << "{ "
		   << rhs.sampler() << ", "
		   << rhs.texture()
		   << " }";
}

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/sampled_texture_inl.hpp>
#endif

#include <cstddef>
#include <functional>
#include <bksge/fnd/functional/hash_combine.hpp>

namespace std
{

template<>
struct hash<bksge::render::SampledTexture>
{
	std::size_t operator()(bksge::render::SampledTexture const& arg) const
	{
		return bksge::hash_combine(
			arg.sampler(),
			arg.texture().id());
	}
};

}	// namespace std
#endif // BKSGE_CORE_RENDER_SAMPLED_TEXTURE_HPP
