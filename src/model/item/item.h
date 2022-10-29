#ifndef __ITEM_H__
#define __ITEM_H__
#include "../subject.h"
#include <string>
class Floor;
class Life;
class Dragon;

class Item: public Subject {
    protected:
        Floor *fl;
        char rep;
        std::string description;
        std::string information;
        bool permisson = true;
        Item();
    public:
        virtual ~Item();
        void notifyObservesrs() override;
        char getRep() const;
        bool hasPermisson() const;
        virtual std::string getDescription() const; // used for showing the effect of the potion when using them 
        virtual std::string getInfo() const; // used for showing the effect of the potion when looking at them
        virtual int effect(Life *who) = 0;
        friend class Floor;
        friend class Dragon;
};

class PickUpable: public Item { 
    public:
        PickUpable();
};

#endif