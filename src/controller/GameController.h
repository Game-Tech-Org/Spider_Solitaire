#pragma once
#include "GameState.h"
#include "Renderer.h"
#include "InputManager.h"

class GameController {
public:
    GameState game;
    Renderer renderer;
    InputManager input;

    void init();
    void update();
    void draw();
    void run(); // main loop
};