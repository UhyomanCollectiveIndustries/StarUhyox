#include "EventBus.h"

void EventBus::subscribeCollision(
    std::function<void(const CollisionEvent&)> listener){
        collisionListeners.push_back(listener);
}

void EventBus::publish(const CollisionEvent& e){
    for(auto& listener : collisionListeners){
        listener(e);
    }
}