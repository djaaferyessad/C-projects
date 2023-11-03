#include "raylib.h"

struct Ball {
	float x, y;
	float speedx, speedy;
	int radius;


	void draw()
	{
		DrawCircle((int)x, (int)y, radius, WHITE);
	}
};

struct Paddle {
	float x, y;
	float speedx, speedy;
	float width, height;
	float X, Y;
	Rectangle rec() {

		return Rectangle{ x + GetScreenWidth() / 2 - height / 2 - width ,y - height / 2,width, height };
	}

	void draw()
	{
		DrawRectangleRec(rec(), WHITE);
	}

};

const int height = 600;
const int width = 800;
const char* textwinner = nullptr;
int sizeText, scoreLeft, scoreRight, score;



int main()
{
	InitWindow(width, height, "Pong");
	SetWindowState(FLAG_VSYNC_HINT);
	Ball ball;
	ball.x = GetScreenWidth() / 2;
	ball.y = GetScreenHeight() / 2;
	ball.radius = 5;
	ball.speedx = 300;
	ball.speedy = 300;

	Paddle paddleleft;
	paddleleft.x = 110 - GetScreenWidth() / 2;
	paddleleft.y = GetScreenHeight() / 2;
	paddleleft.width = 10;
	paddleleft.height = 100;
	paddleleft.speedx = 500;
	paddleleft.speedy = 500;
	paddleleft.Y = paddleleft.y - paddleleft.height / 2;
	paddleleft.X = paddleleft.x + GetScreenWidth() / 2 - paddleleft.height / 2 - paddleleft.width;


	Paddle paddleright;
	paddleright.x = GetScreenWidth() / 2;
	paddleright.y = GetScreenWidth() / 2;
	paddleright.width = 10;
	paddleright.height = 100;
	paddleright.speedx = 500;
	paddleright.speedy = 500;
	paddleright.Y = paddleright.y - paddleright.height / 2;
	paddleright.X = paddleright.x + GetScreenWidth() / 2 - paddleright.height / 2 - paddleright.width;







	while (!WindowShouldClose())
	{
		ball.x += (ball.speedx * GetFrameTime());
		ball.y += (ball.speedy * GetFrameTime());

		if (ball.y > height)
		{
			ball.speedy *= -1;
		}
		if (ball.y < 0)
		{
			ball.speedy *= -1;
		}
		if (IsKeyDown(KEY_W))
		{
			paddleleft.y -= paddleleft.speedy * GetFrameTime();
		}
		if (IsKeyDown(KEY_S))
		{
			paddleleft.y += paddleleft.speedy * GetFrameTime();
		}
		if (IsKeyDown(KEY_UP))
		{
			paddleright.y -= paddleright.speedy * GetFrameTime();
		}
		if (IsKeyDown(KEY_DOWN))
		{
			paddleright.y += paddleright.speedy * GetFrameTime();
		}
		if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.radius, Rectangle{ paddleright.rec() }))
		{
			if (ball.x < 760)
				ball.speedx *= -1.1;

			if (ball.y - paddleright.y > 0)
			{
				if (ball.speedy > 0)
				{
					// going up 
					ball.speedy *= 1.1;

				}
				else
				{
					ball.speedy *= -1.1;
				}
				// Down

			}
			if (ball.y - paddleright.y < 0)
			{
				if (ball.speedy > 0)
				{
					// going down 
					ball.speedy *= -1.1;

				}
				else
				{
					ball.speedy *= 1.1;
				}

				// UP 

			}

		}
		if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.radius, Rectangle{ paddleleft.rec() }))
		{
			if (ball.x > 40)
				ball.speedx *= -1.1;

			if (ball.y - paddleleft.y > 0)
			{
				if (ball.speedy > 0)
					ball.speedy *= 1.1;
				else
				{
					ball.speedy *= -1.1;
				}

			}
			if (ball.y - paddleleft.y < 0)
			{
				if (ball.speedy > 0)
					ball.speedy *= -1.1;
				else
				{
					ball.speedy *= 1.1;
				}

			}

		}

		if (ball.x < 0 || ball.x > width)
		{

			if (ball.x < 0)
			{
				textwinner = "Right Player Wins!";
				sizeText = MeasureText(textwinner, 60);

			}
			else
			{
				textwinner = "Left Player Wins!";
				sizeText = MeasureText(textwinner, 60);


			}

			if (IsKeyPressed(KEY_SPACE))
			{
				if (textwinner == "Right Player Wins!")
				{
					scoreRight++;
					score++;
				}
				if (textwinner == "Left Player Wins!")
				{
					scoreLeft++;
					score++;
				}
				ball.x = GetScreenWidth() / 2;
				ball.y = GetScreenHeight() / 2;
				ball.radius = 5;
				if (score % 2 == 0)
					ball.speedx = 300;
				else
					ball.speedx = -300;
				ball.speedy = 300;
				textwinner = nullptr;

			}
		}

		BeginDrawing();
		ClearBackground(BLACK);
		DrawFPS(10, 10);
		ball.draw();
		paddleleft.draw();
		paddleright.draw();
		DrawText(textwinner, GetScreenWidth() / 2 - sizeText / 2, GetScreenHeight() / 2 - 30, 60, SKYBLUE);
		DrawText(TextFormat("Score : %d", scoreLeft), GetScreenWidth() / 2 - 60, 10, 30, RED);
		DrawText(TextFormat(" - %d", scoreRight), GetScreenWidth() / 2 + 80, 10, 30, RED);

		EndDrawing();

	}




}