#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <zocl/zynq_ioctl.h>
#include "xvadd.h"

int main()
{
	XVadd vadd;
	int ret;

	int fd = open("/dev/dri/renderD128", O_RDWR);
	if (fd < 0) {
		perror("zocl fd failed");
		return fd;
	}

	drm_zocl_create_bo info1 = {4096*4, 0xffffffff, DRM_ZOCL_BO_FLAGS_COHERENT | DRM_ZOCL_BO_FLAGS_CMA};
	ret = ioctl(fd, DRM_IOCTL_ZOCL_CREATE_BO, &info1);
	printf("ret = %d\n", ret);
	printf("handle = %d\n", info1.handle);

	drm_zocl_create_bo info2 = {4096*4, 0xffffffff, DRM_ZOCL_BO_FLAGS_COHERENT | DRM_ZOCL_BO_FLAGS_CMA};
	ret = ioctl(fd, DRM_IOCTL_ZOCL_CREATE_BO, &info2);
	printf("ret = %d\n", ret);
	printf("handle = %d\n", info2.handle);

	drm_zocl_create_bo info3 = {4096*4, 0xffffffff, DRM_ZOCL_BO_FLAGS_COHERENT | DRM_ZOCL_BO_FLAGS_CMA};
	ret = ioctl(fd, DRM_IOCTL_ZOCL_CREATE_BO, &info3);
	printf("ret = %d\n", ret);
	printf("handle = %d\n", info3.handle);

	drm_zocl_info_bo infoInfo1 = {info1.handle, 0, 0};
	ret = ioctl(fd, DRM_IOCTL_ZOCL_INFO_BO, &infoInfo1);
	printf("ret = %d\n", ret);
	printf("handle = %d\n", info1.handle);
	printf("size = %d\n", infoInfo1.handle);
	printf("physical = 0x%x\n", infoInfo1.paddr);

	drm_zocl_info_bo infoInfo2 = {info2.handle, 0, 0};
	ret = ioctl(fd, DRM_IOCTL_ZOCL_INFO_BO, &infoInfo2);
	printf("ret = %d\n", ret);
	printf("handle = %d\n", info2.handle);
	printf("size = %d\n", infoInfo2.handle);
	printf("physical = 0x%x\n", infoInfo2.paddr);

	drm_zocl_info_bo infoInfo3 = {info3.handle, 0, 0};
	ret = ioctl(fd, DRM_IOCTL_ZOCL_INFO_BO, &infoInfo3);
	printf("ret = %d\n", ret);
	printf("handle = %d\n", info3.handle);
	printf("size = %d\n", infoInfo3.handle);
	printf("physical = 0x%x\n", infoInfo3.paddr);

	drm_zocl_map_bo mapInfo1 = {info1.handle, 0, 0};
	ret = ioctl(fd, DRM_IOCTL_ZOCL_MAP_BO, &mapInfo1);
	printf("ret = %d\n", ret);
	printf("handle = %d\n", info1.handle);
	void *ptr1 = mmap(0, info1.size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, mapInfo1.offset);
	printf("offset = 0x%x\n", mapInfo1.offset);
	printf("pointer = 0x%x\n", ptr1);

	drm_zocl_map_bo mapInfo2 = {info2.handle, 0, 0};
	ret = ioctl(fd, DRM_IOCTL_ZOCL_MAP_BO, &mapInfo2);
	printf("ret = %d\n", ret);
	printf("handle = %d\n", info2.handle);
	void *ptr2 = mmap(0, info2.size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, mapInfo2.offset);
	printf("offset = 0x%x\n", mapInfo2.offset);
	printf("pointer = 0x%x\n", ptr2);

	drm_zocl_map_bo mapInfo3 = {info3.handle, 0, 0};
	ret = ioctl(fd, DRM_IOCTL_ZOCL_MAP_BO, &mapInfo3);
	printf("ret = %d\n", ret);
	printf("handle = %d\n", info3.handle);
	void *ptr3 = mmap(0, info3.size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, mapInfo3.offset);
	printf("offset = 0x%x\n", mapInfo3.offset);
	printf("pointer = 0x%x\n", ptr3);

	uint32_t *p1 = (uint32_t *)ptr1;
	uint32_t *p2 = (uint32_t *)ptr2;
	uint32_t *p3 = (uint32_t*) ptr3;
	for (int i=0; i<4096; i++) {
		p1[i] = i;
		p2[i] = 4096 - i;
		p3[i] = 0;
	}

	ret = XVadd_Initialize(&vadd, "vadd");
	if (ret != XST_SUCCESS) {
		perror("vadd Initialize failed");
		return ret;
	}

	XVadd_Set_in1(&vadd, infoInfo1.paddr);
	XVadd_Set_in2(&vadd, infoInfo2.paddr);
	XVadd_Set_out_r(&vadd, infoInfo3.paddr);
	XVadd_Set_size(&vadd, 4096);

	XVadd_Start(&vadd);
	while(!XVadd_IsDone(&vadd));

	bool match = true;
	for (int i=0; i<4096; i++) {
		if (p1[i]+p2[i] != p3[i]) {
			match = false;
			break;
		}
	}

	if (match) printf("TEST PASSED\n");
	else printf("TEST FAILED\n");

	XVadd_Release(&vadd);

	drm_gem_close closeInfo = {info1.handle, 0};
	ioctl(fd, DRM_IOCTL_GEM_CLOSE, &closeInfo);
	closeInfo = {info2.handle, 0};
	ioctl(fd, DRM_IOCTL_GEM_CLOSE, &closeInfo);
	closeInfo = {info3.handle, 0};
	ioctl(fd, DRM_IOCTL_GEM_CLOSE, &closeInfo);

	close(fd);
	return 0;
}
