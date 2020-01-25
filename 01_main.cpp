//Dependencies... Ideally, just those that would be required for this module to compile independently.
//#include<vector>

#include "01_main.hpp"

//#include "02_gamecode_01.hpp"


/*Uncomment the lines below to run concatenate sprite tool*/
	//ConcatenateSpriteFrames("/Agony/OwlAnimR", ".bmp");											//insert asset name as approprite, would be good to prompt for user input perhaps.
	//return 0;

	//Sprite plyr1{ "/Agony/OwlAnimR", "AnimatedSprite", ".bmp", 16, 640, 360 };

	/*Automatic allocation on stack...
	application myallegro;																	
	myallegro.init();
	myallegro.createWindow(displayWidth, displayHeight, FPS);
	myallegro.gameLoop();
	*/


int main()
{
	//invctr = 0;
	
	std::cout << "01_main.cpp - press enter to start main() \n";
	system("pause");
	//std::cout <<  "...the current size of invader_glob_vector = " << invader_glob_vector.size() << "\n";


	/*Example code to demonstarte behaviour of vector
	std::vector<int> input_vector;
	input_vector.push_back(10);			//size = 1
	input_vector.push_back(20);			//size = 2

	arraytest_passbyreference(input_vector);		// input_vector is an array that is populated further by function call... proven by it's size when printed = 3
	for (int i = 0; i < input_vector.size(); i++)
		std::cout << "input_vector" << "[" << i << "]" << "=" << input_vector[i] << " ...and the current size of input.vector = " << input_vector.size() << "\n";
	*/



	/*Moved to... !globals.cpp*/
	//std::cout << "01_main.cpp - press enter to create *myapp \n";
	//system("pause");
	//application *myapp = new application();															//create *myapp (ptr), where type of data pointed to is... new (dynamic/heap) instance of application (class) 					


	std::cout << "01_main.cpp - press enter to start myapp->init() \n";
	system("pause");
	myapp->init();																					//dereference *myapp (ptr) and call the function init							
	
	std::cout << "01_main.cpp - press enter to start myapp-> createWindow(displayWidth, displayHeight, FPS) \n";
	system("pause");
	myapp-> createWindow(displayWidth, displayHeight, FPS);

	
	{

		std::cout << "main.cpp - press enter to start createarrayofinvaders2 \n";
		system("pause");
		//createarrayofinvaders();
		std::vector<Sprite> vectorarrayofinvaders2 = createarrayofinvaders2();				//creates a vectorarrayofinvaders per the return from function named createarrayofinvaders2()
		//std::cout << "...the current size of vectorarrayofinvaders2 = " << vectorarrayofinvaders2.size() << "\n";
		system("pause");


		//std::cout << "main.cpp - press enter to start initarrayofinvaders2 \n";
		//system("pause");
		//initarrayofinvaders3(vectorarrayofinvaders2);


		
		std::cout << "main.cpp - press enter to start somegamecode \n";
		system("pause");
		somegamecode();						//Load bitmap for plyr

		std::cout << "main.cpp - press enter to... initializeInvaders \n";
		system("pause");
		initialize_Invaders();				//Load bitmap for invaders


		std::cout << "01_main.cpp - press enter to start gameLoop\n";
		system("pause");
		myapp->gameLoop(vectorarrayofinvaders2);																				//dereference *myapp (ptr) and call the function gameloop


	}

	std::cout << "01_main.cpp - exited game loop\n";
	std::cout << "Game Object Destructors should have been called \n";
	std::cout << "All objects that need Delete, must now be deleted \n";


	/*
	std::cout << "main.cpp - press enter to start somegamecode2\n";
	system("pause");
	somegamecode2();
	*/


	//al_rest(1);																					//wait for some milliseconds


	std::cout << "01_main.cpp - press enter to delete game objects\n";
	system("pause");
	delete plyr01_glob_ptr;
	//delete invader_glob_ptr;
	//delete[] invader_glob_ptr;																		//Delete array

	//std::cout << "01_main.cpp - press enter to delete myapp\n";
	//system("pause");
	delete myapp;																					//only needed if dynamically allocating instance of application



	std::cout << "main.cpp - now starting to shutdown/uninstall allegro components\n";
	system("pause");


	std::cout << "+App.cpp - Temporary hacked in font cleanup - al_destroy_font(bebasneuereg24pt)\n";
	std::cout << "App.cpp - al_shutdown_ttf_addon()\n";
	system("pause");
	al_shutdown_ttf_addon();
	std::cout << "App.cpp - al_shutdown_font_addon()\n";
	system("pause");
	al_shutdown_font_addon();



	std::cout << "main.cpp - press enter to start... al_shutdown_primitives_addon()\n";
	system("pause");
	al_shutdown_primitives_addon();
	std::cout << "main.cpp - press enter to start... al_shutdown_image_addon()\n";
	system("pause");
	al_shutdown_image_addon();
	std::cout << "main.cpp - press enter to start... al_uninstall_mouse()\n";
	system("pause");
	al_uninstall_mouse();
	std::cout << "main.cpp - press enter to start... al_uninstall_keyboard()\n";
	system("pause");
	al_uninstall_keyboard();
	
	std::cout << "main.cpp - press enter to start... al_uninstall_system()\n";
	system("pause");
	al_uninstall_system();							//This uninstalls the Allegro libs, currently causing grief when vectors destruct after calling it...
	

	std::cout << "main.cpp - reached the logical end\n";
	system("pause");
	



	/*
	std::cout << "main.cpp - press enter to start arraytest\n";
	system("pause");
	arraytest();
	*/


	/*Older method to setup/shutdown allegro stuff
	//void allegro_shut_down(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue)			//someday I might use this function maybe, although most is done by the Deconstructor?
	//{

	//al_destroy_event_queue(event_queue);															//Handled via App\Destructor
	//al_destroy_timer(timer);																		//Handled via App\Destructor
	//al_destroy_display(display);																	//Handled via App\Destructor

	//al_uninstall_audio();																			//Not used just yet

	//std::cout << "main.cpp - al_shutdown_ttf_addon()\n";
	//system("pause");
	//al_shutdown_ttf_addon();																		//Temporarily inserted into App.cpp
	//std::cout << "main.cpp - al_shutdown_font_addon()\n";
	//system("pause");
	//al_shutdown_font_addon();																		//Temporarily inserted into App.cpp
	*/

	return 0;																				//the end
}



