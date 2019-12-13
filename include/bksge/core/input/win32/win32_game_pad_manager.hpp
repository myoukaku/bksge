/**
 *	@file	win32_game_pad_manager.hpp
 *
 *	@brief	Win32GamePadManager の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_INPUT_WIN32_WIN32_GAME_PAD_MANAGER_HPP
#define BKSGE_CORE_INPUT_WIN32_WIN32_GAME_PAD_MANAGER_HPP

#include <bksge/core/input/detail/game_pad_manager_base.hpp>
#include <cstddef>
#include <memory>

namespace bksge
{

namespace input
{

namespace win32
{

/**
 *	@brief	Win32版のGamePadManager
 */
class Win32GamePadManager : public GamePadManagerBase
{
public:
	Win32GamePadManager(void);

	virtual ~Win32GamePadManager();

private:
	void VUpdate(void) override;

	GamePadState const& VGetState(std::size_t index) const override;

	class Impl;
	std::unique_ptr<Impl>	m_impl;
};

}	// namespace win32

using GamePadManager = win32::Win32GamePadManager;

}	// namespace input

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/input/win32/inl/win32_game_pad_manager_inl.hpp>
#endif

#endif // BKSGE_CORE_INPUT_WIN32_WIN32_GAME_PAD_MANAGER_HPP
