﻿/**
 *	@file	vertex_element.hpp
 *
 *	@brief	VertexElement の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VERTEX_ELEMENT_HPP
#define BKSGE_RENDER_VERTEX_ELEMENT_HPP

#include <bksge/render/semantic.hpp>
#include <bksge/render/detail/type_enum.hpp>
//#include <bksge/serialization/access.hpp>
//#include <bksge/serialization/nvp.hpp>
#include <cstddef>

namespace bksge
{

namespace render
{

/**
 *	@brief	頂点要素を宣言するための型
 */
template <typename T, std::size_t N, Semantic S>
struct VertexElement
{
	using value_type = T;
	using const_iterator = T const*;

	static std::size_t const element_num = N;
	static Semantic	   const semantic    = S;
	static TypeEnum    const type_enum   = TypeToEnum<T>::value;

	value_type m_data[N];

	value_type const& operator[](std::size_t index) const;

	const_iterator begin(void) const;

	const_iterator end(void) const;

private:
#if 0
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, unsigned int /*version*/)
	{
		ar & BKSGE_SERIALIZATION_NVP(m_data);
	}
#endif
};

template <typename T, std::size_t N, Semantic S>
bool operator==(VertexElement<T, N, S> const& lhs, VertexElement<T, N, S> const& rhs);

template <typename T, std::size_t N, Semantic S>
bool operator!=(VertexElement<T, N, S> const& lhs, VertexElement<T, N, S> const& rhs);

// よく使う頂点要素
using VPosition		= VertexElement<float, 3, Semantic::kPosition>;
using VNormal		= VertexElement<float, 3, Semantic::kNormal>;
using VColor		= VertexElement<float, 4, Semantic::kColor>;
using VTexCoord		= VertexElement<float, 2, Semantic::kTexCoord>;
using VFogCoord		= VertexElement<float, 1, Semantic::kFogCoord>;
using VPointSize	= VertexElement<float, 1, Semantic::kPointSize>;
using VBlendWeight	= VertexElement<float, 4, Semantic::kBlendWeight>;
using VBlendIndices	= VertexElement<float, 4, Semantic::kBlendIndices>;
using VTangent		= VertexElement<float, 3, Semantic::kTangent>;
using VBinormal		= VertexElement<float, 3, Semantic::kBinormal>;

}	// namespace render

using render::VPosition;
using render::VNormal;
using render::VColor;
using render::VTexCoord;
using render::VFogCoord;
using render::VPointSize;
using render::VBlendWeight;
using render::VBlendIndices;
using render::VTangent;
using render::VBinormal;

}	// namespace bksge

#include <bksge/render/inl/vertex_element_inl.hpp>

#endif // BKSGE_RENDER_VERTEX_ELEMENT_HPP
