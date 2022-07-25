#ifndef __ITEM_H__
#define __ITEM_H__
#include "subject.h"
#include <string>
class Floor;
class Life;
class Dragon;

class Item: public Subject {
    protected:
        Floor *fl;
        char rep;
        std::string description;
        bool permisson;
        Item();
    public:
        virtual ~Item();
        void notifyObservesrs() override;
        char getRep();
        int getRecentX() override;
        int getRecentY() override;
        bool hasPermisson() const;
        virtual std::string getDescription();
        virtual void effect(Life *who) = 0;
        friend class Floor;
        friend class Dragon;
};

class PickUpable: public Item { 
    public:
        PickUpable();
};

#endif