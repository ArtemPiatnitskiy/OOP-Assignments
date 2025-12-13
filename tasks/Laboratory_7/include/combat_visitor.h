#pragma once
#include "visitor.h"
#include "npc.h"

class CombatVisitor : public Visitor {
    public:
        bool canKill(Npc* attacker, Npc* defender);

        void visit(Bear&) override {}
        void visit(Desman&) override {}
        void visit(Bittern&) override {}
    private:
        bool bearVs(const std::string& defenderType);
        bool desmanVs(const std::string& defenderType);
        bool bitternVs(const std::string&);
};