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

inline
DummyWindow::DummyWindow(SizeType const& /*client_size*/, std::string const& /*title*/)
{}

inline
DummyWindow::~DummyWindow()
{}

inline
void DummyWindow::Destroy(void)
{}

inline
void DummyWindow::SetTitle(std::string const& /*title*/)
{}

inline
void DummyWindow::SetClientSize(SizeType const& /*size*/)
{}

inline
auto DummyWindow::ClientSize(void) const -> SizeType
{
	return SizeType{};
}

inline
bool DummyWindow::Update(void)
{
	return true;
}

inline
auto DummyWindow::Handle(void) const -> HandleType
{
	return HandleType{};
}

}	// namespace window

}	// namespace bksge

#endif // BKSGE_WINDOW_DUMMY_INL_DUMMY_WINDOW_INL_HPP
