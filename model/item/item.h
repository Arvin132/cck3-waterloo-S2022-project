#ifndef __ITEM_H__
#define __ITEM_H__
#include "subject.h"
#include <string>
class Floor;
class Creature;

class Item: public Subject {
    protected:
        Floor *fl;
        char rep;
        Item();
        std::string description;
    public:
        virtual ~Item();
        void notifyObservesrs() override;
        char getRep();
        std::string getDescription();
        virtual void effect(Creature *who) = 0;
        friend class Floor;
};


#endif