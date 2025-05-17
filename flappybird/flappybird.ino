#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

// For the Adafruit shield, these are the default.
#define TFT_CLK 13
#define TFT_MISO 12
#define TFT_MOSI 11
#define TFT_CS   10
#define TFT_DC    9   
#define TFT_RST   8
#define D2 2
#define D3 3
#define D4 4
#define D5 5
#define D6 6

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

int game_state = 0; // 0 - meniul principal, 1 - start, 2 - stop, 3 - highscore

int pasareY = 30;

void setup() {
  Serial.begin(9600);
  tft.begin();
  pinMode(A1, INPUT);
  pinMode(D2, INPUT_PULLUP);
  pinMode(D4, INPUT_PULLUP);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);

  tft.fillScreen(ILI9341_DARKGREEN);
  tft.setCursor(22, 60);
  tft.setTextColor(ILI9341_PINK);  tft.setTextSize(3);
  tft.println("FLAPPY BIRD");

  tft.setCursor(90, 200);
  tft.setTextColor(ILI9341_RED);  tft.setTextSize(2);
  tft.println("START");
  
  tft.setCursor(65, 250);
  tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(2);
  tft.println("HIGHSCORE");
}


void loop(void) {

  if (digitalRead(D2) == LOW && game_state == 0) {
    game_state = 1;
    tft.fillScreen(ILI9341_CYAN);
  }

  if (digitalRead(D4) == LOW && (game_state == 0 || game_state == 3)) {
    if (game_state == 0) {
      game_state = 3;
      tft.fillScreen(ILI9341_BLACK);

      tft.setCursor(65, 20);
      tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(2);
      tft.println("HIGHSCORE");
    } else {
      game_state = 0;
      tft.fillScreen(ILI9341_DARKGREEN);
      tft.setCursor(22, 60);
      tft.setTextColor(ILI9341_PINK);  tft.setTextSize(3);
      tft.println("FLAPPY BIRD");

      tft.setCursor(90, 200);
      tft.setTextColor(ILI9341_RED);  tft.setTextSize(2);
      tft.println("START");
      
      tft.setCursor(65, 250);
      tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(2);
      tft.println("HIGHSCORE");
    }
  }

  if (game_state == 1) {

      // Fade IN
    for (int val = 0; val <= 255; val++) {
      analogWrite(D6, val);
      delay(2);
    }

    // Fade OUT
    for (int val = 255; val >= 0; val--) {
      analogWrite(D6, val);
      delay(2);
    }

    int joyY = analogRead(A1);

    tft.fillRect(19, pasareY - 10, 24, 24, ILI9341_CYAN);

    if (joyY < 10) {
      pasareY -= 6;
    } else if (joyY > 1010) {
      pasareY += 6;
    }

    // limitare coordonate pasare
    pasareY = constrain(pasareY, 0, 320 - 24);

    // turnuri
    tft.fillRect(20, 100, 30, 100, ILI9341_MAGENTA);
    tft.fillRect(80, 120, 30, 80, ILI9341_MAGENTA);

    // Capul
    tft.fillRect(26, pasareY - 6, 12, 6, ILI9341_GREENYELLOW);

    // Trup
    tft.fillRect(20, pasareY, 18, 9, ILI9341_GREENYELLOW);

    // Ochi
    tft.fillRect(29, pasareY - 3, 3, 3, ILI9341_WHITE);
    tft.fillRect(32, pasareY - 3, 3, 3, ILI9341_BLACK);

    // Cioc
    tft.fillTriangle(38, pasareY + 3, 38, pasareY + 1, 41, pasareY + 2, ILI9341_ORANGE);

    // Aripa
    tft.fillRect(23, pasareY + 3, 9, 3, ILI9341_OLIVE);

    // Picior
    tft.fillRect(29, pasareY + 9, 3, 3, ILI9341_YELLOW);
  }

  // if (game_state == 0 || game_state == 3) {
  //     // Fade IN
  //   for (int val = 0; val <= 255; val++) {
  //     analogWrite(D5, val);
  //     delay(10);
  //   }

  //   // Fade OUT
  //   for (int val = 255; val >= 0; val--) {
  //     analogWrite(D5, val);
  //     delay(10);
  //   }
  // }
}