/*
 * File:   CpuId.hpp
 * Author: Ringo Leese
 *
 * Created on 27. April 2013, 23:16
 */

#ifndef CPUID_HPP
#define	CPUID_HPP

#include <iostream>

struct CpuRegisters {
	uint32_t eax;
	uint32_t ebx;
	uint32_t ecx;
	uint32_t edx;
};

extern "C" CpuRegisters cpuid(uint32_t in);

class CpuId {
	public:
		enum FeatureBit {
			// ecx Register
			PrescottNewInstructions,
			PCLMULQDQ,
			DebugStore64Bit,
			MONITORAndMWAITInstructions,
			CPLQualifiedDebugStore,
			VirtualMachineExtensions,
			SaferModeExtensions,
			EnhancedSpeedStep,
			ThermalMonitor2,
			SupplementalSSE3Instructions,
			ContextID,
			FusedMultiplyAdd,
			CMPXCHG16BInstruction,
			CanDisableSendingTaskPriorityMessages,
			PerfmonAndDebugCapability,
			ProcessContextIdentifiers,
			DirectCacheAccessForDMAWrites,
			SSE4_1Instructions,
			SSE4_2Instructions,
			x2APICSupport,
			MOVBEInstruction,
			POPCNTInstruction,
			TSCDeadlineSupport,
			AESInstructionSet,
			XSAVE_XRESTOR_XSETBV_XGETBV_Support,
			XSAVEEnabledByOS,
			AdvancedVectorExtensions,
			CVT16InstructionSet,
			RDRANDSupport,
			RunningOnAHypervisor,

			// edx Register
			Onboardx87FPU,
			VirtualModeExtensions,
			DebuggingExtensions,
			PageSizeExtension,
			TimeStampCounter,
			ModelSpecificRegisters,
			PhysicalAddressExtension,
			MachineCheckException,
			CMPXCHG8Instruction,
			OnboardAPIC,
			SYSENTERAndSYSEXITInstructions,
			MemoryTypeRangeRegisters,
			PageGlobalEnableBitInCR4,
			MachineCheckArchitecture,
			ConditionalMoveAndFCMOVInstructions,
			PageAttributeTable,
			PageSizeExtension36Bit,
			ProcessorSerialNumber,
			CLFLUSHInstruction,
			DebugStore,
			OnboardThermalControlMSRsForACPI,
			MMXInstructions,
			FXSAVE_FXRESTOR_Instructions,
			SSEInstructions,
			SSE2Instructions,
			CPUCacheSupportsSelfSnoop,
			HyperThreading,
			ThermalMonitorAuomaticallyLimitsTemperature,
			IA64ProcessorEmulatingx86,
			PendingBreakEnableWakeupSupport,

			// extended features

			// ecx Register
			LAHF_SAHF_InLongMode,
			HyperThreadingNotValid,
			SecureVirtualMachine,
			ExtendedAPICSpace,
			CR8In32BitMode,
			AdvancedBitManipulation,
			SSE4a,
			MisalignedSSEMode,
			PREFETCHAndPREFETCHWInstructions,
			OSVisibleWorkaround,
			InstructionBasedSampling,
			XOPInstructionSet,
			SKINIT_STGI_Instructions,
			WatchdogTimer,
			LightweightProfiling,
			FourOperandsFusedMultiplyAdd,
			TranslationCacheExtension,
			NodeID_MSR,
			TrailingBitManipulation,
			TopologyExtensions,
			CorePerformanceCounterExtensions,
			NBPerformanceCounterExtensions,

			// edx Register
			SYSCALLAndSYSRETInstructions,
			MultiprocessorCapable,
			NXBit,
			ExtendedMMX,
			FXSAVE_FXRSTOR_Instructions,
			FXSAVE_FXRSTOR_Optimizations,
			GibibytePages,
			RDTSCPInstruction,
			LongMode,
			Extended3DNow,
			AMD3DNow
		};

		struct ProcessorInfo {
			uint8_t Stepping;
			uint8_t Model;
			uint8_t Family;
			uint8_t ProcessorType;
			uint8_t ExtendedModel;
			uint8_t ExtendedFamily;
		};
		struct FeatureBits {
			// ecx Register
			bool PrescottNewInstructions;
			bool PCLMULQDQ;
			bool DebugStore64Bit;
			bool MONITORAndMWAITInstructions;
			bool CPLQualifiedDebugStore;
			bool VirtualMachineExtensions;
			bool SaferModeExtensions;
			bool EnhancedSpeedStep;
			bool ThermalMonitor2;
			bool SupplementalSSE3Instructions;
			bool ContextID;
			bool FusedMultiplyAdd;
			bool CMPXCHG16BInstruction;
			bool CanDisableSendingTaskPriorityMessages;
			bool PerfmonAndDebugCapability;
			bool ProcessContextIdentifiers;
			bool DirectCacheAccessForDMAWrites;
			bool SSE4_1Instructions;
			bool SSE4_2Instructions;
			bool x2APICSupport;
			bool MOVBEInstruction;
			bool POPCNTInstruction;
			bool TSCDeadlineSupport;
			bool AESInstructionSet;
			bool XSAVE_XRESTOR_XSETBV_XGETBV_Support;
			bool XSAVEEnabledByOS;
			bool AdvancedVectorExtensions;
			bool CVT16InstructionSet;
			bool RDRANDSupport;
			bool RunningOnAHypervisor;

			// edx Register
			bool Onboardx87FPU;
			bool VirtualModeExtensions;
			bool DebuggingExtensions;
			bool PageSizeExtension;
			bool TimeStampCounter;
			bool ModelSpecificRegisters;
			bool PhysicalAddressExtension;
			bool MachineCheckException;
			bool CMPXCHG8Instruction;
			bool OnboardAPIC;
			bool SYSENTERAndSYSEXITInstructions;
			bool MemoryTypeRangeRegisters;
			bool PageGlobalEnableBitInCR4;
			bool MachineCheckArchitecture;
			bool ConditionalMoveAndFCMOVInstructions;
			bool PageAttributeTable;
			bool PageSizeExtension36Bit;
			bool ProcessorSerialNumber;
			bool CLFLUSHInstruction;
			bool DebugStore;
			bool OnboardThermalControlMSRsForACPI;
			bool MMXInstructions;
			bool FXSAVE_FXRESTOR_Instructions;
			bool SSEInstructions;
			bool SSE2Instructions;
			bool CPUCacheSupportsSelfSnoop;
			bool HyperThreading;
			bool ThermalMonitorAuomaticallyLimitsTemperature;
			bool IA64ProcessorEmulatingx86;
			bool PendingBreakEnableWakeupSupport;

			// extended features

			// ecx Register
			bool LAHF_SAHF_InLongMode;
			bool HyperThreadingNotValid;
			bool SecureVirtualMachine;
			bool ExtendedAPICSpace;
			bool CR8In32BitMode;
			bool AdvancedBitManipulation;
			bool SSE4a;
			bool MisalignedSSEMode;
			bool PREFETCHAndPREFETCHWInstructions;
			bool OSVisibleWorkaround;
			bool InstructionBasedSampling;
			bool XOPInstructionSet;
			bool SKINIT_STGI_Instructions;
			bool WatchdogTimer;
			bool LightweightProfiling;
			bool FourOperandsFusedMultiplyAdd;
			bool TranslationCacheExtension;
			bool NodeID_MSR;
			bool TrailingBitManipulation;
			bool TopologyExtensions;
			bool CorePerformanceCounterExtensions;
			bool NBPerformanceCounterExtensions;

			// edx Register
			bool SYSCALLAndSYSRETInstructions;
			bool MultiprocessorCapable;
			bool NXBit;
			bool ExtendedMMX;
			bool FXSAVE_FXRSTOR_Instructions;
			bool FXSAVE_FXRSTOR_Optimizations;
			bool GibibytePages;
			bool RDTSCPInstruction;
			bool LongMode;
			bool Extended3DNow;
			bool AMD3DNow;
		};

		CpuId();

		std::string getVendorId();
		std::string getProcessorBrandString();
		ProcessorInfo getProcessorInfo();
		FeatureBits getFeatureBits();
		bool getFeatureBit(FeatureBit featureBit);
	private:
		std::string vendorId = "";
		std::string processorBrandString = "";
		ProcessorInfo processorInfo;
		FeatureBits featureBits;

		void detectVendorId();
		void detectProcessorInfoAndFeatureBits();
		void detectExtendedProcessorInfoAndFeatureBits();
		void detectProcessorBrandString();
};

#endif	/* CPUID_HPP */
