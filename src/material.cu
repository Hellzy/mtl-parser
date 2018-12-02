#include <iostream>
#include "material.hh"

__host__
DeviceMaterial::DeviceMaterial(const host_mat_t& m)
{
    kd = m.kd;
    ka = m.ka;
    tex_w = m.tex_w;
    tex_h = m.tex_h;

    cudaMalloc(&kd_map, sizeof(vec3_t) * m.kd_map.size());
    cudaMemcpy(kd_map, m.kd_map.data(), m.kd_map.size() * sizeof(vec3_t), cudaMemcpyHostToDevice);

    std::cout << "w*h = " << tex_w * tex_h << '\n'
              << "vec.size() = " << m.kd_map.size() << '\n';
}

__host__
DeviceMaterial::~DeviceMaterial()
{
    std::cout << "DTOR\n";
    cudaFree(kd_map);
}

__host__
DeviceMaterial& DeviceMaterial::operator=(DeviceMaterial&& m)
{
    kd = m.kd;
    ka = m.kd;
    tex_w = m.tex_w;
    tex_h = m.tex_h;
    kd_map = m.kd_map;
    m.kd_map = nullptr;

    return *this;
}
