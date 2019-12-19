/**
 *	@file	texture.hpp
 *
 *	@brief	Texture クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_TEXTURE_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_TEXTURE_HPP

#include <bksge/core/render/d3d12/detail/fwd/texture_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/command_list_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/command_queue_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/fence_fwd.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/d3d_common/com_ptr.hpp>
#include <bksge/core/render/fwd/texture_fwd.hpp>

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
	ComPtr<ID3D12ResourceN>	m_resource;

};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d12/detail/inl/texture_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_TEXTURE_HPP
