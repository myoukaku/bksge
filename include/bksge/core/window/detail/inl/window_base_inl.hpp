/**
 *	@file	window_base_inl.hpp
 *
 *	@brief	WindowBase クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_WINDOW_DETAIL_INL_WINDOW_BASE_INL_HPP
#define BKSGE_CORE_WINDOW_DETAIL_INL_WINDOW_BASE_INL_HPP

#include <bksge/core/window/detail/window_base.hpp>
#include <bksge/core/math/size2.hpp>
#include <string>

namespace bksge
{

namespace window
{

BKSGE_INLINE
WindowBase::WindowBase(
	SizeType const& client_size,
	std::string const& title)
	: m_client_size(client_size)
	, m_title(title)
{
}

BKSGE_INLINE
WindowBase::~WindowBase()
{
}

BKSGE_INLINE void
WindowBase::Destroy(void)
{
	VDestroy();
}

BKSGE_INLINE bool
WindowBase::Update(void)
{
	return VUpdate();
}

BKSGE_INLINE void
WindowBase::SetTitle(std::string const& title)
{
	m_title = title;
	VSetTitle(title);
}

BKSGE_INLINE void
WindowBase::SetClientSize(SizeType const& size)
{
	m_client_size = size;
	VSetClientSize(size);
}

BKSGE_INLINE std::string const&
WindowBase::title(void) const
{
	return m_title;
}

BKSGE_INLINE auto
WindowBase::client_size(void) const
-> SizeType
{
	return m_client_size;
}

}	// namespace window

}	// namespace bksge

#endif // BKSGE_CORE_WINDOW_DETAIL_INL_WINDOW_BASE_INL_HPP
