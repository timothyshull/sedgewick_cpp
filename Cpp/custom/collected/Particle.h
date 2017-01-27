#ifndef PARTICLE_H
#define PARTICLE_H

#include "utility.h"

using utility::Color;

class Particle {
public:
    Particle(double rx, double ry, double vx, double vy, double radius, double mass, Color& color);

    Particle();

    void move(double dt);

    void draw();

    inline int count() const noexcept { return _count; }

    double time_to_hit(Particle& that);

    double time_to_hit_vertical_wall();

    double time_to_hit_horizontal_wall();

    void bounce_off(Particle& that);

    void bounce_off_vertical_wall();

    void bounce_off_horizontal_wall();

    double kinetic_energy();

    bool operator==(const Particle& rhs);

private:
    static const double _infinity = std::numeric_limits<double>::infinity();
    double _rx;
    double _ry;
    double _vx;
    double _vy;
    double _radius;
    double _mass;
    Color _color;
    int _count;
};

#endif // PARTICLE_H
