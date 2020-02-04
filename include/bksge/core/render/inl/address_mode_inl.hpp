/**
 *	@file	address_mode_inl.hpp
 *
 *	@brief	AddressMode の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_ADDRESS_MODE_INL_HPP
#define BKSGE_CORE_RENDER_INL_ADDRESS_MODE_INL_HPP

#include <bksge/core/render/address_mode.hpp>
#include <unordered_map>
#include <string>

namespace bksge
{

namespace render
{

BKSGE_INLINE
std::string to_string(AddressMode const& address_mode)
{
#define BKSGE_CORE_RENDER_MAKE_ADDRESS_MODE_KVP(x)	{ x, #x }

	static std::unordered_map<AddressMode, std::string> const m =
	{
		BKSGE_CORE_RENDER_MAKE_ADDRESS_MODE_KVP(AddressMode::kRepeat),
		BKSGE_CORE_RENDER_MAKE_ADDRESS_MODE_KVP(AddressMode::kMirror),
		BKSGE_CORE_RENDER_MAKE_ADDRESS_MODE_KVP(AddressMode::kClamp),
		BKSGE_CORE_RENDER_MAKE_ADDRESS_MODE_KVP(AddressMode::kBorder),
	};

	return m.at(address_mode);

#undef BKSGE_CORE_RENDER_MAKE_ADDRESS_MODE_KVP
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_ADDRESS_MODE_INL_HPP
