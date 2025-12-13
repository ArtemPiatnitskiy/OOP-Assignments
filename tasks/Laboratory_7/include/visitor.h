#pragma once

class Bear;
class Desman;
class Bittern;

class Visitor {
    public:
        virtual ~Visitor() = default;

        // Постелитель к кажому типу NPC
        virtual void visit(Bear& bear) = 0;
        virtual void visit(Desman& desman) = 0;
        virtual void visit(Bittern& bittern) = 0;
};
