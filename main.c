#include <math.h>
#include <raylib.h>

int main(void) {
  InitWindow(800, 800, "Game");
  SetTargetFPS(60);

  SetWindowState(FLAG_WINDOW_RESIZABLE);
  // ToggleBorderlessWindowed();

  // Texture2D dirtTexture = LoadTexture("textures/dirt.png");
  Texture2D grassTexture = LoadTexture("textures/grass.png");
  Texture2D playerTexture = LoadTexture("textures/player.png");

  Vector2 Vector2Zero = {0, 0};

  int playerX = 0;
  int playerY = 0;

  const int playerSpeed = 5;
  const int playerSize = 64;

  const Color GRASS_GREEN = {127, 255, 127, 255};

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

    moveX = moveX / magnitude * playerSpeed;
    moveY = moveY / magnitude * playerSpeed;

    playerX += moveX;
    playerY += moveY;

    const int absPlayerX = screenWidth / 2 - playerSize / 2 + playerX;
    const int absPlayerY = screenHeight / 2 - playerSize / 2 + playerY;

    const Rectangle backgroundRectangle = {0, 0, longestSide, longestSide};
    const Rectangle grassRectangle = {0, 0, grassTexture.width,
                                      grassTexture.height};

    const Rectangle characterRectangle = {absPlayerX, absPlayerY, playerSize,
                                          playerSize};
    const Rectangle playerRectangle = {0, 0, playerTexture.width,
                                       playerTexture.height};

    DrawTexturePro(grassTexture, grassRectangle, backgroundRectangle,
                   Vector2Zero, 0.0f, GRASS_GREEN);

    DrawTexturePro(playerTexture, playerRectangle, characterRectangle,
                   Vector2Zero, 0.0f, GetColor(0xaa77ffff));

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
