/*{******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute 'raylib_compile_execute' script
*   Note that compiled executable is placed in the same folder as .c file
*
*   To test the examples on Web, press F6 and execute 'raylib_compile_execute_web' script
*   Web version of the program is generated in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2013-2024 Ramon Santamaria (@raysan5)
*
*******************************************************************************************}*/

#include "raylib.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define MAX_CISIM 1000

typedef enum{
    daire,
    kare
}sekilTipi;
    
struct cisim{
    Vector2 hiz;
    Vector2 konum;
    float kutle;
        
        
    union{
        struct{
            float genislik;
            float uzunluk;
        }kenar;
        float yaricap;         
    }boyut;  
        
    sekilTipi sekil;
};

struct cisim evren[MAX_CISIM] = {0};
int aktifCisimSayisi = 0;

bool daireEkle(float hizX, float hizY, float baslangicX, float baslangicY, float yaricap, float kutle){
    if(aktifCisimSayisi>=MAX_CISIM)
    return false;
    
    int indeks = aktifCisimSayisi;
    
    evren[indeks].konum.x = baslangicX;
    evren[indeks].konum.y = baslangicY;
    
    evren[indeks].hiz.x = hizX;
    evren[indeks].hiz.y = hizY;
    
    evren[indeks].kutle = kutle;
    evren[indeks].sekil = daire;
    
    evren[indeks].boyut.yaricap = yaricap;
    
    aktifCisimSayisi++;
    return true;
}
bool kareEkle(float hizX, float hizY, float baslangicX, float baslangicY, float genislik, float uzunluk, float kutle){
    if(aktifCisimSayisi>=MAX_CISIM)
    return false;
    
    int indeks = aktifCisimSayisi;
    
    evren[indeks].konum.x = baslangicX;
    evren[indeks].konum.y = baslangicY;
    
    evren[indeks].hiz.x = hizX;
    evren[indeks].hiz.y = hizY;
    
    evren[indeks].kutle = kutle;
    evren[indeks].sekil = kare;
    
    evren[indeks].boyut.kenar.uzunluk = uzunluk;
    evren[indeks].boyut.kenar.genislik = genislik;
    
    aktifCisimSayisi++;
    return true;
}
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1600;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    // Main game loop
    
    float g=581.0f;
    float esneklikKatsayisi=0.8f;
    bool ciziliyorMu = false;
    Vector2 cizimBaslangic = {0};
    
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        float dt = GetFrameTime();
        if(dt>=0.1f){dt = 0.1f;}
               
        for(int i=0;i<aktifCisimSayisi;i++){
            //düşüş
            evren[i].hiz.y += dt*g;
            evren[i].konum.x += evren[i].hiz.x*dt;
            evren[i].konum.y += evren[i].hiz.y*dt;
            //duvar kontrolleri
            {
            float sinirx = 0.0;
            float siniry = 0.0;
            
            if(evren[i].sekil == kare){
                sinirx = evren[i].boyut.kenar.genislik / 2.0f;
                siniry = evren[i].boyut.kenar.uzunluk / 2.0f;
            }
            if(evren[i].sekil == daire){
                sinirx = evren[i].boyut.yaricap;
                siniry = evren[i].boyut.yaricap;
            }
            //ekranın altı
            if(siniry + evren[i].konum.y >= screenHeight){
                    evren[i].konum.y = screenHeight - siniry;
                    evren[i].hiz.y = (-1.0f) * esneklikKatsayisi * evren[i].hiz.y;
                }
            //ekranın sağı    
            if(sinirx + evren[i].konum.x >= screenWidth){
                    evren[i].konum.x = screenWidth - sinirx;
                    evren[i].hiz.x = (-1.0f) * evren[i].hiz.x * esneklikKatsayisi ;
                }
            //ekranın solu        
            if( evren[i].konum.x - sinirx  <= 0){
                    evren[i].konum.x = sinirx;
                    evren[i].hiz.x = evren[i].hiz.x * esneklikKatsayisi * (-1.0f);
                }
            }
        }
        //vektör çizme
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            ciziliyorMu=true;
            cizimBaslangic=GetMousePosition(); //vector2 döndürür
        }
        //vektöre göre fırlatma
        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && ciziliyorMu==true){
            
                Vector2 cizimBitis=GetMousePosition();
                
                float hizX=(cizimBitis.x-cizimBaslangic.x)*5.0f;
                float hizY=(cizimBitis.y-cizimBaslangic.y)*5.0f;
                daireEkle(hizX, hizY, cizimBaslangic.x, cizimBaslangic.y, 25.0f, 100.0f);
            
        }
    
        
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            for(int i=0;i<aktifCisimSayisi;i++)
            {
                if(evren[i].sekil==daire)
                    DrawCircleV(evren[i].konum, evren[i].boyut.yaricap, RED);
                else if(evren[i].sekil==kare){
                    Vector2 kareBoyut = {evren[i].boyut.kenar.genislik, evren[i].boyut.kenar.uzunluk};
                    DrawRectangleV(evren[i].konum, kareBoyut, BLUE);
                }
            }
            ClearBackground(RAYWHITE);

            //--ADMİN Paneli--
            GuiSliderBar((Rectangle) {70,20,100,20}, "sekmez", "seker", &esneklikKatsayisi, 0.0f, 1.0f);
            GuiSliderBar((Rectangle) {70,90,100,20}, "düşük yerçekimi", "yüksek", &g, 0.0f, 1000.0f);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}