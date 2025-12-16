#include <math.h>
#include <raylib.h>

#define GRASS_GREEN (Color){127, 255, 127, 255}
#define PLAYER_SPEED 5
#define PLAYER_SIZE 64
#define VECTOR2_ZERO (Vector2){0, 0}

typedef struct Textures {
  Texture2D dirtTexture;
  Texture2D grassTexture;
  Texture2D playerTexture;
} Textures;

typedef struct GameObject {
  Rectangle rect;
  Texture2D texture;
  Color tint;
} GameObject;

void DrawGameObject(GameObject gameObject, int playerX, int playerY,
                    int screenWidth, int screenHeight) {
  Rectangle sourceRect = {0, 0, gameObject.texture.width,
                          gameObject.texture.height};
  Rectangle destRect = {gameObject.rect.x - playerX + (int)(screenWidth / 2) -
                            (int)(gameObject.texture.width / 2),
                        gameObject.rect.y - playerY + (int)(screenHeight / 2) -
                            (int)(gameObject.texture.height / 2),
                        gameObject.rect.width, gameObject.rect.height};

  DrawTexturePro(gameObject.texture, sourceRect, destRect, VECTOR2_ZERO, 0.0f,
                 gameObject.tint);
}

void DrawGameObjects(int playerX, int playerY, int screenWidth,
                     int screenHeight, Textures textures) {

  GameObject bg[] = {(GameObject){.rect = {0, 0, 128, 128},
                                  .texture = textures.dirtTexture,
                                  .tint = WHITE},

                     (GameObject){.rect = {400, 0, PLAYER_SIZE, PLAYER_SIZE},
                                  textures.playerTexture,
                                  RED}};

  for (int i = 0; i < sizeof(bg) / sizeof(GameObject); i++) {
    DrawGameObject(bg[i], playerX, playerY, screenWidth, screenHeight);
  }
}

void DrawGameWorld(int playerX, int playerY, Textures textures) {
  const int screenWidth = GetScreenWidth();
  const int screenHeight = GetScreenHeight();

  // Draw background
  DrawTexturePro(textures.grassTexture,
                 (Rectangle){playerX, playerY, screenWidth, screenHeight},
                 (Rectangle){0, 0, screenWidth, screenHeight}, VECTOR2_ZERO,
                 0.0f, GRASS_GREEN);

  // Draw other objects
  DrawGameObjects(playerX, playerY, screenWidth, screenHeight, textures);
}

int main(void) {
  InitWindow(800, 800, "Game");
  SetTargetFPS(60);

  SetWindowState(FLAG_WINDOW_RESIZABLE);

  Textures textures;
  textures.dirtTexture = LoadTexture("textures/dirt.png");
  textures.grassTexture = LoadTexture("textures/grass.png");
  textures.playerTexture = LoadTexture("textures/player.png");

  int playerX = 0;
  int playerY = 0;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    const int longestSide =
        screenWidth > screenHeight ? screenWidth : screenHeight;

    int moveX = 0;
    int moveY = 0;

    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
      moveX += 1;
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
      moveX -= 1;
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
      moveY -= 1;
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
      moveY += 1;

    double magnitude = sqrt(moveX * moveX + moveY * moveY);

    moveX = moveX / magnitude * PLAYER_SPEED;
    moveY = moveY / magnitude * PLAYER_SPEED;

    playerX += moveX;
    playerY += moveY;

    const Rectangle characterRectangle = {
        (int)(screenWidth / 2 - PLAYER_SIZE / 2),
        (int)(screenHeight / 2 - PLAYER_SIZE / 2), PLAYER_SIZE, PLAYER_SIZE};
    const Rectangle playerRectangle = {0, 0, textures.playerTexture.width,
                                       textures.playerTexture.height};

    DrawGameWorld(playerX, playerY, textures);

    DrawTexturePro(textures.playerTexture, playerRectangle, characterRectangle,
                   VECTOR2_ZERO, 0.0f, GetColor(0xaa77ffff));

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
