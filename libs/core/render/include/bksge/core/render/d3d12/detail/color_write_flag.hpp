/**
 *	@file	color_write_flag.hpp
 *
 *	@brief	ColorWriteFlag クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_COLOR_WRITE_FLAG_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_COLOR_WRITE_FLAG_HPP

#include <bksge/core/render/fwd/color_write_flag_fwd.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

/**
 *	@brief
 */
class ColorWriteFlag
{
public:
	explicit ColorWriteFlag(bksge::ColorWriteFlag color_write_flag);

	operator ::UINT8() const;

private:
	::UINT8	m_color_write_flag;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d12/detail/inl/color_write_flag_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_COLOR_WRITE_FLAG_HPP
