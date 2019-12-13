/**
 *	@file	identifiable.hpp
 *
 *	@brief	Identifiable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_DETAIL_IDENTIFIABLE_HPP
#define BKSGE_CORE_RENDER_DETAIL_IDENTIFIABLE_HPP

#include <bksge/core/render/detail/identifier.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
class Identifiable
{
public:
	Identifiable(void) {}

	Identifier const& id(void) const { return m_id; }

private:
	Identifier m_id;
};

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_DETAIL_IDENTIFIABLE_HPP
