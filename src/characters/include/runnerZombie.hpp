#ifndef __RUNNER_ZOMBIE_HPP__
#define __RUNNER_ZOMBIE_HPP__

#include "zombie.hpp"
#include "player.hpp"

class RunnerZombie: public Zombie{
    private:
        int state = 0; // 0: idle, 1: run, 2: atk, 3: death, 4: hurt
        float counter = 0;
        float randomIdle = 0;
        Player* player = nullptr;

    public:
        RunnerZombie(float frame_rate, float initPosX=0, float initPosY=0, Player* player = nullptr);

        void update() override;
        void moveRight();
        void moveLeft();
        void atk();
        void death() override;
};

#endif