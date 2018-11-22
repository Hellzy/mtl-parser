#pragma once
#include <fstream>
#include <map>
#include <string>

#include "material.hh"

class MTLParser
{
public:
    MTLParser() = default;
    MTLParser(const std::string& filename);

    void load(const std::string& filename);

private:
    material_t parse_material(std::ifstream& ifs);
    void parse_tex_map(const std::string& filename, material_t& m);

private:
    std::map<std::string, material_t> mats_;
};
