#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

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

int8_t game_state = 0; // 0 - meniul principal, 1 - start, 2 - stop, 3 - highscore menu, 4 - gameover, 5 - salvare highscore

int8_t draw_background = 0;
int8_t draw_main_menu = 0;

int16_t red_led = 0;
int16_t green_led = 0;
int16_t duty = 0;

int16_t score = 0;
int16_t scores[5] = {0, 0, 0, 0, 0};

String name;
String names[5] = {"...", "...", "...", "...", "..."};

int16_t birdX = 100;
int16_t birdY = 32;

int8_t case_tower = 0;

int16_t towerY = -1;
int16_t tower1X = 0;
int16_t tower2X = 0;
int16_t h_tower1 = 0;
int16_t h_tower2 = 0;
int8_t reverse_towers = 0;

// functie de intrerupere pentru butonul rosu (PD2)
ISR(INT0_vect) {
  if (!(PIND & (1<<PD2))) {
    // schimbare game_state
    if (game_state == 0) {
      score = 0;
      game_state = 1;
      draw_background = 0;
      towerY = -1;
    } else if (game_state == 4) {
      game_state = 5;
    } else {
      game_state = 3 - game_state;
      draw_main_menu = 0;
    }

    red_led = 0;
    green_led = 0;
    OCR0A = 0;
    OCR0B = 0;
    duty = 0;
  }
}

// functie pentru aprinderea/stingerea LED-urilor
void fade_leds() {
  // functionalitate led rosu
  if (game_state != 1) {
    OCR0A = 0;
    _delay_ms(5);
    if (red_led == 0) {
      if (duty == 256) {
        red_led = 1;
      } else {
        OCR0B = duty;
        duty++;
      }
    } else {
      if (duty == -1) {
        red_led = 0;
      } else {
        OCR0B = duty;
        duty--;
      }
    }
  } else {
    // functionalitate led verde
    OCR0B = 0;
    if (green_led == 0) {
      if (duty == 256) {
        green_led = 1;
      } else {
        OCR0A = duty;
        duty += 2;
      }
    } else {
      if (duty == -1) {
        green_led = 0;
      } else {
        OCR0A = duty;
        duty -= 2;
      }
    }
  }
}

// functie de afisare meniu principal
void show_main_menu() {
  tft.fillScreen(ILI9341_DARKGREEN);

  tft.setTextColor(ILI9341_PINK);
  tft.setTextSize(3);
  tft.setCursor(22, 60);
  tft.println("FLAPPY BIRD");

  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(2);
  tft.setCursor(90, 200);
  tft.println("START");
  
  tft.setTextColor(ILI9341_BLUE);
  tft.setTextSize(2);
  tft.setCursor(65, 250);
  tft.println("HIGHSCORE");
}

// functie de afisare meniu highscore
void show_highscore_menu() {
  tft.fillScreen(ILI9341_BLACK);

  tft.setTextColor(ILI9341_BLUE);
  tft.setTextSize(3);

  tft.setCursor(50, 20);
  tft.println("HIGHSCORE");

  for (int8_t i = 0; i < 5; i++) {
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);

    tft.setCursor(20, 60 + i * 30);
    tft.print(i + 1);
    tft.print(". ");
    tft.print(names[i]);
    tft.print(":");
    tft.print(scores[i]);
  }
}

// functie de afisare a scorului in timpul jocului
void show_score() {
  tft.setTextColor(ILI9341_PINK);
  tft.setTextSize(2);

  tft.setCursor(20, 250);
  tft.print("SCORE:");
  tft.println(score);
}

// functie de afisare text cand se asteapta nume de la jucator
void show_waiting_name() {
  tft.fillScreen(ILI9341_BLACK);
  
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);

  tft.setCursor(40, 130);
  tft.println("Introdu nume");

  tft.setCursor(40, 150);
  tft.println("de la");

  tft.setCursor(40, 170);
  tft.println("tastatura");
}

// functie de update a tabelei de highscore
void update_highscore() {
  if (scores[4] == 0 || score > scores[4]) {
    int8_t insert_pos = -1;
    for (int8_t i = 0; i < 5; i++) {
      if (score > scores[i] || scores[i] == 0) {
        insert_pos = i;
        break;
      }
    }

    if (insert_pos != -1) {
      for (int8_t j = 4; j > insert_pos; j--) {
        scores[j] = scores[j - 1];
        names[j] = names[j - 1];
      }

      scores[insert_pos] = score;
      names[insert_pos] = name;
    }
  }
}

// functie de desenare a background-ului din joc
void draw_background_game() {
  tft.fillRect(0, 0, 240, 200, ILI9341_CYAN);
  tft.fillRect(0, 200, 240, 120, ILI9341_BLACK);
}

// functie de desenare a pasarii
void draw_bird() {
  // Capul
  tft.fillRect(birdY + 12, birdX - 18, 24, 12, ILI9341_GREENYELLOW);

  // Trup
  tft.fillRect(birdY, birdX - 6, 36, 18, ILI9341_GREENYELLOW);

  // Ochi
  tft.fillRect(birdY + 18, birdX - 12, 6, 6, ILI9341_WHITE);
  tft.fillRect(birdY + 24, birdX - 12, 6, 6, ILI9341_BLACK);

  // Cioc
  tft.fillRect(birdY + 36, birdX - 6, 6, 6, ILI9341_ORANGE);

  // Aripa
  tft.fillRect(birdY + 6, birdX, 18, 6, ILI9341_OLIVE);

  // Picior
  tft.fillRect(birdY + 18, birdX + 12, 6, 6, ILI9341_YELLOW);
}

// functie de desenare a turnurilor
void draw_towers() {
  tft.fillRect(towerY, tower1X, 42, h_tower1, ILI9341_MAGENTA);
  tft.fillRect(towerY, tower2X, 42, h_tower2, ILI9341_MAGENTA);
}

// functie de afisare game over
void game_over() {
  tft.fillScreen(ILI9341_CYAN);

  tft.setCursor(40, 150);
  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(3);
  tft.print("GAME OVER");

  tft.setCursor(80, 190);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.print("SCORE:");
  tft.println(score);
}

// functie de repozitionare si modificare a turnurilor
void reset_towers() {
  if (towerY < 0) {
    towerY = 198;
    tower1X = 0;
    h_tower1 = case_tower % 3 == 0 ? 40 : (case_tower % 3 == 1 ? 70 : 100);
    tower2X = h_tower1 + 60;
    h_tower2 = 140 - h_tower1;

    if (reverse_towers == 0) {
      case_tower++;

      if (case_tower == 3) {
        reverse_towers = 1;
        case_tower = 1;
      }
    } else {
      case_tower--;

      if (case_tower == -1) {
        reverse_towers = 0;
        case_tower = 1;
      }
    }
  }
}

// functie de curatare joc
void clear_game() {
  // curatare zona scor
  tft.fillRect(20, 250, 100, 20, ILI9341_BLACK);

  // curatare zona pasare
  tft.fillRect(birdY, birdX - 18, 42, 36, ILI9341_CYAN);

  // curatare zona turnuri
  tft.fillRect(towerY, 0, 42, 200, ILI9341_CYAN);
}

void setup() {
  Serial.begin(9600);
  tft.begin();

  pinMode(A1, INPUT); // joystick

  DDRD &= ~(1 << DDD2); // PD2 ca intrare - buton start/stop
  PORTD |= (1 << PD2);  // pull-up activat

  DDRD &= ~(1 << DDD4); // PD4 ca intrare - buton highscore
  PORTD |= (1 << PD4);  // pull-up activat

  // activare intrerupere pentru PD2
  EICRA  = (1 << ISC01) | (0 << ISC00); // ISC01 = 1, ISC00 = 0 -> falling edge
  EIMSK  = (1 << INT0); // activeaza INT0
  sei(); // activare intrerupere globala

  DDRD |= (1 << DDD5) | (1 << DDD6); // PD5 si PD6 ca iesire

  // COM0A1 = 1, COM0A0 = 0 -> non-invertant pe OC0A (PD6)
  // COM0B1 = 1, COM0B0 = 0 -> non-invertant pe OC0B (PD5)
  // WGM01 = 1, WGM00 = 1 -> Fast PWM (TOP = 0xFF)
  TCCR0A = (1 << COM0A1) | (0 << COM0A0) | (1 << COM0B1) | (0 << COM0B0) | (1 << WGM01) | (1 << WGM00);
  
  // CS02 = 0, CS01 = 1, CS00 = 1 -> prescaler 64
  TCCR0B = (0 << CS02) | (1 << CS01) | (1 << CS00);
}


void loop(void) {
  fade_leds();

  if (game_state == 1 && draw_background == 0) {
    draw_background_game();
    draw_background = 1;
  }

  // caz cand se intra/iese in/din meniul de highscore (cand e apasat butonul albastru)
  if (digitalRead(D4) == LOW && (game_state == 0 || game_state == 3)) {
    if (game_state == 0) {
      game_state = 3;
      show_highscore_menu();
    } else {
      draw_main_menu = 0;
      game_state = 0;
    }
  }

  if (game_state == 0 && draw_main_menu == 0) {
    show_main_menu();
    draw_main_menu = 1;
  }

  // zona jocului
  if (game_state == 1) {
    clear_game();
    show_score();

    towerY -= 42;

    // citire joystick
    int joyY = analogRead(A1);

    // miscare pasare si limitare inaltime
    if (joyY < 10) {
      birdX = birdX - 18 < 18 ? 18 : birdX - 18;
    } else if (joyY > 1010) {
      birdX = birdX + 18 > 182 ? 182 : birdX + 18;
    }

    // incrementare scor
    if ((towerY + 42 < birdY) && (birdX - 18 > h_tower1) && (birdX + 18 < tower2X)) {
      score++;
      tone(3, 523, 100);
    }

    // lovire de turnuri
    if ((towerY < birdY + 42) && (birdY + 42 < towerY + 84) && ((birdX - 18 <= h_tower1) || (birdX + 18 >= tower2X))) {
      tone(3, 300, 100);
      game_state = 4;
      game_over();
    }

    reset_towers();  

    if (game_state == 1) {
      draw_towers();
      draw_bird();
    }
  }

  if (game_state == 5) {
    if (score <= scores[4]) {
      game_state = 0;
      show_main_menu();
    } else {
      show_waiting_name();

      name = "";
      while (Serial.available() == 0) {
        // Asteapta nume de la tastatura
      }

      // Citeste sirul de caractere
      name = Serial.readStringUntil('\n');

      update_highscore();      

      game_state = 3;
      show_highscore_menu();
    }
  }
}