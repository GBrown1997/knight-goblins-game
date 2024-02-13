#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Enemy.h"
#include "Prop.h"
#include <string>

int main()
{
    // Game Screen Dimensions Array
    int screenDimensions[2];
    screenDimensions[0] = 384;
    screenDimensions[1] = 384;

    // Initialise Game Screen Window
    InitWindow(screenDimensions[0], screenDimensions[1], "George's Top-Down Game");

    // Load Background Map
    Texture2D bgMap = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 bgMapPos{ 0.0, 0.0 };
    const float bgMapScale{ 4.0f };

    // Create Instance of Character Class - Called knightPlayer
    Character knightPlayer{ screenDimensions[0], screenDimensions[1] };

    Enemy goblinEnemy{ 
        Vector2 { 800.0f, 300.0f }, 
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")
    };

    Enemy slimeEnemy{
        Vector2{ 500.0f, 700.0f },
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png")
    };

    Enemy* enemies[]{
        &goblinEnemy,
        &slimeEnemy
    };

    for (auto enemy : enemies)
    {
        enemy->setTarget(&knightPlayer);
    }

    Prop props[2]{
        Prop{ Vector2{ 600.0f, 300.0f }, LoadTexture("nature_tileset/Rock.png") },
        Prop{ Vector2{ 400.0f, 500.0f }, LoadTexture("nature_tileset/Log.png") }
    };

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Start Drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // Gets playerKnight worldPos Vector and Flips it - Moves gbMapPos in the opposite direction (Character Sprite stays still. Map moves behind it)
        bgMapPos = Vector2Scale(knightPlayer.getWorldPos(), -1.0f);

        // Draw Background Map
        DrawTextureEx(bgMap, bgMapPos, 0.0, bgMapScale, WHITE);

        // Draw the Props
        for (auto prop : props)
        {
            prop.Render(knightPlayer.getWorldPos());
        }

        if (!knightPlayer.getAlive())   //Player Character is not alive
        {
            DrawText("Game Over!", 55.0f, 45.0f, 40, RED);
            EndDrawing();
            continue;
        }
        else                            //Player Character is alive
        {
            std::string playerHealth = "Health: ";
            playerHealth.append(std::to_string(knightPlayer.getHealth()), 0, 5);
            DrawText(playerHealth.c_str(), 55.0f, 45.0f, 40, RED);
        }

        // Tick Function Called After Drawing Map Texture - Otherwise the map will be drawn on top of the character
        knightPlayer.tick(GetFrameTime());

        // Check the Map Bounds
        if (knightPlayer.getWorldPos().x < 0.0f ||
            knightPlayer.getWorldPos().y < 0.0f ||
            knightPlayer.getWorldPos().x + screenDimensions[0] > bgMap.width * bgMapScale ||
            knightPlayer.getWorldPos().y + screenDimensions[1] > bgMap.height * bgMapScale)
            {
                knightPlayer.undoMovement();
            }

            // Check Prop Collisions
            for (auto prop : props)
            {
                if (CheckCollisionRecs(prop.getCollisionRec(knightPlayer.getWorldPos()), knightPlayer.getCollisionRec()))
                {
                    knightPlayer.undoMovement();
                }
                if (CheckCollisionRecs(prop.getCollisionRec(knightPlayer.getWorldPos()), goblinEnemy.getCollisionRec()))
                {
                    goblinEnemy.undoMovement();
                }
            }

            for (auto enemy : enemies)
            {
                enemy->tick(GetFrameTime());
            }

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                for (auto enemy : enemies)
                {
                    if (CheckCollisionRecs(enemy->getCollisionRec(), knightPlayer.getWeaponCollisionRec()))
                    {
                        enemy->setAlive(false);
                    }
                }
                
            }

        // End Drawing
        EndDrawing();
    }
    UnloadTexture(bgMap);
}
