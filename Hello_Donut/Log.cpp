#include "log.h"

void Donut::renderFrame(double A, double B) {
    vector<char> screen(WIDTH * HEIGHT, ' ');
    vector<double> zbuf(WIDTH * HEIGHT, 0.0);
    cout << "\x1b[2J\x1b[H";
    for (double theta = 0; theta < 2 * M_PI; theta += 0.07) {
        double cost = cos(theta), sint = sin(theta);
        for (double phi = 0; phi < 2 * M_PI; phi += 0.02) {
            double cosp = cos(phi), sinp = sin(phi);
            double circlex = R2 + R1 * cost;
            double circley = R1 * sint;
            double x = circlex * (cos(B) * cosp + sin(A) * sin(B) * sinp) - circley * cos(A) * sin(B);
            double y = circlex * (sin(B) * cosp - sin(A) * cos(B) * sinp) + circley * cos(A) * cos(B);
            double z = K2 + cos(A) * circlex * sinp + circley * sin(A);
            double ooz = 1 / z;
            int xp = int(WIDTH / 2 + K2 * 3 * x * ooz);
            int yp = int(HEIGHT / 2 - K2 * 1.5 * y * ooz);
            int idx = xp + yp * WIDTH;
            double L = cosp * cost * sin(B) - cos(A) * cost * sinp - sin(A) * sint + cos(B) * (cos(A) * sint - cost * sinp * sin(A));
            if (L > 0 && xp >= 0 && xp < WIDTH && yp >= 0 && yp < HEIGHT && ooz > zbuf[idx]) {
                zbuf[idx] = ooz;
                screen[idx] = SHADES[int(L * 8)];
            }
        }
    }
    for (int k = 0; k < WIDTH * HEIGHT; k++) {
        cout << (k % WIDTH ? screen[k] : '\n');
    }
}

void Donut::run() {
    double A = 0, B = 0;
    while (true) {
        renderFrame(A, B);
        A += 0.04;
        B += 0.02;
        this_thread::sleep_for(chrono::milliseconds(30));
    }
}
