#include <X11/Xlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    Display *dpy;
    Window root;
    Window *children;
    unsigned int nchildren;

    int screen_width, screen_height;

    dpy = XOpenDisplay(NULL);
    root = DefaultRootWindow(dpy);

    screen_width = DisplayWidth(dpy, DefaultScreen(dpy));
    screen_height = DisplayHeight(dpy, DefaultScreen(dpy));

    XQueryTree(dpy, root, &root, &root, &children, &nchildren);

    int *x_directions = malloc(nchildren * sizeof(int));
    int *y_directions = malloc(nchildren * sizeof(int));

    srand(time(NULL));

    for (unsigned int i = 0; i < nchildren; i++) {
        x_directions[i] = (rand() % 20 > 10) ? 1 : -1;
        y_directions[i] = (rand() % 20 > 10) ? 1 : -1;
    }
    
    while (1) {
        for (unsigned int i = 0; i < nchildren; i++) {
            XWindowAttributes attr;
            XGetWindowAttributes(dpy, children[i], &attr);

            if (attr.x + attr.width >= screen_width || attr.x <= 0) {
                x_directions[i] = -x_directions[i];
            }
            
            if (attr.y + attr.height >= screen_height || attr.y <= 0) {
                y_directions[i] = -y_directions[i];
            }

            XMoveWindow(dpy, children[i], attr.x + x_directions[i], attr.y + y_directions[i]);
        }
        XFree(children);
        XQueryTree(dpy, root, &root, &root, &children, &nchildren);
        //usleep(16000);
        usleep(16000);
    }
    XCloseDisplay(dpy);
    return 0;
}
