#include "+Sprite.hpp"															//Included per !globals.hpp
#include "!globals.hpp"


Sprite::Sprite()
{
}

Sprite::Sprite(float posx, float posy)
	:
	m_posx{ posx },																	//create object.m_posx and initialize via uniform initialization
	m_posy{ posy },																	//create object.m_posy and initialize via uniform initialization
	m_bitmap {NULL}																	//dereference bitmap (ptr) and initialize as NULL via uniform initialization
	{
	std::cout << "+Sprite.cpp - Sprite(float posx, float posy) constructor called\n";
	}
//Sprite::Sprite(int id, float posx, float posy, float angle, float length, float velx, float vely, int speed, int lives, int boundx, int boundy, int score)




Sprite::Sprite (std::string objectName, std::string assetName, float posx, float posy)
	:
	m_objectName{ objectName },
	m_Name{ assetName },
	m_posx{ posx },																	//create object.m_posx and initialize via uniform initialization
	m_posy{ posy },																	//create object.m_posy and initialize via uniform initialization
	m_bitmap{ NULL }																//dereference bitmap (ptr) and initialize as NULL via uniform initialization
	//PlyrAnimFrame { NULL }
{
	std::cout << "+Sprite.cpp(std::string objectName, std::string assetName, float posx, float posy) constructor called for..." << objectName << "\n";
	system("pause");
	//al_load_bitmap("Assets/x-wing.png");
}
//Sprite::Sprite(int id, float posx, float posy, float angle, float length, float velx, float vely, int speed, int lives, int boundx, int boundy, int score)





Sprite::Sprite (std::string assetName, std::string assetCategory, std::string assetFormat, int numFrames, float posx, float posy)
	:
	m_Name{ assetName },
	m_Cat {assetCategory},
	m_Format {assetFormat},
	m_MaxFrame {numFrames},															//Variable to track total number of animation frames
	m_posx{ posx },																	//create object.m_posx and initialize via uniform initialization
	m_posy{ posy },																	//create object.m_posy and initialize via uniform initialization
	m_CurrFrame {0},																//the first and then current frame of animation to draw
	m_bitmap{ nullptr },
	PlyrAnimFrame {nullptr}
	//DragonAnimFrame[MaxFrame]														//Define Array for Rudimentary Animation
																	//dereference bitmap (ptr) and initialize as NULL via uniform initialization
	{

/*
	std::cout << "+Sprite.cpp - Animated Sprite constructor called\n";
	int num_zero = 2;																//number digits used in anim sequence file names
		for (int i = 0; i < m_MaxFrame; i++)
		{
		std::cout << "adding sprite frame..." << i << "\n";
		std::string assetFrameNumAsString = std::to_string(i);
		std::string  asset_filepath = "assets/" + assetName + std::string(num_zero - assetFrameNumAsString.length(), '0') + assetFrameNumAsString + assetFormat;
//std::string  asset_filepath = assetsDir + assetName + std::string(num_zero -assetFrameNumAsString.length(), '0') + assetFrameNumAsString + assetFormat;
		std::cout << "+Sprite.cpp - Animated Sprite Constructor loading... " << asset_filepath << "\n";
		PlyrAnimFrame[i] = al_load_bitmap(asset_filepath.c_str());
		al_convert_mask_to_alpha(PlyrAnimFrame[i], al_map_rgb(255, 0, 255));		//assign defined color to alpha
		}
	*/

	}



Sprite::~Sprite()
{
	std::cout << "+Sprite.cpp - Sprite destructor (default) called for..." << m_objectName << "\n";
	if (!m_bitmap) { m_bitmap = nullptr; }												//if object.m_bitmap does not exist then object.m_bitmap = null
	al_destroy_bitmap(m_bitmap);

	/*
	for (int i = 0; i < m_MaxFrame; i++)
	{
		if (!PlyrAnimFrame[i]) { PlyrAnimFrame[i] = nullptr; }
		al_destroy_bitmap(PlyrAnimFrame[i]);
		//system("pause");
	}
	*/
}



	
void Sprite::setBitmap(std::string filepath)										//member function to set object.bitmap (setter)
{
	m_bitmap = al_load_bitmap(filepath.c_str());										//bitmap = the sprite per string named filepath, converted into a c-style string, aka an array of characters that is null terminated
}


/*
ALLEGRO_BITMAP *Sprite::getBitmap()													//member function to get object.bitmap
{
	return bitmap;
}
*/


void Sprite::draw()																	//member function to draw, only has access to class member variables but thats all we need I think!!
{
	al_draw_filled_circle(m_posx, m_posy, 25, al_map_rgb(0, 0, 255));				//Test primitive circle
	//al_draw_bitmap(bitmap, m_posx, m_posy, NULL);								
	//al_draw_bitmap(PlyrAnimFrame[m_CurrFrame], m_posx, m_posy, NULL);				//Drawing current frame
	//al_draw_bitmap(DragonAnim[CurrFrame], 900, 200, 0);
	//al_draw_filled_circle(50, 50, 25, al_map_rgb(0, 0, 255));
	//std::cout << "plyr1.x = " << x << endl;
	//al_draw_filled_circle(x, y, 25, al_map_rgb(0, 0, 255));
}


void Sprite::draw_test()																	//member function to draw, only has access to class member variables but thats all we need I think!!
{
	//al_draw_filled_circle(m_posx, m_posy, 25, al_map_rgb(0, 0, 255));							//Test primitive circle
	al_draw_bitmap(m_bitmap, m_posx, m_posy, NULL);								
	//al_draw_bitmap(PlyrAnimFrame[m_CurrFrame], m_posx, m_posy, NULL);				//Drawing current frame
	//al_draw_bitmap(DragonAnim[CurrFrame], 900, 200, 0);
	//al_draw_filled_circle(50, 50, 25, al_map_rgb(0, 0, 255));
	//std::cout << "plyr1.x = " << x << endl;
	//al_draw_filled_circle(x, y, 25, al_map_rgb(0, 0, 255));
}


void Sprite::draw_bitmap()															//member function to draw, only has access to class member variables but thats all we need I think!!
{
	//al_draw_filled_circle(m_posx, m_posy, 25, al_map_rgb(0, 0, 255));				//Test primitive circle
	al_draw_bitmap(m_bitmap, m_posx, m_posy, NULL);
	//al_draw_bitmap(PlyrAnimFrame[m_CurrFrame], m_posx, m_posy, NULL);				//Drawing current frame
	//al_draw_bitmap(DragonAnim[CurrFrame], 900, 200, 0);
	//al_draw_filled_circle(50, 50, 25, al_map_rgb(0, 0, 255));
	//std::cout << "plyr1.x = " << x << endl;
	//al_draw_filled_circle(x, y, 25, al_map_rgb(0, 0, 255));
}

void Sprite::draw_animated_bitmap()													//member function to draw, only has access to class member variables but thats all we need I think!!
{
	//al_draw_filled_circle(m_posx, m_posy, 25, al_map_rgb(0, 0, 255));				//Test primitive circle
	//al_draw_bitmap(bitmap, m_posx, m_posy, NULL);
	al_draw_bitmap(PlyrAnimFrame[m_CurrFrame], m_posx, m_posy, NULL);				//Drawing current frame
	//al_draw_bitmap(DragonAnim[CurrFrame], 900, 200, 0);
	//al_draw_filled_circle(50, 50, 25, al_map_rgb(0, 0, 255));
	//std::cout << "plyr1.x = " << x << endl;
	//al_draw_filled_circle(x, y, 25, al_map_rgb(0, 0, 255));
}



void Sprite::MoveUp()
{
	m_posy -= 4;
	if (m_posy < 0)
		m_posy = 0;
}


void Sprite::MoveDown()
{
	m_posy += 4;
	if (m_posy > displayHeight - 16)
		m_posy = displayHeight - 16;
}


void Sprite::MoveLeft()
{
	m_posx -= 2;
	if (m_posx < 0)
		m_posx = 0;
}


void Sprite::MoveRight()
{
	m_posx += 2;
	if (m_posx > displayWidth - 16)
		m_posx = displayWidth - 16;
}






/*
ALLEGRO_BITMAP *image = NULL;
image = al_load_bitmap("Assets/Plane_sRGB2.png");
imageWidth = al_get_bitmap_width(image2);
imageHeight = al_get_bitmap_height(image2);
*/