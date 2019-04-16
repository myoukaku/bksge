/**
 *	@file	semantic_inl.hpp
 *
 *	@brief	Semantic の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_INL_SEMANTIC_INL_HPP
#define BKSGE_RENDER_INL_SEMANTIC_INL_HPP

#include <bksge/render/semantic.hpp>
#include <unordered_map>
#include <string>

namespace bksge
{

namespace render
{

BKSGE_INLINE Semantic
ToSemantic(std::string const& semantic_str)
{
	static std::unordered_map<std::string, Semantic> const m =
	{
		{ std::string("POSITION"),		Semantic::kPosition },
		{ std::string("NORMAL"),		Semantic::kNormal },
		{ std::string("COLOR"),			Semantic::kColor },
		{ std::string("TEXCOORD"),		Semantic::kTexCoord },
		{ std::string("TEXCOORD0"),		Semantic::kTexCoord },
		{ std::string("TEXCOORD1"),		Semantic::kTexCoord },
		{ std::string("FOGCOORD"),		Semantic::kFogCoord },
		{ std::string("POINTSIZE"),		Semantic::kPointSize },
		{ std::string("BLENDWEIGHT"),	Semantic::kBlendWeight },
		{ std::string("BLENDINDICES"),	Semantic::kBlendIndices },
		{ std::string("TANGENT"),		Semantic::kTangent },
		{ std::string("BINORMAL"),		Semantic::kBinormal },
	};

	auto it = m.find(semantic_str);
	if (it != m.end())
	{
		return it->second;
	}
	return Semantic::kUnknown;
}

BKSGE_INLINE char const*
ToSemanticName(Semantic const& semantic)
{
	static std::unordered_map<Semantic, char const*> const m =
	{
		{ Semantic::kPosition,		"POSITION"     },
		{ Semantic::kNormal,   		"NORMAL"       },
		{ Semantic::kColor,   		"COLOR"        },
		{ Semantic::kTexCoord, 		"TEXCOORD"     },
		{ Semantic::kFogCoord, 		"FOGCOORD"     },
		{ Semantic::kPointSize, 	"POINTSIZE"    },
		{ Semantic::kBlendWeight, 	"BLENDWEIGHT"  },
		{ Semantic::kBlendIndices, 	"BLENDINDICES" },
		{ Semantic::kTangent, 		"TANGENT"      },
		{ Semantic::kBinormal, 		"BINORMAL"     },
	};

	auto it = m.find(semantic);
	if (it != m.end())
	{
		return it->second;
	}
	return "UNKNOWN";
}

BKSGE_INLINE std::string
to_string(Semantic const& semantic)
{
#define BKSGE_RENDER_MAKE_SEMANTIC_KVP(x)	{ x, #x }

	static std::unordered_map<Semantic, std::string> const m =
	{
		BKSGE_RENDER_MAKE_SEMANTIC_KVP(Semantic::kPosition),
		BKSGE_RENDER_MAKE_SEMANTIC_KVP(Semantic::kNormal),
		BKSGE_RENDER_MAKE_SEMANTIC_KVP(Semantic::kColor),
		BKSGE_RENDER_MAKE_SEMANTIC_KVP(Semantic::kTexCoord),
		BKSGE_RENDER_MAKE_SEMANTIC_KVP(Semantic::kFogCoord),
		BKSGE_RENDER_MAKE_SEMANTIC_KVP(Semantic::kPointSize),
		BKSGE_RENDER_MAKE_SEMANTIC_KVP(Semantic::kBlendWeight),
		BKSGE_RENDER_MAKE_SEMANTIC_KVP(Semantic::kBlendIndices),
		BKSGE_RENDER_MAKE_SEMANTIC_KVP(Semantic::kTangent),
		BKSGE_RENDER_MAKE_SEMANTIC_KVP(Semantic::kBinormal),
	};

	auto it = m.find(semantic);
	if (it != m.end())
	{
		return it->second;
	}
	return "Semantic::kUnknown";

#undef BKSGE_RENDER_MAKE_SEMANTIC_KVP
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_INL_SEMANTIC_INL_HPP
