#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

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

	display = al_create_display(640, 480);

	if (!display)
	{
		al_show_native_message_box(NULL, "ERROR", "ERROR", "failed to initialize display!", NULL, NULL);
		return -1;
	}

	al_clear_to_color(al_map_rgb(255, 0, 255));
	al_flip_display();
	al_rest(5.0);
	al_destroy_display(display);
	return 0;

}
