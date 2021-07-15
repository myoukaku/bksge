/**
 *	@file	open_type_font_inl.hpp
 *
 *	@brief	OpenTypeFont の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_INL_OPEN_TYPE_FONT_INL_HPP
#define BKSGE_CORE_FONT_INL_OPEN_TYPE_FONT_INL_HPP

#include <bksge/core/font/open_type_font.hpp>
#include <bksge/core/font/otf/table_directory.hpp>
#include <bksge/core/font/otf/cmap.hpp>
#include <bksge/core/font/otf/head.hpp>
#include <bksge/core/font/otf/hhea.hpp>
#include <bksge/core/font/otf/hmtx.hpp>
#include <bksge/core/font/otf/maxp.hpp>
#include <bksge/core/font/otf/name.hpp>
#include <bksge/core/font/otf/os2.hpp>
#include <bksge/core/font/otf/post.hpp>
#include <bksge/core/font/otf/cvt.hpp>
#include <bksge/core/font/otf/fpgm.hpp>
#include <bksge/core/font/otf/glyf.hpp>
#include <bksge/core/font/otf/loca.hpp>
#include <bksge/core/font/otf/prep.hpp>
#include <bksge/core/font/otf/gasp.hpp>
#include <bksge/core/font/otf/cff.hpp>
#include <bksge/core/font/otf/cff2.hpp>
#include <bksge/core/font/otf/vorg.hpp>
#include <bksge/core/font/otf/svg.hpp>
#include <bksge/core/font/otf/ebdt.hpp>
#include <bksge/core/font/otf/eblc.hpp>
#include <bksge/core/font/otf/ebsc.hpp>
#include <bksge/core/font/otf/cbdt.hpp>
#include <bksge/core/font/otf/cblc.hpp>
#include <bksge/core/font/otf/sbix.hpp>
#include <bksge/core/font/otf/base.hpp>
#include <bksge/core/font/otf/gdef.hpp>
#include <bksge/core/font/otf/gpos.hpp>
#include <bksge/core/font/otf/gsub.hpp>
#include <bksge/core/font/otf/jstf.hpp>
#include <bksge/core/font/otf/math.hpp>
#include <bksge/core/font/otf/avar.hpp>
#include <bksge/core/font/otf/cvar.hpp>
#include <bksge/core/font/otf/fvar.hpp>
#include <bksge/core/font/otf/gvar.hpp>
#include <bksge/core/font/otf/hvar.hpp>
#include <bksge/core/font/otf/mvar.hpp>
#include <bksge/core/font/otf/stat.hpp>
#include <bksge/core/font/otf/vvar.hpp>
#include <bksge/core/font/otf/colr.hpp>
#include <bksge/core/font/otf/cpal.hpp>
#include <bksge/core/font/otf/dsig.hpp>
#include <bksge/core/font/otf/hdmx.hpp>
#include <bksge/core/font/otf/ltsh.hpp>
#include <bksge/core/font/otf/merg.hpp>
#include <bksge/core/font/otf/meta.hpp>
#include <bksge/core/font/otf/vdmx.hpp>
#include <bksge/core/font/otf/vhea.hpp>
#include <bksge/core/font/otf/vmtx.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>
#include <cstdint>

namespace bksge
{

BKSGE_INLINE
OpenTypeFont::OpenTypeFont(std::uint8_t const* ptr, std::size_t size)
{
	(void)size;
	m_table_directory = bksge::make_unique<otf::TableDirectory>(ptr);

	for (auto const& record : m_table_directory->tableRecords)
	{
		std::uint8_t const* src = ptr + record.offset;
		switch (record.tableTag)
		{
		case 'cmap':
			m_cmap = bksge::make_unique<otf::CMapTable>(src);
			break;
		case 'head':
			m_head = bksge::make_unique<otf::FontHeaderTable>(src);
			break;
		case 'hhea':
			m_hhea = bksge::make_unique<otf::HorizontalHeaderTable>(src);
			break;
		case 'maxp':
			m_maxp = bksge::make_unique<otf::MaximumProfile>(src);
			break;
		case 'name':
			m_name = bksge::make_unique<otf::NamingTable>(src);
			break;
		case 'OS/2':
			m_os2  = bksge::make_unique<otf::OS2Table>(src);
			break;
		case 'post':
			m_post = bksge::make_unique<otf::PostScriptTable>(src);
			break;

		case 'cvt ':
			m_cvt  = bksge::make_unique<otf::ControlValueTable>(src, record.length);
			break;
		case 'fpgm':
			m_fpgm = bksge::make_unique<otf::FontProgram>(src, record.length);
			break;
		case 'glyf':
			m_glyf = bksge::make_unique<otf::GlyphData>(src, record.length);
			break;
		case 'prep':
			m_prep = bksge::make_unique<otf::ControlValueProgram>(src, record.length);
			break;
		case 'gasp':
			m_gasp = bksge::make_unique<otf::GaspTable>(src);
			break;

		case 'CFF ':
			m_cff  = bksge::make_unique<otf::CompactFontFormatTable>(src, record.length);
			break;
		case 'CFF2':
			m_cff2 = bksge::make_unique<otf::CompactFontFormat2Table>(src, record.length);
			break;
		case 'VORG':
			m_vorg = bksge::make_unique<otf::VerticalOriginTable>(src);
			break;

		case 'SVG ':
			m_svg = bksge::make_unique<otf::SVGTable>(src);
			break;

		case 'EBDT':
			m_ebdt = bksge::make_unique<otf::EmbeddedBitmapDataTable>(src);
			break;
		case 'EBLC':
			m_eblc = bksge::make_unique<otf::EmbeddedBitmapLocationTable>(src);
			break;
		case 'EBSC':
			m_ebsc = bksge::make_unique<otf::EmbeddedBitmapScalingTable>(src);
			break;
		case 'CBDT':
			m_cbdt = bksge::make_unique<otf::ColorBitmapDataTable>(src);
			break;
		case 'CBLC':
			m_cblc = bksge::make_unique<otf::ColorBitmapLocationTable>(src);
			break;
		case 'sbix':
			m_sbix = bksge::make_unique<otf::StandardBitmapGraphicsTable>(src);
			break;

		case 'BASE':
			m_base = bksge::make_unique<otf::BaselineTable>(src);
			break;
		case 'GDEF':
			m_gdef = bksge::make_unique<otf::GlyphDefinitionTable>(src);
			break;
		case 'GPOS':
			m_gpos = bksge::make_unique<otf::GlyphPositioningTable>(src);
			break;
		case 'GSUB':
			m_gsub = bksge::make_unique<otf::GlyphSubstitutionTable>(src);
			break;
		case 'JSTF':
			m_jstf = bksge::make_unique<otf::JustificationTable>(src);
			break;
		case 'MATH':
			m_math = bksge::make_unique<otf::MathTable>(src);
			break;

		case 'avar':
			m_avar = bksge::make_unique<otf::AxisVariationsTable>(src);
			break;
		case 'fvar':
			m_fvar = bksge::make_unique<otf::FontVariationsTable>(src);
			break;
		case 'gvar':
			m_gvar = bksge::make_unique<otf::GlyphVariationsTable>(src);
			break;
		case 'HVAR':
			m_hvar = bksge::make_unique<otf::HorizontalMetricsVariationsTable>(src);
			break;
		case 'MVAR':
			m_mvar = bksge::make_unique<otf::MetricsVariationsTable>(src);
			break;
		case 'STAT':
			m_stat = bksge::make_unique<otf::StyleAttributesTable>(src);
			break;
		case 'VVAR':
			m_vvar = bksge::make_unique<otf::VerticalMetricsVariationsTable>(src);
			break;

		case 'COLR':
			m_colr = bksge::make_unique<otf::ColorTable>(src);
			break;
		case 'CPAL':
			m_cpal = bksge::make_unique<otf::ColorPaletteTable>(src);
			break;

		case 'DSIG':
			m_dsig = bksge::make_unique<otf::DigitalSignatureTable>(src);
			break;
		case 'LTSH':
			m_ltsh = bksge::make_unique<otf::LinearThresholdTable>(src);
			break;
		case 'MERG':
			m_merg = bksge::make_unique<otf::MergeTable>(src);
			break;
		case 'meta':
			m_meta = bksge::make_unique<otf::MetadataTable>(src);
			break;
		case 'VDMX':
			m_vdmx = bksge::make_unique<otf::VerticalDeviceMetrics>(src);
			break;
		case 'vhea':
			m_vhea = bksge::make_unique<otf::VerticalHeaderTable>(src);
			break;
		}
	}

	for (auto const& record : m_table_directory->tableRecords)
	{
		std::uint8_t const* src = ptr + record.offset;
		switch (record.tableTag)
		{
		case 'hmtx':
			m_hmtx = bksge::make_unique<otf::HorizontalMetricsTable>(
				src,
				m_hhea->numberOfHMetrics,
				m_maxp->numGlyphs);
			break;

		case 'loca':
			m_loca = bksge::make_unique<otf::IndexToLocation>(
				src,
				m_head->indexToLocFormat,
				m_maxp->numGlyphs);
			break;
		case 'cvar':
			m_cvar = bksge::make_unique<otf::CVTVariationsTable>(
				src,
				m_fvar->axisCount());
			break;

		case 'hdmx':
			m_hdmx = bksge::make_unique<otf::HorizontalDeviceMetrics>(
				src,
				m_maxp->numGlyphs);
			break;

		case 'vmtx':
			m_vmtx = bksge::make_unique<otf::VerticalMetricsTable>(
				src,
				m_vhea->numOfLongVerMetrics,
				m_maxp->numGlyphs);
			break;
		}
	}
}

BKSGE_INLINE
OpenTypeFont::~OpenTypeFont()
{
}

BKSGE_INLINE std::uint16_t
OpenTypeFont::GetGlyphIndex(std::uint32_t char_code) const
{
	if (m_cmap == nullptr)
	{
		return 0;
	}

	return m_cmap->GetGlyphIndex(char_code);
}

}	// namespace bksge

#endif // BKSGE_CORE_FONT_INL_OPEN_TYPE_FONT_INL_HPP
