#include <iostream>
#include "parser.hh"

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " 'path/to/file.mtl'\n";
        return 1;
    }

    MTLParser parser(argv[1]);
    return 0;
}
