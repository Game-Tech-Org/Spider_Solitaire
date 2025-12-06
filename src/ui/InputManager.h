#pragma once

class InputManager {
public:
    int selectedCol = -1;
    int selectedIndex = -1;

    void handleClick();
    void handleDrag();
};