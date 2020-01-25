#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

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


	//Initialize Allegro & Addons
	al_init_font_addon();
	al_init_ttf_addon();

	//Setup fonts
	ALLEGRO_FONT* bebasneuereg24pt = al_load_font("BebasNeue_Reg.ttf", 24, 0);
	ALLEGRO_FONT* bebasneuereg16pt = al_load_font("BebasNeue_Reg.ttf", 16, 0);


	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(bebasneuereg24pt, al_map_rgb(255, 0, 255), 50, 50, 0, "Hello World");
	al_draw_text(bebasneuereg16pt, al_map_rgb(255, 0, 255), 640/2, 480/2, ALLEGRO_ALIGN_CENTRE, "Hello World");
	al_draw_text(bebasneuereg16pt, al_map_rgb(255, 0, 255), 620, 350, ALLEGRO_ALIGN_RIGHT, "Hello World");
	
	
	int display_width = al_get_display_width(display);
	int display_height = al_get_display_height(display);
	al_draw_textf(bebasneuereg16pt, al_map_rgb(255, 200, 255), display_width / 2, 400, ALLEGRO_ALIGN_CENTRE, "Width & Height = %i x %i", display_width, display_height);

	al_flip_display();
	al_rest(10.0);


	al_destroy_display(display);
	al_destroy_font(bebasneuereg24pt);
	al_destroy_font(bebasneuereg16pt);
	return 0;


}