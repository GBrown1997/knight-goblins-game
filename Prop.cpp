#include "Prop.h"
#include "raymath.h"

Prop::Prop(Vector2 pos, Texture2D tex) : 
    worldPos(pos), 
    texture(tex)
{

}

void Prop::Render(Vector2 playerKnightPos)
{
    Vector2 screenPos{ Vector2Subtract(worldPos, playerKnightPos) };
    DrawTextureEx(texture, screenPos, 0.0f, scale, WHITE);
}

Rectangle Prop::getCollisionRec(Vector2 playerKnightPos)
{
    Vector2 screenPos{ Vector2Subtract(worldPos, playerKnightPos) };
    return Rectangle{
        screenPos.x,
        screenPos.y,
        texture.width * scale,
        texture.height * scale
    };
}
