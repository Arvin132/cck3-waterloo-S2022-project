#ifndef __ITEM_H__
#define __ITEM_H__
#include "subject.h"
#include <string>
class Floor;
class Life;

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
        int getRecentX() override;
        int getRecentY() override;
        virtual std::string getDescription();
        virtual void effect(Life *who) = 0;
        friend class Floor;
};

class PickUpable: public Item { 
    public:
        PickUpable();
};

#endif