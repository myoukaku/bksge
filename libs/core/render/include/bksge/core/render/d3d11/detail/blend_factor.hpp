﻿/**
 *	@file	blend_factor.hpp
 *
 *	@brief	BlendFactor クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_BLEND_FACTOR_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_BLEND_FACTOR_HPP

#include <bksge/core/render/fwd/blend_factor_fwd.hpp>
#include <bksge/core/render/d3d_common/d3d11.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

/**
 *	@brief
 */
class BlendFactor
{
public:
	explicit BlendFactor(bksge::BlendFactor blend_factor);

	operator ::D3D11_BLEND() const;

private:
	::D3D11_BLEND	m_blend_factor;
};

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d11/detail/inl/blend_factor_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_BLEND_FACTOR_HPP
