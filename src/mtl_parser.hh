#pragma once
#include <fstream>
#include <map>
#include <string>

#include "material.hh"

namespace mtlp
{

    class MTLParser
    {
        public:
            MTLParser() = default;
            MTLParser(const std::string& filename);

            void load(const std::string& filename);
            std::map<std::string, host_mat_t> mats_get() { return mats_; }

        private:
            host_mat_t parse_material(std::ifstream& ifs);
            void parse_tex_map(const std::string& filename, host_mat_t& m);

        private:
            std::map<std::string, host_mat_t> mats_;
    };

} //namespace mtlp
