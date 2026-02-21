#include <iostream>

class Battler {
    public:
        Battler() {
            std::cout << "Battler created!" << std::endl;
        }

        void attack() {
            std::cout << "Battler attacks!" << std::endl;
        }
};