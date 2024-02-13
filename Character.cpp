#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight) :
    windowWidth(winWidth),
    windowHeight(winHeight)
{
    width = texture.width / maxFrames;
    height = texture.height; 
}

Vector2 Character::getScreenPos()
{
    // Vector Used to Draw Character to the Screen - Coordinates of the Upper-Left corner of the texture
    return Vector2{
        // Character Will Always Be Drawn in the Middle of the Screen
        static_cast<float>(windowWidth) / 2.0f - scale * (0.5f * width),  // X-Axis Start Position of Knight
        static_cast<float>(windowHeight) / 2.0f - scale * (0.5f * height) // Y-Axis Start Position of Knight
    };
}

void Character::tick(float deltaTime)
{
    if (!getAlive()) return;


    // Player Character Movement - done by moving the map rather than the character sprite
    if (IsKeyDown(KEY_A))
    {
        velocity.x -= 1.0;
    }
    if (IsKeyDown(KEY_D))
    {
        velocity.x += 1.0;
    }
    if (IsKeyDown(KEY_W))
    {
        velocity.y -= 1.0;
    }
    if (IsKeyDown(KEY_S))
    {
        velocity.y += 1.0;
    }

    BaseCharacter::tick(deltaTime);

    Vector2 swordOrigin{};
    Vector2 swordOffset{};
    float rotation{};
    if (faceRightLeft > 0.0f)
    {
        swordOrigin = { 0.0f, weapon.height * scale };
        swordOffset = { 35.0f, 55.0f };
        weaponCollisionRec = {
            getScreenPos().x + swordOffset.x,
            getScreenPos().y + swordOffset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? 35.0f : 0.0f;
    }
    else
    {
        swordOrigin = { weapon.width * scale, weapon.height * scale };
        swordOffset = { 25.0f, 55.0f };
        weaponCollisionRec = {
            getScreenPos().x + swordOffset.x - weapon.width * scale,
            getScreenPos().y + swordOffset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? -35.0f : 0.0f;
    }

    // Draw the Sword
    Rectangle source{ 0.0f, 0.0f, static_cast<float>(weapon.width) * faceRightLeft, static_cast<float>(weapon.height) };
    Rectangle dest { getScreenPos().x + swordOffset.x, getScreenPos().y + swordOffset.y, weapon.width * scale, weapon.height * scale };
    DrawTexturePro(weapon, source, dest, swordOrigin, rotation, WHITE);

    /*
    DrawRectangleLines(
        weaponCollisionRec.x,
        weaponCollisionRec.y,
        weaponCollisionRec.width,
        weaponCollisionRec.height,
        RED
    );
    */
}

void Character::takeDamage(float damage)
{
    health -= damage;
    if (health <= 0.0f)
    {
        setAlive(false);
    }
}
