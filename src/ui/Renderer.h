#pragma once
#include "Card.h"
#include "Column.h"
#include <raylib.h>

class Renderer {
public:
    Texture2D cardTexture;

    void loadAssets();
    void drawColumn(const Column& col, int x, int y);
    void drawCard(const Card& c, int x, int y);
    void drawGame(const Column columns[10]);
};