/**
 *	@file	open_type_font.hpp
 *
 *	@brief	OpenTypeFont の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OPEN_TYPE_FONT_HPP
#define BKSGE_CORE_FONT_OPEN_TYPE_FONT_HPP

#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/cstddef.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace otf
{

struct TableDirectory;

// Required Tables
struct CMapTable;
struct FontHeaderTable;
struct HorizontalHeaderTable;
struct HorizontalMetricsTable;
struct MaximumProfile;
struct NamingTable;
struct OS2Table;
struct PostScriptTable;

// Tables Related to TrueType Outlines
struct ControlValueTable;
struct FontProgram;
struct GlyphData;
struct IndexToLocation;
struct ControlValueProgram;
struct GaspTable;

// Tables Related to CFF Outlines
struct CompactFontFormatTable;
struct CompactFontFormat2Table;
struct VerticalOriginTable;

// Table Related to SVG Outlines
struct SVGTable;

// Tables Related to Bitmap Glyphs
struct EmbeddedBitmapDataTable;
struct EmbeddedBitmapLocationTable;
struct EmbeddedBitmapScalingTable;
struct ColorBitmapDataTable;
struct ColorBitmapLocationTable;
struct StandardBitmapGraphicsTable;

// Advanced Typographic Tables
struct BaselineTable;
struct GlyphDefinitionTable;
struct GlyphPositioningTable;
struct GlyphSubstitutionTable;
struct JustificationTable;
struct MathTable;

// Tables used for OpenType Font Variations
struct AxisVariationsTable;
struct CVTVariationsTable;
struct FontVariationsTable;
struct GlyphVariationsTable;
struct HorizontalMetricsVariationsTable;
struct MetricsVariationsTable;
struct StyleAttributesTable;
struct VerticalMetricsVariationsTable;

// Tables Related to Color Fonts
struct ColorTable;
struct ColorPaletteTable;
//struct ColorBitmapDataTable;
//struct ColorBitmapLocationTable;
//struct StandardBitmapGraphicsTable;
//struct SVGTable;

// Other OpenType Tables
struct DigitalSignatureTable;
struct HorizontalDeviceMetrics;
// TODO struct KerningTable;
struct LinearThresholdTable;
struct MergeTable;
struct MetadataTable;
//struct StyleAttributesTable;
//struct PCL5Table;
struct VerticalDeviceMetrics;
struct VerticalHeaderTable;
struct VerticalMetricsTable;

}	// namespace otf

class OpenTypeFont
{
public:
	OpenTypeFont(bksge::uint8_t const* ptr, bksge::size_t size);
	~OpenTypeFont();

private:
	bksge::unique_ptr<otf::TableDirectory>				m_table_directory;

	// Required Tables
	bksge::unique_ptr<otf::CMapTable>					m_cmap;
	bksge::unique_ptr<otf::FontHeaderTable>				m_head;
	bksge::unique_ptr<otf::HorizontalHeaderTable>		m_hhea;
	bksge::unique_ptr<otf::HorizontalMetricsTable>		m_hmtx;
	bksge::unique_ptr<otf::MaximumProfile>				m_maxp;
	bksge::unique_ptr<otf::NamingTable>					m_name;
	bksge::unique_ptr<otf::OS2Table>					m_os2;
	bksge::unique_ptr<otf::PostScriptTable>				m_post;

	// Tables Related to TrueType Outlines
	bksge::unique_ptr<otf::ControlValueTable>			m_cvt;
	bksge::unique_ptr<otf::FontProgram>					m_fpgm;
	bksge::unique_ptr<otf::GlyphData>					m_glyf;
	bksge::unique_ptr<otf::IndexToLocation>				m_loca;
	bksge::unique_ptr<otf::ControlValueProgram>			m_prep;
	bksge::unique_ptr<otf::GaspTable>					m_gasp;

	// Tables Related to CFF Outlines
	bksge::unique_ptr<otf::CompactFontFormatTable>		m_cff;
	bksge::unique_ptr<otf::CompactFontFormat2Table>		m_cff2;
	bksge::unique_ptr<otf::VerticalOriginTable>			m_vorg;

	// Table Related to SVG Outlines
	bksge::unique_ptr<otf::SVGTable>					m_svg;

	// Tables Related to Bitmap Glyphs
	bksge::unique_ptr<otf::EmbeddedBitmapDataTable>		m_ebdt;
	bksge::unique_ptr<otf::EmbeddedBitmapLocationTable>	m_eblc;
	bksge::unique_ptr<otf::EmbeddedBitmapScalingTable>	m_ebsc;
	bksge::unique_ptr<otf::ColorBitmapDataTable>		m_cbdt;
	bksge::unique_ptr<otf::ColorBitmapLocationTable>	m_cblc;
	bksge::unique_ptr<otf::StandardBitmapGraphicsTable>	m_sbix;

	// Advanced Typographic Tables
	bksge::unique_ptr<otf::BaselineTable>				m_base;
	bksge::unique_ptr<otf::GlyphDefinitionTable>		m_gdef;
	bksge::unique_ptr<otf::GlyphPositioningTable>		m_gpos;
	bksge::unique_ptr<otf::GlyphSubstitutionTable>		m_gsub;
	bksge::unique_ptr<otf::JustificationTable>			m_jstf;
	bksge::unique_ptr<otf::MathTable>					m_math;

	// Tables used for OpenType Font Variations
	bksge::unique_ptr<otf::AxisVariationsTable>			m_avar;
	bksge::unique_ptr<otf::CVTVariationsTable>			m_cvar;
	bksge::unique_ptr<otf::FontVariationsTable>			m_fvar;
	bksge::unique_ptr<otf::GlyphVariationsTable>		m_gvar;
	bksge::unique_ptr<otf::HorizontalMetricsVariationsTable>	m_hvar;
	bksge::unique_ptr<otf::MetricsVariationsTable>		m_mvar;
	bksge::unique_ptr<otf::StyleAttributesTable>		m_stat;
	bksge::unique_ptr<otf::VerticalMetricsVariationsTable>		m_vvar;

	// Tables Related to Color Fonts
	bksge::unique_ptr<otf::ColorTable>					m_colr;
	bksge::unique_ptr<otf::ColorPaletteTable>			m_cpal;

	// Other OpenType Tables
	bksge::unique_ptr<otf::DigitalSignatureTable>		m_dsig;
	bksge::unique_ptr<otf::HorizontalDeviceMetrics>		m_hdmx;
	bksge::unique_ptr<otf::LinearThresholdTable>		m_ltsh;
	bksge::unique_ptr<otf::MergeTable>					m_merg;
	bksge::unique_ptr<otf::MetadataTable>				m_meta;
	bksge::unique_ptr<otf::VerticalDeviceMetrics>		m_vdmx;
	bksge::unique_ptr<otf::VerticalHeaderTable>			m_vhea;
	bksge::unique_ptr<otf::VerticalMetricsTable>		m_vmtx;
};

}	// namespace bksge

#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/input/inl/game_pad_state_inl.hpp>
#endif

#endif // BKSGE_CORE_FONT_OPEN_TYPE_FONT_HPP
