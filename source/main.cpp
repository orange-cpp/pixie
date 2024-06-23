//
// Created by Vlad on 6/23/2024.
//
#include <print>
#include <thread>
#include <Windows.h>
#include <titanfall_2/Context.h>
#include <titanfall_2/UserCmd.h>

#ifdef USE_CV
#   include<CodeVirtualizer/VirtualizerSDK.h>
#endif

void CreateMove(titanfall_2::UserCmd* cmd)
{
    if (GetAsyncKeyState(VK_F1) & 0x8000)
        cmd->command_number = 0x7FFFFFFF;

    if (GetAsyncKeyState(VK_SHIFT) & 0x8000 && !(cmd->buttons & 1))
        *(float*)((uintptr_t)cmd + 0xAC) += 0.10f;
}

namespace pixie
{
    void Main(const HMODULE moduleHandle)
    {
        auto& ctx = titanfall_2::Context::Get();
        ctx.SetOnCreateMove(CreateMove);

        while (!GetAsyncKeyState(VK_END))
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        FreeLibrary(moduleHandle);
    }
}

extern "C" BOOL WINAPI DllMain(const HMODULE dllHandle, const DWORD callReason, LPVOID)
{
    VIRTUALIZER_START;

    if (callReason != DLL_PROCESS_ATTACH)
        return true;

    DisableThreadLibraryCalls(dllHandle);
    std::thread(pixie::Main, dllHandle).detach();

    VIRTUALIZER_END;
    return true;
}