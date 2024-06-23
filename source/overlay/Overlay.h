//
// Created by Vlad on 6/24/2024.
//

#pragma once

struct IDXGISwapChain;
struct ID3D11DeviceContext;
struct ID3D11RenderTargetView;


namespace pixie::gui
{
    class Overlay
    {
    public:
        explicit Overlay(IDXGISwapChain* swapChain);
        ~Overlay() = default;
        void Render();
    private:
        ID3D11DeviceContext* m_pDeviceContext = nullptr;
        ID3D11RenderTargetView* m_pMainView = nullptr;
    };
}