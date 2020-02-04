/**
 *	@file	root_signature.hpp
 *
 *	@brief	RootSignature クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_ROOT_SIGNATURE_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_ROOT_SIGNATURE_HPP

#include <bksge/core/render/d3d12/detail/fwd/root_signature_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/device_fwd.hpp>
//#include <bksge/core/render/d3d12/detail/fwd/hlsl_shader_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/root_parameters_fwd.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/d3d_common/com_ptr.hpp>

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
		RootParameters const& root_parameters);

	~RootSignature();

	::ID3D12RootSignature* Get(void) const;

private:
	// noncopyable
	RootSignature(RootSignature const&) = delete;
	RootSignature& operator=(RootSignature const&) = delete;

private:
	ComPtr<::ID3D12RootSignature> m_root_signature;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d12/detail/inl/root_signature_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_ROOT_SIGNATURE_HPP
