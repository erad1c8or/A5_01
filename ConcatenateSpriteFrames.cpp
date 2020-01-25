#include <string>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
///#include "+Sprite.hpp"
#include "!globals.hpp"

int ConcatenateSpriteFrames(std::string sourceAnimName, std::string sourceFormat)
{
	//variables
	int imageWidth = 0;
	int imageHeight = 0;
	const int arraySize = 16;

	//allegro variables
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_BITMAP *image[arraySize];
	ALLEGRO_BITMAP *outImage;

	//program init
	if (!al_init())																	//initialize Allegro
		return -1;

	display = al_create_display(displayWidth, displayHeight);						//create our display object
	if (!display)																	//test display object
		return -1;

	//addon init
	al_init_image_addon();


	int num_zeros = 2;															//number digits used in anim sequence file names
	for (int i = 0; i < arraySize; i++)
	{
		std::string sourceAnimFrameNumAsString = std::to_string(i);
		std::string  source_filepath = assetsDir + sourceAnimName + std::string(num_zeros - sourceAnimFrameNumAsString.length(), '0') + sourceAnimFrameNumAsString + sourceFormat;
		std::cout << "+App.cpp - Animated Sprite Constructor loading... " << source_filepath << "\n";
		image[i] = al_load_bitmap(source_filepath.c_str());
		//al_convert_mask_to_alpha(DragonAnimFrame[i], al_map_rgb(106, 76, 48));	//assign defined color to alpha
	}
	
	///image[0] = al_load_bitmap("fliegt w0000.bmp");
	///image[1] = al_load_bitmap("fliegt w0001.bmp");
	///image[2] = al_load_bitmap("fliegt w0002.bmp");
	///image[3] = al_load_bitmap("fliegt w0003.bmp");
	///image[4] = al_load_bitmap("fliegt w0004.bmp");
	///image[5] = al_load_bitmap("fliegt w0005.bmp");
	///image[6] = al_load_bitmap("fliegt w0006.bmp");
	///image[7] = al_load_bitmap("fliegt w0007.bmp");

	imageWidth = al_get_bitmap_width(image[0]);
	imageHeight = al_get_bitmap_height(image[0]);

	outImage = al_create_bitmap(imageWidth * arraySize, imageHeight);

	al_set_target_bitmap(outImage);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	for (int i = 0; i < arraySize; i++)
	{
		al_draw_bitmap(image[i], i * imageWidth, 0, 0);
	}

	al_save_bitmap("sprite_sheet_demo.bmp", outImage);

	al_set_target_bitmap(al_get_backbuffer(display));		//Restore display as the target bitmap

	

	//Cleanup
	for (int i = 0; i < arraySize; i++)
		al_destroy_bitmap(image[i]);
	
	al_destroy_bitmap(outImage);
	al_destroy_display(display);						//destroy our display object

	return 0;
}
