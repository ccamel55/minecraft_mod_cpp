#include <iostream>
#include <cassert>

#include <Windows.h>

BOOL APIENTRY DllMain(HMODULE module_handle, DWORD call_reason, LPVOID reserved)
{
    switch (call_reason)
    {
    case DLL_PROCESS_ATTACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    default:
        break;
    }

    return TRUE;
}