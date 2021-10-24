//#include <stdio.h>
//#include "cprocessing.h"

//#define GOL_GRID_COLS 30
//#define GOL_GRID_ROWS 30
//#define GOL_GRID_BUFFERS 2
//
//#define GOL_ALIVE 1
//#define GOL_DEAD 0
//
//#define TRUE 1
//#define FALSE 0
//
//int gIsPaused;
//int gGrids[GOL_GRID_BUFFERS][GOL_GRID_ROWS][GOL_GRID_COLS];
//
///* Feel free to declare your own variables here */
//
//void game_init(void)
//{
//    /* Set every grids' cells as 'dead' */
//    for (int row = 0; row < GOL_GRID_ROWS; ++row) {
//        for (int col = 0; col < GOL_GRID_COLS; ++col) {
//            for (int i = 0; i < GOL_GRID_BUFFERS; ++i) {
//                gGrids[i][row][col] = GOL_DEAD;
//            }
//        }
//    }
//
//    /*********************************************************
//    *  Let's start with gGrids[0] as the 'reference grid'
//    *  and gGrids[1] as the 'displaying grid'.
//    *
//    *  We initialize gGrids[0] with a simple 'glider'.
//    *********************************************************/
//
//    gGrids[0][1][2] = GOL_ALIVE;
//    gGrids[0][2][3] = GOL_ALIVE;
//    gGrids[0][3][1] = GOL_ALIVE;
//    gGrids[0][3][2] = GOL_ALIVE;
//    gGrids[0][3][3] = GOL_ALIVE;
//
//    /* We start unpaused */
//    gIsPaused = FALSE;
//
//    /* Initialization of your other variables here */
//}
//
//void game_update(void)
//{
//
//}
//
//void game_exit(void)
//{
//
//}

#include <stdio.h>
#include "cprocessing.h"

int width;
int height;

struct character
{
	CP_Vector position;
	CP_Vector speed;
	CP_Vector yspeed;
	CP_Vector gravity;
	CP_Image sprite;
};
struct floor
{
	CP_Vector position;
	CP_Image sprite;
};
float gravity = 1.5f;
struct character player;
struct floor floor1;
float playerX = 100;
float playerY = 100;
float playerwidth = 100;
float playerheight = 100;
float groundwidth = 100;
float groundheight = 100;
float groundX = 50;
float groundY = 100;
int onground = 0;

void game_init(void)
{
	player.sprite = CP_Image_Load("./Assets/Player.png");//player(loading the image from asset folder)
	floor1.sprite = CP_Image_Load("./Assets/floor1.jpg");//ground(loading the image from asset folder)
	width = CP_System_GetWindowWidth();
	height = CP_System_GetWindowHeight();
	// Set position to the center of the screen
	player.position = CP_Vector_Set((float)CP_System_GetWindowHeight() / 2, (float)CP_System_GetWindowWidth() / 2);
	// Set speed to 50 in the x-direction
	player.speed = CP_Vector_Set(100.0f, 0.0f);
	player.yspeed = CP_Vector_Set(0.0f, 2000.0f);
	player.gravity = CP_Vector_Set(0.0f, 10.0f);
	//CP_System_ShowConsole();
}

void game_update(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 250, 0, 255));
	CP_Image_Draw(player.sprite, player.position.x, player.position.y, (float)width / 5, (float)width / 5, 255);//drawing the player sprite
	//temporary drawing of platform to test collision
	CP_Image_Draw(floor1.sprite, 100, 380, (float)width / 10, (float)width / 10, 255);//drawing the platform
	CP_Image_Draw(floor1.sprite, 140, 380, (float)width / 10, (float)width / 10, 255);//drawing the platform
	CP_Image_Draw(floor1.sprite, 180, 380, (float)width / 10, (float)width / 10, 255);//drawing the platform
	CP_Image_Draw(floor1.sprite, 220, 380, (float)width / 10, (float)width / 10, 255);//drawing the platform
	CP_Image_Draw(floor1.sprite, 100, 300, (float)width / 10, (float)width / 10, 255);//drawing the platform
	CP_Image_Draw(floor1.sprite, 100, 340, (float)width / 10, (float)width / 10, 255);//drawing the platform
	CP_Image_Draw(floor1.sprite, 140, 340, (float)width / 10, (float)width / 10, 255);//drawing the platform
	//controls
	if (CP_Input_KeyDown(KEY_D))
	{
		//printf("%.2f %.2f\n",player.position.x,player.position.y);
		player.position = CP_Vector_Add(player.position, CP_Vector_Scale(player.speed, CP_System_GetDt()));
		if (CP_Input_KeyTriggered(KEY_SPACE))
		{
			player.position = CP_Vector_Subtract(player.position, CP_Vector_Scale(player.yspeed, CP_System_GetDt()));
		}
	}
	else if (CP_Input_KeyDown(KEY_A)) 
	{
		//printf("%.2f %.2f\n",player.position.x,player.position.y);
		player.position = CP_Vector_Subtract(player.position, CP_Vector_Scale(player.speed, CP_System_GetDt()));
		if (CP_Input_KeyTriggered(KEY_SPACE))
		{
			player.position = CP_Vector_Subtract(player.position, CP_Vector_Scale(player.yspeed, CP_System_GetDt()));
		}
	}
	else if (CP_Input_KeyTriggered(KEY_SPACE)) 
	{
		//player.yspeed += player.gravity;
		player.position = CP_Vector_Subtract(player.position, CP_Vector_Scale(player.yspeed, CP_System_GetDt()));
	}

	//check to apply gravity onto player
	if (onground == 0) 
	{
		player.position.y += gravity;
	}
	if (onground == 1)
	{
		gravity = 0;
	}
	
		

	//collision check
	//if (playerY > groundY && playerY < groundY + groundheight)
	//{
	//	player.yspeed = CP_Vector_Set(0.0f,0.0f);
	//}
	//else
	//{
	//	player.yspeed = CP_Vector_Set(0.0f, 2000.0f);
	//}
	if (playerY + playerheight > groundY && (playerY + playerheight) < (groundY + groundheight) )
	{
		playerY = groundY - playerheight; //snap the bottom of player to the top of the ground
		onground = 1;
	}

	//else if (CP_Input_KeyReleased(KEY_SPACE))
	//{
	//	player.position = CP_Vector_Subtract(player.position, CP_Vector_Scale(player.gravity, CP_System_GetDt()));
	//}

	
}

void game_exit(void)
{

}
