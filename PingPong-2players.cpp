#include "raylib.h"
#include <iostream>

struct Paddle {
	float x, y;
	float speedx, speedy;
	float width, height;
	Color c;

	Rectangle rec()
	{
		return Rectangle{ x, y, width, height };
	}
	void draw()
	{
		DrawRectangleRec(rec(), c);
	}
};
// paddle that we do for drawinf the levels
Paddle p1[100]{};



struct Ball {
	float x, y;
	float speedx, speedy;
	float radius;

	void draw()
	{
		DrawCircle(x, y, radius, WHITE);
	}

};


void drawLevels(int i , int &add , int sub )
{
	p1[i].x = 300 + add;
	p1[i].y = GetScreenHeight() / 2 - sub;
	p1[i].width = 30;
	p1[i].height = 10;
	p1[i].c = GREEN;
	add += p1[i].width + 2;
}


int main()
{

	int timefruite = 0;
	InitWindow(800, 600, "pong-levels");
	// paddle postion and speed
	Paddle p;
	p.width = 100;
	p.height = 10;
	p.x = GetScreenWidth() / 2 - 50;
	p.y = GetScreenHeight() - 40;
	p.speedx = 500;
	p.speedy = 500;
	p.c = WHITE;
	// ball postion and speed 
	Ball ball;
	ball.x = GetScreenWidth() - 50 ;
	ball.y = GetScreenHeight() / 2 - 100;
	ball.radius = 5;
	ball.speedx = 200;
	ball.speedy = -600;
	// the  fruite which gives extra bounes for the player 
	Paddle fruite;
	fruite.x = GetScreenWidth() / 2;
	fruite.y = GetScreenHeight() / 2 + 40;
	fruite.width = 7;
	fruite.height = 7;
	fruite.c = YELLOW;

	int level = 1; // number of the level 
	int counter = 0; //  i use it for drawing the level 
	int add = 0; // i use it too for drawing the level 
	int sizetext = MeasureText("Press Space to Start", 30); //getting the size of the text 
	int Directiony = 0, Directionx = 0, Timer = 0, CalTimer = 6,Calcollision=0;
	bool steal = false;
	bool start = false;// for the fruite 
	InitAudioDevice(); // for the sounds 
	Sound sound1 = LoadSound("C:/Users/djaafaryessad/Downloads/ball_hitt_paddle.mp3"); // sound of the ball hitting the paddle	
	Sound sound2 = LoadSound("C:/Users/djaafaryessad/Downloads/ball_hitt_paddle.mp3");// sound of the ball hitting the buldingpaddles	
	Sound sound3 = LoadSound("C:/Users/djaafaryessad/Downloads/collectcoin.mp3");
	

		while (!WindowShouldClose() )
		{
			
				// draw the level one stage 
				if (level == 1 && counter == 0)
				{
					for (int i = 0; i < 18; i++)
					{
						if (counter < 6)
						{
							// draw the Base
							drawLevels(i, add, 0);
						}

						if (counter < 10 && counter >= 6)
						{
							if (counter == 6)
								add = 0;
							// draw the above of the base
							drawLevels(i, add, 12);

						}
						if (counter >= 10 && counter < 12)
						{
							if (counter == 10)
								add = 0;
							// draw the 3rd floor
							drawLevels(i, add, 12 * 2);

						}
						if (counter == 12)
						{
							add = 0;
							//draw the last floor
							drawLevels(i, add, 12 * 3);
						}
						counter++;

					}
				}
				// moving  the ball 
				ball.x += (ball.speedx + Directionx) * GetFrameTime();
				ball.y += (ball.speedy + Directiony * 2) * GetFrameTime();

				// moving the paddle left and right
				if (IsKeyDown(KEY_D))
				{
					p.x += p.speedx * GetFrameTime();
				}
				if (IsKeyDown(KEY_A))
				{
					p.x -= p.speedx * GetFrameTime();
				}
				// the ball when she hitting the walls
				if (ball.x < 0 || ball.x > GetScreenWidth())
				{
					Directionx = 0;
					Directiony = 0;
					if (ball.x < 0)
						ball.x = 0;
					if (ball.x > GetScreenWidth())
						ball.x = GetScreenWidth();
					ball.speedx *= -1;
					PlaySound(sound1);
				}
				if (ball.y < 0)
				{
					Directionx = 0;
					Directiony = 0;
					ball.y = 0;
					ball.speedy *= -1;
					PlaySound(sound1);
				}
				//checking the collision between the ball and the paddle 
				if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, p.rec()))
				{
					ball.speedy *= -1.01;
					// the ball is in the left 
					if (ball.x - (p.x + 50) < 0)
					{
						// moving the vectorx 
						if (ball.speedx > 0)
						{
							ball.speedx *= -1.01;
							Directionx = (ball.x - (p.x + 50));
						}
						else
						{
							// getting the direction of the ball is related to the postion of the ball in the paddle
							Directionx = (ball.x - (p.x + 50)) * -1;
						}
						// getting the direction for the angle that the ball should go with 
						Directiony = (ball.x - (p.x + 50)) * -1;

					}
					// the ball is in the right
					if (ball.x - (p.x + p.width / 2) > 0)
					{
						if (ball.speedx < 0)
						{
							ball.speedx *= -1.01;
							Directionx = (ball.x - (p.x + p.width / 2));

						}
						else
						{
							Directionx = (ball.x - (p.x + 50));
						}

						Directiony = (ball.x - (p.x + 50));
					}
					// playing the hitting ball sound 
					PlaySound(sound1);
					// get away from the clitch
					if (ball.y > GetScreenWidth() - 30)
						ball.speedy *= -1;


				}
				// all the way left or right is 50 when it close to the center is going to 0 
				DrawText(TextFormat("Dir : %d", Directionx), 30, 30, 20, WHITE);
				// level one stuff - deleting the paddles and checking the win  
				if (level == 1)
				{
					for (int i = 0; i <= 12; i++)
					{
						if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.radius, p1[i].rec()))
						{
							PlaySound(sound2);
							p1[i].x = GetScreenHeight() + GetRandomValue(0, 100);
							p1[i].y = GetScreenWidth() + GetRandomValue(0, 100);
							p1[i].width = 0;
							p1[i].height = 0;
							ball.speedy *= -1;
							Calcollision++;


						}
						if (Calcollision == 6 || steal)
						{
							
								fruite.y += 0.4;
								DrawRing(Vector2{ fruite.x,fruite.y }, 3, 5, 0, 360, 0, YELLOW);
								steal = true;

								if (CheckCollisionCircleRec(Vector2{ fruite.x,fruite.y }, 5, p.rec()))
								{
									
									p.width += 30;
									PlaySound(sound3);
									fruite.x = GetScreenWidth();
									fruite.y = GetScreenHeight() + 10;
									steal = false;
									timefruite = 0;
									
								}
							
						}
						timefruite += 1;
						DrawText(TextFormat("Time : %d", timefruite), 60, 20, 17,RED);
						if (timefruite / 1000 > 5 )
							p.width = 100;
						p1[i].draw();
						
					}


				}



				//  draw section 
				SetWindowState(FLAG_VSYNC_HINT); // seting the fps like the refresh of the screen 60hz 
				BeginDrawing();
				ClearBackground(BLACK);
				DrawFPS(10, 10); // drawing the fps
				p.draw(); // drwaing the paddle 
				ball.draw(); // drawing the ball	
				Timer++; // calculate the time 
				EndDrawing();
			}
		

		UnloadSound(sound1);
		UnloadSound(sound2);
		UnloadSound(sound3);
		CloseAudioDevice();
	}

