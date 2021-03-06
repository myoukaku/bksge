﻿/**
 *	@file	vertex_array_base_inl.hpp
 *
 *	@brief	VertexArrayBase の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_DETAIL_INL_VERTEX_ARRAY_BASE_INL_HPP
#define BKSGE_CORE_RENDER_DETAIL_INL_VERTEX_ARRAY_BASE_INL_HPP

#include <bksge/core/render/detail/vertex_array_base.hpp>
#include <bksge/core/render/vertex_layout.hpp>
#include <bksge/fnd/cstring/memcmp.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
VertexArrayBase::~VertexArrayBase()
{
}

BKSGE_INLINE bool
operator==(VertexArrayBase const& lhs, VertexArrayBase const& rhs)
{
	return
		lhs.vertex_layout() == rhs.vertex_layout() &&
		lhs.bytes()         == rhs.bytes()         &&
		lhs.count()         == rhs.count()         &&
		(bksge::memcmp(lhs.data(), rhs.data(), lhs.bytes()) == 0);
}

BKSGE_INLINE bool
operator!=(VertexArrayBase const& lhs, VertexArrayBase const& rhs)
{
	return !(lhs == rhs);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_DETAIL_INL_VERTEX_ARRAY_BASE_INL_HPP
