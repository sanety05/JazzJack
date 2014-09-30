#include <Adafruit_NeoPixel.h>

#define LEDPIN 6
#define MICPIN 0
#define MAX_BRIGHTNESS 128
#define MIN_BRIGHTNESS  4
#define MAX_VOLUME 100
#define MIN_VOLUME   0
#define ARRAY_NUM   20          //ミディアンフィルタをかける場合は偶数
#define COLOR_CHANGE 28


Adafruit_NeoPixel strip = Adafruit_NeoPixel(60,LEDPIN,NEO_GRB + NEO_KHZ800);

float volumeArray[ARRAY_NUM];
int index = 0;

float volume,sum;
int brightness = 0;

boolean yellowFlag = false;

int r,g,b;

uint32_t color;

void setup()
{
  Initialize();
}

void loop()
{
  ChangeBrightness(MicProcess(MICPIN));
  
  delay(7.5f);
}

void Initialize()
{
  Serial.begin(9600);
  strip.begin();
  strip.show();
  for(int i = 0; i < 60 ; i++)
    strip.setPixelColor(i,0,0,255); 
}

int MicProcess(int pin)
{
  float val = analogRead(pin);
  val = abs(330 - val);
  volumeArray[index] = val;
  
  /*if(index != 0)
  {
    volumeArray[index] = 0.9f * volumeArray[index-1] + 0.1 * val;
  }
  else
  {
    volumeArray[index] = val;
  }*/
  index ++;
  if(index > ARRAY_NUM)
  {
    index = 0;
  }
  BobbleSort(volumeArray , ARRAY_NUM);
  //volume = sum/10;
  volume = volumeArray[ARRAY_NUM/2];
  //volume = volumeArray[index];
  volume = map(volume,5,450,MIN_VOLUME,MAX_VOLUME);

  sum = 0;
  
  return volume;

}

void ChangeBrightness(float vol)
{
  vol = map(vol,0,100,MIN_BRIGHTNESS,MAX_BRIGHTNESS);
  if(vol > COLOR_CHANGE)
  {
    yellowFlag = true;
  }
  if(yellowFlag && vol < 10)
  {
    yellowFlag = false;
  }
  if(!yellowFlag)
  {
    color = strip.Color(0,0,vol);
  }
  else
  {
    color = strip.Color(0,vol,vol);
  }
  
  for(int i = 0; i < 60 ; i++)
     strip.setPixelColor(i,color); 
  strip.show();
 Serial.println(vol);
}
