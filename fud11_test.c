#include "fud11.c"
#include <X11/keysym.h>

int main() {
    if (newWindow() != 0) return 1;
    
    int player_x = 100;
    int player_y = 100;
    
    while (1) {
        if (pollEvents() != 0) break;
        
        // Clear screen
        for (int y = 0; y < LOGICAL_HEIGHT; y++) {
            for (int x = 0; x < LOGICAL_WIDTH; x++) {
                setPixel(x, y, 0, 0, 0);
            }
        }
        
        // Move player with arrow keys
        if (isKeyPressed(XK_Left)) player_x--;
        if (isKeyPressed(XK_Right)) player_x++;
        if (isKeyPressed(XK_Up)) player_y--;
        if (isKeyPressed(XK_Down)) player_y++;
        
        // Exit on Escape
        if (isKeyPressed(XK_Escape)) break;
        
        // Draw player (red pixel)
        setPixel(player_x, player_y, 255, 0, 0);
        
        // Draw mouse cursor indicator (green pixel)
        setPixel(getMouseX(), getMouseY(), 0, 255, 0);
        
        // Draw blue pixel on left click
        if (isMouseButtonPressed(1)){
            setPixel(getMouseX()-1, getMouseY()-1, 0, 255, 255);
        }
        if (isMouseButtonPressed(2)){
            setPixel(getMouseX(), getMouseY()-1, 255, 0, 255);
        }
        if (isMouseButtonPressed(3)){
            setPixel(getMouseX()+1, getMouseY()-1, 255, 255, 0);
        }
        
        draw();
    }

    closeWindow();
    return 0;
}
