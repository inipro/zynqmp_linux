// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xvadd.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XVadd_CfgInitialize(XVadd *InstancePtr, XVadd_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XVadd_Start(XVadd *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVadd_ReadReg(InstancePtr->Control_BaseAddress, XVADD_CONTROL_ADDR_AP_CTRL) & 0x80;
    XVadd_WriteReg(InstancePtr->Control_BaseAddress, XVADD_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XVadd_IsDone(XVadd *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVadd_ReadReg(InstancePtr->Control_BaseAddress, XVADD_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XVadd_IsIdle(XVadd *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVadd_ReadReg(InstancePtr->Control_BaseAddress, XVADD_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XVadd_IsReady(XVadd *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVadd_ReadReg(InstancePtr->Control_BaseAddress, XVADD_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XVadd_EnableAutoRestart(XVadd *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVadd_WriteReg(InstancePtr->Control_BaseAddress, XVADD_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XVadd_DisableAutoRestart(XVadd *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVadd_WriteReg(InstancePtr->Control_BaseAddress, XVADD_CONTROL_ADDR_AP_CTRL, 0);
}

void XVadd_Set_in1(XVadd *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVadd_WriteReg(InstancePtr->Control_BaseAddress, XVADD_CONTROL_ADDR_IN1_DATA, (u32)(Data));
    XVadd_WriteReg(InstancePtr->Control_BaseAddress, XVADD_CONTROL_ADDR_IN1_DATA + 4, (u32)(Data >> 32));
}

u64 XVadd_Get_in1(XVadd *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVadd_ReadReg(InstancePtr->Control_BaseAddress, XVADD_CONTROL_ADDR_IN1_DATA);
    Data += (u64)XVadd_ReadReg(InstancePtr->Control_BaseAddress, XVADD_CONTROL_ADDR_IN1_DATA + 4) << 32;
    return Data;
}

void XVadd_Set_in2(XVadd *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVadd_WriteReg(InstancePtr->Control_BaseAddress, XVADD_CONTROL_ADDR_IN2_DATA, (u32)(Data));
    XVadd_WriteReg(InstancePtr->Control_BaseAddress, XVADD_CONTROL_ADDR_IN2_DATA + 4, (u32)(Data >> 32));
}

u64 XVadd_Get_in2(XVadd *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVadd_ReadReg(InstancePtr->Control_BaseAddress, XVADD_CONTROL_ADDR_IN2_DATA);
    Data += (u64)XVadd_ReadReg(InstancePtr->Control_BaseAddress, XVADD_CONTROL_ADDR_IN2_DATA + 4) << 32;
    return Data;
}

void XVadd_Set_out_r(XVadd *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVadd_WriteReg(InstancePtr->Control_BaseAddress, XVADD_CONTROL_ADDR_OUT_R_DATA, (u32)(Data));
    XVadd_WriteReg(InstancePtr->Control_BaseAddress, XVADD_CONTROL_ADDR_OUT_R_DATA + 4, (u32)(Data >> 32));
}

u64 XVadd_Get_out_r(XVadd *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVadd_ReadReg(InstancePtr->Control_BaseAddress, XVADD_CONTROL_ADDR_OUT_R_DATA);
    Data += (u64)XVadd_ReadReg(InstancePtr->Control_BaseAddress, XVADD_CONTROL_ADDR_OUT_R_DATA + 4) << 32;
    return Data;
}

void XVadd_Set_size(XVadd *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVadd_WriteReg(InstancePtr->Control_BaseAddress, XVADD_CONTROL_ADDR_SIZE_DATA, Data);
}

u32 XVadd_Get_size(XVadd *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVadd_ReadReg(InstancePtr->Control_BaseAddress, XVADD_CONTROL_ADDR_SIZE_DATA);
    return Data;
}

void XVadd_InterruptGlobalEnable(XVadd *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVadd_WriteReg(InstancePtr->Control_BaseAddress, XVADD_CONTROL_ADDR_GIE, 1);
}

void XVadd_InterruptGlobalDisable(XVadd *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVadd_WriteReg(InstancePtr->Control_BaseAddress, XVADD_CONTROL_ADDR_GIE, 0);
}

void XVadd_InterruptEnable(XVadd *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XVadd_ReadReg(InstancePtr->Control_BaseAddress, XVADD_CONTROL_ADDR_IER);
    XVadd_WriteReg(InstancePtr->Control_BaseAddress, XVADD_CONTROL_ADDR_IER, Register | Mask);
}

void XVadd_InterruptDisable(XVadd *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XVadd_ReadReg(InstancePtr->Control_BaseAddress, XVADD_CONTROL_ADDR_IER);
    XVadd_WriteReg(InstancePtr->Control_BaseAddress, XVADD_CONTROL_ADDR_IER, Register & (~Mask));
}

void XVadd_InterruptClear(XVadd *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVadd_WriteReg(InstancePtr->Control_BaseAddress, XVADD_CONTROL_ADDR_ISR, Mask);
}

u32 XVadd_InterruptGetEnabled(XVadd *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XVadd_ReadReg(InstancePtr->Control_BaseAddress, XVADD_CONTROL_ADDR_IER);
}

u32 XVadd_InterruptGetStatus(XVadd *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XVadd_ReadReg(InstancePtr->Control_BaseAddress, XVADD_CONTROL_ADDR_ISR);
}

