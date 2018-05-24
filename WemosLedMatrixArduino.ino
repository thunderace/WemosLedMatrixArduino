#include <Adafruit_GFX.h>
#include "WEMOS_Matrix_GFX.h"

//#define SNOW 
//#define EXAMPLE1
//#define IMAGE1
//#define IMAGE2
#define TEXT

#ifdef IMAGE2
static const uint8_t PROGMEM
  large_bmp[] =
  { B00000000,
    B00011000,
    B00111100,
    B00111100,
    B00111100,
    B00111100,
    B00011000,
    B00000000 },
  med_bmp[] =
  { B00000000,
    B00000000,
    B00011000,
    B00111100,
    B00111100,
    B00011000,
    B00000000,
    B00000000 },
    empty_bmp[] =
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000 },
  small_bmp[] =
  { B00000000,
    B00000000,
    B00000000,
    B00011000,
    B00011000,
    B00000000,
    B00000000,
    B00000000 };

#endif
#ifdef IMAGE1
const unsigned char image_name[] PROGMEM = {
        B00111100,
        B01000010,
        B10100101,
        B10000001,
        B10100101,
        B10011001,
        B01000010,
        B00111100 },
neutral_bmp[] =
{ B00111100,
        B01000010,
        B10100101,
        B10000001,
        B10111101,
        B10000001,
        B01000010,
        B00111100 },
frown_bmp[] =
{ B00111100,
        B01000010,
        B10100101,
        B10000001,
        B10011001,
        B10100101,
        B01000010,
        B00111100 };        
#endif

#ifdef SNOW
class Flake {
  public:
    Flake() {
      reset();
    }
    void next() {
      x = x + vx;
      y = y + vy;
      if ( x >=8 ) x = 0;
      if ( x < 0 ) x = 7;
      if ( y >= 8 ) {
        reset();
      }
    }
    float x,y;
    float vx,vy;
    void reset() {
      y = 0;
      x = random(8000)/1000.0;
      vx = random(-1000, 1000) / 4000.0;
      vy = random(500, 1000) / 2000.0;
    }
};
#define NUM_FLAKES 10
Flake snow[NUM_FLAKES];
#endif

MLED matrix(5,11,13);

// Arduino  Led matrix shield
// 3.3V     3.3V
// 5V       5V
// GND      GND
// 11       D7
// 13       D5
void setup() {
  // put your setup code here, to run once:
}

void loop() {
#ifdef IMAGE2
  matrix.clear();
  matrix.drawBitmap(0, 0, empty_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(75);
  
  matrix.clear();
  matrix.drawBitmap(0, 0, small_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(75);

  matrix.clear();
  matrix.drawBitmap(0, 0, med_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(75);

  matrix.clear();
  matrix.drawBitmap(0, 0, large_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(75);
  
  matrix.clear();
  matrix.drawBitmap(0, 0, med_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(75);
  
  matrix.clear();
  matrix.drawBitmap(0, 0, small_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(75);
  
  matrix.clear();
  matrix.drawBitmap(0, 0, empty_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(75);
  
#endif
#ifdef TEXT
  matrix.setTextSize(1);
  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(LED_ON);
  for (int8_t x=7; x>=-108; x--) {
          matrix.clear();
          matrix.setCursor(x,0);
          matrix.print("Novasys Ingenierie");
          matrix.writeDisplay();
          delay(100);
  }
/*  
  matrix.setRotation(3);
  for (int8_t x=7; x>=-36; x--) {
          matrix.clear();
          matrix.setCursor(x,0);
          matrix.print("Ingenierie");
          matrix.writeDisplay();
          delay(100);
  }
*/  
  //matrix.setRotation(0);
#endif
#ifdef IMAGE1
  matrix.clear();
  matrix.drawBitmap(0, 0, image_name , 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(500);
  matrix.clear();
  matrix.drawBitmap(0, 0, neutral_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(500);

  matrix.clear();
  matrix.drawBitmap(0, 0, frown_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(500);  
#endif
  
#ifdef SNOW  // snow
  matrix.clear();
  for ( int i=0; i < NUM_FLAKES ; i++ ) {
    snow[i].next();
    int x = floor(snow[i].x);
    int y = floor(snow[i].y);
    matrix.drawPixel(x,y,1); // draw dot
  }
  matrix.writeDisplay();
  delay(50);
#endif

  
#ifdef EXAMPLE1
  // EFFACER LE CONTENU PRECEDENT:
  matrix.clear();
  
  // DESSINER UN PIXEL:
  matrix.drawPixel(x, y, LED_ON);
  
  // DESSINER UNE LIGNE:
  matrix.drawLine( x0, y0, x1, y1, LED_ON);
  
  // DESSINER UN RECTANGLE VIDE:
  matrix.drawRect( x , y, width, height , LED_ON);
  
  // REMPLIR UN RECTANGLE:
  matrix.fillRect(x, y, width, height  , LED_ON);
  
  // DESSINER UN CERCLE VIDE:
  matrix.drawCircle( x , y, radius, LED_ON);
  
  // REMPLIR UN CERCLE:
  matrix.fillCircle(x, y, radius, LED_ON);
  
  // DESSINER UN TRIANGLE VIDE:
  matrix.drawTriangle(x0, y0, x1, y1,  x2, y2, LED_ON );
  
  // REMPLIR UN TRIANGLE:
  matrix.fillTriangle(ux0, y0, x1, y1,  x2, y2, LED_ON);
  
  // TEXTE:
  matrix.setTextSize(1);
  matrix.setTextWrap(false);  // NO TEXT WRAP
  matrix.setTextColor(LED_ON);
  matrix.setCursor(x,y);
  matrix.print("text");
  
  // METTRE A JOUR LES PIXELS A LA MATRICE:
  matrix.writeDisplay();  // write the changes we made to the display
#endif
#if 0
  for(int y=0;y<8;y++)
  {
    for(int x=0;x<8;x++)
    {
        matrix.dot(x,y); // draw dot
        matrix.display();
        delay(20);
        matrix.dot(x,y,0);//clear dot
        matrix.display();
        delay(20);        
    }  
  }
#endif
}

