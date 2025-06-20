#include "raylib.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <fstream>

using namespace std;

int main(){
    int WIDTH = 500;
    int HEIGHT = 600;
    int speed = 5;
    int upd_cost = 10;
    int big = 1;
    InitWindow(WIDTH, HEIGHT, "hello");
    InitAudioDevice();

    Music bgm = LoadMusicStream("andrea.mp3"); 
    PlayMusicStream(bgm); 

    int rectx = 100;
    int recty = 100;
    int rect_wid = 100;
    int rect_hei = 100;
    int score = 0;
    Rectangle upgradeBtn = { 350, 20, 120, 50 }; // x, y, width, height


    SetTargetFPS(60);

    while(!WindowShouldClose()){

       
        UpdateMusicStream(bgm);

        if(IsKeyDown(KEY_W)) recty -= speed;  
        if(IsKeyDown(KEY_S)) recty += speed;
        if(IsKeyDown(KEY_A)) rectx -= speed;
        if(IsKeyDown(KEY_D)) rectx += speed;

        if(rectx < 0) rectx = 0;
        if(rectx + rect_wid > WIDTH) rectx = WIDTH - rect_wid;
        if(recty < 0) recty = 0;
        if(recty + rect_hei > HEIGHT) recty = HEIGHT - rect_hei;
        Vector2 mousepos = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mousepos, upgradeBtn)) {
                if (score >= upd_cost){
                    score -= upd_cost;
                    big += 20;
                    rect_wid = GetRandomValue(big , WIDTH);
                    rect_hei = GetRandomValue(big , WIDTH);
                    upd_cost += 20;
                }
            }
        }   

        
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            if(mousepos.x >= rectx && mousepos.x <= rectx + rect_wid &&
               mousepos.y >= recty && mousepos.y <= recty + rect_hei){

                score += 1;
                rect_hei = GetRandomValue(big, 300);
                rect_wid = GetRandomValue(big, 300);
                rectx = GetRandomValue(0, WIDTH - rect_wid);
                recty = GetRandomValue(0, HEIGHT - rect_hei);
            }
        }

        if (rect_wid>= 500 && rect_hei >=600){
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("you win !!!!!!!!!!!!!!!!!!!!!!!!", 250,300,20,RED);
            EndDrawing();
            std::this_thread::sleep_for(std::chrono::seconds(2));
            ofstream winfile("win.txt");
            if (winfile.is_open()){
                winfile<<"you won!!!!!!!!!!!!!!!"<<endl;
                winfile.close();
            }else{
                cerr<<"sorry couldn't make a file"<<endl;
                return 1;
            }
            CloseWindow();
            CloseAudioDevice();          
            return 0;
        }
        BeginDrawing();
        ClearBackground(WHITE);
        DrawRectangle(rectx, recty, rect_wid, rect_hei, RED);
        DrawText(TextFormat("score %d", score), 10, 10, 30, DARKGRAY);
        DrawRectangleRec(upgradeBtn, GREEN);
        DrawRectangleRec(upgradeBtn, DARKGRAY);
        DrawText("Buy Upgrade", upgradeBtn.x + 10, upgradeBtn.y + 10, 20, LIGHTGRAY);
        DrawText("hot rectangles in your area want to be clicked", 10,90,20,DARKBLUE);
        EndDrawing();
    }   

    UnloadMusicStream(bgm);  
    CloseAudioDevice();      
    CloseWindow();
    return 0;
}