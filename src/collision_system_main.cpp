#include "utility.h"
#include "Particle.h"
#include "Std_in.h"
#include "Std_draw.h"
#include "Collision_system.h"

int main(int argc, char* argv[])
{
    Std_draw::set_canvas_size(800, 800);

    // Std_draw::set_x_scale(1.0/22.0, 21.0/22.0);
    // Std_draw::set_y_scale(1.0/22.0, 21.0/22.0);

    Std_draw::enable_double_buffering();

    std::vector<Particle> particles;

    if (argc == 2) {
        int n = utility::str_to_num(argv[1]);
        particles.clear();
        particles.reserve(n);
        for (auto i = 0; i < n; ++i) {
            particles[i] = Particle{};
        }
    } else {
        int n = Std_in::read_int();
        particles.clear();
        particles.reserve(n);
        double rx;
        double ry;
        double vx;
        double vy;
        double radius;
        double mass;
        int r;
        int g;
        int b;
        for (auto i = 0; i < n; ++i) {
            rx = Std_in::read_double();
            ry = Std_in::read_double();
            vx = Std_in::read_double();
            vy = Std_in::read_double();
            radius = Std_in::read_double();
            mass = Std_in::read_double();
            r = Std_in::read_int();
            g = Std_in::read_int();
            b = Std_in::read_int();
            Color color{r, g, b};
            particles[i] = Particle{rx, ry, vx, vy, radius, mass, color};
        }
    }

    Collision_system system{particles};
    system.simulate(10000);
    return 0;
}