#include "material.hh"

__host__
DeviceMaterial::DeviceMaterial(const host_mat_t& m)
{
    kd = m.kd;
    ka = m.ka;
    tex_w = m.tex_w;
    tex_h = m.tex_h;

    cudaMalloc(&kd_map, sizeof(vec3_t) * m.kd_map.size());
    cudaMemcpy(kd_map, m.kd_map.data(), m.kd_map.size(), cudaMemcpyHostToDevice);
}

__host__
DeviceMaterial::~DeviceMaterial()
{
    cudaFree(kd_map);
}
