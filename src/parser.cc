#include <algorithm>
#include <cctype>
#include <iostream>

#include "parser.hh"

MTLParser::MTLParser(const std::string& filename)
{
    load(filename);
}

void MTLParser::load(const std::string& filename)
{
    std::ifstream ifs(filename);

    while (ifs.good() && !ifs.eof())
    {
        std::string tok;
        ifs >> tok;

        if (!tok.compare("newmtl"))
            parse_material(ifs);
        else
            std::cerr << "Skipping: " << tok << '\n';
    }
}

material_t MTLParser::parse_material(std::ifstream& ifs)
{
    std::string name;
    ifs >> name;

    Material m;

    while (ifs.good() && !ifs.eof())
    {
        std::string tok;
        ifs >> tok;
        std::transform(tok.begin(), tok.end(), tok.begin(), ::tolower);

        if (!tok.compare("ka"))
        {
            ifs >> m.ka.x >> m.ka.y >> m.ka.z;
        }
        else if (!tok.compare("kd"))
        {
            ifs >> m.kd.x >> m.kd.y >> m.kd.z;
        }
        else if (!tok.compare("map_kd"))
        {
            ifs >> tok;
            parse_tex_map(tok, m);
        }
        else if (!tok.compare("newmtl"))
        {
            for (auto it = tok.rbegin(); it != tok.rend(); ++it)
                ifs.putback(*it);
            break;
        }
        else
        {
            std::cerr << "Skipping: " << tok << '\n';
        }
    }

    mats_[name] = m;

    return m;
}
