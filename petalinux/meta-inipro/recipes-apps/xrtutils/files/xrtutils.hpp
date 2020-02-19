/*
 * Copyright (C) 2017 – 2018 Xilinx, Inc.  All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * XILINX BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of the Xilinx shall not be used
 * in advertising or otherwise to promote the sale, use or other dealings in
 * this Software without prior written authorization from Xilinx.
 */

#ifndef _XRTUTILS_H_
#define _XRTUTILS_H_
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <mutex>
#include <string>

//#define CL_HPP_CL_1_2_DEFAULT_BUILD
//#define CL_HPP_TARGET_OPENCL_VERSION 120
//#define CL_HPP_MINIMUM_OPENCL_VERSION 120
//#define CL_HPP_ENABLE_PROGRAM_CONSTRUCTION_FROM_ARRAY_COMPATIBILITY 1
//#define CL_USE_DEPRECATED_OPENCL_1_2_APIS

//#define PROFILING

#include "xcl2.hpp"
#include <CL/cl2.hpp>
//#include "cl_ext_xilinx.h"
#include <iostream>

class XRTDevice {
public:
  static XRTDevice* acquireXRTDevice();
  static void releaseXRTDevice();
  std::vector<cl::Device> devices;
  cl::Device device;
  cl::Context context;
  cl::CommandQueue *cmd_queue;

  uintptr_t getDevMemObjAddr (cl::Buffer &buf) {
    uintptr_t phy;
    cl_mem tmp = buf();
    cl_device_id dev = this->device();
    xclGetMemObjDeviceAddress(tmp, dev, sizeof(uintptr_t), &phy);
    return phy;
  }

private:
  XRTDevice() {
    devices = xcl::get_xil_devices();
    device = devices[0];
    context = device;
    devices.resize(1);
#ifdef PROFILING
    cmd_queue = new cl::CommandQueue (context, device, CL_QUEUE_PROFILING_ENABLE);
#else
    cmd_queue = new cl::CommandQueue (context, device, 0);
#endif
  }
  ~XRTDevice() {
  }

  // copy constructor
  XRTDevice(const XRTDevice&) {
  }

  // assignment operator
  XRTDevice& operator=(const XRTDevice&) {
    return *this;
  }

  // the single instance of the object
  static XRTDevice* _device;

  // the count of references
  static int ref_count;
};

class XRTInstance {
public:
  static XRTInstance* getInstance(const char *kernel_name);
  static void releaseInstance(const char *kernel_name);
  static void lock(const char *kernel_name);
  static void unlock(const char *kernel_name);

  cl::Device getDevice () {
    return xrt_device->device;
  }

  cl::Context getContext() {
    return xrt_device->context;
  }

  cl::CommandQueue *getCmdQueue () {
    return xrt_device->cmd_queue;
  }

  uintptr_t deviceMemPhyAddr(cl::Buffer &buf) {
    return xrt_device->getDevMemObjAddr(buf);
  }

  std::string device_name;
  std::string binaryFile;
  cl::Program::Binaries bins;
  cl::Program *program;

private:
  XRTInstance(XRTDevice *xrtdevice, const char *kernel_name) {
    device_name = xrtdevice->device.getInfo<CL_DEVICE_NAME>();
    binaryFile = xcl::find_binary_file(device_name, kernel_name);
    auto fileBuf = xcl::read_binary_file(binaryFile);
    cl::Program::Binaries bins{{fileBuf.data(), fileBuf.size()}};
    //bins = xcl::import_binary_file(binaryFile);
    program = new cl::Program (xrtdevice->context, xrtdevice->devices, bins);
  }

  ~XRTInstance() {
  }

  // copy constructor
  XRTInstance(const XRTInstance&) {
  }

  // assignment operator
  XRTInstance& operator=(const XRTInstance&) {
    return *this;
  }

  // the single instance of the object
  static XRTInstance* _handle;

  // the count of references
  static int ref_count;

  static XRTDevice *xrt_device;
};

#endif
