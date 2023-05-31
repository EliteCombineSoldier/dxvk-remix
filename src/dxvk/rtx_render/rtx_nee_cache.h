/*
* Copyright (c) 2023, NVIDIA CORPORATION. All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
*/
#pragma once

#include "../dxvk_format.h"
#include "../dxvk_include.h"

#include "../spirv/spirv_code_buffer.h"
#include "rtx_resources.h"
#include "rtx_option.h"

namespace dxvk {

  class RtxContext;

  class NeeCachePass {

  public:

    NeeCachePass(dxvk::DxvkDevice* device);
    ~NeeCachePass();

    void dispatch(
      RtxContext* ctx, 
      const Resources::RaytracingOutput& rtOutput);

    void showImguiSettings();

    void setRaytraceArgs(RaytraceArgs& raytraceArgs) const;

    RW_RTX_OPTION("rtx.neeCache", bool, enable, true, "Enable NEE cache. The integrator will perform NEE on emissive triangles, which usually have significant light contributions, stored in the cache.");
    RTX_OPTION("rtx.neeCache", bool, enableImportanceSampling, true, "Enable importance sampling.");
    RTX_OPTION("rtx.neeCache", bool, enableMIS, true, "Enable MIS.");
    RTX_OPTION("rtx.neeCache", bool, enableJittering, true, "Enable jittering in cell look up.");
    RTX_OPTION("rtx.neeCache", bool, enableInFirstBounce, true, "Enable NEE Cache in the first bounce.");
    RTX_OPTION("rtx.neeCache", bool, enableInSecondAndMoreBounces, true, "Enable NEE Cache in the second and more bounces.");
    RTX_OPTION("rtx.neeCache", bool, enableRandomReplacement, false, "Enable random replacement, in which old triangles will be randomly replaced by newly discovered ones. Otherwise, the ones with highest contribution scores will always be chosen.");
    RTX_OPTION("rtx.neeCache", float, range, 3000, "World space range.");
    RTX_OPTION("rtx.neeCache", float, emissiveTextureSampleFootprintSize, 1.0, "Emissive texture sample footprint size.");
    RTX_OPTION("rtx.neeCache", float, ageCullingSpeed, 0.02, "This threshold determines culling speed of an old triangle. A triangle that is not detected for several frames will be deemed less important and culled quicker.");
  private:
    Rc<vk::DeviceFn> m_vkd;

    dxvk::DxvkDevice* m_device;
  };
} // namespace dxvk
