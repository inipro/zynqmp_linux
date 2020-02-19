// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xvadd.h"

extern XVadd_Config XVadd_ConfigTable[];

XVadd_Config *XVadd_LookupConfig(u16 DeviceId) {
	XVadd_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XVADD_NUM_INSTANCES; Index++) {
		if (XVadd_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XVadd_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XVadd_Initialize(XVadd *InstancePtr, u16 DeviceId) {
	XVadd_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XVadd_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XVadd_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

