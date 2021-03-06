/*
 * File:   CpuId.cpp
 * Author: Ringo Leese
 *
 * Created on 27. April 2013, 23:16
 */

#include <cstdint>
#include <iostream>

#include "CpuId.hpp"

/**
 * @param in input for cpu register eax
 * @return output of the 4 cpu registers eax, ebx, ecx and edx
 */
extern "C" CpuRegisters cpuid(uint32_t in) {
	struct CpuRegisters regs = {0, 0, 0, 0};

	__asm("mov %4, %%eax;"
		"cpuid;"
		"mov %%eax, %0;"
		"mov %%ebx, %1;"
		"mov %%ecx, %2;"
		"mov %%edx, %3;"
		:"=a"(regs.eax), "=b"(regs.ebx), "=c"(regs.ecx), "=d"(regs.edx)
		:"r"(in)
	);

	return regs;
}

CpuId::CpuId() {
	this->detectVendorId();
	this->detectProcessorInfoAndFeatureBits();
	this->detectExtendedProcessorInfoAndFeatureBits();
	this->detectProcessorBrandString();
}

CpuId::CpuId(const CpuId& orig) {

}

CpuId::~CpuId() {

}

void CpuId::detectVendorId() {
	CpuRegisters regs = cpuid(0);
	char vendorID[13];

	vendorID[0] = (regs.ebx) & 0xFF;
	vendorID[1] = (regs.ebx >> 8) & 0xFF;
	vendorID[2] = (regs.ebx >> 16) & 0xFF;
	vendorID[3] = (regs.ebx >> 24);
	vendorID[4] = (regs.edx) & 0xFF;
	vendorID[5] = (regs.edx >> 8) & 0xFF;
	vendorID[6] = (regs.edx >> 16) & 0xFF;
	vendorID[7] = (regs.edx >> 24) & 0xFF;
	vendorID[8] = (regs.ecx) & 0xFF;
	vendorID[9] = (regs.ecx >> 8) & 0xFF;
	vendorID[10] = (regs.ecx >> 16) & 0xFF;
	vendorID[11] = (regs.ecx >> 24) & 0xFF;
	vendorID[12] = '\0';

	this->vendorId = vendorID;
}

string CpuId::getVendorId() {
	return this->vendorId;
}

void CpuId::detectProcessorInfoAndFeatureBits() {
	CpuRegisters regs = cpuid(1);

	uint8_t stepping, model, family, processor_type, extended_model, extended_family;

	stepping = (regs.eax) & 0x0F;
	model = (regs.eax >> 4) & 0x0F;
	family = (regs.eax >> 8) & 0x0F;
	processor_type = (regs.eax >> 12) & 0x03;
	extended_model = (regs.eax >> 16) & 0x0F;
	extended_family = (regs.eax >> 20) & 0xFF;
	this->processorInfo = {
		stepping,
		model,
		family,
		processor_type,
		extended_model,
		extended_family
	};

	this->featureBits = {
		((regs.ecx & 0x01) > 0),
		((regs.ecx & 0x02) > 0),
		((regs.ecx & 0x04) > 0),
		((regs.ecx & 0x08) > 0),
		((regs.ecx & 0x10) > 0),
		((regs.ecx & 0x20) > 0),
		((regs.ecx & 0x40) > 0),
		((regs.ecx & 0x80) > 0),
		((regs.ecx & 0x100) > 0),
		((regs.ecx & 0x200) > 0),
		((regs.ecx & 0x400) > 0),

		((regs.ecx & 0x1000) > 0),
		((regs.ecx & 0x2000) > 0),
		((regs.ecx & 0x4000) > 0),
		((regs.ecx & 0x8000) > 0),

		((regs.ecx & 0x20000) > 0),
		((regs.ecx & 0x40000) > 0),
		((regs.ecx & 0x80000) > 0),
		((regs.ecx & 0x100000) > 0),
		((regs.ecx & 0x200000) > 0),
		((regs.ecx & 0x400000) > 0),
		((regs.ecx & 0x800000) > 0),
		((regs.ecx & 0x1000000) > 0),
		((regs.ecx & 0x2000000) > 0),
		((regs.ecx & 0x4000000) > 0),
		((regs.ecx & 0x8000000) > 0),
		((regs.ecx & 0x10000000) > 0),
		((regs.ecx & 0x20000000) > 0),
		((regs.ecx & 0x40000000) > 0),
		((regs.ecx & 0x80000000) > 0),

		((regs.edx & 0x01) > 0),
		((regs.edx & 0x02) > 0),
		((regs.edx & 0x04) > 0),
		((regs.edx & 0x08) > 0),
		((regs.edx & 0x10) > 0),
		((regs.edx & 0x20) > 0),
		((regs.edx & 0x40) > 0),
		((regs.edx & 0x80) > 0),
		((regs.edx & 0x100) > 0),
		((regs.edx & 0x200) > 0),

		((regs.edx & 0x800) > 0),
		((regs.edx & 0x1000) > 0),
		((regs.edx & 0x2000) > 0),
		((regs.edx & 0x4000) > 0),
		((regs.edx & 0x8000) > 0),
		((regs.edx & 0x10000) > 0),
		((regs.edx & 0x20000) > 0),
		((regs.edx & 0x40000) > 0),
		((regs.edx & 0x80000) > 0),

		((regs.edx & 0x200000) > 0),
		((regs.edx & 0x400000) > 0),
		((regs.edx & 0x800000) > 0),
		((regs.edx & 0x1000000) > 0),
		((regs.edx & 0x2000000) > 0),
		((regs.edx & 0x4000000) > 0),
		((regs.edx & 0x8000000) > 0),
		((regs.edx & 0x10000000) > 0),
		((regs.edx & 0x20000000) > 0),
		((regs.edx & 0x40000000) > 0),
		((regs.edx & 0x80000000) > 0)
	};
}

void CpuId::detectExtendedProcessorInfoAndFeatureBits() {
	CpuRegisters regs = cpuid(0x80000001);

	this->featureBits.LAHF_SAHF_InLongMode = ((regs.ecx & 0x01) > 0);
	this->featureBits.HyperThreadingNotValid = ((regs.ecx & 0x02) > 0);
	this->featureBits.SecureVirtualMachine = ((regs.ecx & 0x04) > 0);
	this->featureBits.ExtendedAPICSpace = ((regs.ecx & 0x08) > 0);
	this->featureBits.CR8In32BitMode = ((regs.ecx & 0x10) > 0);
	this->featureBits.AdvancedBitManipulation = ((regs.ecx & 0x20) > 0);
	this->featureBits.SSE4a = ((regs.ecx & 0x40) > 0);
	this->featureBits.MisalignedSSEMode = ((regs.ecx & 0x80) > 0);
	this->featureBits.PREFETCHAndPREFETCHWInstructions = ((regs.ecx & 0x100) > 0);
	this->featureBits.OSVisibleWorkaround = ((regs.ecx & 0x200) > 0);
	this->featureBits.InstructionBasedSampling = ((regs.ecx & 0x400) > 0);
	this->featureBits.XOPInstructionSet = ((regs.ecx & 0x800) > 0);
	this->featureBits.SKINIT_STGI_Instructions = ((regs.ecx & 0x1000) > 0);
	this->featureBits.WatchdogTimer = ((regs.ecx & 0x2000) > 0);

	this->featureBits.LightweightProfiling = ((regs.ecx & 0x8000) > 0);
	this->featureBits.FourOperandsFusedMultiplyAdd = ((regs.ecx & 0x10000) > 0);
	this->featureBits.TranslationCacheExtension = ((regs.ecx & 0x20000) > 0);

	this->featureBits.NodeID_MSR = ((regs.ecx & 0x80000) > 0);

	this->featureBits.TrailingBitManipulation = ((regs.ecx & 0x200000) > 0);
	this->featureBits.TopologyExtensions = ((regs.ecx & 0x400000) > 0);
	this->featureBits.CorePerformanceCounterExtensions = ((regs.ecx & 0x800000) > 0);
	this->featureBits.NBPerformanceCounterExtensions = ((regs.ecx & 0x1000000) > 0);

	this->featureBits.SYSCALLAndSYSRETInstructions = ((regs.edx & 0x800) > 0);

	this->featureBits.MultiprocessorCapable = ((regs.edx & 0x80000) > 0);
	this->featureBits.NXBit = ((regs.edx & 0x100000) > 0);

	this->featureBits.ExtendedMMX = ((regs.edx & 0x400000) > 0);

	this->featureBits.FXSAVE_FXRSTOR_Instructions = ((regs.edx & 0x1000000) > 0);
	this->featureBits.FXSAVE_FXRSTOR_Optimizations = ((regs.edx & 0x2000000) > 0);
	this->featureBits.GibibytePages = ((regs.edx & 0x4000000) > 0);
	this->featureBits.RDTSCPInstruction = ((regs.edx & 0x8000000) > 0);

	this->featureBits.LongMode = ((regs.edx & 0x20000000) > 0);
	this->featureBits.Extended3DNow = ((regs.edx & 0x40000000) > 0);
	this->featureBits.AMD3DNow = ((regs.edx & 0x80000000) > 0);
}

void CpuId::detectProcessorBrandString() {
	char processorBrandString[49];
	CpuRegisters regs = cpuid(0x80000000);

	if (regs.eax < 0x80000004) { // feature is not supported
		return;
	}

	for(int i = 0; i < 3; i++) {
		int charIndexOffset = i * 16;

		regs = cpuid(0x80000002 + i);

		processorBrandString[charIndexOffset + 0] = (regs.eax) & 0xFF;
		processorBrandString[charIndexOffset + 1] = (regs.eax >> 8) & 0xFF;
		processorBrandString[charIndexOffset + 2] = (regs.eax >> 16) & 0xFF;
		processorBrandString[charIndexOffset + 3] = (regs.eax >> 24);
		processorBrandString[charIndexOffset + 4] = (regs.ebx) & 0xFF;
		processorBrandString[charIndexOffset + 5] = (regs.ebx >> 8) & 0xFF;
		processorBrandString[charIndexOffset + 6] = (regs.ebx >> 16) & 0xFF;
		processorBrandString[charIndexOffset + 7] = (regs.ebx >> 24);
		processorBrandString[charIndexOffset + 8] = (regs.ecx) & 0xFF;
		processorBrandString[charIndexOffset + 9] = (regs.ecx >> 8) & 0xFF;
		processorBrandString[charIndexOffset + 10] = (regs.ecx >> 16) & 0xFF;
		processorBrandString[charIndexOffset + 11] = (regs.ecx >> 24) & 0xFF;
		processorBrandString[charIndexOffset + 12] = (regs.edx) & 0xFF;
		processorBrandString[charIndexOffset + 13] = (regs.edx >> 8) & 0xFF;
		processorBrandString[charIndexOffset + 14] = (regs.edx >> 16) & 0xFF;
		processorBrandString[charIndexOffset + 15] = (regs.edx >> 24) & 0xFF;
	}
	processorBrandString[48] = '\0';

	this->processorBrandString = processorBrandString;
}

string CpuId::getProcessorBrandString() {
	return this->processorBrandString;
}

CpuId::ProcessorInfo CpuId::getProcessorInfo() {
	return this->processorInfo;
}

CpuId::FeatureBits CpuId::getFeatureBits() {
	return this->featureBits;
}

bool CpuId::getFeatureBit(FeatureBit featureBit) {
	switch(featureBit) {
		case FeatureBit::AESInstructionSet:
			return this->featureBits.AESInstructionSet;
			break;
		case FeatureBit::AdvancedVectorExtensions:
			return this->featureBits.AdvancedVectorExtensions;
			break;
		case FeatureBit::CLFLUSHInstruction:
			return this->featureBits.CLFLUSHInstruction;
			break;
		case FeatureBit::CMPXCHG16BInstruction:
			return this->featureBits.CMPXCHG16BInstruction;
			break;
		case FeatureBit::CMPXCHG8Instruction:
			return this->featureBits.CMPXCHG8Instruction;
			break;
		case FeatureBit::CPLQualifiedDebugStore:
			return this->featureBits.CPLQualifiedDebugStore;
			break;
		case FeatureBit::CPUCacheSupportsSelfSnoop:
			return this->featureBits.CPUCacheSupportsSelfSnoop;
			break;
		case FeatureBit::CVT16InstructionSet:
			return this->featureBits.CVT16InstructionSet;
			break;
		case FeatureBit::CanDisableSendingTaskPriorityMessages:
			return this->featureBits.CanDisableSendingTaskPriorityMessages;
			break;
		case FeatureBit::ConditionalMoveAndFCMOVInstructions:
			return this->featureBits.ConditionalMoveAndFCMOVInstructions;
			break;
		case FeatureBit::ContextID:
			return this->featureBits.ContextID;
			break;
		case FeatureBit::DebugStore:
			return this->featureBits.DebugStore;
			break;
		case FeatureBit::DebugStore64Bit:
			return this->featureBits.DebugStore64Bit;
			break;
		case FeatureBit::DebuggingExtensions:
			return this->featureBits.DebuggingExtensions;
			break;
		case FeatureBit::DirectCacheAccessForDMAWrites:
			return this->featureBits.DirectCacheAccessForDMAWrites;
			break;
		case FeatureBit::EnhancedSpeedStep:
			return this->featureBits.EnhancedSpeedStep;
			break;
		case FeatureBit::FXSAVE_FXRESTOR_Instructions:
			return this->featureBits.FXSAVE_FXRESTOR_Instructions;
			break;
		case FeatureBit::FusedMultiplyAdd:
			return this->featureBits.FusedMultiplyAdd;
			break;
		case FeatureBit::HyperThreading:
			return this->featureBits.HyperThreading;
			break;
		case FeatureBit::IA64ProcessorEmulatingx86:
			return this->featureBits.IA64ProcessorEmulatingx86;
			break;
		case FeatureBit::MMXInstructions:
			return this->featureBits.MMXInstructions;
			break;
		case FeatureBit::MONITORAndMWAITInstructions:
			return this->featureBits.MONITORAndMWAITInstructions;
			break;
		case FeatureBit::MOVBEInstruction:
			return this->featureBits.MOVBEInstruction;
			break;
		case FeatureBit::MachineCheckArchitecture:
			return this->featureBits.MachineCheckArchitecture;
			break;
		case FeatureBit::MachineCheckException:
			return this->featureBits.MachineCheckException;
			break;
		case FeatureBit::MemoryTypeRangeRegisters:
			return this->featureBits.MemoryTypeRangeRegisters;
			break;
		case FeatureBit::ModelSpecificRegisters:
			return this->featureBits.ModelSpecificRegisters;
			break;
		case FeatureBit::OnboardAPIC:
			return this->featureBits.OnboardAPIC;
			break;
		case FeatureBit::OnboardThermalControlMSRsForACPI:
			return this->featureBits.OnboardThermalControlMSRsForACPI;
			break;
		case FeatureBit::Onboardx87FPU:
			return this->featureBits.Onboardx87FPU;
			break;
		case FeatureBit::PCLMULQDQ:
			return this->featureBits.PCLMULQDQ;
			break;
		case FeatureBit::POPCNTInstruction:
			return this->featureBits.POPCNTInstruction;
			break;
		case FeatureBit::PageAttributeTable:
			return this->featureBits.PageAttributeTable;
			break;
		case FeatureBit::PageGlobalEnableBitInCR4:
			return this->featureBits.PageGlobalEnableBitInCR4;
			break;
		case FeatureBit::PageSizeExtension:
			return this->featureBits.PageSizeExtension;
			break;
		case FeatureBit::PageSizeExtension36Bit:
			return this->featureBits.PageSizeExtension36Bit;
			break;
		case FeatureBit::PendingBreakEnableWakeupSupport:
			return this->featureBits.PendingBreakEnableWakeupSupport;
			break;
		case FeatureBit::PerfmonAndDebugCapability:
			return this->featureBits.PerfmonAndDebugCapability;
			break;
		case FeatureBit::PhysicalAddressExtension:
			return this->featureBits.PhysicalAddressExtension;
			break;
		case FeatureBit::PrescottNewInstructions:
			return this->featureBits.PrescottNewInstructions;
			break;
		case FeatureBit::ProcessContextIdentifiers:
			return this->featureBits.ProcessContextIdentifiers;
			break;
		case FeatureBit::ProcessorSerialNumber:
			return this->featureBits.ProcessorSerialNumber;
			break;
		case FeatureBit::RDRANDSupport:
			return this->featureBits.RDRANDSupport;
			break;
		case FeatureBit::RunningOnAHypervisor:
			return this->featureBits.RunningOnAHypervisor;
			break;
		case FeatureBit::SSE2Instructions:
			return this->featureBits.SSE2Instructions;
			break;
		case FeatureBit::SSE4_1Instructions:
			return this->featureBits.SSE4_1Instructions;
			break;
		case FeatureBit::SSE4_2Instructions:
			return this->featureBits.SSE4_2Instructions;
			break;
		case FeatureBit::SSEInstructions:
			return this->featureBits.SSEInstructions;
			break;
		case FeatureBit::SYSENTERAndSYSEXITInstructions:
			return this->featureBits.SYSENTERAndSYSEXITInstructions;
			break;
		case FeatureBit::SaferModeExtensions:
			return this->featureBits.SaferModeExtensions;
			break;
		case FeatureBit::SupplementalSSE3Instructions:
			return this->featureBits.SupplementalSSE3Instructions;
			break;
		case FeatureBit::TSCDeadlineSupport:
			return this->featureBits.TSCDeadlineSupport;
			break;
		case FeatureBit::ThermalMonitor2:
			return this->featureBits.ThermalMonitor2;
			break;
		case FeatureBit::ThermalMonitorAuomaticallyLimitsTemperature:
			return this->featureBits.ThermalMonitorAuomaticallyLimitsTemperature;
			break;
		case FeatureBit::TimeStampCounter:
			return this->featureBits.TimeStampCounter;
			break;
		case FeatureBit::VirtualMachineExtensions:
			return this->featureBits.VirtualMachineExtensions;
			break;
		case FeatureBit::VirtualModeExtensions:
			return this->featureBits.VirtualModeExtensions;
			break;
		case FeatureBit::XSAVEEnabledByOS:
			return this->featureBits.XSAVEEnabledByOS;
			break;
		case FeatureBit::XSAVE_XRESTOR_XSETBV_XGETBV_Support:
			return this->featureBits.XSAVE_XRESTOR_XSETBV_XGETBV_Support;
			break;
		case FeatureBit::x2APICSupport:
			return this->featureBits.x2APICSupport;
			break;

		// extended features
		// ecx
		case FeatureBit::LAHF_SAHF_InLongMode:
			return this->featureBits.LAHF_SAHF_InLongMode;
			break;
		case FeatureBit::HyperThreadingNotValid:
			return this->featureBits.HyperThreadingNotValid;
			break;
		case FeatureBit::SecureVirtualMachine:
			return this->featureBits.SecureVirtualMachine;
			break;
		case FeatureBit::ExtendedAPICSpace:
			return this->featureBits.ExtendedAPICSpace;
			break;
		case FeatureBit::CR8In32BitMode:
			return this->featureBits.CR8In32BitMode;
			break;
		case FeatureBit::AdvancedBitManipulation:
			return this->featureBits.AdvancedBitManipulation;
			break;
		case FeatureBit::SSE4a:
			return this->featureBits.SSE4a;
			break;
		case FeatureBit::MisalignedSSEMode:
			return this->featureBits.MisalignedSSEMode;
			break;
		case FeatureBit::PREFETCHAndPREFETCHWInstructions:
			return this->featureBits.PREFETCHAndPREFETCHWInstructions;
			break;
		case FeatureBit::OSVisibleWorkaround:
			return this->featureBits.OSVisibleWorkaround;
			break;
		case FeatureBit::InstructionBasedSampling:
			return this->featureBits.InstructionBasedSampling;
			break;
		case FeatureBit::XOPInstructionSet:
			return this->featureBits.XOPInstructionSet;
			break;
		case FeatureBit::SKINIT_STGI_Instructions:
			return this->featureBits.SKINIT_STGI_Instructions;
			break;
		case FeatureBit::WatchdogTimer:
			return this->featureBits.WatchdogTimer;
			break;
		case FeatureBit::LightweightProfiling:
			return this->featureBits.LightweightProfiling;
			break;
		case FeatureBit::FourOperandsFusedMultiplyAdd:
			return this->featureBits.FourOperandsFusedMultiplyAdd;
			break;
		case FeatureBit::TranslationCacheExtension:
			return this->featureBits.TranslationCacheExtension;
			break;
		case FeatureBit::NodeID_MSR:
			return this->featureBits.NodeID_MSR;
			break;
		case FeatureBit::TrailingBitManipulation:
			return this->featureBits.TrailingBitManipulation;
			break;
		case FeatureBit::TopologyExtensions:
			return this->featureBits.TopologyExtensions;
			break;
		case FeatureBit::CorePerformanceCounterExtensions:
			return this->featureBits.CorePerformanceCounterExtensions;
			break;
		case FeatureBit::NBPerformanceCounterExtensions:
			return this->featureBits.NBPerformanceCounterExtensions;
			break;
		// edx
		case FeatureBit::SYSCALLAndSYSRETInstructions:
			return this->featureBits.SYSCALLAndSYSRETInstructions;
			break;
		case FeatureBit::MultiprocessorCapable:
			return this->featureBits.MultiprocessorCapable;
			break;
		case FeatureBit::NXBit:
			return this->featureBits.NXBit;
			break;
		case FeatureBit::ExtendedMMX:
			return this->featureBits.ExtendedMMX;
			break;
		case FeatureBit::FXSAVE_FXRSTOR_Instructions:
			return this->featureBits.FXSAVE_FXRSTOR_Instructions;
			break;
		case FeatureBit::FXSAVE_FXRSTOR_Optimizations:
			return this->featureBits.FXSAVE_FXRSTOR_Optimizations;
			break;
		case FeatureBit::GibibytePages:
			return this->featureBits.GibibytePages;
			break;
		case FeatureBit::RDTSCPInstruction:
			return this->featureBits.RDTSCPInstruction;
			break;
		case FeatureBit::LongMode:
			return this->featureBits.LongMode;
			break;
		case FeatureBit::Extended3DNow:
			return this->featureBits.Extended3DNow;
			break;
		case FeatureBit::AMD3DNow:
			return this->featureBits.AMD3DNow;
			break;
	}

	return false;
}
