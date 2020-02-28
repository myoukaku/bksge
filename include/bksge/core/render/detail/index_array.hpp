/**
 *	@file	index_array.hpp
 *
 *	@brief	IndexArray の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_DETAIL_INDEX_ARRAY_HPP
#define BKSGE_CORE_RENDER_DETAIL_INDEX_ARRAY_HPP

#include <bksge/core/render/detail/fwd/index_array_fwd.hpp>
#include <bksge/core/render/detail/fwd/type_enum_fwd.hpp>
#include <bksge/core/render/detail/index_array_base.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
//#include <bksge/fnd/serialization/access.hpp>
//#include <bksge/fnd/serialization/nvp.hpp>
//#include <bksge/fnd/serialization/vector.hpp>
//#include <bksge/fnd/serialization/polymorphic_serializable.hpp>
//#include <bksge/fnd/serialization/version.hpp>
#include <vector>

namespace bksge
{

namespace render
{

/**
 *	@brief	インデックス配列
 */
template <typename T>
class IndexArray
	: public IndexArrayBase
	/*, private bksge::serialization::polymorphic_serializable<IndexArray<T>>*/
{
public:
	IndexArray(void);

	template <typename Iterator>
	IndexArray(Iterator first, Iterator last);

	// コピー禁止
	IndexArray(IndexArray const&) = delete;
	IndexArray& operator=(IndexArray const&) = delete;

	TypeEnum type(void) const override;

	const_pointer data(void) const override;

	size_type bytes(void) const override;

	size_type count(void) const override;

	T const& operator[](bksge::size_t i) const;

private:
	std::vector<T>	m_value;

private:
#if 0
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, bksge::serialization::version_t /*version*/)
	{
		ar & BKSGE_SERIALIZATION_BASE_OBJECT_NVP(IndexArrayBase);
		ar & BKSGE_SERIALIZATION_NVP(m_value);
	}
#endif
};

}	// namespace render

}	// namespace bksge

#include <bksge/core/render/detail/inl/index_array_inl.hpp>

#endif // BKSGE_CORE_RENDER_DETAIL_INDEX_ARRAY_HPP
