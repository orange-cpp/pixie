//
// Created by Vlad on 6/23/2024.
//
#include <print>
#include <Windows.h>


extern "C" BOOL WINAPI DllMain(HINSTANCE dllHandle, DWORD callReason, LPVOID)
{
    if (callReason != DLL_PROCESS_ATTACH)
        return TRUE;

    DisableThreadLibraryCalls(dllHandle);
    return true;
}