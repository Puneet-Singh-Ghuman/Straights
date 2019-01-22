#include "Subject.h"
#include "Observer.h"
void Subject::subscribe(Observer *obv){
    observers_.insert(obv);
}

void Subject::unsubscribe(Observer *obv){
    observers_.erase(obv);
}

void Subject::notify(){
    std::set<Observer *>::iterator i;

    for(i = observers_.begin(); i != observers_.end(); ++i){
        (*i)->update();
    }
}
