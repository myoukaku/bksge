/**
 *	@file	constant_buffer_descriptor_fwd.hpp
 *
 *	@brief	ConstantBufferDescriptor クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_FWD_CONSTANT_BUFFER_DESCRIPTOR_FWD_HPP
#define BKSGE_RENDER_D3D12_DETAIL_FWD_CONSTANT_BUFFER_DESCRIPTOR_FWD_HPP

#include <bksge/render/detail/identifier.hpp>
#include <map>
#include <memory>

namespace bksge
{

namespace render
{

namespace d3d12
{

class ConstantBufferDescriptor;

using ConstantBufferDescriptorMap =
	std::map<Identifier, std::shared_ptr<ConstantBufferDescriptor>>;

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_D3D12_DETAIL_FWD_CONSTANT_BUFFER_DESCRIPTOR_FWD_HPP
