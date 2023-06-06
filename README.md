# HelloWorldDriver
Just a base I use for setting up and deploying a driver

https://www.unknowncheats.me/forum/anti-cheat-bypass/374439-kernel_security_check_failure-kdmapper.html

    #include <ntddk.h>
    DRIVER_INITIALIZE DriverEntry;
    #pragma alloc_text (INIT, DriverEntry)
     
     
    NTSTATUS DriverEntry(
        _In_ PDRIVER_OBJECT DriverObject,
        _In_ PUNICODE_STRING RegistryPath
    ) {
	UNREFERENCED_PARAMETER(DriverObject);
	UNREFERENCED_PARAMETER(RegistryPath);
     
        DbgPrint("Driver loaded!");
     
        return STATUS_SUCCESS;
    }

the original code what wrong so UNREFERANCED_PERAMITER has to be added
original post was about troubleshooting KDMapper, here is one solution
"
Project properties -> c++ -> code generation

Disable security checks
"
and
"
Quote:
Originally Posted by mjokeym View Post
I'm not getting this error when compiling it?
Could it be your warning level
Still crashing :<

is your custom entry point set in linker?
"
and the fix by the OP
"

Quote:
Originally Posted by PeriodWay View Post
is your custom entry point set in linker?
I doubt it since I don't know how to do that?

Do you mean like this? (https://docs.microsoft.com/en-us/cpp...l?view=vs-2019)

Quote:
Originally Posted by PeriodWay View Post
is your custom entry point set in linker?

Damn, that was the issue https://i.ibb.co/pW13Pwg/image.png for anyone wondering.

Thanks again!
"
After disabeling security checks and setting a costom entry point, compile your driver and drag the .sys over a compiled KDMapper (both in x64 and Release)
Loads without BSOD

Use DbgView to see output

--------

After you do this the output probobly does not show, this is because of windows moment, this thread fixes it.
https://www.unknowncheats.me/forum/c-and-c-/229419-dbgprint-failing-print-debugger.html

"
Setting DEFAULT to 8 is correct.
Another thing you have to do to get messages appear in my experience, is appending a new line to your string after call DbgPrint/DbgPrintEx.

First, disable all of these in DbgView:
Capture Win32
Capture Global Win32
Enable Verbose Kernel Output
Pass-through
Log Boot

The only thing that should be enabled is:
Capture Kernel
Capture Events


Then in your DriverEntry, call DbgPrintEx like so:
Code:

    DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "YourDriverName: Message Here\n");

Then when you load your driver, you should receive the message correctly.
Here's a screenshot of my DbgView.
"
when he says "setting default to 8 is corrct. He is refering to this.
http://www.osronline.com/article.cfm?article=295
 Open (or add, if it's not already there) the key "HKLM\SYSTEM\CCS\Control\Session Manager\Debug Print Filter".  
Under this key, create a  value with the name "DEFAULT"  
Set the value of this key equal to the DWORD value 8 to enable xxx_INFO_LEVEL output as well as xxx_ERROR_LEVEL output. 
Or try setting the mask to 0xF so you get all output.  You must reboot for these changes to take effect.
Note... Don't set the value named "(default)" -- You actually have to create a new value with the name "DEFAULT" and set that to whatever value you want (0xF, for example).
