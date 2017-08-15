#include "Collision_system.h"
#include "Std_draw.h"

Event::Event(double time, Raw_particle_pointer a, Raw_particle_pointer b)
        : _time{time},
          _a{a},
          _b{b},
          _count_a{a ? a->count() : -1},
          _count_b{b ? b->count() : -1} {}

// clears the original to release ownership
Collision_system::Collision_system(std::vector<Owning_particle_pointer>&& particles) : _particles{particles}
{
    particles.clear();
}

Collision_system::~Collision_system()
{
    for (auto it = _particles.begin(); it != _particles.end(); ++it) {
        if (*it != nullptr) {
            delete *it;
            *it = nullptr;
        }
    }
}

void Collision_system::simulate(double limit)
{
    _pq = Min_pq<Event>{};
    for (auto i = 0; i < _particles.size(); ++i) {
        _predict(_particles[i], limit);
    }
    Event tmp{0, nullptr, nullptr};
    _pq.insert(tmp);

    while (!_pq.is_empty()) {
        Event e = _pq.delete_min();
        if (!e.is_valid()) { continue; }
        Raw_particle_pointer a = e._a;
        Raw_particle_pointer b = e._b;

        for (auto i = 0; i < _particles.size(); ++i) {
            if (_particles[i]) {
                _particles[i]->move(e._time - _time);
            }
        }
        _time = e._time;

        if (a != nullptr && b != nullptr) { a->bounce_off(*b); }
        else if (a != nullptr) { a->bounce_off_vertical_wall(); }
        else if (b != nullptr) { b->bounce_off_horizontal_wall(); }
        else { _redraw(limit); }

        _predict(a, limit);
        _predict(b, limit);
    }
}

void Collision_system::_predict(Raw_particle_pointer a, double limit)
{
    if (a == nullptr) { return; }
    for (auto i = 0; i < _particles.size(); ++i) {
        if (_particles[i]) {
            double dt{a->time_to_hit(*_particles[i])};
            if (_time + dt <= limit) {
                Event tmp{_time + dt, a, _particles[i]};
                _pq.insert(tmp);
            }
        }
    }

    double dt_x{a->time_to_hit_vertical_wall()};
    double dt_y{a->time_to_hit_horizontal_wall()};
    if (_time + dt_x <= limit) {
        Event tmp{_time + dt_x, a, nullptr};
        _pq.insert(tmp);
    }
    if (_time + dt_y <= limit) {
        Event tmp{_time + dt_y, nullptr, a};
        _pq.insert(tmp);
    }
}

void Collision_system::_redraw(double limit)
{
    Std_draw::clear();
    for (auto i = 0; i < _particles.size(); ++i) {
        if (_particles[i]) {
            _particles[i]->draw();
        }
    }
    Std_draw::show();
    Std_draw::pause(20);
    if (_time < limit) {
        Event tmp{_time + 1.0 / _hz, nullptr, nullptr};
        _pq.insert(tmp);
    }
}
