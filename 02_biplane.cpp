
//void BiplaneFloatPoint(ALLEGRO_DISPLAY *&display, SpaceShip &someSpaceShip);			//original fwd declare function

void BiplaneFloatPoint(ALLEGRO_DISPLAY *&display);			//fwd declare function


//void BiplaneFloatPoint(ALLEGRO_DISPLAY *&display, SpaceShip &someSpaceShip)			//original
void BiplaneFloatPoint(ALLEGRO_DISPLAY *&display)
{
	//deceleration
	if (plyr1.length >= 10.0) plyr1.length -= 0.10;

	// check the keys and adjust length and angle of the objects velocity vector according to player input
	al_get_keyboard_state(&keyState);

	if (al_key_down(&keyState, ALLEGRO_KEY_W) && plyr1.length < 15.0)	//If accel (up) and speed < X then accelerate
		plyr1.length += 0.75;

	if (al_key_down(&keyState, ALLEGRO_KEY_S) && plyr1.length > -10.0)	//If braking (down) and speed > X then slow down
		plyr1.length -= 0.75;

	if (al_key_down(&keyState, ALLEGRO_KEY_A))
		plyr1.angle -= 0.06;

	if (al_key_down(&keyState, ALLEGRO_KEY_D))
		plyr1.angle += 0.06;


	// calculate the x- and y-coordinates of the velocity vector
	plyr1.velx = plyr1.length * cos(plyr1.angle);
	plyr1.vely = plyr1.length * sin(plyr1.angle);


	// move the object, and make sure it stays within the display
	plyr1.posx += plyr1.velx;
	if (plyr1.posx >= DisplayWidth) plyr1.posx -= DisplayWidth;
	if (plyr1.posx < 0) plyr1.posx += DisplayWidth;

	plyr1.posy += plyr1.vely;
	if (plyr1.posy >= DisplayHeight) plyr1.posy -= DisplayHeight;
	if (plyr1.posy < 0) plyr1.posy += DisplayHeight;

	// draw the object
	//al_draw_filled_circle(plyr1.posx, plyr1.posy, 25, al_map_rgb(0, 0, 255));
	al_draw_scaled_rotated_bitmap(image2, image2Width / 2, image2Height / 2, plyr1.posx, plyr1.posy, 0.3, 0.3, plyr1.angle, 0);
	al_draw_line(plyr1.posx, plyr1.posy, plyr1.posx + (plyr1.length + 5.0) * cos(plyr1.angle), plyr1.posy + (plyr1.length + 5.0) * sin(plyr1.angle), al_map_rgb(0, 255, 0), 1);