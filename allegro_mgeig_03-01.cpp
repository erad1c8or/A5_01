
/*#include header files... its not clear if these should use a / or \      */
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

int main()

{
	//al_init();

	ALLEGRO_DISPLAY *display = NULL;
	//ALLEGRO_DISPLAY* display = al_create_display(1024, 768);

	if (!al_init())
	{
		al_show_native_message_box(NULL, "ERROR", "ERROR", "failed to initialize allegro!", NULL, NULL);
		return -1;

		/*It seems that upon error the al_show_native_message_box does not display the specified error message if you do not specify a text for the third parameter.
		Well, at least on my system it does not, so I did this:
		al_show_native_message_box(NULL, “ERROR”, “ERROR”,“Failed to initialize allegro!”, NULL, NULL);*/
	}

	int display_width = 1280;
	int display_height = 720;
	display = al_create_display(display_width, display_height);
	//int display_width = al_get_display_width(display);
	//int display_height = al_get_display_height(display);

	if (!display)
	{
		al_show_native_message_box(NULL, "ERROR", "ERROR!", "failed to initialize display!", NULL, NULL);
		return -1;
	}


	ALLEGRO_EVENT_QUEUE* event_que = NULL;
	
	//Initialize Allegro Addons
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_keyboard();


	//Setup fonts
	ALLEGRO_FONT* bebasneuereg24pt = al_load_font("BebasNeue_Reg.ttf", 24, 0);
	ALLEGRO_FONT* bebasneuereg16pt = al_load_font("BebasNeue_Reg.ttf", 16, 0);


	ALLEGRO_EVENT event_kbd; //Declare event_kbd

    bool done = false;
	int posx = display_width/2;
	int posy = display_height/2;

	event_que = al_create_event_queue(); //create an event queue
	al_register_event_source(event_que, al_get_keyboard_event_source());	//get keyboard event and register to the applicable queue



	while (!done)
	{
		al_wait_for_event(event_que, &event_kbd);    //wait for an event from event_que and send it the address of event_kbd
		if (event_kbd.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (event_kbd.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				posy = posy - 10;
					break;
			case ALLEGRO_KEY_DOWN:
				posy = posy + 10;
					break;
			case ALLEGRO_KEY_LEFT:
				posx = posx - 10;
					break;
			case ALLEGRO_KEY_RIGHT:
				posx = posx + 10;
					break;
			}
		}
		else if (event_kbd.type == ALLEGRO_EVENT_KEY_UP)
		{
			if (event_kbd.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				done = true;
		}

		al_draw_filled_rectangle(posx-10,posy-10, posx+10,posy+10, al_map_rgb(255, 0, 255));
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));	//Clear the back buffer
	}



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
	float points[] = {0.0,0.0, 400.0,100.0, 50.0,200.0, 640.0,480.0};  //Array of 8 points to be used for a spline
	al_draw_spline(points, al_map_rgb(255, 0, 255), 1);
	float points2[] = {0,display_height, 200,100, 400,200, display_width,display_height};
	al_draw_spline(points2, al_map_rgb(0, 255, 0), 1);
	al_flip_display();
	al_rest(3.0);


	//Cleanup
	al_destroy_display(display);	//Cleanup display... created via al_create_display
	al_destroy_event_queue(event_que);
	al_destroy_font(bebasneuereg24pt);
	al_destroy_font(bebasneuereg16pt);
	return 0;


}