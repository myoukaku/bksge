/**
 *	@file	null_game_pad_manager.hpp
 *
 *	@brief	NullGamePadManager の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_INPUT_NULL_NULL_GAME_PAD_MANAGER_HPP
#define BKSGE_INPUT_NULL_NULL_GAME_PAD_MANAGER_HPP

#include <bksge/input/detail/game_pad_manager_base.hpp>
#include <cstddef>

namespace bksge
{

namespace input
{

class NullGamePadManager : public GamePadManagerBase
{
public:
	NullGamePadManager(void)
	{
	}

	virtual ~NullGamePadManager()
	{
	}

private:
	virtual void VUpdate(void) override
	{
	}

	virtual GamePadState const& VGetState(std::size_t /*index*/) const override
	{
		static GamePadState const s;
		return s;
	}
};

using GamePadManager = NullGamePadManager;

}	// namespace input

}	// namespace bksge

#endif // BKSGE_INPUT_NULL_NULL_GAME_PAD_MANAGER_HPP
