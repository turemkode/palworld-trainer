#include "Trainer.h"
#include <windows.h>

Trainer::Trainer() : base(0) {}

bool Trainer::Initialize() {
    if (mem.OpenProcessHandle(L"Palworld-Win64-Shipping.exe")) {
        base = mem.GetModuleBase(L"Palworld-Win64-Shipping.exe");
        cheats[VK_NUMPAD1] = {false, base + 0x1405A1B2C, {0x90, 0x90, 0x90}, {0x89, 0x43, 0x10}};
        cheats[VK_NUMPAD2] = {false, base + 0x1406B2C3D, {0x90, 0x90}, {0x88, 0x10}};
        cheats[VK_NUMPAD3] = {false, base + 0x1407C3D4E, {0x90, 0x90, 0x90, 0x90}, {0x48, 0x89, 0x4B, 0x20}};
        return true;
    }
    return false;
}

void Trainer::Toggle(int key) {
    if (cheats.find(key) != cheats.end()) {
        cheats[key].enabled = !cheats[key].enabled;
        ApplyCheat(key, cheats[key].enabled);
    }
}

void Trainer::ApplyCheat(int key, bool state) {
    Cheat& c = cheats[key];
    DWORD old;
    VirtualProtectEx(GetCurrentProcess(), (LPVOID)c.address, c.patch.size(), PAGE_EXECUTE_READWRITE, &old);
    if (state) {
        for(size_t i = 0; i < c.patch.size(); i++) mem.Write<unsigned char>(c.address + i, c.patch[i]);
    } else {
        for(size_t i = 0; i < c.original.size(); i++) mem.Write<unsigned char>(c.address + i, c.original[i]);
    }
    VirtualProtectEx(GetCurrentProcess(), (LPVOID)c.address, c.patch.size(), old, &old);
}

void Trainer::SetValue(uintptr_t offset, int val) {
    mem.Write<int>(base + offset, val);
}

void Trainer::Update() {
    if (GetAsyncKeyState(VK_NUMPAD1) & 1) Toggle(VK_NUMPAD1);
    if (GetAsyncKeyState(VK_NUMPAD2) & 1) Toggle(VK_NUMPAD2);
    if (GetAsyncKeyState(VK_NUMPAD3) & 1) Toggle(VK_NUMPAD3);
    if (GetAsyncKeyState(VK_F1) & 1) SetValue(0x2A1B2C, 999999);
}