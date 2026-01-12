#include "raylib.h"
#include <iostream>
#include <string>
#include <sstream>
#include "./core/SpiderSolitaire.h"

using namespace std;

enum MenuState { MAIN_MENU, PLAYING, EXIT_GAME };

int main() {
    InitWindow(1020, 750, "Spider Solitaire - One Suit");
    SetTargetFPS(60);
    
    SpiderSolitaire game;
    game.loadImages();
    
    Image menuBgImg = LoadImage("Deck Images/menu_bg.jpeg");
    if (!menuBgImg.data) menuBgImg = GenImageColor(1020, 750, Color{20,20,20,255});
    Texture2D menuBg = LoadTextureFromImage(menuBgImg);
    UnloadImage(menuBgImg);
    
    MenuState state = MAIN_MENU;
    int menuSel = 0;
    bool saveExists = false;
    
    while (!WindowShouldClose()) {
        ifstream check("savegame.dat");
        saveExists = check.is_open();
        if (check.is_open()) check.close();
        
        if (state == MAIN_MENU) {
            Vector2 mp = GetMousePosition();
            
            if (IsKeyPressed(KEY_DOWN)) menuSel = (menuSel+1)%(saveExists?3:2);
            if (IsKeyPressed(KEY_UP)) menuSel = (menuSel-1+(saveExists?3:2))%(saveExists?3:2);
            
            Rectangle btnContinue = {360, 340, 300, 50};
            Rectangle btnNewGame = {360, 405, 300, 50};
            Rectangle btnExit = {360, 470, 300, 50};
            
            if (CheckCollisionPointRec(mp, btnContinue) && saveExists) { 
                menuSel = 0; 
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { 
                    game.load(); 
                    state = PLAYING; 
                } 
            }
            else if (CheckCollisionPointRec(mp, btnNewGame)) { 
                menuSel = saveExists ? 1 : 0; 
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { 
                    game.newGame(); 
                    state = PLAYING; 
                } 
            }
            else if (CheckCollisionPointRec(mp, btnExit)) { 
                menuSel = saveExists ? 2 : 1; 
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
                    state = EXIT_GAME; 
            }
            
            if (IsKeyPressed(KEY_ENTER)) {
                if (saveExists) {
                    if (menuSel == 0) { game.load(); state = PLAYING; }
                    else if (menuSel == 1) { game.newGame(); state = PLAYING; }
                    else if (menuSel == 2) state = EXIT_GAME;
                } else {
                    if (menuSel == 0) { game.newGame(); state = PLAYING; }
                    else if (menuSel == 1) state = EXIT_GAME;
                }
            }
            
            BeginDrawing();
            ClearBackground(BLACK);
            
            DrawTexturePro(menuBg, {0,0,(float)menuBg.width,(float)menuBg.height}, 
                          {0,0,1020,750}, {0,0}, 0, WHITE);
            
            DrawRectangle(0, 0, 1020, 750, Color{0,0,0,120});
            
            DrawTextWithShadow("SPIDER", 355, 110, 64, Color{0,0,0,255}, Color{220,20,20,255});
            DrawTextWithShadow("SOLITAIRE", 310, 185, 64, Color{0,0,0,255}, Color{220,20,20,255});
            
            if (saveExists) {
                Color cb = (menuSel==0) ? Color{220,20,20,255} : Color{120,0,0,220};
                Color cb2 = (menuSel==0) ? Color{255,215,0,255} : Color{220,20,20,255};
                DrawRectangleRec(btnContinue, cb);
                DrawRectangleLinesEx(btnContinue, 3.0f, cb2);
                DrawTextWithShadow("Continue", 415, 354, 28, Color{0,0,0,200}, WHITE);
            }
            
            int ngs = saveExists ? 1 : 0;
            Color ngb = (menuSel==ngs) ? Color{220,20,20,255} : Color{120,0,0,220};
            Color ngb2 = (menuSel==ngs) ? Color{255,215,0,255} : Color{220,20,20,255};
            DrawRectangleRec(btnNewGame, ngb);
            DrawRectangleLinesEx(btnNewGame, 3.0f, ngb2);
            DrawTextWithShadow("New Game", 405, 419, 28, Color{0,0,0,200}, WHITE);
            
            int es = saveExists ? 2 : 1;
            Color eb = (menuSel==es) ? Color{220,20,20,255} : Color{120,0,0,220};
            Color eb2 = (menuSel==es) ? Color{255,215,0,255} : Color{220,20,20,255};
            DrawRectangleRec(btnExit, eb);
            DrawRectangleLinesEx(btnExit, 3.0f, eb2);
            DrawTextWithShadow("Exit", 460, 484, 28, Color{0,0,0,200}, WHITE);
            
            DrawTextWithShadow("Use Arrow Keys or Mouse to Select", 330, 590, 19, Color{0,0,0,200}, Color{200,200,200,255});
            
            EndDrawing();
        }
        else if (state == PLAYING) {
            if (IsKeyPressed(KEY_ESCAPE)) {
                game.save();
                state = MAIN_MENU;
                menuSel = 0;
            }
            
            game.handleInput();
            game.update(GetFrameTime());
            
            BeginDrawing();
            game.draw();
            EndDrawing();
        }
        else if (state == EXIT_GAME) {
            break;
        }
    }
    
    game.save();
    game.unloadImages();
    UnloadTexture(menuBg);
    CloseWindow();
    return 0;
}