#ifndef PARTICLE_H
#define PARTICLE_H

class Particle {
public:
    Particle(double rx, double ry, double vx, double vy, double radius, double mass, Color& color);

    Particle();

    void move(double dt);

    void draw();

    int count();

    double timeToHit(Particle& that);

    double timeToHitVerticalWall();

    double timeToHitHorizontalWall();

    void bounceOff(Particle& that);

    void bounceOffVerticalWall();

    void bounceOffHorizontalWall();

    double kineticEnergy();

private:
    double rx;
    double ry;
    double vx;
    double vy;
    double radius;
    double mass;
    Color color;
    int count;
};

#endif // PARTICLE_H
