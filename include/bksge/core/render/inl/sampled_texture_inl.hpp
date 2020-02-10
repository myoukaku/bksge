/**
 *	@file	sampled_texture_inl.hpp
 *
 *	@brief	SampledTexture の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_SAMPLED_TEXTURE_INL_HPP
#define BKSGE_CORE_RENDER_INL_SAMPLED_TEXTURE_INL_HPP

#include <bksge/core/render/sampled_texture.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
SampledTexture::SampledTexture(void)
{
}

BKSGE_INLINE
SampledTexture::SampledTexture(
	Sampler const& sampler,
	Texture const& texture)
	: m_sampler(sampler)
	, m_texture(texture)
{
}

BKSGE_INLINE Texture&
SampledTexture::texture(void)
{
	return m_texture;
}

BKSGE_INLINE Sampler&
SampledTexture::sampler(void)
{
	return m_sampler;
}

BKSGE_INLINE Texture const&
SampledTexture::texture(void) const
{
	return m_texture;
}

BKSGE_INLINE Sampler const&
SampledTexture::sampler(void) const
{
	return m_sampler;
}

BKSGE_INLINE bool
operator==(SampledTexture const& lhs, SampledTexture const& rhs)
{
	return
		lhs.sampler() == rhs.sampler() &&
		lhs.texture() == rhs.texture();
}

BKSGE_INLINE bool
operator!=(SampledTexture const& lhs, SampledTexture const& rhs)
{
	return !(lhs == rhs);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_SAMPLED_TEXTURE_INL_HPP
