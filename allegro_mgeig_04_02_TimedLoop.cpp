/*#include header files... its not clear if these should use a / or \      */

#include <iostream>     //includes the header file iostream
using namespace std;    //tells the compiler to use the std library


#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>


enum KEYS { UP, DOWN, LEFT, RIGHT };	//enum to specify the array



int main()

{
	//al_init();

	//ALLEGRO_DISPLAY *display = NULL;
	//ALLEGRO_DISPLAY* display = al_create_display(1024, 768);

	if (!al_init())
	{
		al_show_native_message_box(NULL, "ERROR", "ERROR", "failed to initialize allegro!", NULL, NULL);
		return -1;

		/*It seems that upon error the al_show_native_message_box does not display the specified error message if you do not specify a text for the third parameter.
		Well, at least on my system it does not, so I did this:
		al_show_native_message_box(NULL, “ERROR”, “ERROR”,“Failed to initialize allegro!”, NULL, NULL);*/
	}

	
	//display = al_create_display(display_width, display_height);
	//int display_width = al_get_display_width(display);
	//int display_height = al_get_display_height(display);


	int display_width = 1280;
	int display_height = 720;
	ALLEGRO_DISPLAY* display = al_create_display(display_width, display_height);
	if (!display)
	{
		al_show_native_message_box(NULL, "ERROR", "ERROR!", "failed to initialize display!", NULL, NULL);
		return -1;
	}


	//Initialize Allegro Addons
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();


	
	int FPS = 60;
	int plyrx = display_width / 2;
	int plyry = display_height / 2;
	bool keys[4]{ false, false, false, false };	//array for key states



	
	
	ALLEGRO_TIMER* looptimer = al_create_timer(1.0 / 60.0);		//declare???, create timer and set interval = 1 second / FPS... 1/60 = 60 FPS
	ALLEGRO_EVENT_QUEUE* event_que = al_create_event_queue();


	//Setup fonts
	//ALLEGRO_FONT* font = al_create_builtin_font();
	ALLEGRO_FONT* bebasneuereg24pt = al_load_font("BebasNeue_Reg.ttf", 24, 0);
	ALLEGRO_FONT* bebasneuereg16pt = al_load_font("BebasNeue_Reg.ttf", 16, 0);



	al_register_event_source(event_que, al_get_keyboard_event_source());	//get keyboard event and register to the applicable queue
	al_register_event_source(event_que, al_get_mouse_event_source());	//get mouse event and register to the applicable queue
	al_register_event_source(event_que, al_get_display_event_source(display));
	al_register_event_source(event_que, al_get_timer_event_source(looptimer));	//register timer event to the event_que






	//04-02
	bool quitapp = false;
	bool redraw = true;	//the bool named 'redraw' is used to ensure we render per the timer, but to move the rendering outside of the timer event handler
	int count = 1;
	int testing = 0;
	ALLEGRO_EVENT event; //Declare event var
	al_start_timer(looptimer);	//start timer
	while (!quitapp)	//while donekbd is false
	{
		std::cout << "start of loop" << endl;
		al_wait_for_event(event_que, &event);    //wait for an event from event_que and send it the address of event
		if (event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (event.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				count = count + 1000;
				keys[UP] = true;
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
			case ALLEGRO_KEY_ESCAPE:
				quitapp = true;
				break;
			}
		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)	//detect the display window being closed
		{
			quitapp = true;
		}
		
		else if (event.type == ALLEGRO_EVENT_TIMER)	//update position of player every frame
		{
			
			//std::cout << "in timer " << redraw << endl;

			plyry = plyry - keys[UP] * 5 + keys[DOWN] * 5;
			plyrx = plyrx - keys[LEFT] * 5 + keys[RIGHT] * 5;
			//posy = posy - keys[UP]* 10;
			//posy = posy + keys[DOWN]*10;
			//posx = posx - keys[LEFT]*10;
			//posx = posx + keys[RIGHT]*10;
			redraw = true;	//the bool named 'redraw' is used to ensure we render per the timer, but the rendering is done outside of the timer event handler
			//al_draw_textf(bebasneuereg24pt, al_map_rgb(255, 0, 255), display_width / 2, 500, ALLEGRO_ALIGN_CENTRE, "Frames = %d", redraw);


			
			//NEED TO FIND HOW TO PRINT TO CONSOLE OR TO FILE - The contents of the EVENT CUE

		}

		if (al_is_event_queue_empty(event_que) == true)
			//std::cout << "event_que is empty" << event_que << endl;
			testing = 100;
		if (al_is_event_queue_empty(event_que) == false)
			//std::cout << "not empty event_que is not empty " << event_que << endl;
			testing = 0;
		if (redraw && al_is_event_queue_empty(event_que)) //only redraw if plyr position has changed and event_que is empty so we know the new position is representative of input
		{
			//std::cout << "in render " << redraw << endl;
			redraw = false;	//the bool named 'redraw' is used to ensure we render per the timer, but to move the rendering outside of the timer event handler
			
			//al_draw_textf(bebasneuereg24pt, al_map_rgb(255, 0, 255), display_width / 2, 600, ALLEGRO_ALIGN_CENTRE, "Frames = %d", redraw);
			//count = count + 1;
			
			al_draw_filled_rectangle(plyrx - 10, plyry - 10, plyrx + 10, plyry + 10, al_map_rgb(255, 0, 255));
			//al_draw_textf(bebasneuereg24pt, al_map_rgb(255, 0, 255), display_width / 2, display_height / 2, ALLEGRO_ALIGN_CENTRE, "Frames = %i", count);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));	//Clear the back buffer
			
		}
		std::cout << "end of loop" << endl;
	}





	/*04-01
	bool donetiming = false;
	int count = 0;
	ALLEGRO_EVENT event; //Declare event var
	al_start_timer(looptimer);	//start timer
	while (!donetiming)	//while donetiming is false
	{
		al_wait_for_event(event_que, &event);    //wait for an event from event_que...   ????and send it the address of event
		count = count + 1;
		if (count > 6000)
		{
			donetiming = true;
		}
		else
		{
			al_draw_textf(bebasneuereg24pt, al_map_rgb(255, 0, 255), display_width / 2, display_height / 2, ALLEGRO_ALIGN_CENTRE, "Frames = %i", count);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));	//Clear the back buffer
		}
	}*/



	/*Mouse Input Loop
	al_hide_mouse_cursor(display);
	bool donemouse = false;
	bool drawcursor = true;
	while (!donemouse)	//while donemouse is false
	{
		al_wait_for_event(event_que, &event);    //wait for an event from event_que and send it the address of event
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)	//detect the display window being closed
		{
			donemouse = true;
		}
		else if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			posx = event.mouse.x;
			posy = event.mouse.y;
		}
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (event.mouse.button & 2)
				donemouse = true;
			else if (event.mouse.button & 1)
				drawcursor = !drawcursor;
		}

		if (drawcursor)
			al_draw_filled_rectangle(posx - 10, posy - 10, posx + 10, posy + 10, al_map_rgb(255, 0, 255));
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));	//Clear the back buffer
	}*/






	/*Keyboard Input Loop
	bool donekbd = false;
	while (!donekbd)	//while donekbd is false
	{
		al_wait_for_event(event_que, &event);    //wait for an event from event_que and send it the address of event_kbd
		if (event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (event.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
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
			case ALLEGRO_KEY_ESCAPE:
				donekbd = true;
				break;
			}
		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)	//detect the display window being closed
		{
			donekbd = true;
		}

		posy = posy - keys[UP] * 5 + keys[DOWN] * 5;
		posx = posx - keys[LEFT] * 5 + keys[RIGHT] * 5;

		//posy = posy - keys[UP]* 10;
		//posy = posy + keys[DOWN]*10;
		//posx = posx - keys[LEFT]*10;
		//posx = posx + keys[RIGHT]*10;

		al_draw_filled_rectangle(posx - 10, posy - 10, posx + 10, posy + 10, al_map_rgb(255, 0, 255));
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));	//Clear the back buffer
	}*/



	/*primitives loop
	bool doneprimitives = false;
	while (!doneprimitives)  //while doneprimitives is false, do as below...
	{
		//Text
		al_clear_to_color(al_map_rgb(0, 0, 0));	//Clear the back buffer
		al_draw_text(bebasneuereg24pt, al_map_rgb(255, 0, 255), 50, 50, 0, "Hello World");
		al_draw_text(bebasneuereg16pt, al_map_rgb(255, 0, 255), 640 / 2, 480 / 2, ALLEGRO_ALIGN_CENTRE, "Hello World");
		al_draw_text(bebasneuereg16pt, al_map_rgb(255, 0, 255), 620, 350, ALLEGRO_ALIGN_RIGHT, "Hello World");
		al_draw_textf(bebasneuereg16pt, al_map_rgb(255, 200, 255), display_width / 2, 400, ALLEGRO_ALIGN_CENTRE, "Width & Height = %i x %i", display_width, display_height);
		al_flip_display();
		al_rest(3.0);


		//Pixels
		al_clear_to_color(al_map_rgb(0, 0, 0));	//Clear the back buffer
		al_draw_pixel(100, 100, al_map_rgb(255, 0, 255));
		al_flip_display();
		al_rest(3.0);

		//Lines
		al_clear_to_color(al_map_rgb(0, 0, 0));	//Clear the back buffer
		al_draw_line(100, 100, display_width - 100, 100, al_map_rgb(255, 0, 255), 1);
		al_draw_line(100, 200, display_width - 100, 200, al_map_rgb(255, 0, 255), 5);
		al_draw_line(0, 300, display_width, 300, al_map_rgb(255, 0, 255), 5);
		al_draw_line(100, 200, display_width - 100, 400, al_map_rgb(255, 0, 255), 5);
		al_draw_line(100, 100, 100, 300, al_map_rgb(255, 0, 255), 1);
		al_flip_display();
		al_rest(3.0);

		//Triangles
		al_clear_to_color(al_map_rgb(0, 0, 0));	//Clear the back buffer
		al_draw_triangle(10, 200, 100, 10, 190, 200, al_map_rgb(255, 0, 255), 1);
		al_draw_filled_triangle(250, 200, 250, 100, 350, 200, al_map_rgb(255, 0, 255));
		al_flip_display();
		al_rest(3.0);

		//Rectangles
		al_clear_to_color(al_map_rgb(0, 0, 0));	//Clear the back buffer
		al_draw_rectangle(50, 100, 150, 200, al_map_rgb(255, 0, 255), 3);
		al_draw_rounded_rectangle(200, 100, 300, 150, 5, 5, al_map_rgb(255, 0, 255), 1);
		al_draw_filled_rectangle(50, 300, 150, 450, al_map_rgb(255, 0, 255));
		al_draw_filled_rounded_rectangle(200, 300, 300, 450, 5, 5, al_map_rgb(255, 0, 255));
		al_flip_display();
		al_rest(3.0);

		//Circles
		al_clear_to_color(al_map_rgb(0, 0, 0));	//Clear the back buffer
		al_draw_circle(display_width / 2, display_height / 2, 100, al_map_rgb(255, 0, 255), 3);
		al_draw_filled_circle(100, 300, 50, al_map_rgb(255, 255, 255));
		al_flip_display();
		al_rest(3.0);

		//Ellipse
		al_clear_to_color(al_map_rgb(0, 0, 0));	//Clear the back buffer
		al_draw_ellipse(display_width / 2, display_height / 2, 50, 100, al_map_rgb(255, 0, 255), 3);
		al_draw_filled_ellipse(100, 300, 50, 75, al_map_rgb(255, 255, 255));
		al_flip_display();
		al_rest(3.0);


		//Spline
		al_clear_to_color(al_map_rgb(0, 0, 0));	//Clear the back buffer
		float points[] = { 0.0,0.0, 400.0,100.0, 50.0,200.0, 640.0,480.0 };  //Array of 8 points to be used for a spline
		al_draw_spline(points, al_map_rgb(255, 0, 255), 1);
		float points2[] = { 0,display_height, 200,100, 400,200, display_width,display_height };
		al_draw_spline(points2, al_map_rgb(0, 255, 0), 1);
		al_flip_display();
		al_rest(3.0);

		doneprimitives = true;

	}*/



	//Cleanup
	al_destroy_display(display);	//Cleanup display... created via al_create_display
	al_destroy_event_queue(event_que);
	al_destroy_timer(looptimer);
	al_destroy_font(bebasneuereg24pt);
	al_destroy_font(bebasneuereg16pt);



	return 0;

}