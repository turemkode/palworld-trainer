#include "MemoryManager.h"
#include <tlhelp32.h>

MemoryManager::MemoryManager() : pId(0), hProc(NULL) {}

MemoryManager::~MemoryManager() {
    CloseHandleProc();
}

bool MemoryManager::OpenProcessHandle(const std::wstring& processName) {
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    
    if (Process32First(snap, &pe32)) {
        do {
            if (processName == pe32.szExeFile) {
                pId = pe32.th32ProcessID;
                hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
                CloseHandle(snap);
                return true;
            }
        } while (Process32Next(snap, &pe32));
    }
    CloseHandle(snap);
    return false;
}

void MemoryManager::CloseHandleProc() {
    if (hProc) CloseHandle(hProc);
}

uintptr_t MemoryManager::GetModuleBase(const std::wstring& moduleName) {
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pId);
    MODULEENTRY32 me32;
    me32.dwSize = sizeof(MODULEENTRY32);
    
    if (Module32First(snap, &me32)) {
        do {
            if (moduleName == me32.szModule) {
                CloseHandle(snap);
                return (uintptr_t)me32.modBaseAddr;
            }
        } while (Module32Next(snap, &me32));
    }
    CloseHandle(snap);
    return 0;
}