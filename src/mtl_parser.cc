#include <algorithm>
#include <cctype>
#include <iostream>

#include "mtl_parser.hh"

namespace mtlp
{

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
#ifdef DEBUG
            else
                std::cerr << "Skipping: " << tok << '\n';
#endif
        }
    }

    host_mat_t MTLParser::parse_material(std::ifstream& ifs)
    {
        std::string name;
        ifs >> name;

        host_mat_t m;

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
#ifdef DEBUG
            else
            {
                std::cerr << "Skipping: " << tok << '\n';
            }
#endif
        }

        mats_[name] = m;

        return m;
    }

} //namespace mtlp
