#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include <vector>
#include "Particle.h"
#include "Min_pq.h"

class Collision_system;

class Event {
public:
    Event() = default;

    Event(const Event&) = default;

    Event(Event&&) = default;

    ~Event() = default;

    Event& operator=(const Event&) = default;

    Event& operator=(Event&&) = default;

    Event(double time, Raw_particle_pointer a, Raw_particle_pointer b);

    inline bool operator<(const Event& rhs) const { return this->_time < rhs._time; }

    inline bool is_valid() const { return (_a != nullptr && _a->count() == _count_a) && (_b != nullptr && _b->count() == _count_b); }

private:
    using Raw_particle_pointer = Particle*

    double _time;
    Raw_particle_pointer _a;
    Raw_particle_pointer _b;
    int _count_a;
    int _count_b;

    friend class Collision_system;
};

class Collision_system {
public:
    Collision_system() = default;

    Collision_system(const Collision_system&) = default;

    Collision_system(Collision_system&&) = default;

    Collision_system& operator=(const Collision_system&) = default;

    Collision_system& operator=(Collision_system&&) = default;

    ~Collision_system();

    Collision_system(std::vector<Owning_particle_pointer>&& particles);

    void simulate(double limit);

private:
    using Owning_particle_pointer = Particle*;
    using Raw_particle_pointer = Particle*;

    Min_pq<Event> _pq;
    double _time;
    double _hz;
    std::vector<Owning_particle_pointer> _particles;

    void _predict(Raw_particle_pointer a, double limit);

    void _redraw(double limit);
};

#endif // COLLISION_SYSTEM_H
