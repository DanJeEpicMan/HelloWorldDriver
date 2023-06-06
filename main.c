#include <ntddk.h>
DRIVER_INITIALIZE DriverEntry;
#pragma alloc_text (INIT, DriverEntry)


NTSTATUS DriverEntry(
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PUNICODE_STRING RegistryPath
) {
    UNREFERENCED_PARAMETER(DriverObject);
    UNREFERENCED_PARAMETER(RegistryPath);

    DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "YourDriverName: Message Here\n");

    return STATUS_SUCCESS;
}