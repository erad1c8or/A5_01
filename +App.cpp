

#include <iostream>
#include "+App.hpp"
#include "+Sprite.hpp"

#include "!globals.hpp"

//init and createWindow should ideally be integrated into the Constructor and Destructor per application.hpp, but this is tricky as the Constructor/Destructor cannot have returns


application::application()										//Start of Constructor
{
	std::cout << "+App.cpp - application base constructor called\n";
	display = nullptr;
	timer = nullptr;
	event_queue = nullptr;
	looping = true;
	redraw = false;
}


application::~application()										//Start of Destructor
{
	std::cout << "+App.cpp - application base destructor called\n";
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);
}


int application::init()
{
	std::cout << "+App.cpp - myapp->init\n";
	if (!al_init())
	{
		al_show_native_message_box(NULL, "ERROR", "ERROR", "failed to initialize allegro!", NULL, NULL);
		return -1;
		/*Upon error the al_show_native_message_box does not display the specified error message unless text is specified for the third parameter.
		for example... al_show_native_message_box(NULL, “ERROR”, “ERROR”,“Failed to initialize allegro!”, NULL, NULL);*/
	}
	return 0;
}


int application::createWindow(int width, int height, float FPS)
{
	std::cout << "+App.cpp - myapp->createWindow\n";
	
	/*initialize allegro display*/
	al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_REQUIRE);				//int option, int value, int importance... 
	/*Forces vsync to be on and sets the option, value and importance as noted below...
	option = 26 = ALLEGRO_VSYNC
	value = 1 means force on... 2 means forced off and 0 means default behaviour that may be on or off
	importance = 1 means ALLEGRO_REQUIRE... Other options are 2 = ALLEGRO_SUGGEST and 0 = ALLEGRO_DONTCARE
	*/
	
	display = al_create_display(width, height);
	if (!display)
	{
		al_show_native_message_box(NULL, "ERROR", "ERROR!", "failed to create display!", NULL, NULL);
		al_destroy_display(display);
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);
	if (!timer)
	{
		al_show_native_message_box(NULL, "ERROR", "ERROR!", "failed to create timer!", NULL, NULL);
		al_destroy_timer(timer);
		al_destroy_display(display);
		return -1;
	}

	event_queue = al_create_event_queue();
	if (!event_queue)
	{
		al_show_native_message_box(NULL, "ERROR", "ERROR!", "failed to create event queue!", NULL, NULL);
		al_destroy_event_queue(event_queue);
		al_destroy_timer(timer);
		al_destroy_display(display);
		return -1;
	}

	al_install_keyboard();
	al_install_mouse();
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();



	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	return 0;
}


void application::gameLoop(std::vector<Sprite> &vectorarrayofinvaders2)
{
	std::cout << "+App.cpp - entered gameLoop\n";
	//std::cout << "+App.cpp - Test String Constructor\n";
		
	
	/*void Sprite::setBitmap(std::string filepath)									//member function to set object.bitmap
	{
	bitmap = al_load_bitmap(filepath.c_str());									//bitmap = the sprite per string named filepath, converted into a c-style string, aka an array of characters that is null terminated
	}*/

	system("pause");


	//std::cout << "+App.cpp - creating game objects on stack\n";
	
	//Sprite plyr01{ "Agony/OwlAnimR", "AnimatedSprite", ".bmp", 16, 640, 360 };
	//Sprite plyr02{ "biplane", "AnimatedSprite", ".png", 1, 840, 360 };

	//extern Sprite invader{ "Square_16x16_Green", "AnimatedSprite", ".bmp", 1, 300, 300 };
	//extern Sprite invader{ "Square_16x16_Green", "AnimatedSprite", ".png", 1, 300, 300 };
	//Sprite invader{ "Square_16x16_Green", "AnimatedSprite", ".png", 1, 300, 300 };
	//Sprite invader{ "Square_16x16_Green", "AnimatedSprite", ".png", 1, 300, 300 };


	//Sprite plyr1{ 640, 360 };											//create plyr1 (object/var), of data type... Sprite (class) via uniform initialization, might be best left in +App.hpp within private:
	//std::cout << "+App.cpp - set bitmap for plyr1\n";
	//plyr1.setBitmap(asset_filepath);							//the default working directory is the project directory, where the .cpp and .hpp live
	//plyr1.setBitmap("assets/dragon_jjh.bmp");							//the default working directory is the project directory, where the .cpp and .hpp live


	//Sprite plyr2{ 100, 100 };											//create plyr2 (object/var), of data type... Sprite (class) via uniform initialization, might be best left in +App.hpp within private:
	//std::cout << "+App.cpp - set bitmap for plyr2\n";
	//plyr2.setBitmap("assets/dragon00.bmp");
	
	
	//std::cout << "+App.cpp - loading font\n";
	//system("pause");
	//ALLEGRO_FONT *bebasneuereg24pt = al_load_ttf_font("Assets/BebasNeue_Reg.ttf", 24, 0);

	
	
	/*Basic Animation
	ALLEGRO_BITMAP *DragonAnim[MaxFrame];	//Define Array for Rudimentary Animation
	for (int i = 0; i < MaxFrame + 1; i++)
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
	*/
	

	//create game objects...
	//could be moved to main.cpp or elsewhere, so long as the scope of the plyr1 and plyr2 are either global or at least extended so they accessible from that level
	//currently plyr1 and ply2 are declared in +App.hpp where they have Private scope, meaning they are visible to the +App class and I believe friends of the +App class

	//what i used to do here was plyr1.setBitmap and plyr2.setBitmap...


	//Trying to acccess these objects and members in main.hpp
	//See comments for where this might be best placed of all, but also note, I can't create these in !globals.hpp because each file including , tries to create the object...
	//In the case of const types, the behaviour is different so they are OK in !globals.hpp


	//declare object of type Sprite named plyr1 & plyr2, and using extern to extend visibility of plyr1 and plyr2 to the whole program.
	//so it doesn't matter where in the CPP files that plyr1 and ply2 are defined so long as they are only defined once per the one definition rule
	//per 2019/02/20, they are defined in +Sprite.hpp but I might change this in the future so they are defined in either main.cpp +App.cpp or !globals.cpp
	//App.hpp is probably the right place to define these overall however, so long as they are not used outside of the scope of 'application' class.

	//#include "+Sprite.hpp"											//can't declare objects of type class, without including the class structure/definition
	//class Sprite;														//fwd declaration of class sprite
	//extern Sprite plyr1;												//declare object of type Sprite named plyr1, and using extern to extend visibility of plyr1 to the whole program.
	//extern Sprite plyr2;												//declare object of type Sprite named plyr2, and using extern to extend visibility of plyr2 to the whole program.


	std::cout << "+App.cpp - starting game loop proper\n";

	al_start_timer(timer);
	while (looping)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			
			//player.doLogic(keyboard);

			//Per 2019/12/29, that below is done Ibelieve.
			//Temporarily disabling animation because it causes a crash when the PlyrX object only has one frame
			//To make this work, I think that I need to make CurrFrame be associated to the PlyrX object in the constructor etc.




			/*Keyboard Input*/
			if (keys[UP])
				//std::cout << "keysUP\n";
				//invaderglob_pntr->m_posy--;
				(*plyr01_glob_ptr).MoveUp();							//This is equivalent to... plyr01_glob_ptr->MoveUp(); re calling function from the class that plyr01_glob_ptr points to.
			else if (keys[DOWN])
				//std::cout << "keysDOWN\n";
				plyr01_glob_ptr->MoveDown();
			if (keys[LEFT])
				//std::cout << "keysLEFT\n";
				plyr01_glob_ptr->MoveLeft();
			else if (keys[RIGHT])
				//std::cout << "keysRIGHT\n";
				plyr01_glob_ptr->MoveRight();


			// Basic Animation for plyr1, rendering the next frame of animation every X (per FrameDelay) frames, as 1 animation frame each frame is too fast.
			if (++FrameCount >= FrameDelay)								//If incremented FrameCount >= FrameDelay, it's time to render the next animation frame.
			{
				//if (++plyr01.m_CurrFrame >= plyr01.m_MaxFrame)					//If the next frame of animation is equal to, or greater than the number of the last frame...
					//plyr01.m_CurrFrame = 0;										//... reset to the first frame in the array

				//if (++plyr02.m_CurrFrame >= plyr2.m_MaxFrame)					//If the next frame of animation is equal to, or greater than the number of the last frame...
					//plyr02.m_CurrFrame = 0;										//... reset to the first frame in the array

				FrameCount = 0;											//Finally we reset FrameCount to 0 so we know when to draw the next animation frame
			}



			if (++FrameCount >= FrameDelay)
			{
				for (int i = 0; i < vectorarrayofinvaders2.size(); i++)
				{
					if (vectorarrayofinvaders2[i].m_posx < displayWidth - 16)
					{
						vectorarrayofinvaders2[i].m_posx += 16;
					}
				}
				FrameCount = 0;
			}

			redraw = true;
		}



		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				//keyboard.key[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				//keyboard.key[DOWN] = true;
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				//keyboard.key[LEFT] = true;
				keys[LEFT] = true;
				break;	
			case ALLEGRO_KEY_RIGHT:
				//keyboard.key[RIGHT] = true;
				keys[RIGHT] = true;
				break;
			}
		}
		
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				//keyboard.key[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				//keyboard.key[DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				//keyboard.key[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				//keyboard.key[RIGHT] = false;
				break;
			}
		}
			
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				looping = false;
			}



		//rendering
		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));
			
			// Draw
			//std::cout << "TESTING" << endl;
			//std::cout << "plyr1.m_posx = " << plyr1.m_posx << endl;
			//std::cout << "plyr2.id = " << plyr2.m_id << endl;
			//BiplaneFloatPoint(display, plyr1);
			//cout << "draw plyr1\n";
		

			//plyr01.draw_animated_bitmap();																//pass plyr1 to draw...
			//plyr02.draw_animated_bitmap();
			
			//invader01.m_posx++;

			plyr01_glob_ptr->draw_bitmap();


			/*
			for (int i = 0; i < invadersNum; i++)													//This becomes redundant
			{
				//invader_glob_ptr[i].m_posx += 1;
				invader_glob_ptr[i].draw_bitmap();
				//invader_glob_vector[i].draw_bitmap();
				//vectorarrayofinvaders2[i].draw_bitmap();
			}
			*/


			for (int i = 0; i < vectorarrayofinvaders2.size(); i++)									//Need to pass invadersTotal to the gameloop
			{
				vectorarrayofinvaders2[i].draw_bitmap();
			}
			
					
			
			//invaderglob->drawtest();

			//somegamecode2();

			//al_draw_textf(bebasneuereg24pt, al_map_rgb(255, 0, 255), displayWidth-1150, displayHeight - 30, ALLEGRO_ALIGN_CENTRE, "plyr1.m_posx: %f", plyr1.m_posx);
			//al_draw_filled_circle(plyr1.x, plyr1.y, 25, al_map_rgb(0, 0, 255));
		
			al_flip_display();
		}
	}

//Cleanup/Shutdown/Uninstall moved to main()


}





/*
void BiplaneFloatPoint(ALLEGRO_DISPLAY *&display, sprite &someSprite)
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
	al_draw_filled_circle(plyr1.posx, plyr1.posy, 25, al_map_rgb(0, 0, 255));
	//al_draw_scaled_rotated_bitmap(image2, image2Width / 2, image2Height / 2, plyr1.posx, plyr1.posy, 0.3, 0.3, plyr1.angle, 0);
	//al_draw_line(plyr1.posx, plyr1.posy, plyr1.posx + (plyr1.length + 5.0) * cos(plyr1.angle), plyr1.posy + (plyr1.length + 5.0) * sin(plyr1.angle), al_map_rgb(0, 255, 0), 1);
}
*/