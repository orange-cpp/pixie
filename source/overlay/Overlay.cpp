//
// Created by Vlad on 6/24/2024.
//

#include "Overlay.h"
#include <d3d11.h>
#include <tuple>
#include <imgui/imgui.h>
#include <imgui/imgui_freetype.h>
#include <imgui/imgui_impl_dx11.h>
#include <imgui/imgui_impl_win32.h>
namespace pixie::gui
{
    Overlay::Overlay(IDXGISwapChain *swapChain)
    {
        ID3D11Device* pDevice = nullptr;

        std::ignore = swapChain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(&pDevice));

        ID3D11Texture2D* pBackBuffer;
        std::ignore = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));

        D3D11_RENDER_TARGET_VIEW_DESC rtv_desc = {};
        rtv_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        rtv_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;

        std::ignore = pDevice->CreateRenderTargetView(pBackBuffer, &rtv_desc, &m_pMainView);

        pBackBuffer->Release();

        DXGI_SWAP_CHAIN_DESC sd;
        swapChain->GetDesc(&sd);

        ImGui::CreateContext();
        ImGuiIO& io     = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        pDevice->GetImmediateContext(&m_pDeviceContext);

        ImGui_ImplWin32_Init(sd.OutputWindow);
        ImGui_ImplDX11_Init(pDevice, m_pDeviceContext);


        ImFontConfig cfg;
        cfg.FontBuilderFlags |= ImGuiFreeTypeBuilderFlags_Monochrome | ImGuiFreeTypeBuilderFlags_MonoHinting;
        io.Fonts->AddFontFromFileTTF(R"(C:\Windows\Fonts\verdanab.ttf)", 13.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    }

    void Overlay::Render()
    {
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        ImGui::GetForegroundDrawList()->AddText(ImVec2(), ImColor(255, 0, 0),
                                                "Press 'INSERT' key to open / close the menu."
                                                " Use mouse to navigate in menu.");
        ImGui::Begin("Example window");
        {
            ImGui::End();
        }

        ImGui::EndFrame();
        ImGui::Render();
        m_pDeviceContext->OMSetRenderTargets(1, &m_pMainView, nullptr);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    }
}
