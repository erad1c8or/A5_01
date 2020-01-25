/*Things to do...
Rationalize use of name spaces...
Change co-ordinate system so that logic and rendering work, scale to higher resolutions, and are not dependent upon the Display/Window size.
Classes
Link Lists
Virtual Functions
*/


#include "maingameloop.hpp"
#include "explosion.hpp"
//#include "setupart.hpp"


/*globals*/
bool keys[8]{ false, false, false, false, false, false, false, false };	//Set all keys to not pressed



const int NumPlyr1Bullets = 10;
const int NumComets = 10;
const int NumParticles = 100;
const int NumPoints = 3;		//Redundant???? - Think this was used for a Triangle array of some sorts but not sure.



int imageRad = 20;	//dimensions for bitmap

//Rotation... temporarily moved to globals
int image2Width = 0;
int image2Height = 0;
float image2Degree = 0;


int image3Width = 0;
int image3Height = 0;
//float image3Height = 0;


int image4Width = 0;
int image4Height = 0;




/*ALLEGRO variables*/
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_BITMAP *image = NULL;
ALLEGRO_BITMAP *image2 = NULL;
ALLEGRO_BITMAP *image3 = NULL;
ALLEGRO_BITMAP *image4 = NULL;
ALLEGRO_BITMAP *DragonAnim[MaxFrame];	//Define Array for Rudimentary Animation

ALLEGRO_EVENT_QUEUE *event_que = NULL;
ALLEGRO_TIMER *gamelooptimer = NULL;
ALLEGRO_KEYBOARD_STATE keyState;



/*Define/Create Objects*/
SpaceShip plyr1;	//create object of type SpaceShip named plyr1
Explosion DefenderSplosion[NumParticles];	//create object of type Explosion named defendersplosion

/*object variables*/
//SpaceShip plyr1;	//plyr1 is an object of structure type SpaceShip
//SpaceShip plyr2;	//plyr2 is an object of structure type SpaceShip
//Bullet PlyrBullets[NumPlyr1Bullets]; //PlyrBullets is an array of type Bullet, and the size of the array is... NumPlyr1Bullets
//Comet comets[NumComets];
// !!! Thanks for the great videos! I suggest you to change Bullet bullets[5]; to Bullet bullets[NUM_BULLETS]; and use sizeof(bullet) besides of int size! :)



/*function prototypes - C++ requires functions to be declared before they are called and these are called function prototypes*/
//void InitPlyrShip(SpaceShip &someSpaceShip);	//declare/fwd define & pass by reference
void DrawShip(SpaceShip &someSpaceShip);
void MoveShipUp(SpaceShip &someSpaceShip);
void MoveShipDown(SpaceShip &someSpaceShip);
void MoveShipLeft(SpaceShip &someSpaceShip);
void MoveShipRight(SpaceShip &someSpaceShip);
float RotateShipLeft(float image2Degree);
float RotateShipRight(float image2Degree);

void InitBullet(Bullet someBullets[], int NumBullets);
void FireBullet(Bullet someBullets[], int NumBullets, SpaceShip &someSpaceShip);
void DrawBullet(Bullet someBullets[], int NumBullets);	//
void UpdateBullet(Bullet someBullets[], int NumBullets);
void InitComet(Comet comets[], int size);
void SpawnComet(Comet comets[], int size);
void DrawComet(Comet comets[], int size);
void UpdateComet(Comet comets[], int size);
void CollideBullet(Bullet PlyrBullets[], int NumBullets, Comet comets[], int cometSize, SpaceShip &someSpaceShip);
void CollideComet(Comet comets[], int cometSize, SpaceShip &someSpaceShip);							//cometSize is NumComets kinda... Active Comets might be a better name

void DrawEdgesOfDisplay(ALLEGRO_DISPLAY *&display);
void DrawCircle(ALLEGRO_DISPLAY *&display);
void RacingCarFloatPoint(ALLEGRO_DISPLAY *&display);
void RacingCarFixedPoint(ALLEGRO_DISPLAY *&display);
void AsteroidsFloatPoint(ALLEGRO_DISPLAY *&display);
void BiplaneFloatPoint(ALLEGRO_DISPLAY *&display, SpaceShip &someSpaceShip);


void CircleFadeEffect(ALLEGRO_DISPLAY *&display, SpaceShip &someSpaceShip, float Scale);
void draw_special_circle(float cx, float cy, float radius, ALLEGRO_COLOR outer_color, ALLEGRO_COLOR center_color);




//void DrawPolygonTriangle();

//void draw_circle(int DisplayWidth, int DisplayHeight, ALLEGRO_DISPLAY(display));
//std::tuple<int,int,int,float,float> draw_circle(int x, int y, int length, float angle, float angle_stepsize);




int main(void)
{

	/*primitive variables*/
	bool quitapp = false;
	bool redraw = true;	//the bool named 'redraw' is used to ensure we render per the timer, but to move the rendering outside of the timer event handler
	bool isGameOver = false;
	//plyr1.lives = 3;	//temporary hack to set plyr1.lives = 3



	//Scaling
	float Scale = 100;



	/*
	ALLEGRO_COLOR white = al_map_rgb_f(1, 1, 1);
	ALLEGRO_VERTEX v[15] = {
	{.x = 128,.y = 0,.z = 0,.color = white,.u = 128,.v = 0},
	{.x = 0,.y = 256,.z = 0,.color = white,.u = 0,.v = 256},
	{.x = 256,.y = 256,.z = 0,.color = white,.u = 256,.v = 256} };
	//al_draw_prim(v, NULL, texture, 0, 3, ALLEGRO_PRIM_TRIANGLE_LIST);
	*/




	/*initialize allegro*/
	if (!al_init())
	{
		al_show_native_message_box(NULL, "ERROR", "ERROR", "failed to initialize allegro!", NULL, NULL);
		return -1;
		/*Upon error the al_show_native_message_box does not display the specified error message unless text is specified for the third parameter.
		for example... al_show_native_message_box(NULL, “ERROR”, “ERROR”,“Failed to initialize allegro!”, NULL, NULL);*/
	}

	/*setup & initialize allegro display*/
	al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_REQUIRE);	//int option, int value, int importance... 
	/*
	the line above forces vsync to be on and sets the option, valu and importance as noted below
	option = 26 = ALLEGRO_VSYNC
	value = 1 means force on... 2 means forced off and 0 means default behaviour that may be on or off
	importance = 1 means ALLEGRO_REQUIRE... Other options are 2 = ALLEGRO_SUGGEST and 0 = ALLEGRO_DONTCARE
	*/
	display = al_create_display(DisplayWidth, DisplayHeight);
	if (!display)
	{
		al_show_native_message_box(NULL, "ERROR", "ERROR!", "failed to initialize display!", NULL, NULL);
		return -1;
	}


	/*initialize allegro addons*/
	al_install_keyboard();
	al_install_mouse();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_init_image_addon();

	//At some time I should add error checking to these.


	/*setup fonts*/
	//ALLEGRO_FONT* font = al_create_builtin_font();
	ALLEGRO_FONT *bebasneuereg24pt = al_load_font("Assets/BebasNeue_Reg.ttf", 24, 0);
	//ALLEGRO_FONT *bebasneuereg16pt = al_load_font("BebasNeue_Reg.ttf", 16, 0);



	//SetupArt();

	//Render Ship As Bitmap that will be blitted (bit block transfer) to the display
	image = al_create_bitmap(imageRad * 2, imageRad * 2);
	al_set_target_bitmap(image);
	//al_clear_to_color(al_map_rgb(125, 125, 125));	//test code to show bitmap total area
	al_draw_filled_rectangle(imageRad, imageRad - 9, imageRad + 10, imageRad - 7, al_map_rgb(255, 0, 0));
	al_draw_filled_rectangle(imageRad, imageRad + 9, imageRad + 10, imageRad + 7, al_map_rgb(255, 0, 0));
	al_draw_filled_triangle(imageRad - 12, imageRad - 17, imageRad + 12, imageRad, imageRad - 12, imageRad + 17, al_map_rgb(0, 255, 0));
	al_draw_filled_rectangle(imageRad - 12, imageRad - 2, imageRad + 15, imageRad + 2, al_map_rgb(0, 0, 255));
	al_set_target_bitmap(al_get_backbuffer(display));


	image2 = al_load_bitmap("Assets/Plane_sRGB2.png");
	image2Width = al_get_bitmap_width(image2);
	image2Height = al_get_bitmap_height(image2);


	image3 = al_load_bitmap("Assets/circle_fill_2.png");
	image3Width = al_get_bitmap_width(image3);
	image3Height = al_get_bitmap_height(image3);


	image4 = al_load_bitmap("Assets/dragon_jjh.bmp");
	image4Width = al_get_bitmap_width(image4);
	image4Height = al_get_bitmap_height(image4);
	al_convert_mask_to_alpha(image4, al_map_rgb(106, 76, 48));	//assign defined color to alpha


	/*Rudimentary Anim*/
	//for (int i = 0; i < MaxFrame + 1; i++)
	DragonAnim[0] = al_load_bitmap("Assets/Dragon00.bmp");
	DragonAnim[1] = al_load_bitmap("Assets/Dragon01.bmp");
	DragonAnim[2] = al_load_bitmap("Assets/Dragon02.bmp");
	DragonAnim[3] = al_load_bitmap("Assets/Dragon03.bmp");
	DragonAnim[4] = al_load_bitmap("Assets/Dragon04.bmp");
	DragonAnim[5] = al_load_bitmap("Assets/Dragon05.bmp");
	DragonAnim[6] = al_load_bitmap("Assets/Dragon06.bmp");
	DragonAnim[7] = al_load_bitmap("Assets/Dragon07.bmp");
	DragonAnim[8] = al_load_bitmap("Assets/Dragon08.bmp");
	for (int i = 0; i < MaxFrame; i++)
		al_convert_mask_to_alpha(DragonAnim[i], al_map_rgb(106, 76, 48));	//assign defined color to alpha







	//const int MaxFrame = 8;
	//int CurrFrame = 0;
	//int FrameCount = 0;
	//int FrameDelay = 5;



	/*initialize objects*/
	//srand(time(NULL));	//seed the random number generator
	InitPlyrShip(plyr1);	//initialize plyr1 object
	//InitShip(plyr2);	//initialize ship for plyr2
	//InitBullet(PlyrBullets, NumPlyr1Bullets);	//initialize bullets for plyr1
	//InitComet(comets, NumComets);	//initialize comets






	/*Create Event Queue, Timer & Register Events to the Queue*/
	event_que = al_create_event_queue();	//create event queue
	gamelooptimer = al_create_timer(1.0 / FPS);		//declare???, create timer and set interval = 1 second / FPS... 1/60 = 60 FPS
	if (!gamelooptimer)
	{
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}
	al_register_event_source(event_que, al_get_keyboard_event_source());	//get keyboard event and register to the applicable queue
	al_register_event_source(event_que, al_get_mouse_event_source());	//get mouse event and register to the applicable queue
	al_register_event_source(event_que, al_get_display_event_source(display));
	al_register_event_source(event_que, al_get_timer_event_source(gamelooptimer));	//register timer event to the event_que


	/*Start Game Loop*/

	al_start_timer(gamelooptimer);	//start timer and main loop immediately follows
	while (!quitapp)	//while variable quitapp is false
	{
		//al_wait_for_vsync();	//commented out as this always occurs once when flipdisplay
		ALLEGRO_EVENT event; //Declare event var
		//std::cout << "start of loop" << endl;

		al_wait_for_event(event_que, &event);    //wait for an event from event_que and send it the address of event

		if (event.type == ALLEGRO_EVENT_TIMER)	//update position of player every frame
		{
			redraw = true;	//the bool named 'redraw' is used to ensure we render per the timer, but the rendering is done outside of the timer event handler
			UpdateDefenderExplosion(DefenderSplosion, NumParticles);


			/* Rudimentary Animation*/
			if (++FrameCount >= FrameDelay)
			{
				if (++CurrFrame >= MaxFrame)
					CurrFrame = 0;

				FrameCount = 0;
			}


			if (keys[UP])
			{
				std::cout << "keys[UP]" << endl;
				Scale += 25.0f;	//for scaling test
			}
			if (keys[DOWN])
			{
				std::cout << "keys[DOWN]" << endl;
				Scale -= 25.0f;	//for scaling test
			}
			if (keys[LEFT])
			{
				std::cout << "keys[LEFT]" << endl;
				//image2Degree = RotateShipLeft(image2Degree);		//Old code to rotate an overhead spaceship, not the biplane and even then probably redundant now.
			}
			if (keys[RIGHT])
			{
				std::cout << "keys[RIGHT]" << endl;
				//image2Degree = RotateShipRight(image2Degree);		//Old code to rotate an overhead spaceship, not the biplane and even then probably redundant now.
			}
			if (keys[SPACE])
				std::cout << "keys[SPACE]" << endl;

			if (!isGameOver)
			{
				//std::cout << "GAME IN PROGRESS" << endl;

				if (plyr1.lives <= 0)
				{
					std::cout << "GAME OVER" << endl;
					isGameOver = true;
				}
			}
		}


		else if (event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (event.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				//plyr1.lives++;	//temporary means to increase plyr1.lives
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
				//InitDefenderExplosion(display, DefenderSplosion, NumParticles, DisplayWidth / 2, DisplayHeight / 2, 300);
				InitDefenderExplosion(DefenderSplosion, NumParticles, plyr1.posx, plyr1.posy, 300);
				break;
			case ALLEGRO_KEY_X:
				keys[X] = true;
				plyr1.lives--;	//temporary means to decrease plyr1.lives
				break;
			case ALLEGRO_KEY_ESCAPE:
				//std::cout << "ESC_KEY_DOWN" << endl;
				quitapp = true;
				break;
			}
		}
		else if (event.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (event.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			case ALLEGRO_KEY_ESCAPE:
				//std::cout << "ESC_KEY_UP" << endl;
				quitapp = true;
				break;
			}
		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)	//detect the display window being closed
		{
			quitapp = true;
		}



		//Rendertime
		if (redraw && al_is_event_queue_empty(event_que)) //only redraw if timer event fired and event_que is empty so we know the new position is representative of input
		{
			//std::cout << "RENDER TIME... Redraw=" << redraw << endl;
			redraw = false;	//the bool named 'redraw' is used to ensure we render per the timer, but to move the rendering outside of the timer event handler

			//std::cout << "plyr1.lives = " << plyr1.lives;
			//al_rest(3);

			if (!isGameOver)
			{

				al_draw_bitmap(image4, 100, 200, 0);
				al_draw_bitmap(DragonAnim[CurrFrame], 900, 200, 0);
				DrawDefenderExplosion(DefenderSplosion, NumParticles);
				BiplaneFloatPoint(display, plyr1);


				//CircleFadeEffect(display, plyr1, Scale);
				//al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);		//the default premultiplied alpha blenfding
				//al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ONE);				//additive blending
				//al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ZERO);				//copy blending
				//al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);	//transparency blending
				//al_set_blender(ALLEGRO_ADD, ALLEGRO_DEST_COLOR, ALLEGRO_ZERO);		//Multiplyn Blender
				draw_special_circle(plyr1.posx, plyr1.posy, Scale, al_map_rgba_f(1.0f, 0.0f, 0.0f, 1.0f), al_map_rgba_f(0.0f, 0.0f, 0.0f, 0.0f));	//Alpha Value of 1 = Opaque



				DrawEdgesOfDisplay(display);
				//al_draw_scaled_bitmap(image2, 0 , 0,  image2Width, image2Height, DisplayWidth / 2 - image2Width/2, DisplayHeight / 2 - image2Height/2, image2Width * scale, image2Height * scale, 0);
				//al_draw_rotated_bitmap(image2, image2Width / 2, image2Height / 2, DisplayWidth / 2, DisplayHeight / 2, image2Degree * PI / 180, 0);
				//al_draw_bitmap(image2, DisplayWidth/2-image2Width/2, DisplayHeight/2-image2Height/2, 0);
				//al_draw_bitmap(image, DisplayWidth/2, DisplayHeight/2, 0);

				al_draw_textf(bebasneuereg24pt, al_map_rgb(255, 0, 255), 50, DisplayHeight - 30, ALLEGRO_ALIGN_CENTRE, "LIVES: %i", plyr1.lives);
				al_draw_textf(bebasneuereg24pt, al_map_rgb(255, 0, 255), 300, DisplayHeight - 30, ALLEGRO_ALIGN_CENTRE, "plyr1.angle: %f", plyr1.angle);
				al_draw_textf(bebasneuereg24pt, al_map_rgb(255, 0, 255), 500, DisplayHeight - 30, ALLEGRO_ALIGN_CENTRE, "plyr1.length: %f", plyr1.length);
				al_draw_textf(bebasneuereg24pt, al_map_rgb(255, 0, 255), 670, DisplayHeight - 30, ALLEGRO_ALIGN_CENTRE, "Scale: %f", Scale);
			}
			else
			{
				//al_rest(0.10);
				//DrawPolygonTriangle();
				DrawCircle(display);
				//RacingCarFloatPoint(display);
				//RacingCarFixedPoint(display);
				//al_rest(25);
				al_draw_textf(bebasneuereg24pt, al_map_rgb(255, 0, 255), DisplayWidth / 2, DisplayHeight / 2, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
				al_draw_textf(bebasneuereg24pt, al_map_rgb(255, 0, 255), DisplayWidth / 2, DisplayHeight / 2 + 25, ALLEGRO_ALIGN_CENTRE, "PRESS ESC to Quit");
				/*al_get_keyboard_state(&keyState);
				if (al_key_down(&keyState, ALLEGRO_KEY_TAB))
					quitapp = true;
				else
				{
				}*/
			}
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));	//Clear the back buffer
		}
		//std::cout << "end of loop" << endl;
	}




	//cleanup
	al_destroy_timer(gamelooptimer);
	al_destroy_event_queue(event_que);
	al_destroy_display(display);	//Cleanup display... created via al_create_display
	al_destroy_font(bebasneuereg24pt);
	al_destroy_bitmap(image);
	al_destroy_bitmap(image2);
	al_destroy_bitmap(image3);
	al_destroy_bitmap(image4);
	for (int i = 0; i < MaxFrame; i++)
		al_destroy_bitmap(DragonAnim[i]);

	//al_destroy_font(bebasneuereg16pt);

	return true;
}



void DrawCircle(ALLEGRO_DISPLAY *&display)
/*DrawCircle()*/
{
	int x, y;
	int length = 100;
	float angle = -PI / 2;	//starting angle was originally 0.0
	float angle_stepsize = 0.1;

	// go through all angles from 0 to 2 * PI radians
	while (angle < 3 * PI / 2)	//was originally 2*PI
	{
		// calculate x, y from a vector with known length and angle
		x = length * cos(angle);
		y = length * sin(angle);

		al_draw_pixel(x + DisplayWidth / 2, y + DisplayHeight / 2, al_map_rgb(255, 0, 255));
		//drawpixel(screen,
			//x + SCREEN_W / 2, y + SCREEN_H / 2,
			//makecol(255, 255, 255));
		angle += angle_stepsize;
		al_flip_display();
		//al_rest(0.05);
		//int i;
		//cout << "Please enter an integer value: ";
		//cin >> i;
	}
}




void BiplaneFloatPoint(ALLEGRO_DISPLAY *&display, SpaceShip &someSpaceShip)
{
	//deceleration
	if (plyr1.length >= 10.0) plyr1.length -= 0.10;

	// check the keys and adjust length and angle of the objects velocity vector according to player input
	al_get_keyboard_state(&keyState);

	if (al_key_down(&keyState, ALLEGRO_KEY_W) && plyr1.length < 15.0)	//If accel (up) and speed < X then accelerate
		plyr1.length += 0.75;

	if (al_key_down(&keyState, ALLEGRO_KEY_S) && plyr1.length > -10.0)	//If braking (down) and speed > X then slow down
		plyr1.length -= 0.75;

	if (al_key_down(&keyState, ALLEGRO_KEY_A))
		plyr1.angle -= 0.06;

	if (al_key_down(&keyState, ALLEGRO_KEY_D))
		plyr1.angle += 0.06;


	// calculate the x- and y-coordinates of the velocity vector
	plyr1.velx = plyr1.length * cos(plyr1.angle);
	plyr1.vely = plyr1.length * sin(plyr1.angle);


	// move the object, and make sure it stays within the display
	plyr1.posx += plyr1.velx;
	if (plyr1.posx >= DisplayWidth) plyr1.posx -= DisplayWidth;
	if (plyr1.posx < 0) plyr1.posx += DisplayWidth;

	plyr1.posy += plyr1.vely;
	if (plyr1.posy >= DisplayHeight) plyr1.posy -= DisplayHeight;
	if (plyr1.posy < 0) plyr1.posy += DisplayHeight;

	// draw the object
	//al_draw_filled_circle(plyr1.posx, plyr1.posy, 25, al_map_rgb(0, 0, 255));
	al_draw_scaled_rotated_bitmap(image2, image2Width / 2, image2Height / 2, plyr1.posx, plyr1.posy, 0.3, 0.3, plyr1.angle, 0);
	al_draw_line(plyr1.posx, plyr1.posy, plyr1.posx + (plyr1.length + 5.0) * cos(plyr1.angle), plyr1.posy + (plyr1.length + 5.0) * sin(plyr1.angle), al_map_rgb(0, 255, 0), 1);
}






void CircleFadeEffect(ALLEGRO_DISPLAY *&display, SpaceShip &someSpaceShip, float Scale)
{
	/*
	Huge circle of Alpha, so whole screen is visible, until it scales down.
	Blend with black overlay, so black is left around the outside of the above alpha area.

	// calculate the x- and y-coordinates of the velocity vector
	plyr1.velx = plyr1.length * cos(plyr1.angle);
	plyr1.vely = plyr1.length * sin(plyr1.angle);


	// move the object, and make sure it stays within the display
	plyr1.posx += plyr1.velx;
	if (plyr1.posx >= DisplayWidth) plyr1.posx -= DisplayWidth;
	if (plyr1.posx < 0) plyr1.posx += DisplayWidth;

	plyr1.posy += plyr1.vely;
	if (plyr1.posy >= DisplayHeight) plyr1.posy -= DisplayHeight;
	if (plyr1.posy < 0) plyr1.posy += DisplayHeight;
	*/

	// draw the object
	//al_draw_filled_circle(plyr1.posx, plyr1.posy, 25, al_map_rgb(0, 0, 255));

	al_draw_scaled_rotated_bitmap(image3, image3Width / 2, image3Height / 2, plyr1.posx, plyr1.posy, Scale, Scale, plyr1.angle, 0);

}


void draw_special_circle(float cx, float cy, float radius, ALLEGRO_COLOR outer_color, ALLEGRO_COLOR center_color)
{
	struct ALLEGRO_VERTEX vertex_cache[ALLEGRO_VERTEX_CACHE_SIZE];		//x/y/z/u/v/color

	int NumSegments;

	assert(radius >= 0);		//abort if this is false
	//num_segments = ALLEGRO_PRIM_QUALITY * sqrtf(r);
	NumSegments = 100;	//just to see how this works

	if (NumSegments < 2)
		return;

	if (NumSegments >= ALLEGRO_VERTEX_CACHE_SIZE)
	{
		NumSegments = ALLEGRO_VERTEX_CACHE_SIZE - 1;
	}


	al_calculate_arc(&(vertex_cache[1].x), sizeof(ALLEGRO_VERTEX), cx, cy, radius, radius, 0, ALLEGRO_PI * 2, 0, NumSegments);

	//al_calculate_arc(&(vertex_cache[1].x), 2 * sizeof(float), cx, cy, radius, radius, 0, ALLEGRO_PI * 2, 0, NumSegments);

	vertex_cache[0].x = cx;
	vertex_cache[0].y = cy;
	vertex_cache[0].color = center_color;

	for (int i = 0; i < NumSegments + 1; i++)
	{
		vertex_cache[i].color = outer_color;
		vertex_cache[i].z = 0;
	}

	vertex_cache[0].color = center_color;		//Set color for shared vertex. This must come after the above. Not sure why yet.

	al_draw_prim(vertex_cache, NULL, NULL, 0, NumSegments + 1, ALLEGRO_PRIM_TRIANGLE_FAN);
	//al_draw_prim(vertex_cache, NULL, NULL, 0, NumSegments + 1, ALLEGRO_PRIM_POINT_LIST);

}





void AsteroidsFloatPoint(ALLEGRO_DISPLAY *&display)
{
	// length and angle of the racing car's velocity vector
	bool moving = true;
	float angle = -PI / 2;	//starting angle is top of circle
	float length = 0.0;

	// x- and y-coordinates of the velocity vector
	float vel_x, vel_y;

	// x- and y-position of the racing car
	float x = DisplayWidth / 2;
	float y = DisplayHeight / 2;

	while (moving)
	{

		//deceleration
		if (length > 10.0)
			length = length - 0.10;


		// check the keys and move the car
		al_get_keyboard_state(&keyState);

		if (al_key_down(&keyState, ALLEGRO_KEY_W) && length < 15.0)	//If accel (up) and speed < 100 then accelerate
			length += 0.75;

		//if (al_key_down(&keyState, ALLEGRO_KEY_S) && length > 0.0)	//If braking (down) and speed > 0 then slow down
			//length -= 0.25;

		if (al_key_down(&keyState, ALLEGRO_KEY_A))
			angle = (angle - 0.06);

		if (al_key_down(&keyState, ALLEGRO_KEY_D))
			angle = (angle + 0.06);


		// calculate the x- and y-coordinates of the velocity vector
		vel_x = length * cos(angle);
		vel_y = length * sin(angle);


		// move the car, and make sure it stays within the display
		x += vel_x;
		if (x >= DisplayWidth) x -= DisplayWidth;
		if (x < 0) x += DisplayWidth;

		y += vel_y;
		if (y >= DisplayHeight) y -= DisplayHeight;
		if (y < 0) y += DisplayHeight;

		// draw the racing car
		al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_REQUIRE);
		//al_draw_filled_circle(x, y, 25, al_map_rgb(0, 0, 255));
		al_draw_scaled_rotated_bitmap(image2, image2Width / 2, image2Height / 2, x, y, 0.3, 0.3, angle, 0);
		al_draw_line(x, y, x + (length + 5.0) * cos(angle), y + (length + 5.0) * sin(angle), al_map_rgb(0, 255, 0), 1);
		// wait for 10 milliseconds, or else we'd go too fast
		//al_rest(0.09);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));	//Clear the back buffer
	}
}








void RacingCarFloatPoint(ALLEGRO_DISPLAY *&display)
{
	// length and angle of the racing car's velocity vector
	bool moving = true;
	float angle = -PI / 2;	//starting angle is top of circle
	float length = 0.0;

	// x- and y-coordinates of the velocity vector
	float vel_x, vel_y;

	// x- and y-position of the racing car
	float x = DisplayWidth / 2;
	float y = DisplayHeight / 2;

	while (moving)
	{
		// erase the old image
		//circlefill(screen, fixtoi(x), fixtoi(y), 10, makecol(0, 0, 0));
		//al_draw_filled_circle(x, y, 25, al_map_rgb(0, 0, 0));
		//al_flip_display();

		// check the keys and move the car
		al_get_keyboard_state(&keyState);

		if (al_key_down(&keyState, ALLEGRO_KEY_W) && length < 10.0)	//If accel (up) and speed < 100 then accelerate
			length += 0.25;

		if (al_key_down(&keyState, ALLEGRO_KEY_S) && length > 0.0)	//If braking (down) and speed > 0 then slow down
			length -= 0.25;

		if (al_key_down(&keyState, ALLEGRO_KEY_A))
			angle = (angle - 0.1);

		if (al_key_down(&keyState, ALLEGRO_KEY_D))
			angle = (angle + 0.1);

		// calculate the x- and y-coordinates of the velocity vector
		vel_x = length * cos(angle);
		vel_y = length * sin(angle);


		// move the car, and make sure it stays within the screen
		x += vel_x;
		if (x >= DisplayWidth) x -= DisplayWidth;
		if (x < 0) x += DisplayWidth;

		y += vel_y;
		if (y >= DisplayHeight) y -= DisplayHeight;
		if (y < 0) y += DisplayHeight;

		// draw the racing car
		//al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_REQUIRE);
		//circle(screen, fixtoi(x), fixtoi(y), 10, makecol(0, 0, 255));
		al_draw_filled_circle(x, y, 25, al_map_rgb(0, 0, 255));
		//line(screen, 
		al_draw_line(x, y, x + (length + 5.0) * cos(angle), y + (length + 5.0) * sin(angle), al_map_rgb(255, 0, 0), 1);
		// wait for 10 milliseconds, or else we'd go too fast
		//al_rest(0.09);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));	//Clear the back buffer
	}
}









void RacingCarFixedPoint(ALLEGRO_DISPLAY *&display)
{
	// length and angle of the racing car's velocity vector
	bool moving = true;
	al_fixed angle = al_itofix(0);
	al_fixed length = al_itofix(0);

	// x- and y-coordinates of the velocity vector
	al_fixed vel_x, vel_y;

	// x- and y-position of the racing car
	al_fixed x = al_itofix(DisplayWidth / 2);
	al_fixed y = al_itofix(DisplayHeight / 2);

	while (moving)
	{
		// erase the old image
		//circlefill(screen, fixtoi(x), fixtoi(y), 10, makecol(0, 0, 0));
		al_draw_filled_circle(al_fixtoi(x), al_fixtoi(y), 35, al_map_rgb(0, 0, 0));
		al_flip_display();

		// check the keys and move the car
		al_get_keyboard_state(&keyState);

		if (al_key_down(&keyState, ALLEGRO_KEY_W) && length < al_itofix(30))	//If accel (up) and speed < 100 then accelerate
			length += al_ftofix(0.25);

		if (al_key_down(&keyState, ALLEGRO_KEY_S) && length > al_itofix(0))	//If braking (down) and speed > 0 then slow down
			length -= al_ftofix(0.25);

		if (al_key_down(&keyState, ALLEGRO_KEY_A))
			angle = (angle - al_itofix(5)) & 0xFFFFFF;

		if (al_key_down(&keyState, ALLEGRO_KEY_D))
			angle = (angle + al_itofix(5)) & 0xFFFFFF;

		// calculate the x- and y-coordinates of the velocity vector
		vel_x = al_fixmul(length, al_fixcos(angle));
		vel_y = al_fixmul(length, al_fixsin(angle));


		// move the car, and make sure it stays within the screen
		x += vel_x;
		if (x >= al_itofix(DisplayWidth)) x -= al_itofix(DisplayWidth);
		if (x < al_itofix(0)) x += al_itofix(DisplayWidth);
		y += vel_y;
		if (y >= al_itofix(DisplayHeight)) y -= al_itofix(DisplayHeight);
		if (y < al_itofix(0)) y += al_itofix(DisplayHeight);

		// draw the racing car
		//al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_REQUIRE);
		//circle(screen, fixtoi(x), fixtoi(y), 10, makecol(0, 0, 255));
		al_draw_filled_circle(al_fixtoi(x), al_fixtoi(y), 25, al_map_rgb(0, 0, 255));
		//line(screen, 
		al_draw_line(al_fixtof(x), al_fixtof(y), al_fixtof(x + al_fixtof(length + al_itofix(5)) * al_fixcos(angle)), al_fixtof(y + al_fixtof(length + al_itofix(5)) * al_fixsin(angle)), al_map_rgb(255, 0, 0), 1);
		// wait for 10 milliseconds, or else we'd go too fast
		//al_rest(0.09);
		al_flip_display();
	}
}






void DrawEdgesOfDisplay(ALLEGRO_DISPLAY *&display)
{
	//float left_x = 0.5;  Original
	float left_x = 0.1;
	float rght_x = al_get_display_width(display);	// -0.5;
	float top_y = 0.1;
	float bottom_y = al_get_display_height(display); // - 0.5;
	ALLEGRO_COLOR color = al_map_rgb(255, 0, 0);
	float thickness = 1.0;

	//al_clear_to_color(al_map_rgb(255, 255, 255));
	al_draw_line(left_x, top_y, rght_x, top_y, color, thickness);	//Top
	al_draw_line(left_x, top_y, left_x, bottom_y, color, thickness);	//Left
	//al_draw_line(rght_x, top_y, rght_x, bottom_y, color, thickness);	//Right - has bug
	al_draw_line(rght_x, top_y, rght_x, bottom_y, color, thickness);	//Right
	//al_draw_line(left_x, bottom_y, rght_x, bottom_y, color, thickness);	//bottom - has bug
	al_draw_line(left_x, bottom_y, rght_x, bottom_y, color, thickness);	//bottom
}










void DrawShip(SpaceShip &someSpaceShip)	//DrawShip Function, don't return anything because its doing it by reference so all changes stay
{
	al_draw_filled_rectangle(someSpaceShip.posx, someSpaceShip.posy - 9, someSpaceShip.posx + 10, someSpaceShip.posy - 7, al_map_rgb(255, 0, 0));
	al_draw_filled_rectangle(someSpaceShip.posx, someSpaceShip.posy + 9, someSpaceShip.posx + 10, someSpaceShip.posy + 7, al_map_rgb(255, 0, 0));
	al_draw_filled_triangle(someSpaceShip.posx - 12, someSpaceShip.posy - 17, someSpaceShip.posx + 12, someSpaceShip.posy, someSpaceShip.posx - 12, someSpaceShip.posy + 17, al_map_rgb(0, 255, 0));
	al_draw_filled_rectangle(someSpaceShip.posx - 12, someSpaceShip.posy - 2, someSpaceShip.posx + 15, someSpaceShip.posy + 2, al_map_rgb(0, 0, 255));
}



void MoveShipUp(SpaceShip &someSpaceShip)
{
	someSpaceShip.posy -= someSpaceShip.speed;
	if (someSpaceShip.posy < 17)
		someSpaceShip.posy = 17;
}


void MoveShipDown(SpaceShip &someSpaceShip)
{
	someSpaceShip.posy += someSpaceShip.speed;
	if (someSpaceShip.posy > DisplayHeight - 17)
		someSpaceShip.posy = DisplayHeight - 17;
}


void MoveShipLeft(SpaceShip &someSpaceShip)
{
	someSpaceShip.posx -= someSpaceShip.speed;
	if (someSpaceShip.posx < 20)
		someSpaceShip.posx = 20;
}


void MoveShipRight(SpaceShip &someSpaceShip)
{
	someSpaceShip.posx += someSpaceShip.speed;
	if (someSpaceShip.posx > 300)
		someSpaceShip.posx = 300;
}


float RotateShipLeft(float ShipRotation)
{
	//std::cout << ShipRotation << endl;
	//al_rest(0.25);
	ShipRotation -= 10;
	if (ShipRotation < 0)
		ShipRotation = 360 - 10;
	return ShipRotation;
}



float RotateShipRight(float ShipRotation)
{
	ShipRotation += 10;
	if (ShipRotation > 360)
		ShipRotation = 0;
	return ShipRotation;
}





void InitBullet(Bullet someBullets[], int NumBullets)	//
{
	for (int i = 0; i < NumBullets; i++)
	{
		someBullets[i].id = BULLET;
		someBullets[i].speed = 10;
		someBullets[i].live = false;
	}
}


void FireBullet(Bullet someBullets[], int NumBullets, SpaceShip &someSpaceShip)
{
	for (int i = 0; i < NumBullets; i++)
	{
		if (!someBullets[i].live)
		{
			someBullets[i].posx = someSpaceShip.posx + 17;
			someBullets[i].posy = someSpaceShip.posy;
			someBullets[i].live = true;
			break;
		}
	}
}


void DrawBullet(Bullet someBullets[], int NumBullets)	//
{
	for (int i = 0; i < NumBullets; i++)
	{
		if (someBullets[i].live)
			al_draw_filled_circle(someBullets[i].posx, someBullets[i].posy, 2, al_map_rgb(255, 255, 255));
	}
}


void UpdateBullet(Bullet someBullets[], int NumBullets)
{
	for (int i = 0; i < NumBullets; i++)
	{
		if (someBullets[i].live)
		{
			someBullets[i].posx += someBullets[i].speed;
			if (someBullets[i].posx > DisplayWidth)
				someBullets[i].live = false;
		}
	}
}


void CollideBullet(Bullet someBullets[], int NumBullets, Comet comets[], int cometSize, SpaceShip &someSpaceShip)
{
	for (int i = 0; i < NumBullets; i++)
	{
		if (someBullets[i].live)
		{
			for (int j = 0; j < cometSize; j++)
			{
				if (comets[j].live)
				{
					if (someBullets[i].posx > (comets[j].posx - comets[j].boundx) &&
						someBullets[i].posx < (comets[j].posx + comets[j].boundx) &&
						someBullets[i].posy >(comets[j].posy - comets[j].boundy) &&
						someBullets[i].posy < (comets[j].posy + comets[j].boundy))
					{
						someBullets[i].live = false;
						comets[j].live = false;
						someSpaceShip.score++;
					}
				}
			}
		}
	}
}



void InitComet(Comet comets[], int size)
{
	for (int i = 0; i < size; i++)
	{
		comets[i].id = ENEMY;
		comets[i].live = false;
		comets[i].speed = 5;
		comets[i].boundx = 18;
		comets[i].boundy = 18;
	}
}


void SpawnComet(Comet comets[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (!comets[i].live)
		{
			if (rand() % 50 == 0)
			{
				comets[i].live = true;
				comets[i].posx = DisplayWidth;
				comets[i].posy = 30 + rand() % (DisplayHeight - 60);

				break;
			}
		}
	}
}


void DrawComet(Comet comets[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (comets[i].live)
		{
			al_draw_filled_circle(comets[i].posx, comets[i].posy, 20, al_map_rgb(255, 0, 0));
		}
	}
}


void UpdateComet(Comet comets[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (comets[i].live)
		{
			comets[i].posx -= comets[i].speed;

			if (comets[i].posx < 0)
				comets[i].live = false;
		}
	}
}


void CollideComet(Comet comets[], int cometSize, SpaceShip &someSpaceShip)
{
	for (int i = 0; i < cometSize; i++)
	{
		if (comets[i].live)
		{
			if (comets[i].posx - comets[i].boundx < someSpaceShip.posx + someSpaceShip.boundx &&
				comets[i].posx + comets[i].boundx > someSpaceShip.posx - someSpaceShip.boundx &&
				comets[i].posy - comets[i].boundy < someSpaceShip.posy + someSpaceShip.boundy &&
				comets[i].posy + comets[i].boundy > someSpaceShip.posy - someSpaceShip.boundy)
			{
				someSpaceShip.lives--;
				comets[i].live = false;
			}
			/*else if (comets[i].posx < 0)	//This is disabled as I decided I didn't want a game rule that makes the player lsoe a life for each comet the player fails to shoot down
			{
				comets[i].live = false;
				someSpaceShip.lives--;
			}*/
		}
	}
}



/*void DrawPolygonTriangle()
{

	//al_draw_prim(TriVerts, NULL, image2, 0, 3, ALLEGRO_PRIM_TRIANGLE_LIST);
	//ALLEGRO_VERTEX TriVerts = NULL;	//Init
	//TriVerts[] = {
}*/

