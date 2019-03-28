/**
 *	@file	dummy_mouse_manager.hpp
 *
 *	@brief	DummyMouseManager の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_INPUT_DUMMY_DUMMY_MOUSE_MANAGER_HPP
#define BKSGE_INPUT_DUMMY_DUMMY_MOUSE_MANAGER_HPP

#include <bksge/input/detail/mouse_manager_base.hpp>
#include <cstddef>

namespace bksge
{

namespace input
{

class DummyMouseManager : public MouseManagerBase
{
public:
	DummyMouseManager(void)
	{
	}

	virtual ~DummyMouseManager()
	{
	}

private:
	virtual void VUpdate(void) override
	{
	}

	virtual MouseState const& VGetState(std::size_t /*index*/) const override
	{
		static MouseState const s;
		return s;
	}
};

using MouseManager = DummyMouseManager;

}	// namespace input

}	// namespace bksge

#endif // BKSGE_INPUT_DUMMY_DUMMY_MOUSE_MANAGER_HPP
