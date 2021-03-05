#include <TVout.h>
#include <GyverButton.h>
#include <fontALL.h>
#include <stdint.h>
#include "Image.h"

// My types
#define uint8_t u8
#define uint16_t u16

#define KEYBOARD_SIZE 6

PROGMEM const u8 vowels[][8] = {
  {0b01111110, 0b11111111, 0b11000011, 0b11000011, 0b11111111, 0b11111111, 0b11000011, 0b11000011}, // А
  {0b11111111, 0b11111111, 0b11000000, 0b11111110, 0b11111110, 0b11000000, 0b11111111, 0b11111111}, // Е
  {0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11001111, 0b11001111, 0b11110011, 0b11110011}, // И
  {0b01111110, 0b11111111, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11111111, 0b01111110}, // О
  {0b11000011, 0b11000011, 0b11111111, 0b11111111, 0b00000011, 0b00000011, 0b11111100, 0b11111100}, // У
  {0b11000011, 0b11000011, 0b11111011, 0b11111011, 0b11001111, 0b11001111, 0b11111101, 0b11111101}, // Ы
  {0b11111111, 0b11111111, 0b00000011, 0b00111111, 0b00111111, 0b00000011, 0b11111111, 0b11111111}, // Э
  {0b11001110, 0b11011011, 0b11011011, 0b11111011, 0b11111011, 0b11011011, 0b11011011, 0b11001110}, // Ю
  {0b00011111, 0b00011111, 0b00110011, 0b00110011, 0b00001111, 0b00001111, 0b00110011, 0b00110011} // Я
};

PROGMEM const u8 cons[][8] = {
  {0b11111111, 0b11111111, 0b11000000, 0b11111110, 0b11111111, 0b11000011, 0b11111111, 0b11111110}, // Б
  {0b11111110, 0b11111110, 0b11000010, 0b11111111, 0b11111111, 0b11000001, 0b11111111, 0b11111111}, // В
  {0b11111111, 0b11111111, 0b11000000, 0b11000000, 0b11000000, 0b11000000, 0b11000000, 0b11000000}, // Г
  {0b00011110, 0b00010110, 0b00100110, 0b01100110, 0b01111110, 0b11000011, 0b11000011, 0b11000011}, // Д
  {0b11011011, 0b01011010, 0b00111100, 0b00111100, 0b01011010, 0b01011010, 0b11011011, 0b11011011}, // Ж
  {0b00001110, 0b00010001, 0b00000001, 0b00000110, 0b00000001, 0b00000001, 0b00010001, 0b00001110}, // З
  {0b11000011, 0b11000110, 0b11011100, 0b11110000, 0b11110000, 0b11011000, 0b11001110, 0b11000111}, // К
  {0b00011111, 0b00110011, 0b00110011, 0b00110011, 0b01110011, 0b01100011, 0b11100011, 0b11100011}, // Л
  {0b11100111, 0b11111111, 0b11011011, 0b11011011, 0b11000011, 0b11000011, 0b11000011, 0b11000011}, // М
  {0b11000011, 0b11000011, 0b11000011, 0b11111111, 0b11111111, 0b11000011, 0b11000011, 0b11000011}, // Н
  {0b11111111, 0b11111111, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011}, // П
  {0b11111110, 0b11111110, 0b11000011, 0b11000011, 0b11000011, 0b11111100, 0b11111100, 0b11000000}, // Р
  {0b00111111, 0b00111111, 0b11000000, 0b11000000, 0b11000000, 0b11000000, 0b00111111, 0b00111111}, // С
  {0b11111111, 0b11111111, 0b00011000, 0b00011000, 0b00011000, 0b00011000, 0b00011000, 0b00011000}, // Т
  {0b11111111, 0b11011011, 0b11011011, 0b11011011, 0b11111111, 0b00011000, 0b00011000, 0b00011000}, // Ф
  {0b11000011, 0b11000011, 0b00100100, 0b00011000, 0b00011000, 0b00100100, 0b11000011, 0b11000011}, // Х
  {0b11001100, 0b11001100, 0b11001100, 0b11001100, 0b11111111, 0b11111111, 0b00000011, 0b00000011}, // Ц
  {0b11000011, 0b11000011, 0b11000011, 0b11111111, 0b11111111, 0b00000011, 0b00000011, 0b00000011}, // Ч
  {0b11011011, 0b11011011, 0b11011011, 0b11011011, 0b11011011, 0b11011011, 0b11111111, 0b11111111}, // Ш
  {0b11010110, 0b11010110, 0b11010110, 0b11010110, 0b11010110, 0b11111110, 0b11111110, 0b00000001}, // Щ
  {0b11000000, 0b11000000, 0b11111110, 0b00111110, 0b00110011, 0b00110011, 0b00111110, 0b00111110}, // Ъ
  {0b11000000, 0b11000000, 0b11111100, 0b11111100, 0b11000110, 0b11000110, 0b11111100, 0b11111100} // Ь
};

PROGMEM const u8 digits[][8] = {
  {0b01111110, 0b11111111, 0b11000111, 0b11001011, 0b11010011, 0b11100011, 0b11111111, 0b01111110}, // 0
  {0b00011000, 0b00111000, 0b01111000, 0b00011000, 0b00011000, 0b00011000, 0b11111111, 0b11111111}, // 1
  {0b01111110, 0b11111111, 0b11000011, 0b00011111, 0b01110000, 0b11000011, 0b11111111, 0b11111111}, // 2
  {0b01111110, 0b11111111, 0b11000011, 0b00011110, 0b00011110, 0b11000011, 0b11111111, 0b01111110}, // 3
  {0b00011100, 0b00101100, 0b01001100, 0b11001100, 0b11111111, 0b00001100, 0b00011110, 0b00011110}, // 4
  {0b11111111, 0b11111111, 0b11000000, 0b11111111, 0b00000011, 0b11000011, 0b11111111, 0b01111110}, // 5
  {0b00111111, 0b01111111, 0b11000000, 0b11111111, 0b11000011, 0b11000011, 0b11111111, 0b01111110}, // 6
  {0b11111111, 0b11111111, 0b11000011, 0b00001111, 0b00001100, 0b00011000, 0b00011000, 0b00011000}, // 7
  {0b00111100, 0b01000010, 0b01000010, 0b00111100, 0b01111110, 0b11000011, 0b11000011, 0b01111110}, // 8
  {0b11111111, 0b11111111, 0b11000011, 0b11000011, 0b11111111, 0b00000011, 0b11111111, 0b11111111}, // 9
};

PROGMEM const u8 signs[][8] = {
  {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b11000000, 0b11000000}, // .
  {0b11000000, 0b11000000, 0b11000000, 0b11000000, 0b11000000, 0b00000000, 0b11000000, 0b11000000}, // !
  {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000}, // space
};

TVout TV;
GButton keyboard[KEYBOARD_SIZE];
u16 analog;
short pressedButton;

// ------------ Output ------------
#define FONT 0, 8, 8
void printWin()
{
  TV.bitmap(20, 30, cons[10], FONT);
  TV.bitmap(30, 30, vowels[3], FONT);
  TV.bitmap(40, 30, cons[0], FONT);
  TV.bitmap(50, 30, vowels[1], FONT);
  TV.bitmap(60, 30, cons[3], FONT);
  TV.bitmap(70, 30, vowels[0], FONT);
  TV.bitmap(80, 30, signs[1], FONT);
  // Победа!
}

void printNewGame()
{
  TV.bitmap(0, 0, cons[9], FONT);
  TV.bitmap(10, 0, vowels[3], FONT);
  TV.bitmap(20, 0, cons[1], FONT);
  TV.bitmap(30, 0, vowels[0], FONT);
  TV.bitmap(40, 0, vowels[8], FONT);
  TV.bitmap(50, 0, signs[2], FONT);
  TV.bitmap(60, 0, vowels[2], FONT);
  TV.bitmap(70, 0, cons[2], FONT);
  TV.bitmap(80, 0, cons[11], FONT);
  TV.bitmap(90, 0, vowels[0], FONT);
  // Новая игра

  TV.bitmap(0, 20, digits[1], FONT);
  TV.bitmap(10, 20, signs[0], FONT);
  TV.bitmap(20, 20, cons[2], FONT);
  TV.bitmap(30, 20, cons[7], FONT);
  TV.bitmap(40, 20, vowels[0], FONT);
  TV.bitmap(50, 20, cons[12], FONT);
  TV.bitmap(60, 20, cons[9], FONT);
  TV.bitmap(70, 20, vowels[5], FONT);
  TV.bitmap(80, 20, vowels[1], FONT);
  // 1. Гласные

  TV.bitmap(0, 40, digits[2], FONT);
  TV.bitmap(10, 40, signs[0], FONT);
  TV.bitmap(20, 40, cons[12], FONT);
  TV.bitmap(30, 40, vowels[3], FONT);
  TV.bitmap(40, 40, cons[2], FONT);
  TV.bitmap(50, 40, cons[7], FONT);
  TV.bitmap(60, 40, vowels[0], FONT);
  TV.bitmap(70, 40, cons[12], FONT);
  TV.bitmap(80, 40, cons[9], FONT);
  TV.bitmap(90, 40, vowels[5], FONT);
  TV.bitmap(100, 40, vowels[1], FONT);
  // 2. Согласные

  TV.bitmap(0, 60, digits[3], FONT);
  TV.bitmap(10, 60, signs[0], FONT);
  TV.bitmap(20, 60, cons[16], FONT);
  TV.bitmap(30, 60, vowels[2], FONT);
  TV.bitmap(40, 60, cons[14], FONT);
  TV.bitmap(50, 60, cons[11], FONT);
  TV.bitmap(60, 60, vowels[5], FONT);
  // 3. Цифры
}

void printCityName()
{
  TV.bitmap(30, 20, cons[9], FONT);
  TV.bitmap(40, 20, vowels[3], FONT);
  TV.bitmap(50, 20, cons[1], FONT);
  TV.bitmap(60, 20, vowels[5], FONT);
  TV.bitmap(70, 20, vowels[1], FONT);

  TV.bitmap(10, 40, cons[8], FONT);
  TV.bitmap(20, 40, vowels[0], FONT);
  TV.bitmap(30, 40, cons[11], FONT);
  TV.bitmap(40, 40, cons[6], FONT);
  TV.bitmap(50, 40, vowels[3], FONT);
  TV.bitmap(60, 40, cons[1], FONT);
  TV.bitmap(70, 40, vowels[2], FONT);
  TV.bitmap(80, 40, cons[17], FONT);
  TV.bitmap(90, 40, vowels[2], FONT);

  // Новые Марковичи
}

// ------------ Card ------------
#define OPEN 1
#define CLOSED 0

struct Card
{
  u8 x, y, c;
  u8 (*symbols)[8];
  bool style = CLOSED;
  bool destroyed = false;

  void destroy()
  {
    this->destroyed = true;
    this->draw();
  }
  
  void draw()
  {
    if (!this->destroyed)
    {
      if (this->style)
      {
        TV.draw_rect(this->x * 31 + 10, this->y * 44 + 6, 28, 40, WHITE, BLACK);
        TV.bitmap(this->x * 31 + 10 + 11, this->y * 44 + 6 + 16, this->symbols[this->c], 0, 8, 8);
      }
      else
      {
        TV.draw_rect(this->x * 31 + 10, this->y * 44 + 6, 28, 40, WHITE, WHITE);
      }  
    }
    else
    {
      TV.draw_rect(this->x * 31 + 10, this->y * 44 + 6, 28, 40, BLACK, BLACK);
    }
  }

  void toggleStyle()
  {
    if (style)
      style = CLOSED;
    else
      style = OPEN;
  }

  Card(u8 x, u8 y, u8 c, u8 mode)
  {
    this->x = x;
    this->y = y;
    this->c = c;
    
    switch (mode)
    {
      case 0:
        this->symbols = vowels;
        break;
      case 1:
        this->symbols = cons;
        break;
      case 2:
        this->symbols = digits;
        break;
    }
  }
};

// ------------ Game Engine ------------
#define NOT_SEL 255

struct GameEngine
{
private:
  void initCards(u8* cardsMap, u8 mode)
  {
    u8 index;
    for (u8 i = 0; i < 2; i++)
    {
      for (u8 j = 0; j < 3; j++)
      {
        index = i * (KEYBOARD_SIZE / 2) + j;
        this->cards[index] = new Card(j, i, cardsMap[index], mode);
        this->cards[index]->draw();
      }
    }
  }
public:
  u8 selectedCards[2] = { NOT_SEL, NOT_SEL };
  Card* cards[KEYBOARD_SIZE];
  u8* cardsMap;
  u8 win = 0;

  void toggleStyles(u8 pressedButton)
  {
    switch (pressedButton)
    {
      case 0:
        cards[0]->toggleStyle();
        cards[0]->draw();
        break;
      case 1:
        cards[1]->toggleStyle();
        cards[1]->draw();
        break;
      case 2:
        cards[2]->toggleStyle();
        cards[2]->draw();
        break;
      case 3:
        cards[3]->toggleStyle();
        cards[3]->draw();
        break;
      case 4:
        cards[4]->toggleStyle();
        cards[4]->draw();
        break;
      case 5:
        cards[5]->toggleStyle();
        cards[5]->draw();
        break;
    }
  }

  void checkCards()
  {
    if ((selectedCards[0] != NOT_SEL && selectedCards[1] != NOT_SEL) && (cards[selectedCards[0]]->c == cards[selectedCards[1]]->c) && !cards[selectedCards[0]]->destroyed && !cards[selectedCards[1]]->destroyed)
    {
//      Serial.println("here");
      TV.delay(500);
      cards[selectedCards[0]]->destroy();
      cards[selectedCards[1]]->destroy();
      win++;
    }
  }

  void selectCard(u8 pressedButton)
  {
    if (selectedCards[0] == NOT_SEL)
    {
      selectedCards[0] = pressedButton;
    }
    else if (selectedCards[1] == NOT_SEL && selectedCards[0] != pressedButton)
    {
      selectedCards[1] = pressedButton;
    }
    else
    {
      this->toggleStyles(selectedCards[0]);
      this->toggleStyles(selectedCards[1]);
      selectedCards[0] = pressedButton;
      selectedCards[1] = NOT_SEL;
    }
    this->toggleStyles(pressedButton);
  }

  GameEngine(u8* cardsMap, u8 mode)
  {
    this->cardsMap = cardsMap;
    this->initCards(this->cardsMap, mode);
  }
};

// ------------ Keyboard ------------
void keyboard_init(GButton* keyboard)
{
  for (u8 i = 0; i < KEYBOARD_SIZE; i++)
  {
    keyboard[i] = GButton();
    keyboard[i].setType(LOW_PULL);
  }
}

u8 getPressedButton(GButton* keyboard, u16 analog)
{
  for (u8 i = 0; i < KEYBOARD_SIZE; i++)
  {
    analog = analogRead(i);
    keyboard[i].tick(analog > 1000 && analog < 1024);
    if (keyboard[i].isPress()) return i;
  }
  return NOT_SEL;
}

bool inArray(u8* numbers, u8 count, u8 number)
{
  for (u8 i = 0; i < count; i++)
    if (numbers[i] == number)
      return true;

  return false;
}

void shuffleArray(u8* arr, u8 c)
{
  u8 last = 0;
  u8 temp = arr[last];
  for (u8 i = 0; i < c; i++)
  {
    u8 index = random(c);
    arr[last] = arr[index];
    last = index;
  }
  arr[last] = temp;
}

void randomCardsMap(u8* cardsMap, u8 mode)
{
  switch (mode)
    {
      case 0:
        mode = 9;
        break;
      case 1:
        mode = 22;
        break;
      case 2:
        mode = 10;
        break;
    }
  
  u8 randomNumber;
  for (u8 i = 0; i < KEYBOARD_SIZE / 2; i++)
  {
    while (true)
    {
      randomNumber = random(0, mode);
      if (!inArray(cardsMap, KEYBOARD_SIZE / 2, randomNumber))
      {
        cardsMap[i] = randomNumber;
        cardsMap[i + 3] = randomNumber;
        break;
      }
    }
  }

  shuffleArray(cardsMap, KEYBOARD_SIZE);
}

// ------------ Setup ------------
void setup()
{
  TV.begin(NTSC,120,96);
  TV.select_font(font8x8ext);

  for (int i = 0; i < 96; i++)
    TV.bitmap(0, i, image[i], 0, 120, 1);
  TV.delay(7000);
  TV.clear_screen();
  printCityName();
  TV.delay(7000);
  TV.clear_screen();
  TV.println("\n\n\n\n  Therobots");
  TV.delay(7000);
  
  keyboard_init(keyboard);
  TV.clear_screen();
}

// ------------ Loop ------------
u8 cardsMap[KEYBOARD_SIZE];
GameEngine* engine;
u8 mode;
u8 loopIter;

void loop()
{
// ------------ Menu loop ------------
  printNewGame();

  loopIter = 0;
  while (true)
  {    
    mode = getPressedButton(keyboard, analog);

    if (loopIter < KEYBOARD_SIZE)
    {
      loopIter++;
      continue;
    }

    if (mode > 2)
      continue;
    
    break;
  }

  TV.clear_screen();
  
  randomCardsMap(cardsMap, mode);
  engine = new GameEngine(cardsMap, mode);

// ------------ Game loop ------------
  loopIter = 0;
  while (true)
  {        
    pressedButton = getPressedButton(keyboard, analog);

    if (loopIter < KEYBOARD_SIZE)
    {
      loopIter++;
      continue;
    }
    
    if (pressedButton != NOT_SEL)
    {
      engine->selectCard(pressedButton);
      engine->checkCards();
    }

    if (engine->win == 3)
    {
      break;
    }
  }
  TV.clear_screen();
  printWin();
  TV.delay(7000);
  TV.clear_screen();

  for (u8 i = 0; i < KEYBOARD_SIZE; i++)
  {
    delete engine->cards[i];
    engine->cards[i] = NULL;
  }

  delete engine;
  engine = NULL;
}
