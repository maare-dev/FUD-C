/*
def createWindow():
    new window with
        fixed window size of real pixel - 256*3x256*3
        scaling of video mem - 3
        title - FUD-C | 0.0.1 alpha
def setPixel():
    getting rgb from specific cells of memory
    and setting it to current pixel
def getPixel():
    getting rgb of current pixel
    and setting rgb fields with it
def draw():
    draw frame
*/

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static Display *display = NULL;
static Window window = 0;
static GC gc = NULL;
static XImage *img_buffer = NULL;

static uint8_t key_states[256] = {0};
static int mouse_x = 0;
static int mouse_y = 0;
static uint8_t mouse_button_states[6] = {0};
static Atom wm_delete_window = 0;

#define WINDOW_WIDTH 256*3
#define WINDOW_HEIGHT 256*3
#define PIXEL_SCALE 3
#define LOGICAL_WIDTH (WINDOW_WIDTH / PIXEL_SCALE)
#define LOGICAL_HEIGHT (WINDOW_HEIGHT / PIXEL_SCALE)

int newWindow(void) {
    int screen;
    XSetWindowAttributes attrs;
    Visual *visual;
    int depth;

    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "ERR: cannot open display\n");
        exit(1);
    }

    screen = DefaultScreen(display);
    visual = DefaultVisual(display, screen);
    depth = DefaultDepth(display, screen);

    attrs.background_pixel = WhitePixel(display, screen);
    attrs.border_pixel = BlackPixel(display, screen);
    attrs.event_mask = 
        ExposureMask | 
        KeyPressMask | 
        KeyReleaseMask | 
        ButtonPressMask | 
        ButtonReleaseMask | 
        PointerMotionMask | 
        StructureNotifyMask;

    window = XCreateWindow(
        display,
        RootWindow(display, screen),
        0, 0,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        0,
        depth,
        InputOutput,
        visual,
        CWBackPixel | CWBorderPixel | CWEventMask,
        &attrs
    );

    XSizeHints hints;
    hints.flags = PMinSize | PMaxSize;
    hints.min_width = WINDOW_WIDTH;
    hints.min_height = WINDOW_HEIGHT;
    hints.max_width = WINDOW_WIDTH;
    hints.max_height = WINDOW_HEIGHT;
    XSetWMNormalHints(display, window, &hints);

    char *name = "FUD-C | 0.0.1 alpha";
    XStoreName(display, window, name);
    XMapWindow(display, window);
    gc = XCreateGC(display, window, 0, NULL);

    wm_delete_window = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, window, &wm_delete_window, 1);

    img_buffer = XCreateImage(
        display,
        visual,
        depth,
        ZPixmap,
        0,
        (char *)calloc(WINDOW_WIDTH * WINDOW_HEIGHT, sizeof(unsigned long)),
        WINDOW_WIDTH, WINDOW_HEIGHT,
        32, 0
    );

    if (img_buffer == NULL) {
        fprintf(stderr, "ERR: cannot create image buffer\n");
        exit(1);
    }

    memset(img_buffer->data, 0, img_buffer->bytes_per_line * img_buffer->height);
    return 0;
}

void setPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
    int real_x, real_y, sx, sy;
    unsigned long color;

    if (x < 0 || x >= LOGICAL_WIDTH || y < 0 || y >= LOGICAL_HEIGHT) {
        return;
    }

    color = (r << 16) | (g << 8) | b;

    for (sy = 0; sy < PIXEL_SCALE; sy++) {
        for (sx = 0; sx < PIXEL_SCALE; sx++) {
            real_x = x * PIXEL_SCALE + sx;
            real_y = y * PIXEL_SCALE + sy;
            
            if (real_x < WINDOW_WIDTH && real_y < WINDOW_HEIGHT) {
                XPutPixel(img_buffer, real_x, real_y, color);
            }
        }
    }
}

int getPixelColor(int x, int y) {
    int real_x, real_y;
    unsigned long color;

    if (x < 0 || x >= LOGICAL_WIDTH || y < 0 || y >= LOGICAL_HEIGHT) {
        return 0;
    }

    real_x = x * PIXEL_SCALE + PIXEL_SCALE / 2;
    real_y = y * PIXEL_SCALE + PIXEL_SCALE / 2;

    color = XGetPixel(img_buffer, real_x, real_y);
    return (int)color;
}
void getPixel(int x, int y, uint8_t *rgb) {
    unsigned long color = (unsigned long)getPixelColor(x, y);
    
    rgb[0] = (color >> 16) & 0xFF;
    rgb[1] = (color >> 8) & 0xFF;
    rgb[2] = color & 0xFF;
}

void draw(void) {
    XPutImage(display, window, gc, img_buffer, 0, 0, 0, 0, 
              WINDOW_WIDTH, WINDOW_HEIGHT);
    XFlush(display);
}

int pollEvents(void) {
    XEvent event;

    while (XCheckMaskEvent(display, -1, &event)) {
        switch (event.type) {
            case ClientMessage:
                if (event.xclient.format == 32 && 
                    (Atom)event.xclient.data.l[0] == wm_delete_window) {
                    return 1;
                }
                break;
            case DestroyNotify:
                return 1;
            case Expose:
                draw();
                break;
            case KeyPress: {
                KeySym keysym = XLookupKeysym(&event.xkey, 0);
                int keycode = (int)keysym & 0xFF;
                if (keycode >= 0 && keycode < 256) {
                    key_states[keycode] = 1;
                }
                break;
            }
            case KeyRelease: {
                KeySym keysym = XLookupKeysym(&event.xkey, 0);
                int keycode = (int)keysym & 0xFF;
                if (keycode >= 0 && keycode < 256) {
                    key_states[keycode] = 0;
                }
                break;
            }
            case ButtonPress: {
                if (event.xbutton.button >= 1 && event.xbutton.button <= 5) {
                    mouse_button_states[event.xbutton.button] = 1;
                    mouse_x = event.xbutton.x / PIXEL_SCALE;
                    mouse_y = event.xbutton.y / PIXEL_SCALE;
                }
                break;
            }
            case ButtonRelease: {
                if (event.xbutton.button >= 1 && event.xbutton.button <= 5) {
                    mouse_button_states[event.xbutton.button] = 0;
                    mouse_x = event.xbutton.x / PIXEL_SCALE;
                    mouse_y = event.xbutton.y / PIXEL_SCALE;
                }
                break;
            }
            case MotionNotify: {
                mouse_x = event.xmotion.x / PIXEL_SCALE;
                mouse_y = event.xmotion.y / PIXEL_SCALE;
                break;
            }
        }
    }

    usleep(16);
    return 0;
}

void closeWindow(void) {
    if (img_buffer != NULL) {
        if (img_buffer->data != NULL) {
            free(img_buffer->data);
        }
        XDestroyImage(img_buffer);
        img_buffer = NULL;
    }

    if (gc != NULL) {
        XFreeGC(display, gc);
    }

    if (window != 0) {
        XDestroyWindow(display, window);
    }

    if (display != NULL) {
        XCloseDisplay(display);
        display = NULL;
    }
}

int isKeyPressed(int keysym) {
    int keycode = keysym & 0xFF;
    if (keycode >= 0 && keycode < 256) {
        return key_states[keycode];
    }
    return 0;
}

int getMouseX(void) {
    return mouse_x;
}

int getMouseY(void) {
    return mouse_y;
}

int isMouseButtonPressed(int button) {
    if (button >= 0 && button <= 5) {
        return mouse_button_states[button];
    }
    return 0;
}