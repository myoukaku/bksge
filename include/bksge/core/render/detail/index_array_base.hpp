/**
 *	@file	index_array_base.hpp
 *
 *	@brief	IndexArrayBase の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_DETAIL_INDEX_ARRAY_BASE_HPP
#define BKSGE_CORE_RENDER_DETAIL_INDEX_ARRAY_BASE_HPP

#include <bksge/core/render/detail/fwd/index_array_base_fwd.hpp>
#include <bksge/core/render/detail/fwd/type_enum_fwd.hpp>
//#include <bksge/fnd/serialization/access.hpp>
//#include <bksge/fnd/serialization/nvp.hpp>
#include <cstddef>

namespace bksge
{

namespace render
{

/**
 *	@brief	インデックス配列
 */
class IndexArrayBase
{
public:
	using const_pointer = void const*;
	using size_type = std::size_t;

	virtual ~IndexArrayBase();

	virtual TypeEnum type(void) const = 0;

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

bool operator==(IndexArrayBase const& lhs, IndexArrayBase const& rhs);
bool operator!=(IndexArrayBase const& lhs, IndexArrayBase const& rhs);

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/detail/inl/index_array_base_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_DETAIL_INDEX_ARRAY_BASE_HPP
