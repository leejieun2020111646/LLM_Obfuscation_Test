#include <math.h>
#include <sys/time.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>

double L, angle, P, dt = 0.016, T, Z, D = 1, d, positions[999], E, h = 8, I, J, K, velocities[999];
double M, m, O, offsets[999], j = 0.033, i = 1000, r, t, u, v, W, screenScale = 74.5, length = 221;
double X = 7.26, a, B, gravity = 32.2, c, F, H;
int N, q, C, numPoints, p, U;
Window win;
char displayText[52];
GC graphicsContext;

int main() {
    Display* display = XOpenDisplay(0);
    win = RootWindow(display, 0);
    XSetForeground(display, graphicsContext = XCreateGC(display, win, 0, 0), BlackPixel(display, 0));

    while (scanf("%lf%lf%lf", positions + numPoints, velocities + numPoints, positions + numPoints) + 1) {
        numPoints++;
    }

    win = XCreateSimpleWindow(display, win, 0, 0, 400, 400, 0, 0, WhitePixel(display, 0));
    XSelectInput(display, win, KeyPressMask);
    XMapWindow(display, win);

    for (;;) {
        struct timeval delay = {0, dt * 1e6};

        K = cos(j);
        N = 1e4;
        M += H * dt;
        Z = D * K;
        F += dt * P;
        r = E * K;
        W = cos(O);
        m = K * W;
        H = K * T;
        O += (D * dt * F / K) + (d / K * E * dt);
        B = sin(j);
        a = B * T * D - E * W;

        XClearWindow(display, win);

        t = T * E + D * B * W;
        j += (d * dt * D) - (dt * F * E);
        P = W * E * B - T * D;

        for (angle += (I = D * W + E * T * B, E * d / K * B + v + B / K * F * D) * dt; p < numPoints;) {
            T = positions[p] + i;
            E = c - velocities[p];
            D = offsets[p] - L;
            K = D * m - B * T - H * E;

            if (positions[p] + velocities[p] + positions[p] == 0 ||
                K < fabs(W = T * r - I * E + D * P) ||
                fabs(D = t * D + Z * T - a * E) > K) {
                N = 1e4;
            } else {
                q = (W / K) * 400 + 200;
                C = 200 + (400 / K * D);
                if (N != 1e4) {
                    XDrawLine(display, win, graphicsContext, N, U, q, C);
                }
                N = q;
                U = C;
            }
            p++;
        }

        L += dt * (X * t + P * M + m * length);
        T = X * X + length * length + M * M;

        XDrawString(display, win, graphicsContext, 20, 380, displayText, 17);
        D = v / length * 15;
        i += (B * length - M * r - X * Z) * dt;

        while (XPending(display)) {
            XEvent event;
            XNextEvent(display, &event);
            int keySym = XLookupKeysym(&event.xkey, 0);

            if (keySym == XK_Up) {
                u++;
            } else if (keySym == XK_Down) {
                u--;
            } else if (keySym == XK_Left) {
                h--;
            } else if (keySym == XK_Right) {
                h++;
            }
        }

        m = 15 * F / length;
        c += (I = M / length, length * H + I * M + a * X) * dt;
        H = gravity * r + v * X - F * length + ((E = 0.1 + X * 4.9 / length, t = T * m / 32 - I * T / 24) / screenScale);
        K = F * M + ((h * 1e4 / length - (T + E * 5 * T * E) / 300) / screenScale) - X * d - B * gravity;
        a = 2.63 / length * d;
        X += ((d * length - T / screenScale * (0.19 * E + a * 0.64 + J / 1e3)) - M * v + gravity * Z) * dt;
        length += K * dt;
        W = d;

        sprintf(displayText, "%5d %3d %7d", (int)(length / 1.7), (C = 9000 + O * 57.3) % 550, (int)i);
        d += T * (0.45 - 14 / length * X - a * 130 - J * 0.14) * dt / 125e2 + F * dt * v;
        P = (T * (47 * I - m * 52 + E * 94 * D - t * 0.38 + u * 0.21 * E) / 100 + W * 179 * v) / 2312;

        select(0, NULL, NULL, NULL, &delay);
        v -= (W * F - T * (0.63 * m - I * 0.086 + m * E * 19 - D * 25 - 0.11 * u) / 107e2) * dt;
        D = cos(angle);
        E = sin(angle);
    }

    return 0;
}
