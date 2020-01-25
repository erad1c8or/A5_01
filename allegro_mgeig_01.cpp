#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

int main()

{
	//al_init();

	ALLEGRO_DISPLAY *display = NULL;
	//ALLEGRO_DISPLAY* display = al_create_display(1024, 768);

	if(!al_init())
	{
		al_show_native_message_box(NULL, "ERROR", "ERROR", "failed to initialize allegro!", NULL, NULL);
		return -1;
	}
	
	display = al_create_display(640, 480);

	if (!display)
	{
		al_show_native_message_box(NULL, "ERROR", "ERROR", "failed to initialize display!", NULL, NULL);
		return -1;
	}

	al_destroy_display(display);
	return 0;



}
