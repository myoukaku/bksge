/**
 *	@file	sampled_texture.hpp
 *
 *	@brief	SampledTexture クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_SAMPLED_TEXTURE_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_SAMPLED_TEXTURE_HPP

#include <bksge/core/render/gl/detail/fwd/texture_fwd.hpp>
#include <bksge/core/render/gl/detail/fwd/sampler_fwd.hpp>
#include <bksge/core/render/gl/detail/fwd/resource_pool_fwd.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>
#include <bksge/core/render/fwd/sampled_texture_fwd.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief	SampledTexture を OpenGL で使えるように変換したクラス
 */
class SampledTexture
{
public:
	explicit SampledTexture(
		ResourcePool* resource_pool,
		bksge::SampledTexture const& sampled_texture);

	explicit SampledTexture(
		SamplerShared const& sampler,
		TextureShared const& texture);

	void Bind(GLint location) const;

private:
	// noncopyable
	//SampledTexture(SampledTexture const&) = delete;
	//SampledTexture& operator=(SampledTexture const&) = delete;

private:
	TextureShared	m_texture;
	SamplerShared	m_sampler;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/sampled_texture_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_SAMPLED_TEXTURE_HPP
