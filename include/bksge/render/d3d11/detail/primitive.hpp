/**
 *	@file	primitive.hpp
 *
 *	@brief	Primitive クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_DETAIL_PRIMITIVE_HPP
#define BKSGE_RENDER_D3D11_DETAIL_PRIMITIVE_HPP

#include <bksge/render/fwd/primitive_fwd.hpp>
#include <bksge/render/d3d_common/d3d11.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

/**
 *	@brief
 */
class Primitive
{
public:
	explicit Primitive(bksge::Primitive primitive);

	operator ::D3D11_PRIMITIVE_TOPOLOGY() const;

private:
	::D3D11_PRIMITIVE_TOPOLOGY	m_primitive;
};

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d11/detail/inl/primitive_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D11_DETAIL_PRIMITIVE_HPP
