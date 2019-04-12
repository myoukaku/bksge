/**
 *	@file	vertex_array_base.hpp
 *
 *	@brief	VertexArrayBase の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_DETAIL_VERTEX_ARRAY_BASE_HPP
#define BKSGE_RENDER_DETAIL_VERTEX_ARRAY_BASE_HPP

#include <bksge/render/detail/fwd/vertex_array_base_fwd.hpp>
#include <bksge/render/detail/fwd/vertex_layout_fwd.hpp>
//#include <bksge/serialization/access.hpp>
//#include <bksge/serialization/nvp.hpp>
#include <cstddef>

namespace bksge
{

namespace render
{

/**
 *	@brief	頂点配列
 */
class VertexArrayBase
{
public:
	using const_pointer = void const*;
	using size_type = std::size_t;

	virtual ~VertexArrayBase();

	virtual VertexLayout const& vertex_layout(void) const = 0;

	virtual const_pointer data(void) const = 0;

	virtual size_type bytes(void) const = 0;

	virtual size_type count(void) const = 0;

private:
#if 0
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& /*ar*/, unsigned int /*version*/)
	{
	}
#endif
};

bool operator==(VertexArrayBase const& lhs, VertexArrayBase const& rhs);
bool operator!=(VertexArrayBase const& lhs, VertexArrayBase const& rhs);

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/detail/inl/vertex_array_base_inl.hpp>
#endif

#endif // BKSGE_RENDER_DETAIL_VERTEX_ARRAY_BASE_HPP
