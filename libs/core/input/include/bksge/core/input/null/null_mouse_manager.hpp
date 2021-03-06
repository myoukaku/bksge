﻿/**
 *	@file	null_mouse_manager.hpp
 *
 *	@brief	NullMouseManager の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_INPUT_NULL_NULL_MOUSE_MANAGER_HPP
#define BKSGE_CORE_INPUT_NULL_NULL_MOUSE_MANAGER_HPP

#include <bksge/core/input/detail/mouse_manager_base.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

namespace bksge
{

namespace input
{

class NullMouseManager : public MouseManagerBase
{
public:
	NullMouseManager(void)
	{
	}

	virtual ~NullMouseManager()
	{
	}

private:
	void VUpdate(void) override
	{
	}

	MouseState const& VGetState(bksge::size_t /*index*/) const override
	{
		static MouseState const s;
		return s;
	}
};

using MouseManager = NullMouseManager;

}	// namespace input

}	// namespace bksge

#endif // BKSGE_CORE_INPUT_NULL_NULL_MOUSE_MANAGER_HPP
