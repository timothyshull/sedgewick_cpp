int main(int argc, char *argv[]) {
    StdDraw.setCanvasSize(800, 800);

    // remove the border
    // StdDraw.setXscale(1.0/22.0, 21.0/22.0);
    // StdDraw.setYscale(1.0/22.0, 21.0/22.0);

    // enable double buffering
    StdDraw.enableDoubleBuffering();

    // the array of particles
    Particle[] particles;

    // create n random particles
    if (args.length == 1) {
        int n = Integer.parseInt(args[0]);
        particles = new Particle[n];
        for (int i = 0; i < n; i++)
            particles[i] = new Particle();
    }

        // or read from standard input
    else {
        int n = StdIn.readInt();
        particles = new Particle[n];
        for (int i = 0; i < n; i++) {
            double rx = StdIn.readDouble();
            double ry = StdIn.readDouble();
            double vx = StdIn.readDouble();
            double vy = StdIn.readDouble();
            double radius = StdIn.readDouble();
            double mass = StdIn.readDouble();
            int r = StdIn.readInt();
            int g = StdIn.readInt();
            int b = StdIn.readInt();
            Color color = new Color(r, g, b);
            particles[i] = new Particle(rx, ry, vx, vy, radius, mass, color);
        }
    }

    // create collision system and simulate
    CollisionSystem system = new CollisionSystem(particles);
    system.simulate(10000);
    return 0;
}