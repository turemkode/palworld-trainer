#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <windows.h>
#include <string>
#include <vector>

struct ModuleInfo {
    std::wstring name;
    uintptr_t baseAddress;
    size_t size;
};

class MemoryManager {
private:
    DWORD pId;
    HANDLE hProc;
    std::vector<ModuleInfo> modules;

public:
    MemoryManager();
    ~MemoryManager();
    bool OpenProcessHandle(const std::wstring& processName);
    void CloseHandleProc();
    uintptr_t GetModuleBase(const std::wstring& moduleName);
    
    template <typename T>
    T Read(uintptr_t addr) {
        T val{};
        ReadProcessMemory(hProc, (LPCVOID)addr, &val, sizeof(T), NULL);
        return val;
    }

    template <typename T>
    void Write(uintptr_t addr, T val) {
        WriteProcessMemory(hProc, (LPVOID)addr, &val, sizeof(T), NULL);
    }
};

#endif