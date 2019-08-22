/**
 *	@file	win32_mouse_manager.hpp
 *
 *	@brief	Win32MouseManager の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_INPUT_WIN32_WIN32_MOUSE_MANAGER_HPP
#define BKSGE_INPUT_WIN32_WIN32_MOUSE_MANAGER_HPP

#include <bksge/input/detail/mouse_manager_base.hpp>
#include <cstddef>
#include <memory>

namespace bksge
{

namespace input
{

namespace win32
{

/**
 *	@brief	Win32版のMouseManager
 */
class Win32MouseManager : public MouseManagerBase
{
public:
	Win32MouseManager(void);

	virtual ~Win32MouseManager();

private:
	void VUpdate(void) override;

	MouseState const& VGetState(std::size_t index) const override;

	class Impl;
	std::unique_ptr<Impl>	m_impl;
};

}	// namespace win32

using MouseManager = win32::Win32MouseManager;

}	// namespace input

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/input/win32/inl/win32_mouse_manager_inl.hpp>
#endif

#endif // BKSGE_INPUT_WIN32_WIN32_MOUSE_MANAGER_HPP
