/**
 *	@file	index_array.hpp
 *
 *	@brief	IndexArray の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_DETAIL_INDEX_ARRAY_HPP
#define BKSGE_RENDER_DETAIL_INDEX_ARRAY_HPP

#include <bksge/render/detail/fwd/index_array_fwd.hpp>
#include <bksge/render/detail/fwd/type_enum_fwd.hpp>
#include <bksge/render/detail/index_array_base.hpp>
//#include <bksge/serialization/access.hpp>
//#include <bksge/serialization/nvp.hpp>
//#include <bksge/serialization/vector.hpp>
//#include <bksge/serialization/polymorphic_serializable.hpp>
#include <cstddef>
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

	virtual TypeEnum type(void) const override;

	virtual const_pointer data(void) const override;

	virtual size_type bytes(void) const override;

	virtual size_type count(void) const override;

	T const& operator[](std::size_t i) const;

private:
	std::vector<T>	m_value;

private:
#if 0
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, unsigned int /*version*/)
	{
		ar & BKSGE_SERIALIZATION_BASE_OBJECT_NVP(IndexArrayBase);
		ar & BKSGE_SERIALIZATION_NVP(m_value);
	}
#endif
};

}	// namespace render

}	// namespace bksge

#include <bksge/render/detail/inl/index_array_inl.hpp>

#endif // BKSGE_RENDER_DETAIL_INDEX_ARRAY_HPP
