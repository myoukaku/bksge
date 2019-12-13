/**
 *	@file	type_enum.hpp
 *
 *	@brief	TypeEnum クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_TYPE_ENUM_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_TYPE_ENUM_HPP

#include <bksge/core/render/detail/fwd/type_enum_fwd.hpp>
#include <bksge/core/render/d3d_common/dxgiformat.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

/**
 *	@brief
 */
class TypeEnum
{
public:
	explicit TypeEnum(bksge::TypeEnum type);

	operator ::DXGI_FORMAT() const;

private:
	::DXGI_FORMAT	m_type;
};

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d11/detail/inl/type_enum_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_TYPE_ENUM_HPP
