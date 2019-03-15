/**
 *	@file	dummy_window_inl.hpp
 *
 *	@brief	DummyWindow クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_WINDOW_DUMMY_INL_DUMMY_WINDOW_INL_HPP
#define BKSGE_WINDOW_DUMMY_INL_DUMMY_WINDOW_INL_HPP

#include <bksge/window/dummy/dummy_window.hpp>
#include <string>

namespace bksge
{

namespace window
{

BKSGE_INLINE
DummyWindow::DummyWindow(SizeType const& /*client_size*/, std::string const& /*title*/)
{}

BKSGE_INLINE
DummyWindow::~DummyWindow()
{}

BKSGE_INLINE
void DummyWindow::Destroy(void)
{}

BKSGE_INLINE
void DummyWindow::SetTitle(std::string const& /*title*/)
{}

BKSGE_INLINE
void DummyWindow::SetClientSize(SizeType const& /*size*/)
{}

BKSGE_INLINE
auto DummyWindow::ClientSize(void) const -> SizeType
{
	return SizeType{};
}

BKSGE_INLINE
bool DummyWindow::Update(void)
{
	return true;
}

BKSGE_INLINE
auto DummyWindow::Handle(void) const -> HandleType
{
	return HandleType{};
}

}	// namespace window

}	// namespace bksge

#endif // BKSGE_WINDOW_DUMMY_INL_DUMMY_WINDOW_INL_HPP
