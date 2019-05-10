/**
 *	@file	d3d12_constant_buffer_descriptor_fwd.hpp
 *
 *	@brief	D3D12ConstantBufferDescriptor クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_FWD_D3D12_CONSTANT_BUFFER_DESCRIPTOR_FWD_HPP
#define BKSGE_RENDER_D3D12_FWD_D3D12_CONSTANT_BUFFER_DESCRIPTOR_FWD_HPP

#include <bksge/render/detail/identifier.hpp>
#include <map>
#include <memory>

namespace bksge
{

namespace render
{

class D3D12ConstantBufferDescriptor;

using D3D12ConstantBufferDescriptorMap =
	std::map<Identifier, std::shared_ptr<D3D12ConstantBufferDescriptor>>;

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_D3D12_FWD_D3D12_CONSTANT_BUFFER_DESCRIPTOR_FWD_HPP
