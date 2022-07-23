//
// Created by kmajdi on 2022-07-14.
//

#ifndef CCK3_WATERLOO_S2022_PROJECT_SUBJECT_H
#define CCK3_WATERLOO_S2022_PROJECT_SUBJECT_H
#include <vector>
class Observer;

class Subject {
    protected:
      int recentX;
      int recentY;
      std::vector<Observer*> observers;
    public:
      virtual ~Subject();
      virtual void notifyObservesrs() = 0;
      int virtual getRecentX() = 0;
      int virtual getRecentY() = 0;
      void attach(Observer *ob);
      void detach(Observer *ob);
};


#endif //CCK3_WATERLOO_S2022_PROJECT_SUBJECT_H
