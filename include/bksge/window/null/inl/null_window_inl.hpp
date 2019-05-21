/**
 *	@file	null_window_inl.hpp
 *
 *	@brief	NullWindow クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_WINDOW_NULL_INL_NULL_WINDOW_INL_HPP
#define BKSGE_WINDOW_NULL_INL_NULL_WINDOW_INL_HPP

#include <bksge/window/null/null_window.hpp>
#include <string>

namespace bksge
{

namespace window
{

BKSGE_INLINE
NullWindow::NullWindow(
	SizeType const& client_size,
	std::string const& title)
	: Base(client_size, title)
{}

BKSGE_INLINE
NullWindow::~NullWindow()
{
	Destroy();
}

BKSGE_INLINE void
NullWindow::VDestroy(void)
{}

BKSGE_INLINE void
NullWindow::VSetTitle(std::string const& /*title*/)
{}

BKSGE_INLINE void
NullWindow::VSetClientSize(SizeType const& /*size*/)
{}

BKSGE_INLINE bool
NullWindow::VUpdate(void)
{
	return true;
}

BKSGE_INLINE auto
NullWindow::handle(void) const
-> HandleType
{
	return HandleType{};
}

}	// namespace window

}	// namespace bksge

#endif // BKSGE_WINDOW_NULL_INL_NULL_WINDOW_INL_HPP
