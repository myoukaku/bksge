/**
 *	@file	texture.hpp
 *
 *	@brief	Texture クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_TEXTURE_HPP
#define BKSGE_RENDER_D3D12_DETAIL_TEXTURE_HPP

#include <bksge/render/d3d12/detail/fwd/texture_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/device_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/command_list_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/command_queue_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/fence_fwd.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
#include <bksge/render/fwd/texture_fwd.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

class Texture
{
public:
	explicit Texture(
		Device* device,
		CommandList* command_list,
		CommandQueue* command_queue,
		Fence* fence,
		bksge::Texture const& texture);

	~Texture();

	void CreateView(Device* device, ::D3D12_CPU_DESCRIPTOR_HANDLE dest);

private:
	ComPtr<::ID3D12Resource>	m_resource;

};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/detail/inl/texture_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_DETAIL_TEXTURE_HPP
