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
NullWindow::NullWindow(SizeType const& /*client_size*/, std::string const& /*title*/)
{}

BKSGE_INLINE
NullWindow::~NullWindow()
{}

BKSGE_INLINE
void NullWindow::Destroy(void)
{}

BKSGE_INLINE
void NullWindow::SetTitle(std::string const& /*title*/)
{}

BKSGE_INLINE
void NullWindow::SetClientSize(SizeType const& /*size*/)
{}

BKSGE_INLINE
auto NullWindow::ClientSize(void) const -> SizeType
{
	return SizeType{};
}

BKSGE_INLINE
bool NullWindow::Update(void)
{
	return true;
}

BKSGE_INLINE
auto NullWindow::Handle(void) const -> HandleType
{
	return HandleType{};
}

}	// namespace window

}	// namespace bksge

#endif // BKSGE_WINDOW_NULL_INL_NULL_WINDOW_INL_HPP
