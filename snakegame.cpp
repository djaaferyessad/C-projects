#include "raylib.h"

const int width = 600;
const int height = 600;
const int size = 500;

void drawlines(float x1, float x2, float y1, float y2)
{
	DrawLineEx(Vector2{ x1,y1 }, Vector2{ x2,y2 }, 5, GREEN);
}

void drawHead(float x, float y, int radius, Color c)
{
	DrawCircle(x, y, radius, c);
}



float playerx[size], playery[size];



struct fruite {
	float x, y;
	float width, height;

	Rectangle rec()
	{
		return Rectangle{ x, y, width, height };
	}

	void draw()
	{
		DrawRectangleRec(rec(), YELLOW);
	}

};



int main()
{

	InitWindow(width, height, "snake");
	SetWindowState(FLAG_VSYNC_HINT);
	bool gameover = false;
	char prevKey;
	playerx[0] = GetScreenWidth() / 2;
	playery[0] = GetScreenHeight() / 2;


	int counter = 0;
	float prevX = 0, prevY = 0;
	fruite f;
	f.x = GetRandomValue(11, width - 11);
	f.y = GetRandomValue(11, height - 11);
	f.width = 8;
	f.height = 8;




	char key = 'w';
	while (!WindowShouldClose())
	{
		// restarting the game 
		if (IsKeyPressed(KEY_SPACE) && gameover)
		{
			playerx[0] = GetScreenWidth() / 2;
			playery[0] = GetScreenHeight() / 2;
			counter = 0;
			gameover = false;


		}

		// saving the vector x and y of the head 
		prevX = playerx[0];
		prevY = playery[0];

		// geting the input from the user 
		if (IsKeyPressed(KEY_W) && prevKey != 's')
		{
			key = 'w';
		}
		if (IsKeyPressed(KEY_S) && prevKey != 'w')
		{
			key = 's';
		}
		if (IsKeyPressed(KEY_D) && prevKey != 'a')
		{
			key = 'd';
		}
		if (IsKeyPressed(KEY_A) && prevKey != 'd')
		{
			key = 'a';
		}

		if (gameover)
		{
			key = 'g';
		}
		prevKey = key;


		// moving the head of the snake 
		switch (key)
		{
		case 'w':
			playery[0] -= 4;
			break;
		case 's':
			playery[0] += 4;
			break;
		case 'a':
			playerx[0] -= 4;
			break;
		case 'd':
			playerx[0] += 4;
			break;
		case 'g':
			break;

		}


		// adding the taill
		for (int i = 1; i <= counter; i++)
		{
			float tmpx = playerx[i];
			float tmpy = playery[i];
			playerx[i] = prevX;
			playery[i] = prevY;
			prevX = tmpx;
			prevY = tmpy;
		}


		// check the collision with him self
		for (int i = 1; i <= counter; i++)
		{

			if (playerx[0] == playerx[i] && playery[0] == playery[i])
			{
				gameover = true;
			}

		}
		// check collision with the wall 
		if (playerx[0] < 11 || playerx[0] > width + 11 || playery[0] < 11 || playery[0] > height - 11)
		{
			gameover = true;
		}



		// checking the collision between the snake the fruite 
		if (CheckCollisionCircleRec(Vector2{ (float)playerx[0],(float)playery[0] }, 11, f.rec()))
		{

			f.x = GetRandomValue(11, width - 10);
			f.y = GetRandomValue(11, height - 10);
			counter++;


		}





		// drawing  all the things we need 
		BeginDrawing();
		ClearBackground(BLACK);
		drawlines(0, width, 1, 1); // the up line 
		drawlines(1, 1, 0, height); // the left line 
		drawlines(0, width, height, height); // the the down line 
		drawlines(width - 1, width - 1, 0, height); // the right line 
		DrawText(TextFormat("Score: %d", counter), GetScreenWidth() / 2 - 60, 10, 30, RED); // drawinf the score 
		f.draw(); // drawing the fruite 
		drawHead(playerx[0], playery[0], 11, BLUE); // drawing the headof the snake 
		for (int i = 1; i <= counter; i++)
		{
			drawHead(playerx[i], playery[i], 6, WHITE); // draweing the taill of the snake 
		}
		if (gameover == true)
		{
			// draw  the gameover section 
			const char* text = "if u want to restart the game press space ";
			int sizetezt = MeasureText(text, 22);
			DrawText(" Game Over !!!", GetScreenWidth() / 2 - 160, GetScreenHeight() / 2, 30, PURPLE);
			DrawText(text, GetScreenWidth() / 2 - sizetezt / 2, GetScreenHeight() / 2 - 30, 22, BROWN);
		}
		EndDrawing();
	}
}



























/*#include "raylib.h"




int main()
{
	InitWindow(800, 600, "pong-levels");
	SetTargetFPS(60);
	while (!WindowShouldClose)
	{
		BeginDrawing();
		ClearBackground(BLACK);
		DrawFPS(10, 10);
		EndDrawing();



	}
	*/
