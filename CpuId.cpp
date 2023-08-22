/*
 * File:   CpuId.cpp
 * Author: Ringo Leese
 *
 * Created on 27. April 2013, 23:16
 */

#include <cstdint>
#include <iostream>

#include "CpuId.hpp"

using namespace std;

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

string CpuId::getVendorId() const {
	return this->vendorId;
}

void CpuId::detectProcessorInfoAndFeatureBits() {
	CpuRegisters regs = cpuid(1);

	uint8_t stepping = (regs.eax) & 0x0F;
	uint8_t model = (regs.eax >> 4) & 0x0F;
	uint8_t family = (regs.eax >> 8) & 0x0F;
	uint8_t processor_type = (regs.eax >> 12) & 0x03;
	uint8_t extended_model = (regs.eax >> 16) & 0x0F;
	uint8_t extended_family = (regs.eax >> 20) & 0xFF;
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

string CpuId::getProcessorBrandString() const {
	return this->processorBrandString;
}

CpuId::ProcessorInfo CpuId::getProcessorInfo() const {
	return this->processorInfo;
}

CpuId::FeatureBits CpuId::getFeatureBits() const {
	return this->featureBits;
}

bool CpuId::getFeatureBit(FeatureBit featureBit) const {
	switch(featureBit) {
		case FeatureBit::AESInstructionSet:
			return this->featureBits.AESInstructionSet;
		case FeatureBit::AdvancedVectorExtensions:
			return this->featureBits.AdvancedVectorExtensions;
		case FeatureBit::CLFLUSHInstruction:
			return this->featureBits.CLFLUSHInstruction;
		case FeatureBit::CMPXCHG16BInstruction:
			return this->featureBits.CMPXCHG16BInstruction;
		case FeatureBit::CMPXCHG8Instruction:
			return this->featureBits.CMPXCHG8Instruction;
		case FeatureBit::CPLQualifiedDebugStore:
			return this->featureBits.CPLQualifiedDebugStore;
		case FeatureBit::CPUCacheSupportsSelfSnoop:
			return this->featureBits.CPUCacheSupportsSelfSnoop;
		case FeatureBit::CVT16InstructionSet:
			return this->featureBits.CVT16InstructionSet;
		case FeatureBit::CanDisableSendingTaskPriorityMessages:
			return this->featureBits.CanDisableSendingTaskPriorityMessages;
		case FeatureBit::ConditionalMoveAndFCMOVInstructions:
			return this->featureBits.ConditionalMoveAndFCMOVInstructions;
		case FeatureBit::ContextID:
			return this->featureBits.ContextID;
		case FeatureBit::DebugStore:
			return this->featureBits.DebugStore;
		case FeatureBit::DebugStore64Bit:
			return this->featureBits.DebugStore64Bit;
		case FeatureBit::DebuggingExtensions:
			return this->featureBits.DebuggingExtensions;
		case FeatureBit::DirectCacheAccessForDMAWrites:
			return this->featureBits.DirectCacheAccessForDMAWrites;
		case FeatureBit::EnhancedSpeedStep:
			return this->featureBits.EnhancedSpeedStep;
		case FeatureBit::FXSAVE_FXRESTOR_Instructions:
			return this->featureBits.FXSAVE_FXRESTOR_Instructions;
		case FeatureBit::FusedMultiplyAdd:
			return this->featureBits.FusedMultiplyAdd;
		case FeatureBit::HyperThreading:
			return this->featureBits.HyperThreading;
		case FeatureBit::IA64ProcessorEmulatingx86:
			return this->featureBits.IA64ProcessorEmulatingx86;
		case FeatureBit::MMXInstructions:
			return this->featureBits.MMXInstructions;
		case FeatureBit::MONITORAndMWAITInstructions:
			return this->featureBits.MONITORAndMWAITInstructions;
		case FeatureBit::MOVBEInstruction:
			return this->featureBits.MOVBEInstruction;
		case FeatureBit::MachineCheckArchitecture:
			return this->featureBits.MachineCheckArchitecture;
		case FeatureBit::MachineCheckException:
			return this->featureBits.MachineCheckException;
		case FeatureBit::MemoryTypeRangeRegisters:
			return this->featureBits.MemoryTypeRangeRegisters;
		case FeatureBit::ModelSpecificRegisters:
			return this->featureBits.ModelSpecificRegisters;
		case FeatureBit::OnboardAPIC:
			return this->featureBits.OnboardAPIC;
		case FeatureBit::OnboardThermalControlMSRsForACPI:
			return this->featureBits.OnboardThermalControlMSRsForACPI;
		case FeatureBit::Onboardx87FPU:
			return this->featureBits.Onboardx87FPU;
		case FeatureBit::PCLMULQDQ:
			return this->featureBits.PCLMULQDQ;
		case FeatureBit::POPCNTInstruction:
			return this->featureBits.POPCNTInstruction;
		case FeatureBit::PageAttributeTable:
			return this->featureBits.PageAttributeTable;
		case FeatureBit::PageGlobalEnableBitInCR4:
			return this->featureBits.PageGlobalEnableBitInCR4;
		case FeatureBit::PageSizeExtension:
			return this->featureBits.PageSizeExtension;
		case FeatureBit::PageSizeExtension36Bit:
			return this->featureBits.PageSizeExtension36Bit;
		case FeatureBit::PendingBreakEnableWakeupSupport:
			return this->featureBits.PendingBreakEnableWakeupSupport;
		case FeatureBit::PerfmonAndDebugCapability:
			return this->featureBits.PerfmonAndDebugCapability;
		case FeatureBit::PhysicalAddressExtension:
			return this->featureBits.PhysicalAddressExtension;
		case FeatureBit::PrescottNewInstructions:
			return this->featureBits.PrescottNewInstructions;
		case FeatureBit::ProcessContextIdentifiers:
			return this->featureBits.ProcessContextIdentifiers;
		case FeatureBit::ProcessorSerialNumber:
			return this->featureBits.ProcessorSerialNumber;
		case FeatureBit::RDRANDSupport:
			return this->featureBits.RDRANDSupport;
		case FeatureBit::RunningOnAHypervisor:
			return this->featureBits.RunningOnAHypervisor;
		case FeatureBit::SSE2Instructions:
			return this->featureBits.SSE2Instructions;
		case FeatureBit::SSE4_1Instructions:
			return this->featureBits.SSE4_1Instructions;
		case FeatureBit::SSE4_2Instructions:
			return this->featureBits.SSE4_2Instructions;
		case FeatureBit::SSEInstructions:
			return this->featureBits.SSEInstructions;
		case FeatureBit::SYSENTERAndSYSEXITInstructions:
			return this->featureBits.SYSENTERAndSYSEXITInstructions;
		case FeatureBit::SaferModeExtensions:
			return this->featureBits.SaferModeExtensions;
		case FeatureBit::SupplementalSSE3Instructions:
			return this->featureBits.SupplementalSSE3Instructions;
		case FeatureBit::TSCDeadlineSupport:
			return this->featureBits.TSCDeadlineSupport;
		case FeatureBit::ThermalMonitor2:
			return this->featureBits.ThermalMonitor2;
		case FeatureBit::ThermalMonitorAuomaticallyLimitsTemperature:
			return this->featureBits.ThermalMonitorAuomaticallyLimitsTemperature;
		case FeatureBit::TimeStampCounter:
			return this->featureBits.TimeStampCounter;
		case FeatureBit::VirtualMachineExtensions:
			return this->featureBits.VirtualMachineExtensions;
		case FeatureBit::VirtualModeExtensions:
			return this->featureBits.VirtualModeExtensions;
		case FeatureBit::XSAVEEnabledByOS:
			return this->featureBits.XSAVEEnabledByOS;
		case FeatureBit::XSAVE_XRESTOR_XSETBV_XGETBV_Support:
			return this->featureBits.XSAVE_XRESTOR_XSETBV_XGETBV_Support;
		case FeatureBit::x2APICSupport:
			return this->featureBits.x2APICSupport;

		// extended features
		// ecx
		case FeatureBit::LAHF_SAHF_InLongMode:
			return this->featureBits.LAHF_SAHF_InLongMode;
		case FeatureBit::HyperThreadingNotValid:
			return this->featureBits.HyperThreadingNotValid;
		case FeatureBit::SecureVirtualMachine:
			return this->featureBits.SecureVirtualMachine;
		case FeatureBit::ExtendedAPICSpace:
			return this->featureBits.ExtendedAPICSpace;
		case FeatureBit::CR8In32BitMode:
			return this->featureBits.CR8In32BitMode;
		case FeatureBit::AdvancedBitManipulation:
			return this->featureBits.AdvancedBitManipulation;
		case FeatureBit::SSE4a:
			return this->featureBits.SSE4a;
		case FeatureBit::MisalignedSSEMode:
			return this->featureBits.MisalignedSSEMode;
		case FeatureBit::PREFETCHAndPREFETCHWInstructions:
			return this->featureBits.PREFETCHAndPREFETCHWInstructions;
		case FeatureBit::OSVisibleWorkaround:
			return this->featureBits.OSVisibleWorkaround;
		case FeatureBit::InstructionBasedSampling:
			return this->featureBits.InstructionBasedSampling;
		case FeatureBit::XOPInstructionSet:
			return this->featureBits.XOPInstructionSet;
		case FeatureBit::SKINIT_STGI_Instructions:
			return this->featureBits.SKINIT_STGI_Instructions;
		case FeatureBit::WatchdogTimer:
			return this->featureBits.WatchdogTimer;
		case FeatureBit::LightweightProfiling:
			return this->featureBits.LightweightProfiling;
		case FeatureBit::FourOperandsFusedMultiplyAdd:
			return this->featureBits.FourOperandsFusedMultiplyAdd;
		case FeatureBit::TranslationCacheExtension:
			return this->featureBits.TranslationCacheExtension;
		case FeatureBit::NodeID_MSR:
			return this->featureBits.NodeID_MSR;
		case FeatureBit::TrailingBitManipulation:
			return this->featureBits.TrailingBitManipulation;
		case FeatureBit::TopologyExtensions:
			return this->featureBits.TopologyExtensions;
		case FeatureBit::CorePerformanceCounterExtensions:
			return this->featureBits.CorePerformanceCounterExtensions;
		case FeatureBit::NBPerformanceCounterExtensions:
			return this->featureBits.NBPerformanceCounterExtensions;
		// edx
		case FeatureBit::SYSCALLAndSYSRETInstructions:
			return this->featureBits.SYSCALLAndSYSRETInstructions;
		case FeatureBit::MultiprocessorCapable:
			return this->featureBits.MultiprocessorCapable;
		case FeatureBit::NXBit:
			return this->featureBits.NXBit;
		case FeatureBit::ExtendedMMX:
			return this->featureBits.ExtendedMMX;
		case FeatureBit::FXSAVE_FXRSTOR_Instructions:
			return this->featureBits.FXSAVE_FXRSTOR_Instructions;
		case FeatureBit::FXSAVE_FXRSTOR_Optimizations:
			return this->featureBits.FXSAVE_FXRSTOR_Optimizations;
		case FeatureBit::GibibytePages:
			return this->featureBits.GibibytePages;
		case FeatureBit::RDTSCPInstruction:
			return this->featureBits.RDTSCPInstruction;
		case FeatureBit::LongMode:
			return this->featureBits.LongMode;
		case FeatureBit::Extended3DNow:
			return this->featureBits.Extended3DNow;
		case FeatureBit::AMD3DNow:
			return this->featureBits.AMD3DNow;
	}

	return false;
}
