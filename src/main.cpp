#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

// Displej ma 128 pixelu na sirku
#define SCREEN_WIDTH 128

// Displej ma 64 pixelu na vysku
#define SCREEN_HEIGHT 64

// Wire pro lepsi komunikaci mezi Arduinem a periferii (displejem)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pin, na kterem je nastaven senzor
#define PULSE_SENSOR_PIN 36

// 500/20ms znamena, ze budeme merit tep 10 sekund
#define NUMBER_OF_VALS 500

// Inicializace signalu
int Signal;
int last_bpm = 0;

void setup()
{
  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  delay(2000);
}

// https://stackoverflow.com/questions/31203438/apply-median-filter-manually-with-opencv-differences-with-medianblur-function

// Jednoduchy medianovy filtr
int median(int data[], int length) {
  // Iterace pres pole hodnot
  for (int i = 0; i < length - 1; i++) {
    // Porovnavani hodnot
    for (int j = i + 1; j < length; j++) {
      if (data[j] < data[i]) {
        int temp = data[i];
        data[i] = data[j];
        data[j] = temp;
      }
    }
  }
  // Vrati hodnotu uprostred pole
  return data[length / 2];
}

void loop()
{
  // Pro odcitani vterin
  // Nastavi hodnotu na aktualni hodnotu v programu
  unsigned long previous_millis = millis();

  // Cas, ktery odcitame (tuto dobu trva mereni)
  int time = 10;

  // Interval 1000ms (po kterych chceme odecist 1 vterinu)
  const long interval = 1000;

  // Seznam s hodnotami z mereni
  int values[NUMBER_OF_VALS];

  // Pocet anomalii
  int anomally = 0;
  int bpm = 0;
  int median_value = 0;

  // Pokus provadime 10 vterin, tak aby hodnoty byly presnejsi a zaroven to netrvalo celou minutu
  // While loop mel lepsi funkcionalitu
  int i = 0;
  while (i < NUMBER_OF_VALS)
  {
    // Kolik milisekund bezi aktualne program
    unsigned long curent_millis = millis();

    // If, ktery nam odecita vteriny a ukazuje je na displeji
    if (curent_millis - previous_millis >= interval)
    {
      previous_millis = curent_millis;
      time--;
      // Displej muze ukazovat pouze 0-9
      if (time >= 0)
      {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.println("BPM: " + String(last_bpm));
        display.setCursor(0, 30);
        display.println("Time: " + String(time));
        display.display();
      }
    }

    // Ziskame hodnoty ze senzoru
    int read = analogRead(PULSE_SENSOR_PIN);
    values[i] = read;

    // Mezi dalsim merenim pockame 20ms
    delay(20);
    i++;
  }

  // Volame medianovy filtr na nami ziskane hodnoty
  median_value = median(values, NUMBER_OF_VALS);

  // Cyklus prochazejici namerene hodnoty
  int y = 0;
  while (y < NUMBER_OF_VALS)
  {
    // Pokud to byly anomalie, ktere byly 40 nad hodnotu z medianoveho filtru
    if (median_value + 40 < values[y])
    {
      anomally++;
    }
    y++;
  }
  y = 0;

  // Mereni trva 10 sekund, proto vynasobime 6, abychom dostali minutu
  int current_bpm = anomally * 6;

  // Nastavi displej
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.setTextColor(WHITE);

  // Posledni namerena hodnota se nastavi do last_bpm
  // Podminky pro zmereni adekvatniho tepu 
  if (current_bpm > 40 && current_bpm < 200)
  {
    last_bpm = current_bpm;
  }

  // Zobrazi posledni namerenou hodnonu na displeji spolecne se vterinami, ktere zbyvaji do konce
  display.println("BPM: " + String(last_bpm));
  display.setCursor(0, 30);
  display.println("Time: " + String(time));
  display.display();
}