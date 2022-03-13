//** Variante: Test#ifndef Test_h#define Test_h#define KEY_SYSRQ 0x46#define WHEEL_DIST 1// ** Konstantenconst int AK_MODECOUNT = 3;const char AK_VARIANT[] = {"Test "};const char *AK_MODETEXT[AK_MODECOUNT] = {" normal ","Presentr"," Office "};const char *AK_KEYTEXT[AK_MODECOUNT][AK_KEYCOUNT] =	{		{"PlayP","Druck","Calc ","Teams","Paste","TCall","MicMt","PASTE","Copy "," PTT "},		{" <-> "," ESC ","White","Teams","Start","Black","MicMt","Prev.","Next "," PTT "},		{"Scrol"," ESC ","Calc ","Print","Paste"," Cut ","Menu ","PASTE","Copy ","Enter"},	};	//const char *AK_KEYTEXT3[AK_KEYCOUNT] = {"30§§§","31§§§","32§§§","33§§§","34§§§","35###","36§§§","37§§§","38§§§","29§§§"};//const char *AK_KEYTEXT4[AK_KEYCOUNT] = {"40§§§","41§§§","42§§§","43§§§","44§§§","45###","46§§§","47§§§","48§§§","49§§§"};//const char *AK_KEYTEXT5[AK_KEYCOUNT] = {"50§§§","51§§§","52§§§","53§§§","54§§§","55###","56§§§","57§§§","58§§§","59§§§"};// ** Encoder-Funkionenvoid AK_EncoderUpAction (int Mode){  switch (Mode)  {    case 0:	  Consumer.write(MEDIA_VOLUME_UP);      break;    case 1:   	  Keyboard.write(KEY_RIGHT_ARROW);      break;    case 2:	  Mouse.move(0,0,-WHEEL_DIST);      break;  };};void AK_EncoderDownAction (int Mode){  switch (Mode)  {    case 0:	  Consumer.write(MEDIA_VOLUME_DOWN);      break;    case 1:   	  Keyboard.write(KEY_LEFT_ARROW);      break;    case 2:	  Mouse.move(0,0,WHEEL_DIST);      break;  };};// ** Tastenaktionenvoid AK_Key0PressAction (int Mode){  switch (Mode)  {    case 0:      break;    case 1:      break;    case 2:	  Keyboard.press(KEY_LEFT_CTRL);      break;  };};void AK_Key0ReleaseAction (int Mode){  switch (Mode)  {    case 0:		  Consumer.write(MEDIA_PLAY_PAUSE);      break;    case 1:		  Consumer.write(MEDIA_PLAY_PAUSE);      break;    case 2:	  Keyboard.release(KEY_LEFT_CTRL);      break;  };};void AK_Key1PressAction (int Mode){  switch (Mode)  {    case 0:      Keyboard.write(KEY_PRINTSCREEN);    break;    case 1:      Keyboard.write(KEY_ESC);      break;    case 2:      Keyboard.write(KEY_ESC);      break;  };};void AK_Key1ReleaseAction (int Mode){  switch (Mode)  {    case 0:      break;    case 1:      break;    case 2:      break;  };};void AK_Key2PressAction (int Mode){  switch (Mode)  {    case 0:      Consumer.write(CONSUMER_CALCULATOR);      break;    case 1:	  Keyboard.write('w');      break;    case 2:      Consumer.write(CONSUMER_CALCULATOR);      break;  };};void AK_Key2ReleaseAction (int Mode){  switch (Mode)  {    case 0:      break;    case 1:      break;    case 2:      break;  };};void AK_Key3PressAction (int Mode){  switch (Mode)  {    case 0:	  Keyboard.press(KEY_LEFT_CTRL);	  Keyboard.press(KEY_LEFT_SHIFT);	  Keyboard.press('e');	  Keyboard.releaseAll();      break;    case 1:	  Keyboard.press(KEY_LEFT_CTRL);	  Keyboard.press(KEY_LEFT_SHIFT);	  Keyboard.press('e');	  Keyboard.releaseAll();      break;    case 2:      Keyboard.write(KEY_PRINTSCREEN);  break;  };};void AK_Key3ReleaseAction (int Mode){  switch (Mode)  {    case 0:      break;    case 1:      break;    case 2:      break;  };};void AK_Key4PressAction (int Mode){  switch (Mode)  {    case 0:	  Keyboard.press(KEY_LEFT_CTRL);	  Keyboard.press('v');      break;    case 1:	  Keyboard.press(KEY_LEFT_SHIFT);	  Keyboard.press(KEY_F5);	  Keyboard.releaseAll();      break;    case 2:	  Keyboard.press(KEY_LEFT_CTRL);	  Keyboard.press('v');      break;  };};void AK_Key4ReleaseAction (int Mode){  switch (Mode)  {    case 0:	  Keyboard.releaseAll();      break;    case 1:      break;    case 2:	  Keyboard.releaseAll();      break;  };};void AK_Key5PressAction (int Mode){  switch (Mode)  {    case 0:	  Keyboard.press(KEY_LEFT_CTRL);	  Keyboard.press(KEY_LEFT_SHIFT);	  Keyboard.press('h');	  Keyboard.releaseAll();      break;    case 1:	  Keyboard.write('b');      break;    case 2:	  Keyboard.press(KEY_LEFT_CTRL);	  Keyboard.write('x');	  Keyboard.releaseAll();      break;  };};void AK_Key5ReleaseAction (int Mode){  switch (Mode)  {    case 0:      break;    case 1:      break;    case 2:      break;  };};void AK_Key6PressAction (int Mode){  switch (Mode)  {    case 0:	  Keyboard.press(KEY_LEFT_CTRL);	  Keyboard.press(KEY_LEFT_SHIFT);	  Keyboard.press('m');	  Keyboard.releaseAll();      break;    case 1:	  Keyboard.press(KEY_LEFT_CTRL);	  Keyboard.press(KEY_LEFT_SHIFT);	  Keyboard.press('m');	  Keyboard.releaseAll();      break;    case 2:      Keyboard.write(KEY_MENU);      break;  };};void AK_Key6ReleaseAction (int Mode){  switch (Mode)  {    case 0:      break;    case 1:      break;    case 2:      break;  };};void AK_Key7PressAction (int Mode){  switch (Mode)  {    case 0:	  Keyboard.press(KEY_LEFT_CTRL);	  Keyboard.press(KEY_LEFT_SHIFT);	  Keyboard.press('v');	  Keyboard.release(KEY_LEFT_CTRL);	  Keyboard.release('v');      break;    case 1:	  Keyboard.press(KEY_LEFT_ARROW);      break;    case 2:	  Keyboard.press(KEY_LEFT_CTRL);	  Keyboard.press(KEY_LEFT_SHIFT);	  Keyboard.press('v');	  Keyboard.release(KEY_LEFT_CTRL);	  Keyboard.release('v');      break;  };};void AK_Key7ReleaseAction (int Mode){  switch (Mode)  {    case 0:	  Keyboard.releaseAll();      break;    case 1:	  Keyboard.release(KEY_LEFT_ARROW);      break;    case 2:	  Keyboard.releaseAll();      break;  };};void AK_Key8PressAction (int Mode){  switch (Mode)  {    case 0:	  Keyboard.press(KEY_LEFT_CTRL);	  Keyboard.press('c');      break;    case 1:   	  Keyboard.press(KEY_RIGHT_ARROW);	  break;    case 2:	  Keyboard.press(KEY_LEFT_CTRL);	  Keyboard.press('c');      break;  };};void AK_Key8ReleaseAction (int Mode){  switch (Mode)  {    case 0:	  Keyboard.releaseAll();      break;    case 1:   	  Keyboard.release(KEY_RIGHT_ARROW);      break;    case 2:	  Keyboard.releaseAll();      break;  };};void AK_Key9PressAction (int Mode){  switch (Mode)  {    case 0:	  Keyboard.press(KEY_LEFT_CTRL);	  Keyboard.press(KEY_LEFT_SHIFT);	  Keyboard.write('m');	  Keyboard.releaseAll();      break;    case 1:	  Keyboard.press(KEY_LEFT_CTRL);	  Keyboard.press(KEY_LEFT_SHIFT);	  Keyboard.write('m');	  Keyboard.releaseAll();      break;    case 2:	  Keyboard.write(KEY_RETURN);      break;  };};void AK_Key9ReleaseAction (int Mode){  switch (Mode)  {    case 0:	  Keyboard.press(KEY_LEFT_CTRL);	  Keyboard.press(KEY_LEFT_SHIFT);	  Keyboard.write('m');	  Keyboard.releaseAll();      break;    case 1:	  Keyboard.press(KEY_LEFT_CTRL);	  Keyboard.press(KEY_LEFT_SHIFT);	  Keyboard.write('m');	  Keyboard.releaseAll();      break;    case 2:      break;  };};#endif