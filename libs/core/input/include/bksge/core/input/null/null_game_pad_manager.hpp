﻿/**
 *	@file	null_game_pad_manager.hpp
 *
 *	@brief	NullGamePadManager の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_INPUT_NULL_NULL_GAME_PAD_MANAGER_HPP
#define BKSGE_CORE_INPUT_NULL_NULL_GAME_PAD_MANAGER_HPP

#include <bksge/core/input/detail/game_pad_manager_base.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

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
	void VUpdate(void) override
	{
	}

	GamePadState const& VGetState(bksge::size_t /*index*/) const override
	{
		static GamePadState const s;
		return s;
	}
};

using GamePadManager = NullGamePadManager;

}	// namespace input

}	// namespace bksge

#endif // BKSGE_CORE_INPUT_NULL_NULL_GAME_PAD_MANAGER_HPP
