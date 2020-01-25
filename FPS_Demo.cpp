#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

//#include <allegro5/allegro_direct3d.h>

const float FPS = 120.0f;

int main(int argc, char **argv)
{
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_BITMAP *bitmap = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *ttf_font;

	bool exit = false;

	if (!al_init())
	{
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);
	if (!timer)
	{
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	int screen_width = 1280;
	int screen_height = 720;

	//   al_set_new_display_flags(ALLEGRO_DIRECT3D);

	display = al_create_display(screen_width, screen_height);

	if (!display)
	{
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}

	if (!al_init_primitives_addon())
	{
		fprintf(stderr, "failed to initiialize primitives addon!\n");
		return -1;
	}

	if (!al_install_keyboard())
	{
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return -1;
	}

	event_queue = al_create_event_queue();

	if (!event_queue)
	{
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	bitmap = al_create_bitmap(screen_width, screen_height);
	if (!bitmap)
	{
		fprintf(stderr, "failed to create bouncer bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	//al_set_target_bitmap(bitmap);
	//al_clear_to_color(al_map_rgb(0, 0, 0));
	//al_set_target_bitmap(al_get_backbuffer(display));

	//al_flip_display();
	al_start_timer(timer);

	al_init_font_addon();
	if (!al_init_ttf_addon()) {
		fprintf(stderr, "failed to initialize the ttf addon.\n");
		return -1;
	}


	ttf_font = al_load_ttf_font("BebasNeue_Reg.ttf", 24, 0);

	//ALLEGRO_FONT* bebasneuereg24pt = al_load_font("BebasNeue_Reg.ttf", 24, 0);


	if (!ttf_font) {
		fprintf(stderr, "failed to load font.\n");
		return -1;
	}


	bool redraw = true;

	double old_time = al_get_time();


	while (!exit)
	{
		double new_time = al_get_time();
		double fps = 1.0 / (new_time - old_time);
		old_time = new_time;

		if (redraw)
		{
			int r = rand() % 255;
			int g = rand() % 255;
			int b = rand() % 255;
			int a = rand() % 128 + 64;
			int x1 = rand() % screen_width;
			int x2 = rand() % screen_width;
			int y1 = rand() % screen_height;
			int y2 = rand() % screen_height;

			//al_set_target_bitmap(bitmap);
			//ALLEGRO_COLOR color = al_map_rgba(r*a / 255, g*a / 255, b*a / 255, a);
			//al_draw_line(x1, y1, x2, y2, color, 20.0);	//draw shape into bitmap
			//al_set_target_backbuffer(display);
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_filled_triangle(250, 200, 250, 100, 350, 200, al_map_rgb(255, 0, 255));
			//al_draw_bitmap(bitmap, 0, 0, 0);	//draws shape into display backbuffer???
			al_draw_filled_rectangle(16.0f, 32.0f, 156.0f, 52.0f, al_map_rgb(255, 0, 255)); //draws black behind fps counter
			al_draw_textf(ttf_font, al_map_rgb(255, 255, 0), 16, 32, 0, "FPS: %f", (float)fps); //text is displaying extra 00
			al_flip_display();
			redraw = false;
		}
		while (1)
		{
			ALLEGRO_EVENT ev;
			al_wait_for_event(event_queue, &ev);
			if (ev.type == ALLEGRO_EVENT_TIMER)
			{
				redraw = true;
			}
			else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				exit = true;
				break;
			}
			else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				{
					exit = true;
					break;
				}
			}
			if (al_is_event_queue_empty(event_queue))
			{
				break;
			}// this way all events are used
		}
	}

	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}