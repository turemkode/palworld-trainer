#include <iostream>
#include <thread>
#include "Trainer.h"

int main() {
    Trainer trainer;
    std::cout << "Loading Palworld Engine Hooks..." << std::endl;
    
    if (!trainer.Initialize()) {
        std::cout << "Failed to find process. Launch game first." << std::endl;
        return 1;
    }
    
    std::cout << "Trainer Ready." << std::endl;
    std::cout << "..." << std::endl;

    while (!(GetAsyncKeyState(VK_END) & 0x8000)) {
        trainer.Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    return 0;
}