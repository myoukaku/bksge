/**
 *	@file	mouse_manager_base.hpp
 *
 *	@brief	MouseManagerBase の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_INPUT_DETAIL_MOUSE_MANAGER_BASE_HPP
#define BKSGE_CORE_INPUT_DETAIL_MOUSE_MANAGER_BASE_HPP

#include <bksge/core/input/mouse_state.hpp>
#include <cstddef>

namespace bksge
{

namespace input
{

/**
 *	@brief
 */
class MouseManagerBase
{
public:
	MouseManagerBase(void)
	{}

	virtual ~MouseManagerBase()
	{}

	/**
	 *	@brief	マウスの状態を更新します
	 */
	void Update(void)
	{
		VUpdate();
	}

	/**
	 *	@brief	マウスの状態を取得します
	 */
	MouseState const& state(std::size_t index) const
	{
		return VGetState(index);
	}

private:
	virtual void VUpdate(void) = 0;

	virtual MouseState const& VGetState(std::size_t index) const = 0;
};

}	// namespace input

}	// namespace bksge

#endif // BKSGE_CORE_INPUT_DETAIL_MOUSE_MANAGER_BASE_HPP
