/**
 *	@file	keyboard_manager_base.hpp
 *
 *	@brief	KeyboardManagerBase の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_INPUT_DETAIL_KEYBOARD_MANAGER_BASE_HPP
#define BKSGE_INPUT_DETAIL_KEYBOARD_MANAGER_BASE_HPP

#include <bksge/input/keyboard_state.hpp>
#include <cstddef>

namespace bksge
{

namespace input
{

/**
 *	@brief
 */
class KeyboardManagerBase
{
public:
	KeyboardManagerBase(void)
	{}

	virtual ~KeyboardManagerBase()
	{}

	/**
	 *	@brief	キーボードの状態を更新します
	 */
	void Update(void)
	{
		VUpdate();
	}

	/**
	 *	@brief	キーボードの状態を取得します
	 */
	KeyboardState const& state(std::size_t index) const
	{
		return VGetState(index);
	}

private:
	virtual void VUpdate(void) = 0;

	virtual KeyboardState const& VGetState(std::size_t index) const = 0;
};

}	// namespace input

}	// namespace bksge

#endif // BKSGE_INPUT_DETAIL_KEYBOARD_MANAGER_BASE_HPP
