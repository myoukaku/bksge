/**
 *	@file	bool.hpp
 *
 *	@brief	Bool クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_BOOL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_BOOL_HPP

#include <bksge/core/render/gl/detail/gl_h.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief	bool を OpenGL の GLboolean に変換
 */
class Bool
{
public:
	explicit Bool(bool b);

	operator ::GLboolean() const;

private:
	::GLboolean const	m_bool;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/bool_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_BOOL_HPP
