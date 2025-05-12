#include <raylib.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>

int main() 
{
    // Initialize the window
    constexpr int screenWidth = 1200;
    constexpr int screenHeight = 600;
    
    //set up windows and fps config
    InitWindow(screenWidth, screenHeight, "MyEngine");
    SetTargetFPS(90);
    

    // Grid data
    int count = 5;
    float spacing = 4;

    //set up the first camera
    Camera cameraL = {0};
    cameraL.position = {-1.0f, 0.0f, 0.0f};
    cameraL.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    cameraL.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    cameraL.fovy = 45.0f;
    RenderTexture screenL = LoadRenderTexture(screenWidth/2, screenHeight);
    cameraL.projection = CAMERA_PERSPECTIVE;


    //set up the second camera
    Camera cameraR = {0};
    cameraR.position = {1.0f, 0.0f, 0.0f};
    cameraR.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    cameraR.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    cameraR.fovy = 45.0f;
    RenderTexture screenR = LoadRenderTexture(screenWidth/2, screenHeight);
    cameraR.projection = CAMERA_PERSPECTIVE;

    //split screen
    Rectangle splitScreenRect = { 0.0f, 0.0f, (float)screenL.texture.width, (float)-screenL.texture.height };

    //setting mouse
    DisableCursor();
    
    while (!WindowShouldClose())
    {
        
        UpdateCamera(&cameraL, CAMERA_FIRST_PERSON);
        UpdateCamera(&cameraR, CAMERA_FIRST_PERSON);    

        

        //rendering and camera split screen
       BeginTextureMode(screenL);
            ClearBackground(SKYBLUE);
            
            BeginMode3D(cameraL);
                DrawFPS(0,0);
                // Draw scene: grid of cube trees on a plane to make a "world"
                DrawPlane((Vector3){ 0, 0, 0 }, (Vector2){ 50, 50 }, BEIGE); // Simple world plane

                for (float x = -count*spacing; x <= count*spacing; x += spacing)
                {
                    for (float z = -count*spacing; z <= count*spacing; z += spacing)
                    {
                        DrawCube((Vector3) { x, 1.5f, z }, 1, 1, 1, LIME);
                        DrawCube((Vector3) { x, 0.5f, z }, 0.25f, 1, 0.25f, BROWN);
                    }
                }

              
                
            EndMode3D();
            
            
        EndTextureMode();

        // Draw Player2 view to the render texture
        BeginTextureMode(screenR);
            ClearBackground(SKYBLUE);
            
            BeginMode3D(cameraR);
            
                // Draw scene: grid of cube trees on a plane to make a "world"
                DrawPlane((Vector3){ 0, 0, 0 }, (Vector2){ 50, 50 }, BEIGE); // Simple world plane

                for (float x = -count*spacing; x <= count*spacing; x += spacing)
                {
                    for (float z = -count*spacing; z <= count*spacing; z += spacing)
                    {
                        DrawCube((Vector3) { x, 1.5f, z }, 1, 1, 1, LIME);
                        DrawCube((Vector3) { x, 0.5f, z }, 0.25f, 1, 0.25f, BROWN);
                    }
                }

                
            EndMode3D();
            
            
        EndTextureMode();

        // Draw both views render textures to the screen side by side
        BeginDrawing();
            ClearBackground(BLACK);
            
            DrawTextureRec(screenL.texture, splitScreenRect, (Vector2){ 0, 0 }, WHITE);
            DrawTextureRec(screenR.texture, splitScreenRect, (Vector2){ screenWidth/2.0f, 0 }, WHITE);
            
            DrawRectangle(GetScreenWidth()/2 - 2, 0, 4, GetScreenHeight(), LIGHTGRAY);
        EndDrawing();
    }
    
    
    CloseWindow();
}