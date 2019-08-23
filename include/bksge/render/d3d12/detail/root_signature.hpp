/**
 *	@file	root_signature.hpp
 *
 *	@brief	RootSignature クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_ROOT_SIGNATURE_HPP
#define BKSGE_RENDER_D3D12_DETAIL_ROOT_SIGNATURE_HPP

#include <bksge/render/d3d12/detail/fwd/root_signature_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/device_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/hlsl_shader_fwd.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

class RootSignature
{
public:
	explicit RootSignature(
		Device* device,
		HLSLShaderMap const& shader_map);

	~RootSignature();

	::ID3D12RootSignature* Get(void) const;

	::UINT GetRootParameterCount(void) const;

private:
	ComPtr<::ID3D12RootSignature> m_root_signature;
	::UINT m_root_parameter_count;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/detail/inl/root_signature_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_DETAIL_ROOT_SIGNATURE_HPP
