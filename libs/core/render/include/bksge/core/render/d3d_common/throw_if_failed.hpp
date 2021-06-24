/**
 *	@file	throw_if_failed.hpp
 *
 *	@brief	ThrowIfFailed の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D_COMMON_THROW_IF_FAILED_HPP
#define BKSGE_CORE_RENDER_D3D_COMMON_THROW_IF_FAILED_HPP

#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/stdexcept/runtime_error.hpp>

namespace bksge
{

namespace render
{

class HrException : public bksge::runtime_error
{
public:
	explicit HrException(::HRESULT hr)
		: bksge::runtime_error(HrToString(hr))
		, m_hr(hr)
	{}

	::HRESULT Error() const
	{
		return m_hr;
	}

private:
	bksge::string HrToString(::HRESULT hr)
	{
		char s_str[64] ={};
		sprintf_s(s_str, "HRESULT of 0x%08X", static_cast<::UINT>(hr));
		return bksge::string(s_str);
	}

private:
	::HRESULT const m_hr;
};

inline void ThrowIfFailed(::HRESULT hr)
{
	if (FAILED(hr))
	{
		throw HrException(hr);
	}
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_D3D_COMMON_THROW_IF_FAILED_HPP
