#include <boost/gil.hpp>
#include <boost/gil/extension/io/jpeg.hpp>

#include "parser.hh"

void MTLParser::parse_tex_map(const std::string& filename, material_t& m)
{
    boost::gil::rgb8_image_t tex;
    boost::gil::read_image(filename, tex, boost::gil::jpeg_tag());

    m.tex_w = tex.width();
    m.tex_h = tex.height();

    auto v = view(tex);

    for (const auto& pix : v)
        m.kd_map.push_back({pix[0], pix[1], pix[2]});
}
