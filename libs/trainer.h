#ifndef TRAINER_H
#define TRAINER_H

#include "MemoryManager.h"
#include <map>

struct Cheat {
    bool enabled;
    uintptr_t address;
    std::vector<unsigned char> patch;
    std::vector<unsigned char> original;
};

class Trainer {
private:
    MemoryManager mem;
    uintptr_t base;
    std::map<int, Cheat> cheats;

public:
    Trainer();
    bool Initialize();
    void Toggle(int key);
    void Update();
    void ApplyCheat(int key, bool state);
    void SetValue(uintptr_t offset, int val);
};

#endif