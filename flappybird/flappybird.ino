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

int score = 0;

int pasareX = 100;
int pasareY = 32;

int case_tower = 0;

int towerY = -1;
int tower1X = 0;
int tower2X = 0;
int h_tower1 = 0;
int h_tower2 = 0;

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

  // TODO: caz cand game_state e 0
  // TODO: efecte sonore
  // TODO: introducere nume, scor_nou
  // TODO: PWM LED-uri
  // TODO: intrerupere start/stop

  if (digitalRead(D2) == LOW && game_state == 0) {
    game_state = 1;
    tft.fillRect(0, 0, 240, 200, ILI9341_CYAN);
    tft.fillRect(0, 200, 240, 120, ILI9341_BLACK);
    score = 0;
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

  // if (game_state != 1) {
  //   // Fade IN
  //   for (int val = 0; val <= 255; val++) {
  //     analogWrite(D5, val);
  //     delay(2);
  //   }

  //   // Fade OUT
  //   for (int val = 255; val >= 0; val--) {
  //     analogWrite(D5, val);
  //     delay(2);
  //   }
  // }

  if (game_state == 1) {

    tft.fillRect(0, 200, 240, 120, ILI9341_BLACK);
    tft.setCursor(20, 250);
    tft.setTextColor(ILI9341_PINK);  tft.setTextSize(2);
    tft.print("SCORE:");
    tft.println(score);

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

    tft.fillRect(pasareY, pasareX - 18, 42, 36, ILI9341_CYAN);
    tft.fillRect(towerY, 0, 42, 200, ILI9341_CYAN);
    towerY -= 42;

    int joyY = analogRead(A1);

    if (joyY < 10) {
      pasareX -= 18;
    } else if (joyY > 1010) {
      pasareX += 18;
    }

    if ((towerY + 42 < pasareY) && (pasareX - 18 > h_tower1) && (pasareX + 18 < tower2X)) {
      score++;
    }

    if ((towerY < pasareY + 42) && (pasareY + 42 < towerY + 84) && ((pasareX - 18 <= h_tower1) || (pasareX + 18 >= tower2X))) {
      Serial.print("STOP!");
      // tft.fillScreen(ILI9341_CYAN);
      // tft.setCursor(30, 160);
      // tft.setTextColor(ILI9341_DARKGREEN);  tft.setTextSize(3);
      // tft.print("GAME OVER");
      // tft.setCursor(100, 200);
      // tft.setTextColor(ILI9341_BLACK);  tft.setTextSize(2);
      // tft.print("SCORE:");
      // tft.println(score);
      game_state = 0;
    }

    if (towerY < 0) {
      towerY = 198;
      tower1X = 0;
      h_tower1 = case_tower % 3 == 0 ? 40 : (case_tower % 3 == 1 ? 70 : 100);
      tower2X = h_tower1 + 60;
      h_tower2 = 140 - h_tower1;
      case_tower++;
      case_tower %= 3;
    }
    
    tft.fillRect(towerY, tower1X, 42, h_tower1, ILI9341_MAGENTA);
    tft.fillRect(towerY, tower2X, 42, h_tower2, ILI9341_MAGENTA);    

    // limitare coordonate pasare
    pasareX = constrain(pasareX, 18, 182);

    // turnuri
    // tft.fillRect(20, 100, 30, 100, ILI9341_MAGENTA);
    // tft.fillRect(80, 120, 30, 80, ILI9341_MAGENTA);

    // Capul
    tft.fillRect(pasareY + 12, pasareX - 18, 24, 12, ILI9341_GREENYELLOW);

    // Trup
    tft.fillRect(pasareY, pasareX - 6, 36, 18, ILI9341_GREENYELLOW);

    // Ochi
    tft.fillRect(pasareY + 18, pasareX - 12, 6, 6, ILI9341_WHITE);
    tft.fillRect(pasareY + 24, pasareX - 12, 6, 6, ILI9341_BLACK);

    // Cioc
    tft.fillRect(pasareY + 36, pasareX - 6, 6, 6, ILI9341_ORANGE);

    // Aripa
    tft.fillRect(pasareY + 6, pasareX, 18, 6, ILI9341_OLIVE);

    // Picior
    tft.fillRect(pasareY + 18, pasareX + 12, 6, 6, ILI9341_YELLOW);
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