// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XVADD_H
#define XVADD_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xvadd_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
#else
typedef struct {
    u16 DeviceId;
    u32 Control_BaseAddress;
} XVadd_Config;
#endif

typedef struct {
    u32 Control_BaseAddress;
    u32 IsReady;
} XVadd;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XVadd_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XVadd_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XVadd_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XVadd_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XVadd_Initialize(XVadd *InstancePtr, u16 DeviceId);
XVadd_Config* XVadd_LookupConfig(u16 DeviceId);
int XVadd_CfgInitialize(XVadd *InstancePtr, XVadd_Config *ConfigPtr);
#else
int XVadd_Initialize(XVadd *InstancePtr, const char* InstanceName);
int XVadd_Release(XVadd *InstancePtr);
#endif

void XVadd_Start(XVadd *InstancePtr);
u32 XVadd_IsDone(XVadd *InstancePtr);
u32 XVadd_IsIdle(XVadd *InstancePtr);
u32 XVadd_IsReady(XVadd *InstancePtr);
void XVadd_EnableAutoRestart(XVadd *InstancePtr);
void XVadd_DisableAutoRestart(XVadd *InstancePtr);

void XVadd_Set_in1(XVadd *InstancePtr, u64 Data);
u64 XVadd_Get_in1(XVadd *InstancePtr);
void XVadd_Set_in2(XVadd *InstancePtr, u64 Data);
u64 XVadd_Get_in2(XVadd *InstancePtr);
void XVadd_Set_out_r(XVadd *InstancePtr, u64 Data);
u64 XVadd_Get_out_r(XVadd *InstancePtr);
void XVadd_Set_size(XVadd *InstancePtr, u32 Data);
u32 XVadd_Get_size(XVadd *InstancePtr);

void XVadd_InterruptGlobalEnable(XVadd *InstancePtr);
void XVadd_InterruptGlobalDisable(XVadd *InstancePtr);
void XVadd_InterruptEnable(XVadd *InstancePtr, u32 Mask);
void XVadd_InterruptDisable(XVadd *InstancePtr, u32 Mask);
void XVadd_InterruptClear(XVadd *InstancePtr, u32 Mask);
u32 XVadd_InterruptGetEnabled(XVadd *InstancePtr);
u32 XVadd_InterruptGetStatus(XVadd *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
