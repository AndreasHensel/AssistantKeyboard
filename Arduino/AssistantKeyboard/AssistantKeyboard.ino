// AssistantKeyboard
//
// für Hardware Version 0.1
//
// die Sketch-Projektdatei enthält das Basisprogramm mit allen grundlegenden Funktionen
// Verschiedene Ausführungen der Konfiguration wird durch das entsprechende Include festgelegt.
// Dort sind auch die Tastentexte hinterlegt.

// ** Arduino-Includes
#include <Keyboard.h> // in IDE integriert

// ** externe Includes
// OLED-Ansteuerung
#include <GyverOLED.h>  //https://github.com/GyverLibs/GyverOLED

// ** Includes für verschiedene Ausführungen

// Dreh-Encoder
// This optional setting causes Encoder to use more optimized code,
// It must be defined before Encoder.h is included.
#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>  // https://github.com/PaulStoffregen/Encoder 

// ** Konstanten
// Version der Software, enthält auch die Ausführung
const char cAK_ver[5] ="v0.1 ";

// ** Hardware-Definition
// Anzahl der Tasten (3x3 Tasten, Drehencoder-Taste)
const int cAK_KeyCount = 10;

// onboard LEDs
const int cRX_LED = 17;
const int cTX_LED = 30;

// Pins Drehencoder
const int cAK_EncoderA = 0;
const int cAK_EncoderB = 1;

// Pins Tastenmatrix
const int cAK_KeyColumn [3] = {10,16,14};
const int cAK_KeyRow [3] = {6,7,8};

// **  Include für Ausführung
#include <Test.h>
//#include <AK_???.h>
//#include <AK_???.h>
//const int cAK_ModeCount = 2;
//const char cAK_Variant[5] = {"Test "};
//const char *cAK_ModeText[cAK_ModeCount] = {" normal  "," Seminar "};
//const char *cAK_KeyText0[cAK_KeyCount] = {"00***","01***","02***","03***","04***","05***","06***","07***","08***","09***"};
//const char *cAK_KeyText1[cAK_KeyCount] = {"10###","11###","12###","13###","14###","15###","16###","17###","18###","19###"};

// ** Textpositionen
// Textposition für die Anzeige des aktuellen Modus im Grunbdbild
const int cAK_ModeTextXpos = 80;
const int cAK_ModeTextYpos = 1;
// Textpostionen der Tastenbeschriftung
const int cAK_KeyTextXpos[cAK_KeyCount] = {1,8,48,90,8,48,90,8,48,90};
const int cAK_KeyTextYpos[cAK_KeyCount] = {1,2,2,2,4,4,4,6,6,6};

// ** Variablen
// OLED
GyverOLED<SSH1106_128x64> AK_Oled;

// Drehencoder
Encoder AK_Encoder(cAK_EncoderA, cAK_EncoderB);

// allgemeine globale Variablen
int AK_Mode = 0;
int AK_ModeSelect = 0;
bool AK_SetupMode = true;

// Status der Tasten
bool AK_KeyIsPressed[cAK_KeyCount] =  {false,false,false,false,false,false,false,false,false,false};
bool AK_KeyPressedMem[cAK_KeyCount] = {false,false,false,false,false,false,false,false,false,false};
bool AK_KeyPressed[cAK_KeyCount] =    {false,false,false,false,false,false,false,false,false,false};
bool AK_KeyReleased[cAK_KeyCount] =   {false,false,false,false,false,false,false,false,false,false};



void setup()
{
// Pinmodes
  pinMode(cRX_LED, OUTPUT);
  pinMode(cTX_LED, OUTPUT);

// OLED insitialisieren und Startbild anzeigen
  AK_Oled.init();
  AK_Oled.clear();
  AK_Oled.home();            // курсор в 0,0
  AK_Oled.print("Hallo!");   // печатай что угодно: числа, строки, float, как Serial!
  AK_Oled.setCursor(1, 2);   // курсор в (пиксель X, строка Y)
  AK_Oled.print("Ich bin Dein");
  AK_Oled.setCursor(1, 4);
  AK_Oled.invertText(true);
  AK_Oled.print("* AssistantKeyboard *");
  AK_Oled.invertText(false);
  AK_Oled.setCursor(1, 6);
  AK_Oled.print(cAK_ver);
  AK_Oled.print(cAK_Variant);
  AK_Oled.update();
  delay(2000);

// initial Tastenbelegung anzeigen
  AK_DrawKeyText(AK_Mode);

};

void loop()
{
// LEDs für Debug
  digitalWrite(cRX_LED, AK_SetupMode);
  digitalWrite(cRX_LED, false);

// Tasten einlesen
  AK_KeyRead();
  AK_KeyProcess();
  AK_RotaryRead();

 // Funktionen aufrufen
 if (AK_SetupMode)
  {
// im Setup-Mode Tastatur-Funktionen ausschalten
    Keyboard.releaseAll();
    Keyboard.end();
  }
    else
  {
// Normaler Mode: Tastaturfunktionen aktivieren
    Keyboard.begin();

// 
    for (int Key; Key<cAK_KeyCount ;Key++)
    {
// wurde eine Taste gedrückt: Aktion aufrufen
      if (AK_KeyPressed[Key])
      switch (Key)
      {
        case 0: AK_Key0PressAction(AK_Mode); break;
        case 1: AK_Key1PressAction(AK_Mode); break;
        case 2: AK_Key2PressAction(AK_Mode); break;
        case 3: AK_Key3PressAction(AK_Mode); break;
        case 4: AK_Key4PressAction(AK_Mode); break;
        case 5: AK_Key5PressAction(AK_Mode); break;
        case 6: AK_Key6PressAction(AK_Mode); break;
        case 7: AK_Key7PressAction(AK_Mode); break;
        case 8: AK_Key8PressAction(AK_Mode); break;
        case 9: AK_Key9PressAction(AK_Mode); break;
      };
// wurde eine Taste losgelassen: Aktion aufrufen
      if (AK_KeyReleased[Key])
      switch (Key)
      {
        case 0: AK_Key0ReleaseAction(AK_Mode); break;
        case 1: AK_Key1ReleaseAction(AK_Mode); break;
        case 2: AK_Key2ReleaseAction(AK_Mode); break;
        case 3: AK_Key3ReleaseAction(AK_Mode); break;
        case 4: AK_Key4ReleaseAction(AK_Mode); break;
        case 5: AK_Key5ReleaseAction(AK_Mode); break;
        case 6: AK_Key6ReleaseAction(AK_Mode); break;
        case 7: AK_Key7ReleaseAction(AK_Mode); break;
        case 9: AK_Key9ReleaseAction(AK_Mode); break;
      };

    };
  };
  
};

// ** Tastentexte anzeigen
void AK_DrawKeyText(int Mode)
{
  AK_Oled.clear();
  AK_Oled.invertText(false);
  AK_Oled.setScale(1);
  AK_Oled.home();           
  AK_Oled.print("<-        Mode: ");
  
  AK_Oled.setCursor(1,2);   
  AK_Oled.setCursor(1,4);   
  AK_Oled.setCursor(1,6);   
  AK_Oled.fastLineH(11,0,127);
  AK_Oled.fastLineH(27,0,127);
  AK_Oled.fastLineH(43,0,127);
  AK_Oled.fastLineH(59,0,127);
  AK_Oled.fastLineV(0,12,59);
  AK_Oled.fastLineV(43,12,59);
  AK_Oled.fastLineV(83,12,59);
  AK_Oled.fastLineV(127,12,59);

  for (int i=0; i<cAK_KeyCount; i++)
  {
    AK_Oled.setCursor(cAK_KeyTextXpos[i],cAK_KeyTextYpos[i]);
    if (Mode == 0)
      AK_Oled.print(cAK_KeyText0[i]);
    else
      AK_Oled.print(cAK_KeyText1[i]);
    
  };
  AK_Oled.update();
};

// ** Setup-Bild anzeigen
void AK_DrawSetup()
{
  AK_Oled.clear();
  AK_Oled.invertText(false);
  AK_Oled.setScale(1);
  AK_Oled.home();
  AK_Oled.print("Modus wählen:");
  AK_Oled.setCursor(140,3);
  for (int i; i < cAK_ModeCount; i++)
  {
    AK_Oled.invertText(i==AK_ModeSelect);
    AK_Oled.setCursor(140,i+3);
    AK_Oled.print(cAK_ModeText[i]);
  } ;  
};

// ** Tasten einlesen
void AK_KeyRead()
{
//  AK_KeyIsPressed[0] = digitalRead(AK_Key0);
//  AK_KeyIsPressed[1] = digitalRead(AK_Key1);
};

// ** Tasten auswerten
void AK_KeyProcess()
{
  for (int Key=0; Key<cAK_KeyCount; Key++)
  {
    AK_KeyPressed[Key] = false;
    AK_KeyReleased[Key] = false;
    if (AK_KeyIsPressed[Key])
      AK_KeyPressed[Key] = !AK_KeyPressedMem[Key];
    else
      AK_KeyReleased[Key] = AK_KeyPressedMem[Key];
    AK_KeyPressedMem[Key] = AK_KeyIsPressed[Key];
  };
};

// ** Drehencoder einlesen
void AK_RotaryRead()
{

};

