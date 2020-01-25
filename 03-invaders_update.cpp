//Dependecies...


/*WIP C++

int lpctr = invaders.sizeof();
int invaders_dir {right};							//make this an enum?
int invaders_lstdir {0};							


//REM If all eNeMiEs have moved, we set the one to be moved next, based on direction
  110 IF E1D%=8 AND LPCTR%=25 LET LPCTR% = 24 : 
  ELSE IF E1D%=1 AND LPCTR%=25 LET LPCTR%=17 : REM If all eNeMiEs have moved, we set the one to be moved next, based on direction


 //REM Check for eNeMiEs that are alive and at the edge of the playfield, where further movement would take them over the edge of the playfield...
 //163 IF LPCTR%=0 AND E1D%=41 THEN : LET LPCTR%=17 : LET E1D%=1
 //164 IF LPCTR%=25 AND E1D%=42 THEN : LET LPCTR%=24 : LET E1D%=8
 //170 IF LPCTR%=0 AND E1D%=8 OR LPCTR%=17 AND E1D%=1 THEN PROC_ChkEdg


 //REM Check eNeMiEs moving Right (8) and update the next eNeMiE position/direction as applicable
 //210 IF E1D%=8 THEN
 //211 LET STDNME{(LPCTR%)}.LSTX%=STDNME{(LPCTR%)}.POSX%
 //212 IF STDNME{(LPCTR%)}.HLTH%=10 LET STDNME{(LPCTR%)}.POSX%=STDNME{(LPCTR%)}.POSX%+8           REM playing here to vary speed from +1 to +32
 //213 LET STDNME{(LPCTR%)}.LSTY%=STDNME{(LPCTR%)}.POSY%
 //214 IF STDNME{(LPCTR%)}.HLTH%=10 LET STDNME{(LPCTR%)}.POSY%=STDNME{(LPCTR%)}.POSY%
 //215 ENDIF





		DEFPROC_ChkEdg : REM Check after all eNeMiEs have completed a cycle of movement to see if any are at the edge of the playfield
		REM MOVE 900,1000 : GCOL 0,0 : VDU 224,224,224,224,224,224,224 : REM Undraw debug
		REM MOVE 288,1000 : GCOL 0,0 : VDU 224,224,224,224 : REM Undraw score
		REM MOVE 64,1000 : GCOL 0,3 : PRINT "SCORE: ";STDNME{(3)}.POSX%
		REM MOVE 432,1000 : GCOL 0,3 : PRINT "STDNME{(1)}.POSX: ";LPCTR% : REM Debug
		REM ANYKEY% = GET
		IF E1D%=8 THEN
		  FOR X=1 TO 24
			IF STDNME{(X)}.HLTH%=10 AND STDNME{(X)}.POSX% >=1184 : LET E1D%=41 : LET LPCTR%=24 : REM LPCTR%=10 Means Collision with Edge
		  NEXT X
		ENDIF

		IF E1D%=1 THEN
		  FOR X=1 TO 24
			IF STDNME{(X)}.HLTH%=10 AND STDNME{(X)}.POSX% <=64 : LET E1D%=42 : LET LPCTR%=17 : REM LPCTR%=10 Means Collision with Edge
		  NEXT X
		ENDIF
		REM ANYKEY% = GET
		REM IF E1D%=8 AND LPCTR%=10 LET LPCTR% = 9
		IF E1D%=8 AND LPCTR%=0 LET LPCTR%=24
		IF E1D%=1 AND LPCTR%=25 LET LPCTR%=17
		REM IF E1D%=41 AND LPCTR%=10 LET LPCTR%=9
		REM IF E1D%=42 AND LPCTR%=10 LET LPCTR%=7
		ENDPROC




*/




/*BASIC

   53 LPCTR%=24 :REM This must be equal to the number of enemies, per the start of the game
   54 E1D%=8 : LSTDIR%=0 : REM 0 = Static, 1 = Left, 2=Up, 4=Down, 8=Right, 41=Down/Left & 42=Down/Right
   56 PROC_SetupNME : REM Setup Variables
   57 LET JOYX%=0 : LET JOY0%=0


   60 REM CLS

   70 REM WAIT 5000

	  REM Main loop starts here at 100

  100 JOYX%=ADVAL(1) : JOY0%=ADVAL(0)        REM Get values from Joystick
  102 MOVE 64,1000 : GCOL 0,3 : PRINT "SCORE: ";SC%
  103 MOVE 432,1000 : GCOL 0,3 : PRINT "STDNME{(1)}.POSX: ";JOYX% : REM Debug


  110 IF E1D%=8 AND LPCTR%=25 LET LPCTR% = 24 : ELSE IF E1D%=1 AND LPCTR%=25 LET LPCTR%=17 : REM If all eNeMiEs have moved, we set the one to be moved next, based on direction


	  REM Check for eNeMiEs that are alive and at the edge of the playfield, where further movement would take them over the edge of the playfield...
  163 IF LPCTR%=0 AND E1D%=41 THEN : LET LPCTR%=17 : LET E1D%=1
  164 IF LPCTR%=25 AND E1D%=42 THEN : LET LPCTR%=24 : LET E1D%=8
  170 IF LPCTR%=0 AND E1D%=8 OR LPCTR%=17 AND E1D%=1 THEN PROC_ChkEdg

	  REM Check eNeMiEs moving Right (8) and update the next eNeMiE position/direction as applicable
  210 IF E1D%=8 THEN
  211   LET STDNME{(LPCTR%)}.LSTX%=STDNME{(LPCTR%)}.POSX%
  212   IF STDNME{(LPCTR%)}.HLTH%=10 LET STDNME{(LPCTR%)}.POSX%=STDNME{(LPCTR%)}.POSX%+8           REM playing here to vary speed from +1 to +32
  213   LET STDNME{(LPCTR%)}.LSTY%=STDNME{(LPCTR%)}.POSY%
  214   IF STDNME{(LPCTR%)}.HLTH%=10 LET STDNME{(LPCTR%)}.POSY%=STDNME{(LPCTR%)}.POSY%
  215 ENDIF


	  REM Check eNeMiEs moving Left (1) and update the next eNeMiE position/direction as applicable
  220 IF E1D%=1 THEN
  222   LET STDNME{(LPCTR%)}.LSTX%=STDNME{(LPCTR%)}.POSX%
  223   IF STDNME{(LPCTR%)}.HLTH%=10 LET STDNME{(LPCTR%)}.POSX%=STDNME{(LPCTR%)}.POSX%-8          REM playing here to vary speed from -1 to -32
  224   LET STDNME{(LPCTR%)}.LSTY%=STDNME{(LPCTR%)}.POSY%
  225   IF STDNME{(LPCTR%)}.HLTH%=10 LET STDNME{(LPCTR%)}.POSY%=STDNME{(LPCTR%)}.POSY%
  226 ENDIF

	  REM Check eNeMiEs moving Down and then Left (41) and update the next eNeMiE position/direction as applicable
  230 IF E1D%=41 THEN
  231   REM MOVE 900,1000 : GCOL 0,0 : VDU 224,224,224,224,224,224,224 : REM Undraw debug
  232   REM MOVE 432,1000 : GCOL 0,3 : PRINT "STDNME{(1)}.POSX: ";LPCTR% : REM ANYKEY% = GET
  233   LET STDNME{(LPCTR%)}.LSTX%=STDNME{(LPCTR%)}.POSX%
  234   IF STDNME{(LPCTR%)}.HLTH%=10 LET STDNME{(LPCTR%)}.POSX%=STDNME{(LPCTR%)}.POSX%
  235   LET STDNME{(LPCTR%)}.LSTY%=STDNME{(LPCTR%)}.POSY%
  236   IF STDNME{(LPCTR%)}.HLTH%=10 LET STDNME{(LPCTR%)}.POSY%=STDNME{(LPCTR%)}.POSY%-32
  237 ENDIF

	  REM Check eNeMiEs moving Down and then Right (42) and update the next eNeMiE position/direction as applicable
  240 IF E1D%=42 THEN
  241   REM MOVE 900,1000 : GCOL 0,0 : VDU 224,224,224,224,224,224,224 : REM Undraw debug
  242   REM MOVE 432,1000 : GCOL 0,3 : PRINT "STDNME{(1)}.POSX: ";LPCTR% : REM ANYKEY% = GET
  243   LET STDNME{(LPCTR%)}.LSTX%=STDNME{(LPCTR%)}.POSX%
  244   IF STDNME{(LPCTR%)}.HLTH%=10 LET STDNME{(LPCTR%)}.POSX%=STDNME{(LPCTR%)}.POSX%
  245   LET STDNME{(LPCTR%)}.LSTY%=STDNME{(LPCTR%)}.POSY%
  246   IF STDNME{(LPCTR%)}.HLTH%=10 LET STDNME{(LPCTR%)}.POSY%=STDNME{(LPCTR%)}.POSY%-32
  247 ENDIF

*/

