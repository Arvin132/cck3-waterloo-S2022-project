//
// Created by kmajdi on 2022-07-14.
//

#ifndef CCK3_WATERLOO_S2022_PROJECT_OBSERVER_H
#define CCK3_WATERLOO_S2022_PROJECT_OBSERVER_H
class Creature;
class Floor;
class Item;

class Observer {
    public:
      virtual ~Observer();
      void virtual notify(Creature &who) = 0;
      void virtual notify(Floor &who) = 0;
      void virtual notify(Item &who) = 0;
};


#endif 
