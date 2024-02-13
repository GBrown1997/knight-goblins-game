#include "raylib.h"
#include "raymath.h"

class Prop
{
public:
    Prop(Vector2 pos, Texture2D tex);
    void Render(Vector2 playerKnightPos);
    Rectangle getCollisionRec(Vector2 playerKnightPos);

private:
    Texture2D texture{};
    Vector2 worldPos{};
    float scale{ 4.0f };

};
