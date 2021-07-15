/**
 *	@file	game_pad_manager_base.hpp
 *
 *	@brief	GamePadManagerBase の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_INPUT_DETAIL_GAME_PAD_MANAGER_BASE_HPP
#define BKSGE_CORE_INPUT_DETAIL_GAME_PAD_MANAGER_BASE_HPP

#include <bksge/core/input/game_pad_state.hpp>
#include <cstddef>

namespace bksge
{

namespace input
{

/**
 *	@brief
 */
class GamePadManagerBase
{
public:
	GamePadManagerBase(void)
	{}

	virtual ~GamePadManagerBase()
	{}

	/**
	 *	@brief	ゲームパッドの状態を更新します
	 */
	void Update(void)
	{
		VUpdate();
	}

	/**
	 *	@brief	ゲームパッドの状態を取得します
	 */
	GamePadState const& state(std::size_t index) const
	{
		return VGetState(index);
	}

private:
	virtual void VUpdate(void) = 0;

	virtual GamePadState const& VGetState(std::size_t index) const = 0;
};

}	// namespace input

}	// namespace bksge

#endif // BKSGE_CORE_INPUT_DETAIL_GAME_PAD_MANAGER_BASE_HPP
