#pragma once
#include <string>
#include "npc.h"

class Desman : public Npc {
    public:
        Desman(int x, int y, const std::string& name);

        void accept(Visitor& visitor) override;

        void printInfo() const override;

        int getMoveDistance() const override { return 5; }
        int getKillDistance() const override { return 20; }

    private:
        static const std::string kType;
};