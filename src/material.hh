#pragma once
#include <string>
#include <vector>
#include <cuda_runtime.h>

#include "types.hh"

/***
 * Skeleton for a material structure, used as a parent class for CPU/GPU material
 */
struct MaterialSkel
{
    vec3_t kd;
    vec3_t ka;
    size_t tex_w;
    size_t tex_h;
};

struct HostMaterial : MaterialSkel
{
    std::vector<vec3_t> kd_map;
};
using host_mat_t = HostMaterial;

struct DeviceMaterial : MaterialSkel
{
    DeviceMaterial() = default;
    __host__ explicit DeviceMaterial(const host_mat_t& m);
    __host__ DeviceMaterial& operator=(DeviceMaterial&& m);
    __host__ ~DeviceMaterial();

    vec3_t* kd_map;
};
using dev_mat_t = DeviceMaterial;
