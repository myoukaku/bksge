/**
 *	@file	constant_buffer_fwd.hpp
 *
 *	@brief	ConstantBuffer クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_FWD_CONSTANT_BUFFER_FWD_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_FWD_CONSTANT_BUFFER_FWD_HPP

#include <bksge/fnd/cstddef/size_t.hpp>
#include <memory>
#include <map>

namespace bksge
{

namespace render
{

namespace d3d12
{

class ConstantBuffer;
using ConstantBufferShared = std::shared_ptr<ConstantBuffer>;
using ConstantBufferMap = std::map<bksge::size_t, ConstantBufferShared>;

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_FWD_CONSTANT_BUFFER_FWD_HPP
