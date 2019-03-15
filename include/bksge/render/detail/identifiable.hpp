/**
 *	@file	identifiable.hpp
 *
 *	@brief	Identifiable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_DETAIL_IDENTIFIABLE_HPP
#define BKSGE_RENDER_DETAIL_IDENTIFIABLE_HPP

#include <bksge/render/detail/identifier.hpp>

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

#endif // BKSGE_RENDER_DETAIL_IDENTIFIABLE_HPP
