#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

int main()
{
	
	//Initialize Allegro & Addons
	al_init();
	al_install_keyboard();

	//Pointers to setup display, font, timer & queue
	ALLEGRO_DISPLAY* display = al_create_display(1024, 768);
	ALLEGRO_FONT* font = al_create_builtin_font();
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);		//declare???, create timer and set interval = 1 second / FPS... 1/30 = 30 FPS
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	bool redraw = true;
	ALLEGRO_EVENT event;
	al_start_timer(timer);
	while (true)	//Start infinite loop that is only exited via break, was originally written as... while (1)
	{
		al_wait_for_event(queue, &event);	//Something like wait for an event to hit the queue and send it to the variable named event

		if (event.type == ALLEGRO_EVENT_TIMER) //Check that the event is an ALLEGRO TIMER EVENT
			redraw = true;	//
		else if ((event.type == ALLEGRO_EVENT_KEY_DOWN) || (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE))
			break;	//Break out of infinite loop if a key is pressed or the display window is closed

		if (redraw && al_is_event_queue_empty(queue))	//when redraw is true and the event queue is empty (true) they are are both the same value
		{
			al_clear_to_color(al_map_rgb(100, 0, 0));	//Clear the back buffer
			al_draw_text(font, al_map_rgb(100, 255, 255), 0, 0, 0, "Hello world!");	//draw text to the back buffer
			al_flip_display();	//flip the display
			redraw = false;	//In this example, at this stage everything that needs to be drawn is done, so redraw is set false, indicating the frame has been rendered
		}
	}


	//Cleanup
	al_destroy_display(display);
	al_destroy_font(font);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);

	return 0;
}