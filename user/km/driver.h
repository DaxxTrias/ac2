#ifndef DRIVER_H
#define DRIVER_H

#include <Windows.h>

#include "../threadpool.h"
#include "../client.h"

#define IOCCTL_RUN_NMI_CALLBACKS CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2001, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_VALIDATE_DRIVER_OBJECTS CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2002, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_MONITOR_CALLBACKS_FOR_REPORTS CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2003, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_NOTIFY_DRIVER_ON_PROCESS_LAUNCH CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2004, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_HANDLE_REPORTS_IN_CALLBACK_QUEUE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2005, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_PERFORM_VIRTUALIZATION_CHECK CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2006, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_ENUMERATE_HANDLE_TABLES CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2007, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_RETRIEVE_MODULE_EXECUTABLE_REGIONS CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2008, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_REQUEST_TOTAL_MODULE_SIZE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2009, METHOD_BUFFERED, FILE_ANY_ACCESS)


#define MAX_HANDLE_REPORTS_PER_IRP 10

namespace kernelmode
{
	class Driver
	{
		HANDLE driver_handle;
		LPCWSTR driver_name;
		std::shared_ptr<global::Client> report_interface;

		VOID QueryReportQueue();
		ULONG RequestTotalModuleSize();

	public:

		Driver(LPCWSTR DriverName, std::shared_ptr<global::Client> ReportInterface );

		VOID RunNmiCallbacks();
		VOID VerifySystemModules();
		VOID RunCallbackReportQueue();
		VOID NotifyDriverOnProcessLaunch();
		VOID DetectSystemVirtualization();
		VOID ValidateKPRCBThreads();
		VOID CheckDriverHeartbeat();
		VOID CheckHandleTableEntries();
		VOID RequestModuleExecutableRegions();
		/* todo: driver integrity check */
	};

	struct DRIVER_INITIATION_INFORMATION
	{
		LONG protected_process_id;
	};

	struct HYPERVISOR_DETECTION_REPORT
	{
		INT aperf_msr_timing_check;
		INT invd_emulation_check;
	};
}

#endif
