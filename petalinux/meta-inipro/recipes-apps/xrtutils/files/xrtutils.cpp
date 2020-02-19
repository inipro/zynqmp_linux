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

#include "xrtutils.hpp"
#include <map>

//#define DEBUG_PRINT

std::mutex device_acq_mutex;
std::mutex device_rls_mutex;

std::mutex acq_mutex;
std::mutex rls_mutex;

std::mutex proc_mutex;

int XRTInstance::ref_count = 0;
XRTInstance* XRTInstance::_handle = NULL;
int XRTDevice::ref_count = 0;
XRTDevice* XRTDevice::_device = NULL;
XRTDevice *XRTInstance::xrt_device = NULL;

XRTDevice* XRTDevice::acquireXRTDevice(){
  std::lock_guard<std::mutex> acquire_lock(device_acq_mutex);
  if (NULL == _device){
    _device = new XRTDevice();
#ifdef DEBUG_PRINT
    std::cout << "[XRT Utils] Created XRT Device " << _device << std::endl;
#endif
  }
  ref_count++;
#ifdef DEBUG_PRINT
  std::cout << "[XRT Utils] Increased XRT Device reference to " << ref_count << std::endl;
#endif
  return _device;
}

void XRTDevice::releaseXRTDevice() {
  std::lock_guard<std::mutex> release_lock(device_rls_mutex);
  ref_count--;
#ifdef DEBUG_PRINT
  std::cout << "[XRT Utils] Decreased XRT Device reference to " << ref_count << std::endl;
#endif

  if ((0 == ref_count) && (NULL != _device)) {
#ifdef DEBUG_PRINT
    std::cout << "[XRT Utils] Destroying XRT Device : " << _device << std::endl;
#endif
    delete _device->cmd_queue;
    delete _device;
    _device = NULL;
  }
}

XRTInstance* XRTInstance::getInstance(const char *kernel_name){
  std::lock_guard<std::mutex> acquire_lock(acq_mutex);
  if (NULL == _handle){
    xrt_device = XRTDevice::acquireXRTDevice();
    _handle = new XRTInstance(xrt_device, kernel_name);
#ifdef DEBUG_PRINT
    std::cout << "[XRT Utils: " << kernel_name << "] Created XRT Instance " << _handle << std::endl;
#endif
  }
  ref_count++;
#ifdef DEBUG_PRINT
  std::cout << "[XRT Utils: " << kernel_name << "] Increased XRT Instance reference to " << ref_count << std::endl;
#endif
  return _handle;
}

void XRTInstance::releaseInstance(const char *kernel_name) {
  std::lock_guard<std::mutex> release_lock(rls_mutex);
  ref_count--;
#ifdef DEBUG_PRINT
  std::cout << "[XRT Utils: " << kernel_name << "] Decreased XRT Instance reference to " << ref_count << std::endl;
#endif
  if ((0 == ref_count) && (NULL != _handle)) {
#ifdef DEBUG_PRINT
    std::cout << "[XRT Utils: " << kernel_name << "] Destroying XRT Instance : " << _handle << std::endl;
#endif
    delete _handle->program;
    XRTDevice::releaseXRTDevice();
    delete _handle;
    _handle = NULL;
  }
}

void XRTInstance::lock (const char *kernel_name) {
#ifdef DEBUG_PRINT
  std::cout << "[XRT Utils: " << kernel_name << "] Aquire Processing Lock" << std::endl;
#endif
  return proc_mutex.lock();
}

void XRTInstance::unlock (const char *kernel_name) {
#ifdef DEBUG_PRINT
  std::cout << "[XRT Utils: " << kernel_name << "] Release Processing Lock" << std::endl;
#endif
  return proc_mutex.unlock();
}
