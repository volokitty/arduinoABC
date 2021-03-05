#include <TVout.h>
#include <GyverButton.h>
#include <fontALL.h>
#include <stdint.h>
#include <Entropy.h>

// My types
#define uint8_t u8
#define uint16_t u16

#define KEYBOARD_SIZE 6

PROGMEM const unsigned char russianFont[][8] = {
  {0b01111110, 0b10000001, 0b10000001, 0b10000001, 0b11111111, 0b10000001, 0b10000001, 0b10000001}, // А
  {0b11111111, 0b10000000, 0b10000000, 0b11111110, 0b10000001, 0b10000001, 0b10000001, 0b11111110}, // Б
  {0b11111100, 0b10000010, 0b10000010, 0b11111110, 0b10000001, 0b10000001, 0b10000001, 0b11111110}, // В
  {0b11111111, 0b10000000, 0b10000000, 0b10000000, 0b10000000, 0b10000000, 0b10000000, 0b10000000}, // Г
  {0b00111100, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b11111111, 0b10000001, 0b10000001}, // Д
  {0b11111111, 0b10000000, 0b10000000, 0b11111100, 0b10000000, 0b10000000, 0b10000000, 0b11111111}, // Е
};

TVout TV;
GButton keyboard[KEYBOARD_SIZE];
u16 analog;
short pressedButton;

// ------------ Card ------------
#define OPEN 1
#define CLOSED 0

struct Card
{
  u8 x, y, c;
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
        TV.bitmap(this->x * 31 + 10 + 11, this->y * 44 + 6 + 16, russianFont[this->c], 0, 8, 8);
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

  Card(u8 x, u8 y, u8 c)
  {
    this->x = x;
    this->y = y;
    this->c = c;
  }
};

// ------------ Game Engine ------------
#define NOT_SEL 255

struct GameEngine
{
private:
  void initCards(u8* cardsMap)
  {
    u8 index;
    for (u8 i = 0; i < 2; i++)
    {
      for (u8 j = 0; j < 3; j++)
      {
        index = i * (KEYBOARD_SIZE / 2) + j;
        this->cards[index] = new Card(j, i, cardsMap[index]);
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

  GameEngine(u8* cardsMap)
  {
    this->cardsMap = cardsMap;
    this->initCards(this->cardsMap);
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

void randomCardsMap(u8* cardsMap)
{
  u8 randomNumber;
  for (u8 i = 0; i < KEYBOARD_SIZE / 2; i++)
  {
    while (true)
    {
      randomNumber = random(0, 6);
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
  
  keyboard_init(keyboard);
}

// ------------ Loop ------------
u8 cardsMap[KEYBOARD_SIZE];
GameEngine* engine;

void loop()
{
  randomCardsMap(cardsMap);
  engine = new GameEngine(cardsMap);

// ------------ Game loop ------------
  u8 loopIter = 0;
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
  TV.println("You win! <3");
  TV.delay(2000);
  TV.clear_screen();

  for (u8 i = 0; i < KEYBOARD_SIZE; i++)
  {
    delete engine->cards[i];
    engine->cards[i] = NULL;
  }

  delete engine;
  engine = NULL;
}
