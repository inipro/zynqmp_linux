#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <cstring>
#include <thread>
#include <chrono>
#include <time.h>
#include <unistd.h>
#include <zocl/zynq_ioctl.h>

#define XVADD_VADD_CONTROL_ADDR_AP_CTRL    0x00
#define XVADD_VADD_CONTROL_ADDR_GIE        0x04
#define XVADD_VADD_CONTROL_ADDR_IER        0x08
#define XVADD_VADD_CONTROL_ADDR_ISR        0x0c
#define XVADD_VADD_CONTROL_ADDR_IN1_DATA   0x10
#define XVADD_VADD_CONTROL_BITS_IN1_DATA   64
#define XVADD_VADD_CONTROL_ADDR_IN2_DATA   0x1c
#define XVADD_VADD_CONTROL_BITS_IN2_DATA   64
#define XVADD_VADD_CONTROL_ADDR_OUT_R_DATA 0x28
#define XVADD_VADD_CONTROL_BITS_OUT_R_DATA 64
#define XVADD_VADD_CONTROL_ADDR_SIZE_DATA  0x34
#define XVADD_VADD_CONTROL_BITS_SIZE_DATA  32


bool is_ready(uint32_t *addptr) {
  return !((*(addptr + XVADD_VADD_CONTROL_ADDR_AP_CTRL) >> 0) & 0x1);
}

bool is_done(uint32_t *addptr) {
  return ((*(addptr + XVADD_VADD_CONTROL_ADDR_AP_CTRL) >> 1) & 0x1);
}

bool is_idle(uint32_t *addptr) {
  return ((*(addptr + XVADD_VADD_CONTROL_ADDR_AP_CTRL) >> 2) & 0x1);
}

void start_kernel(uint32_t *addptr) {
  *(addptr + XVADD_VADD_CONTROL_ADDR_AP_CTRL) |= 0x1;
}

void print_kernel_status(uint32_t *add1ptr){

  uint32_t isDone, isIdle, isReady;
  isDone = is_done(add1ptr);
  isIdle = is_idle(add1ptr);
  isReady = is_ready(add1ptr);
  printf("---current kernel status done:%d, idle:%d, Ready:%d ---\n\r", isDone, isIdle, isReady);

}

int main(int argc, char *argv[])
{
    if (argc > 2) {
        std::cerr << "Usage: " << argv[0] << " [freq]\n";
        return 1;
    }

    int fd = open("/dev/dri/renderD128",  O_RDWR);
    if (fd < 0) {
        return -1;
    }

    std::cout << "============================================================" << std::endl;
    std::cout << "CREATE" << std::endl;
    drm_zocl_create_bo info1 = {4096*4, 0xffffffff, DRM_ZOCL_BO_FLAGS_COHERENT | DRM_ZOCL_BO_FLAGS_CMA};
    int result = ioctl(fd, DRM_IOCTL_ZOCL_CREATE_BO, &info1);
    std::cout << "result = " << result << std::endl;
    std::cout << "Handle " << info1.handle << std::endl;

    drm_zocl_create_bo info2 = {4096*4, 0xffffffff, DRM_ZOCL_BO_FLAGS_COHERENT | DRM_ZOCL_BO_FLAGS_CMA};
    result = ioctl(fd, DRM_IOCTL_ZOCL_CREATE_BO, &info2);
    std::cout << "result = " << result << std::endl;
    std::cout << "Handle " << info2.handle << std::endl;

    drm_zocl_create_bo info3 = {4096*4, 0xffffffff, DRM_ZOCL_BO_FLAGS_COHERENT | DRM_ZOCL_BO_FLAGS_CMA};
    result = ioctl(fd, DRM_IOCTL_ZOCL_CREATE_BO, &info3);
    std::cout << "result = " << result << std::endl;
    std::cout << "Handle " << info3.handle << std::endl;


    std::cout << "============================================================" << std::endl;
    std::cout << "INFO" << std::endl;
    drm_zocl_info_bo infoInfo1 = {info1.handle, 0, 0};
    result = ioctl(fd, DRM_IOCTL_ZOCL_INFO_BO, &infoInfo1);
    std::cout << "result = " << result << std::endl;
    std::cout << "Handle " << info1.handle << std::endl;
    std::cout << "Size " << infoInfo1.size << std::endl;
    std::cout << "Physical " << std::hex << infoInfo1.paddr << std::dec << std::endl;

    std::cout << "============================================================" << std::endl;
    drm_zocl_info_bo infoInfo2 = {info2.handle, 0, 0};
    result = ioctl(fd, DRM_IOCTL_ZOCL_INFO_BO, &infoInfo2);
    std::cout << "result = " << result << std::endl;
    std::cout << "Handle " << info2.handle << std::endl;
    std::cout << "Size " << infoInfo2.size << std::endl;
    std::cout << "Physical " << std::hex << infoInfo2.paddr << std::dec << std::endl;

    std::cout << "============================================================" << std::endl;
    drm_zocl_info_bo infoInfo3 = {info3.handle, 0, 0};
    result = ioctl(fd, DRM_IOCTL_ZOCL_INFO_BO, &infoInfo3);
    std::cout << "result = " << result << std::endl;
    std::cout << "Handle " << info3.handle << std::endl;
    std::cout << "Size " << infoInfo3.size << std::endl;
    std::cout << "Physical " << std::hex << infoInfo3.paddr << std::dec << std::endl;

    std::cout << "============================================================" << std::endl;
    std::cout << "MMAP" << std::endl;
    drm_zocl_map_bo mapInfo1 = {info1.handle, 0, 0};
    result = ioctl(fd, DRM_IOCTL_ZOCL_MAP_BO, &mapInfo1);
    std::cout << "result = " << result << std::endl;
    std::cout << "Handle " << info1.handle << std::endl;
    void *ptr1 = mmap(0, info1.size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, mapInfo1.offset);
    std::cout << "Offset "  << std::hex << mapInfo1.offset << std::dec << std::endl;
    std::cout << "Pointer " << ptr1 << std::endl;

    drm_zocl_map_bo mapInfo2 = {info2.handle, 0, 0};
    result = ioctl(fd, DRM_IOCTL_ZOCL_MAP_BO, &mapInfo2);
    std::cout << "result = " << result << std::endl;
    std::cout << "Handle " << info2.handle << std::endl;
    void *ptr2 = mmap(0, info2.size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, mapInfo2.offset);
    std::cout << "Offset "  << std::hex << mapInfo2.offset << std::dec << std::endl;
    std::cout << "Pointer " << ptr2 << std::endl;

    drm_zocl_map_bo mapInfo3 = {info3.handle, 0, 0};
    result = ioctl(fd, DRM_IOCTL_ZOCL_MAP_BO, &mapInfo3);
    std::cout << "result = " << result << std::endl;
    std::cout << "Handle " << info3.handle << std::endl;
    void *ptr3 = mmap(0, info3.size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, mapInfo3.offset);
    std::cout << "Offset "  << std::hex << mapInfo3.offset << std::dec << std::endl;
    std::cout << "Pointer " << ptr3 << std::endl;

    std::cout << "============================================================" << std::endl;
    uint32_t *p1 = (uint32_t*) ptr1;
    uint32_t *p2 = (uint32_t*) ptr2;
    
    for (int i=0; i<4096; i++) {
        p1[i] = i;
        p2[i] = i;
    }
    
    std::cout << "============================================================" << std::endl;
    std::cout << "Compute Unit Status: " << std::endl;
    uint32_t *add1ptr = (uint32_t*)mmap(0, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    printf("Compute Unit addr: %p\n", add1ptr);

    //Print the registers again before starting the kernel
    for (int i = 0; i < 13; ++i) {
      printf("Addr: %p, Data 0x%x\n", add1ptr + i, (uint32_t)(*(add1ptr + i)));
    }
    std::cout << "=================Writing values===========================================" << std::endl;
    try {

      //Set the address of in1
      *(add1ptr + (XVADD_VADD_CONTROL_ADDR_IN1_DATA/4) ) = infoInfo1.paddr;
      //*(add1ptr + (XVADD_VADD_CONTROL_ADDR_IN1_DATA/4) + 1) = infoInfo1.paddr >> 32;

      //Set the address of in2
      *(add1ptr + (XVADD_VADD_CONTROL_ADDR_IN2_DATA/4) ) = infoInfo2.paddr;
      //*(add1ptr + (XVADD_VADD_CONTROL_ADDR_IN2_DATA/4) + 1) = infoInfo2.paddr >> 32;

      //Set the address of out_r
      *(add1ptr + (XVADD_VADD_CONTROL_ADDR_OUT_R_DATA/4) ) = infoInfo3.paddr;
      //*(add1ptr + (XVADD_VADD_CONTROL_ADDR_OUT_R_DATA/4) + 1) = infoInfo3.paddr >> 32;

      //Set #of elements
      *(add1ptr + (XVADD_VADD_CONTROL_ADDR_SIZE_DATA/4) ) = 4096;

      std::cout << "=================Reading back values===========================================" << std::endl;

      unsigned i = XVADD_VADD_CONTROL_ADDR_IN1_DATA/4;
      printf("Addr: %p, Offset: %d, Data 0x%x\n", add1ptr + i, i, (uint32_t)(*(add1ptr + i)));
      i = XVADD_VADD_CONTROL_ADDR_IN2_DATA/4;
      printf("Addr: %p, Offset: %d, Data 0x%x\n", add1ptr + i, i, (uint32_t)(*(add1ptr + i)));
      i = XVADD_VADD_CONTROL_ADDR_OUT_R_DATA/4;
      printf("Addr: %p, Offset: %d, Data 0x%x\n", add1ptr + i, i, (uint32_t)(*(add1ptr + i)));
      i = XVADD_VADD_CONTROL_ADDR_SIZE_DATA/4;
      printf("Addr: %p, Offset: %d, Data 0x%x\n", add1ptr + i, i, (uint32_t)(*(add1ptr + i)));

      uint32_t isDone, isIdle, isReady;
      isDone = is_done(add1ptr);
      isIdle = is_idle(add1ptr);
      isReady = is_ready(add1ptr);
      printf("---current kernel status done:%d, idle:%d, Ready:%d ---\n\r", isDone, isIdle, isReady);

      printf (">>>>Now starting kernel...\n\r");

      start_kernel(add1ptr );


      while (1){
        isDone = is_done(add1ptr);
        isIdle = is_idle(add1ptr);
        isReady = is_ready(add1ptr);
        printf("---current kernel status done:%d, idle:%d, Ready:%d ---\n\r", isDone, isIdle, isReady);
        if (isDone && isIdle) {

          printf("Exiting while 1 loop ---\n\r");
          break;
        }
        usleep(100);

      }
      /*
      printf("====Quit test built-in kernel---\n\r");
      printf("====Printing 100 elements of in1---\n\r");
      p1 = (uint32_t*) ptr1;
      for (int i = 0; i < 100; ++i) {
        printf("Mem addr: 0x%x, Data: 0x%x\n\r", p1 + i, p1[i]);
      }
      printf("====Printing 100 elements of in2---\n\r");
      p2 = (uint32_t*) ptr2;
      for (int i = 0; i < 100; ++i) {
        printf("Mem addr: 0x%x, Data: 0x%x\n\r", p2 + i, p2[i]);
      }
      printf("====Printing 100 elements of out_r---\n\r");
      uint32_t *p3 = (uint32_t*) ptr3;
      for (int i = 0; i < 100; ++i) {
        printf("Mem addr: 0x%x, Data: 0x%x\n\r", p3 + i, p3[i]);
      }
      */
      uint32_t *p3 = (uint32_t*) ptr3;
      bool match = true;
      for (int i=0; i<4096; i++) {
	if (p1[i]+p2[i] != p3[i]) {
	  match = false;
	  break;
	}
      }

      std::cout << "TEST " << (match ? "PASSED" : "FAILED") << std::endl;

      print_kernel_status(add1ptr);

      std::cout << "============================================================" << std::endl;
    }
    catch (...) {

      std::cout << "CLOSE" << std::endl;
      drm_gem_close closeInfo = {info1.handle, 0};
      result = ioctl(fd, DRM_IOCTL_GEM_CLOSE, &closeInfo);
      std::cout << "result = " << result << std::endl;

      closeInfo.handle = info2.handle;
      result = ioctl(fd, DRM_IOCTL_GEM_CLOSE, &closeInfo);
      std::cout << "result = " << result << std::endl;

      closeInfo.handle = info3.handle;
      result = ioctl(fd, DRM_IOCTL_GEM_CLOSE, &closeInfo);
      std::cout << "result = " << result << std::endl;

      result = close(fd);
      std::cout << "result = " << result << std::endl;
      return result;
    }


    std::cout << "CLOSE" << std::endl;
    drm_gem_close closeInfo = {info1.handle, 0};
    result = ioctl(fd, DRM_IOCTL_GEM_CLOSE, &closeInfo);
    std::cout << "result = " << result << std::endl;

    closeInfo.handle = info2.handle;
    result = ioctl(fd, DRM_IOCTL_GEM_CLOSE, &closeInfo);
    std::cout << "result = " << result << std::endl;

    closeInfo.handle = info3.handle;
    result = ioctl(fd, DRM_IOCTL_GEM_CLOSE, &closeInfo);
    std::cout << "result = " << result << std::endl;

    result = close(fd);
    std::cout << "result = " << result << std::endl;

    return result;
}
