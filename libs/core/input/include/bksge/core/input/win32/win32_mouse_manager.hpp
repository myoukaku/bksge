/**
 *	@file	win32_mouse_manager.hpp
 *
 *	@brief	Win32MouseManager の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_INPUT_WIN32_WIN32_MOUSE_MANAGER_HPP
#define BKSGE_CORE_INPUT_WIN32_WIN32_MOUSE_MANAGER_HPP

#include <bksge/core/input/detail/mouse_manager_base.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <cstddef>

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
	bksge::unique_ptr<Impl>	m_impl;
};

}	// namespace win32

using MouseManager = win32::Win32MouseManager;

}	// namespace input

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/input/win32/inl/win32_mouse_manager_inl.hpp>
#endif

#endif // BKSGE_CORE_INPUT_WIN32_WIN32_MOUSE_MANAGER_HPP
