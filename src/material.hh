#pragma once
#include <string>
#include <vector>

#include "types.hh"

struct Material
{
    vec3_t kd;
    vec3_t ka;
    std::vector<vec3_t> kd_map;

    size_t tex_w;
    size_t tex_h;

    vec3_t map_get(size_t u, size_t v) const
    {
        return kd_map[tex_w * 3 * v + 3 * u];
    }
};
using material_t = Material;
