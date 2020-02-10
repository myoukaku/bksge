/**
 *	@file	sampled_texture_inl.hpp
 *
 *	@brief	SampledTexture クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_SAMPLED_TEXTURE_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_SAMPLED_TEXTURE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/sampled_texture.hpp>
#include <bksge/core/render/gl/detail/sampler.hpp>
#include <bksge/core/render/gl/detail/texture.hpp>
#include <bksge/core/render/gl/detail/resource_pool.hpp>
#include <bksge/core/render/sampled_texture.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

BKSGE_INLINE
SampledTexture::SampledTexture(
	ResourcePool* resource_pool, bksge::SampledTexture const& sampled_texture)
	: m_texture(resource_pool->GetGlTexture(sampled_texture.texture()))
	, m_sampler(resource_pool->GetGlSampler(sampled_texture.sampler()))
{
}

BKSGE_INLINE void
SampledTexture::Bind(GLint location) const
{
	m_texture->Bind(location);
	m_sampler->Bind(location);
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_SAMPLED_TEXTURE_INL_HPP
