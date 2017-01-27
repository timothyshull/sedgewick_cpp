#include <cmath>

#include "Particle.h"
#include "Std_random.h"
#include "Std_draw.h"

Particle::Particle(double rx, double ry, double vx, double vy, double radius, double mass, Color& color)
        : _rx{rx},
          _ry{ry},
          _vx{vx},
          _vy{vy},
          _radius{radius},
          _mass{mass},
          _color{color} {}

Particle::Particle()
        : _rx{Std_random::uniform(0.0, 1.0)},
          _ry{Std_random::uniform(0.0, 1.0)},
          _vx{Std_random::uniform(-0.005, 0.005)},
          _vy{Std_random::uniform(-0.005, 0.005)},
          _radius{0.01},
          _mass{0.5},
          _color{Color{0, 0, 0, 255}} {}

void Particle::move(double dt)
{
    _rx += _vx * dt;
    _ry += _vy * dt;
}

void Particle::draw()
{
    Std_draw::set_pen_color(_color);
    Std_draw::filled_circle(_rx, _ry, _radius);
}

double Particle::time_to_hit(Particle& that)
{
    if (*this == that) { return _infinity; }
    double dx{that._rx - _rx};
    double dy{that._ry - _ry};
    double dvx{that._vx - _vx};
    double dvy{that._vy - _vy};
    double dvdr{dx * dvx + dy * dvy};
    if (dvdr > 0) { return _infinity; }
    double dvdv{dvx * dvx + dvy * dvy};
    double drdr{dx * dx + dy * dy};
    double sigma{_radius + that._radius};
    double d{(dvdr * dvdr) - dvdv * (drdr - sigma * sigma)};
    // if (drdr < sigma*sigma) Std_out::print_line("overlapping particles");
    if (d < 0) { return _infinity; }
    return -(dvdr + std::sqrt(d)) / dvdv;
}

double Particle::time_to_hit_vertical_wall()
{
    if (_vx > 0) { return (1.0 - _rx - _radius) / _vx; }
    else if (_vx < 0) { return (_radius - _rx) / _vx; }
    else { return _infinity; }
}

double Particle::time_to_hit_horizontal_wall()
{
    if (_vy > 0) { return (1.0 - _ry - _radius) / _vy; }
    else if (_vy < 0) { return (_radius - _ry) / _vy; }
    else { return _infinity; }
}

void Particle::bounce_off(Particle& that)
{
    double dx{that._rx - _rx};
    double dy{that._ry - _ry};
    double dvx{that._vx - _vx};
    double dvy{that._vy - _vy};
    double dvdr{dx * dvx + dy * dvy};
    double dist{_radius + that._radius};

    double magnitude{2 * _mass * that._mass * dvdr / ((_mass + that._mass) * dist)};

    double fx{magnitude * dx / dist};
    double fy{magnitude * dy / dist};

    _vx += fx / _mass;
    _vy += fy / _mass;
    that._vx -= fx / that._mass;
    that._vy -= fy / that._mass;

    ++_count;
    ++that._count;
}

void Particle::bounce_off_vertical_wall()
{
    _vx = -_vx;
    ++_count;
}

void Particle::bounce_off_horizontal_wall()
{
    _vy = -_vy;
    ++_count;
}

double Particle::kinetic_energy()
{
    return 0.5 * _mass * (_vx * _vx + _vy * _vy);
}
