/**
 *	@file	address_mode_fwd.hpp
 *
 *	@brief	AddressMode の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_FWD_ADDRESS_MODE_FWD_HPP
#define BKSGE_CORE_RENDER_FWD_ADDRESS_MODE_FWD_HPP

#include <bksge/fnd/cstdint/uint32_t.hpp>

namespace bksge
{

namespace render
{

enum class AddressMode : bksge::uint32_t;

}	// namespace render

using render::AddressMode;

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_FWD_ADDRESS_MODE_FWD_HPP
