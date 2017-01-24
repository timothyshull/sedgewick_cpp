#include "Collision_system.h"

Collision_system::Collision_system(std::vector<Particle>& particles)
{
    this.particles = particles.clone();
}

void Collision_system::simulate(double limit)
{
    pq = new MinPQ<Event>();
    for (int i = 0; i < particles.length; ++i) {
        predict(particles[i], limit);
    }
    pq.insert(new Event(0, null, null));        // redraw event


    // the main event-driven simulation loop
    while (!pq.is_empty()) {

        // get impending event, discard if invalidated
        Event e = pq.delMin();
        if (!e.isValid()) continue;
        Particle a = e.a;
        Particle b = e.b;

        // physical collision, so update positions, and then simulation clock
        for (int i = 0; i < particles.length; ++i)
            particles[i].move(e.time - t);
        t = e.time;

        // process event
        if (a != null && b != null) a.bounceOff(b);              // particle-particle collision
        else if (a != null && b == null) a.bounceOffVerticalWall();   // particle-wall collision
        else if (a == null && b != null) b.bounceOffHorizontalWall(); // particle-wall collision
        else if (a == null && b == null) redraw(limit);               // redraw event

        // update the priority queue with new collisions involving a or b
        predict(a, limit);
        predict(b, limit);
    }
}

void Collision_system::predict(Particle& a, double limit)
{
    if (a == null) return;

    // particle-particle collisions
    for (int i = 0; i < particles.length; ++i) {
        double dt = a.timeToHit(particles[i]);
        if (t + dt <= limit)
            pq.insert(new Event(t + dt, a, particles[i]));
    }

    // particle-wall collisions
    double dtX = a.timeToHitVerticalWall();
    double dtY = a.timeToHitHorizontalWall();
    if (t + dtX <= limit) pq.insert(new Event(t + dtX, a, null));
    if (t + dtY <= limit) pq.insert(new Event(t + dtY, null, a));
}

void Collision_system::redraw(double limit)
{
    Std_draw::clear();
    for (int i = 0; i < particles.length; ++i) {
        particles[i].draw();
    }
    Std_draw::show();
    Std_draw::pause(20);
    if (t < limit) {
        pq.insert(new Event(t + 1.0 / hz, null, null));
    }
}
