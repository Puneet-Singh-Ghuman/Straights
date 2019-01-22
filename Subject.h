#ifndef SUBJECT_H
#define SUBJECT_H

#include <set>
class Observer;

class Subject {
    private:
        std::set<Observer *> observers_;

    public:
        void subscribe(Observer *);
        void unsubscribe(Observer *);
        void notify();
};

#endif
