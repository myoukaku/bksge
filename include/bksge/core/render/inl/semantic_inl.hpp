/**
 *	@file	semantic_inl.hpp
 *
 *	@brief	Semantic の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_SEMANTIC_INL_HPP
#define BKSGE_CORE_RENDER_INL_SEMANTIC_INL_HPP

#include <bksge/core/render/semantic.hpp>
#include <bksge/fnd/config.hpp>
#include <string>

namespace bksge
{

namespace render
{

BKSGE_INLINE Semantic
ToSemantic(std::string const& semantic_str)
{
	if (semantic_str == "POSITION")		{ return Semantic::kPosition; }
	if (semantic_str == "NORMAL")		{ return Semantic::kNormal; }
	if (semantic_str == "COLOR")		{ return Semantic::kColor; }
	if (semantic_str == "TEXCOORD")		{ return Semantic::kTexCoord; }
	if (semantic_str == "TEXCOORD0")	{ return Semantic::kTexCoord; }
	if (semantic_str == "TEXCOORD1")	{ return Semantic::kTexCoord; }
	if (semantic_str == "FOGCOORD")		{ return Semantic::kFogCoord; }
	if (semantic_str == "POINTSIZE")	{ return Semantic::kPointSize; }
	if (semantic_str == "BLENDWEIGHT")	{ return Semantic::kBlendWeight; }
	if (semantic_str == "BLENDINDICES")	{ return Semantic::kBlendIndices; }
	if (semantic_str == "TANGENT")		{ return Semantic::kTangent; }
	if (semantic_str == "BINORMAL")		{ return Semantic::kBinormal; }

	return Semantic::kUnknown;
}

BKSGE_INLINE char const*
ToSemanticName(Semantic const& semantic)
{
	switch (semantic)
	{
	case Semantic::kPosition:		return "POSITION";
	case Semantic::kNormal:   		return "NORMAL";
	case Semantic::kColor:   		return "COLOR";
	case Semantic::kTexCoord: 		return "TEXCOORD";
	case Semantic::kFogCoord: 		return "FOGCOORD";
	case Semantic::kPointSize: 		return "POINTSIZE";
	case Semantic::kBlendWeight: 	return "BLENDWEIGHT";
	case Semantic::kBlendIndices: 	return "BLENDINDICES";
	case Semantic::kTangent: 		return "TANGENT";
	case Semantic::kBinormal: 		return "BINORMAL";
	case Semantic::kUnknown: 		return "UNKNOWN";
	}

	return "UNKNOWN";
}

BKSGE_INLINE std::string
to_string(Semantic const& semantic)
{
#define BKSGE_CORE_RENDER_SEMANTIC_KVP(x)	case x: return #x

	switch (semantic)
	{
		BKSGE_CORE_RENDER_SEMANTIC_KVP(Semantic::kPosition);
		BKSGE_CORE_RENDER_SEMANTIC_KVP(Semantic::kNormal);
		BKSGE_CORE_RENDER_SEMANTIC_KVP(Semantic::kColor);
		BKSGE_CORE_RENDER_SEMANTIC_KVP(Semantic::kTexCoord);
		BKSGE_CORE_RENDER_SEMANTIC_KVP(Semantic::kFogCoord);
		BKSGE_CORE_RENDER_SEMANTIC_KVP(Semantic::kPointSize);
		BKSGE_CORE_RENDER_SEMANTIC_KVP(Semantic::kBlendWeight);
		BKSGE_CORE_RENDER_SEMANTIC_KVP(Semantic::kBlendIndices);
		BKSGE_CORE_RENDER_SEMANTIC_KVP(Semantic::kTangent);
		BKSGE_CORE_RENDER_SEMANTIC_KVP(Semantic::kBinormal);
		BKSGE_CORE_RENDER_SEMANTIC_KVP(Semantic::kUnknown);
	}

	return "Semantic::kUnknown";

#undef BKSGE_CORE_RENDER_SEMANTIC_KVP
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_SEMANTIC_INL_HPP
