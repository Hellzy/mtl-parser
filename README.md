# MTL Parser

This little projects aim at parsing .mtl files.

## Work Done

As of now, the parser handles creation of newmtl objects, as well as:

- ka
- kd
- kd_map

Since this project is developped only to serve as a tool in my rasterizer, it
does not implement all required features to parse an mtl file, because I don't
need all of them. Missing features will be added later.

## Error handling

I did not focus on error handling. For now the parser trusts the user input.
It will detect an invalid instruction and will skip it, however it won't
necessarily detect an incorrect value within a rule.

## Building

- `make` to build the library
- `make clean` to erase .so and .o files

Building the project takes quite a long time because of all the templates
required by `boost::gil`. I will try to use something else later. For now
I isolated the part where I use gil in a single file so that any other file
modification won't trigger a long compilation.
