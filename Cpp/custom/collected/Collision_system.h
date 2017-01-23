#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include <vector>
#include "Particle.h"
#include "Min_pq.h"

class Event {
public:
    bool operator<(const Event& rhs) const
    {
        return this->time < rhs.time;
    }

    bool isValid() {
        if (a.count() != countA) {
            return false;
        }
        if (b.count() != countB) {
            return false;
        }
        return true;
    }

private:
    double time;
    Particle a;
    Particle b;
    int countA;
    int countB;
};

class Collision_system {
    Collision_system(std::vector<Particle>& particles);

    void simulate(double limit);

private:
    Min_pq <Event> pq;
    double t;
    double hz;
    std::vector<Particle> particles;

    void predict(Particle& a, double limit);

    void redraw(double limit);

};

#endif // COLLISION_SYSTEM_H
