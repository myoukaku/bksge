﻿/**
 *	@file	sampler.hpp
 *
 *	@brief	Sampler クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_SAMPLER_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_SAMPLER_HPP

#include <bksge/core/render/gl/detail/fwd/sampler_fwd.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>
#include <bksge/core/render/fwd/sampler_fwd.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief	Sampler を OpenGL で使えるように変換したクラス
 */
class Sampler
{
public:
	explicit Sampler(bksge::Sampler const& sampler);

	~Sampler();

	void Bind(GLint location) const;

private:
	// noncopyable
	Sampler(Sampler const&) = delete;
	Sampler& operator=(Sampler const&) = delete;

private:
	::GLuint	m_id;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/sampler_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_SAMPLER_HPP
