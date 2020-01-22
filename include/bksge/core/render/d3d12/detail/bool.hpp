/**
 *	@file	bool.hpp
 *
 *	@brief	Bool クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_BOOL_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_BOOL_HPP

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
class Bool
{
public:
	explicit Bool(bool b);

	operator ::BOOL() const;

private:
	::BOOL	m_bool;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d12/detail/inl/bool_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_BOOL_HPP
