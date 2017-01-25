#include "Particle.h"

Particle::Particle(double rx, double ry, double vx, double vy, double radius, double mass, Color& color)
        : rx{rx},
          ry{ry},
          vx{vx},
          vy{vy},
          radius{radius},
          mass{mass},
          color{color} {}

Particle::Particle()
{
    rx = Std_random::uniform(0.0, 1.0);
    ry = Std_random::uniform(0.0, 1.0);
    vx = Std_random::uniform(-0.005, 0.005);
    vy = Std_random::uniform(-0.005, 0.005);
    radius = 0.01;
    mass = 0.5;
    color = Color.BLACK;
}

void Particle::move(double dt)
{
    rx += vx * dt;
    ry += vy * dt;
}

void Particle::draw()
{
    Std_draw::setPenColor(color);
    Std_draw::filledCircle(rx, ry, radius);
}

int Particle::count()
{
    return count;
}

double Particle::timeToHit(Particle& that)
{
    if (this == that) return INFINITY;
    double dx = that.rx - this.rx;
    double dy = that.ry - this.ry;
    double dvx = that.vx - this.vx;
    double dvy = that.vy - this.vy;
    double dvdr = dx * dvx + dy * dvy;
    if (dvdr > 0) return INFINITY;
    double dvdv = dvx * dvx + dvy * dvy;
    double drdr = dx * dx + dy * dy;
    double sigma = this.radius + that.radius;
    double d = (dvdr * dvdr) - dvdv * (drdr - sigma * sigma);
    // if (drdr < sigma*sigma) Std_out::print_line("overlapping particles");
    if (d < 0) return INFINITY;
    return -(dvdr + std::sqrt(d)) / dvdv;
}

double Particle::timeToHitVerticalWall()
{
    if (vx > 0) return (1.0 - rx - radius) / vx;
    else if (vx < 0) return (radius - rx) / vx;
    else return INFINITY;
}

double Particle::timeToHitHorizontalWall()
{
    if (vy > 0) return (1.0 - ry - radius) / vy;
    else if (vy < 0) return (radius - ry) / vy;
    else return INFINITY;
}

void Particle::bounceOff(Particle& that)
{
    double dx = that.rx - this.rx;
    double dy = that.ry - this.ry;
    double dvx = that.vx - this.vx;
    double dvy = that.vy - this.vy;
    double dvdr = dx * dvx + dy * dvy;             // dv dot dr
    double dist = this.radius + that.radius;   // distance between particle centers at collison

    // magnitude of normal force
    double magnitude = 2 * this.mass * that.mass * dvdr / ((this.mass + that.mass) * dist);

    // normal force, and in x and y directions
    double fx = magnitude * dx / dist;
    double fy = magnitude * dy / dist;

    // update velocities according to normal force
    this.vx += fx / this.mass;
    this.vy += fy / this.mass;
    that.vx -= fx / that.mass;
    that.vy -= fy / that.mass;

    // update collision counts
    this.count++;
    that.count++;
}

void Particle::bounceOffVerticalWall()
{
    vx = -vx;
    ++count;
}

void Particle::bounceOffHorizontalWall()
{
    vy = -vy;
    ++count;
}

double Particle::kineticEnergy()
{
    return 0.5 * mass * (vx * vx + vy * vy);
}
