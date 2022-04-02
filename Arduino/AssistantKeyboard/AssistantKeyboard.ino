// AssistantKeyboard
//
// für Hardware Version 1.1
//
// die Sketch-Projektdatei enthält das Basisprogramm mit allen grundlegenden Funktionen
// Verschiedene Ausführungen der Konfiguration wird durch das entsprechende Include festgelegt.
// Dort sind auch die Tastentexte hinterlegt.

// ** externe Includes
// OLED-Ansteuerung
#include <GyverOLED.h>  //https://github.com/GyverLibs/GyverOLED

// Dreh-Encoder
// This optional setting causes Encoder to use more optimized code,
// It must be defined before Encoder.h is included.
#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>  // https://github.com/PaulStoffregen/Encoder

// Consumer: für Media-Funktionen
#define HID_CUSTOM_LAYOUT
#define LAYOUT_GERMAN
#include <HID-Project.h>

// ** Konstanten
// Version der Software
const char AK_VER[] = "v1.1 ";

// ** Hardware-Definition
// Anzahl der Tasten (3x3 Tasten, Drehencoder-Taste)
const int AK_KEYCOUNT = 10;

// const int AK_KEYDEBOUNCE = 1;

// onboard LEDs
const int PIN_RX_LED = 17;
const int PIN_TX_LED = 30;

// Pins Drehencoder
const int PIN_AK_ENCODERA = 1;
const int PIN_AK_ENCODERB = 0;
const int PIN_AK_ENCODERP = 4;

// Pins Tastenmatrix
const int AK_KEYCOLUMNCOUNT = 3;
const int AK_KEYROWCOUNT = 3;
const int PIN_AK_KEYCOLUMN[AK_KEYCOLUMNCOUNT] = { 10, 16, 14 };
const int PIN_AK_KEYROW[AK_KEYROWCOUNT] = { 6, 7, 8 };

// **  Include für Ausführung
#include <IBF.h>

// ** Textpositionen
// Textposition für die Anzeige des aktuellen Modus im Grundbild
const int AK_MODETEXTX = 80;
const int AK_MODETEXTY = 0;
// Textpostionen der Tastenbeschriftung
const int AK_KEYTEXTX[AK_KEYCOUNT] = { 8, 8, 48, 90, 8, 48, 90, 8, 48, 90 };
const int AK_KEYTEXTY[AK_KEYCOUNT] = { 0, 2, 2, 2, 4, 4, 4, 6, 6, 6 };

// Spezielle Tasten
const int AK_SETUPENTERKEY = 9;
const int AK_SETUPCANCELKEY = 1;

// ** Variablen
// OLED
GyverOLED<SSH1106_128x64> AK_Oled;

// Drehencoder
Encoder AK_Encoder(PIN_AK_ENCODERA, PIN_AK_ENCODERB);

// allgemeine globale Variablen
int AK_Mode = 0;
int AK_ModeSelect = 0;
int AK_LastEncoderValue;
bool AK_SetupMode = true;
bool AK_SetupModeOn = false;

// Status der Tasten
bool AK_KeyIsPressed[AK_KEYCOUNT] = { false, false, false, false, false, false, false, false, false, false };
bool AK_KeyPressedMem[AK_KEYCOUNT] = { false, false, false, false, false, false, false, false, false, false };
bool AK_KeyPressed[AK_KEYCOUNT] = { false, false, false, false, false, false, false, false, false, false };
bool AK_KeyReleased[AK_KEYCOUNT] = { false, false, false, false, false, false, false, false, false, false };

// Encoder
bool AK_EncoderUp = false;
bool AK_EncoderDown = false;

void setup() {
  // ** Pinmodes

  // LED for ***debug
  // pinMode(PIN_RX_LED, OUTPUT);
  // pinMode(PIN_TX_LED, OUTPUT);
  // Serial.begin(9600);

  // pinmode für Tasten
  for (int i = 0; i < AK_KEYCOLUMNCOUNT; i++) {
    pinMode(PIN_AK_KEYCOLUMN[i], INPUT_PULLUP);
  };
  // Tastenmatrix initialisieren
  for (int i = 0; i < AK_KEYROWCOUNT; i++) {
    pinMode(PIN_AK_KEYROW[i], OUTPUT);
    digitalWrite(PIN_AK_KEYROW[i], true);
  };

  // ** Rotary
  pinMode(PIN_AK_ENCODERA, INPUT_PULLUP);
  pinMode(PIN_AK_ENCODERB, INPUT_PULLUP);
  pinMode(PIN_AK_ENCODERP, INPUT_PULLUP);

  // Init Encoder
  AK_Encoder.write(0);

    // ** OLED insitialisieren und Startbild anzeigen
  AK_Oled.init();
  AK_Oled.clear();
  AK_Oled.home();
  AK_Oled.print("Hallo!");
  AK_Oled.setCursor(1, 2);
  AK_Oled.print("Ich bin Dein");
  AK_Oled.setCursor(1, 4);
  AK_Oled.invertText(true);
  AK_Oled.print("* AssistantKeyboard *");
  AK_Oled.invertText(false);
  AK_Oled.setCursor(1, 6);
  AK_Oled.print(AK_VER);
  AK_Oled.print(AK_VARIANT);
  AK_Oled.update();
  delay(1500);
};

void loop() {
  // LEDs für ***debug
  // digitalWrite(PIN_RX_LED, !AK_SetupMode);
  // digitalWrite(PIN_TX_LED, true);

  // Entprellen
  //delay(AK_KEYDEBOUNCE);

  // Tasten einlesen
  AK_KeyRead();
  AK_KeyProcess();
  AK_RotaryRead();

  // Funktionen aufrufen
  if (AK_SetupMode)
  {
    // im Setup-Mode Tastatur-Funktionen ausschalten
    if (!AK_SetupModeOn)
    {
      Keyboard.releaseAll();
      Keyboard.end();
      Consumer.end();
      Mouse.end();
      AK_DrawSetup();
      AK_ModeSelect = AK_Mode;
      AK_SetupModeOn = true;
    }

    // Setup-Mode fertig?
    if (AK_KeyReleased[0] && !AK_KeyIsPressed[AK_SETUPENTERKEY])
    {
      AK_Mode = AK_ModeSelect;
      AK_SetupMode = false;
    }
    if (AK_KeyReleased[AK_SETUPCANCELKEY])
    {
      AK_SetupMode = false;
    }

    // vorherigen Eintrag anwählen
    if (AK_EncoderDown)
    {
      if (AK_ModeSelect <= 0)
      {
        AK_ModeSelect = AK_MODECOUNT - 1;
      }
      else
      {
        AK_ModeSelect--;
      };
    }

    // nächsten Eintrag wählen
    if (AK_EncoderUp)
    {
      AK_ModeSelect++;
      if (AK_ModeSelect >= AK_MODECOUNT)
      {
        AK_ModeSelect = 0;
      };
    };

    // Anzeige aktualisieren
    if (AK_EncoderUp | AK_EncoderDown)
    {
      AK_DrawSetup();
    }
  }
  else
  {
    // Normaler Mode: Tastaturfunktionen aktivieren
    if (AK_SetupModeOn)
    {
      Keyboard.begin();
      Consumer.begin();
      Mouse.begin();
      AK_DrawKeyText();
      AK_SetupModeOn = false;
    }

    //  Setup aufrufen
    if (AK_KeyIsPressed[0] && AK_KeyPressed[AK_SETUPENTERKEY]) {
      AK_SetupMode = true;
    }
    else

    // normaler Betrieb
    {
      if (AK_EncoderUp)
      {
        AK_EncoderUpAction(AK_Mode);
      };

      if (AK_EncoderDown)
      {
        AK_EncoderDownAction(AK_Mode);
      };

      for (int Key = 0; Key < AK_KEYCOUNT; Key++)
      {
        // wurde eine Taste gedrückt: Aktion aufrufen
        if (AK_KeyPressed[Key])
        {
          AK_UpdateKey(Key);
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
        };
        // wurde eine Taste losgelassen: Aktion aufrufen
        if (AK_KeyReleased[Key])
        {
          AK_UpdateKey(Key);
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
            case 8: AK_Key8ReleaseAction(AK_Mode); break;
            case 9: AK_Key9ReleaseAction(AK_Mode); break;
          };
        };
      };
    }
  };
};
// END-OF-LOOP

// ** Tastenstatus anzeigen
void AK_UpdateKey(int Key)
{
  AK_Oled.invertText(AK_KeyPressed[Key]);
  AK_PrintKey(Key);
  AK_Oled.invertText(false);
  AK_Oled.update();
};

// ** Tastentexte anzeigen
void AK_DrawKeyText()
{
  AK_Oled.clear();
  AK_Oled.invertText(false);
  AK_Oled.setScale(1);
  AK_Oled.home();
  AK_Oled.print("<       Mode: ");
  AK_Oled.setCursor(1, 2);
  AK_Oled.setCursor(1, 4);
  AK_Oled.setCursor(1, 6);
  AK_Oled.fastLineH(11, 0, 127);
  AK_Oled.fastLineH(27, 0, 127);
  AK_Oled.fastLineH(43, 0, 127);
  AK_Oled.fastLineH(59, 0, 127);
  AK_Oled.fastLineV(0, 12, 59);
  AK_Oled.fastLineV(43, 12, 59);
  AK_Oled.fastLineV(83, 12, 59);
  AK_Oled.fastLineV(127, 12, 59);

  for (int i = 0; i < AK_KEYCOUNT; i++)
  {
    AK_PrintKey(i);
  };

  AK_Oled.setCursor(AK_MODETEXTX, AK_MODETEXTY);
  AK_Oled.invertText(true);
  AK_Oled.print(AK_MODETEXT[AK_Mode]);
  AK_Oled.invertText(false);

  AK_Oled.update();
};

// **Tastentext anzeigen
void AK_PrintKey(int Key)
{
  AK_Oled.setCursor(AK_KEYTEXTX[Key], AK_KEYTEXTY[Key]);
  AK_Oled.print(AK_KEYTEXT[AK_Mode][Key]);
};


// ** Setup-Bild anzeigen
void AK_DrawSetup()
{
  AK_Oled.clear();
  AK_Oled.invertText(false);
  AK_Oled.setScale(1);
  AK_Oled.home();
  AK_Oled.print("Modus-Wahl:");
  AK_Oled.setCursor(48, 3);
  for (int i = 0; i < AK_MODECOUNT; i++)
  {
    AK_Oled.setCursor(32, i + 2);
    AK_Oled.print(i);
    AK_Oled.setCursor(40, i + 2);
    AK_Oled.invertText(i == AK_ModeSelect);
    AK_Oled.print(AK_MODETEXT[i]);
    AK_Oled.invertText(false);
  };
  AK_Oled.update();
};

// ** Tasten einlesen
void AK_KeyRead()
{
  AK_KeyIsPressed[0] = !digitalRead(PIN_AK_ENCODERP);

  for (int i = 0; i < AK_KEYROWCOUNT; i++)
  {
    digitalWrite(PIN_AK_KEYROW[i], false);
    for (int j = 0; j < AK_KEYCOLUMNCOUNT; j++)
    {
      AK_KeyIsPressed[(i * AK_KEYROWCOUNT) + j + 1] = !digitalRead(PIN_AK_KEYCOLUMN[j]);
    };
    digitalWrite(PIN_AK_KEYROW[i], true);
  };
};

// ** Tasten auswerten
void AK_KeyProcess()
{
  for (int Key = 0; Key < AK_KEYCOUNT; Key++)
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
  int EncoderValue = AK_Encoder.read();
  AK_EncoderUp = (EncoderValue > 0) ;
  AK_EncoderDown = (EncoderValue < 0);
  if (EncoderValue !=0)
  { 
    delay(100);
    AK_Encoder.write(0);
  }
};
  
