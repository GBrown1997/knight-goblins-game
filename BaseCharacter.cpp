#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{

}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        width * scale,
        height * scale
    };
}

void BaseCharacter::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

    // Update Animation Frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.0f;
        if (frame > maxFrames)
        {
            frame = 0;
        }
    }

    if (Vector2Length(velocity) != 0.0)
    {
        // worldPos = Vector That Determines Which Direction The Screen Must Move In
        // Set worldPos = worldPos + direction
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.0f ? faceRightLeft = -1.0f : faceRightLeft = 1.0f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
    velocity = {};

    // Draw the Player Character
    Rectangle source{ frame * width, 0.0f, faceRightLeft * width, height };
    Rectangle dest{ getScreenPos().x, getScreenPos().y, scale * width, scale * height };
    DrawTexturePro(texture, source, dest, Vector2{}, 0.0f, WHITE);
}
