// This is a demonstration on how to use an input device to trigger changes on your neo pixels.
// You should wire a momentary push button to connect from ground to a digital IO pin.  When you
// press the button it will change to a new pixel animation.  Note that you need to press the
// button once to start the first animation!

#include <Adafruit_NeoPixel.h>
#include <ButtonDebounce.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define DEBOUNCE_DELAY  250
#define BUTTON0_PIN   D1   // Digital IO pin connected to the button.  This will be
#define BUTTON1_PIN   D2   // driven with a pull-up resistor so the switch should
#define BUTTON2_PIN   D3   // pull the pin to ground momentarily.  On a high -> low
#define BUTTON3_PIN   D4   // transition the button press logic will execute.

#define PIXEL0_PIN    D5    // Digital IO pin connected to the NeoPixels.
#define PIXEL1_PIN    D6    // Digital IO pin connected to the NeoPixels.
#define PIXEL2_PIN    D7    // Digital IO pin connected to the NeoPixels.
#define PIXEL3_PIN    D8    // Digital IO pin connected to the NeoPixels.

#define PIXEL_COUNT 147
#define FADEOUTDELAY 10
#define FADEOUTSTEP  3
#define MINWHITE     15



const char* ssid = "museomix-team5";
const char* password = "museomix";
const char* mqtt_server = "192.168.1.103";

//WiFiClient espClient;
//PubSubClient client(espClient);

// Parameter 1 = number of pixels in strip,  neopixel stick has 8
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick
Adafruit_NeoPixel strip0 = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL0_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL1_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL2_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL3_PIN, NEO_GRB + NEO_KHZ800);

ButtonDebounce button0(BUTTON0_PIN, DEBOUNCE_DELAY);
ButtonDebounce button1(BUTTON1_PIN, DEBOUNCE_DELAY);
ButtonDebounce button2(BUTTON2_PIN, DEBOUNCE_DELAY);
ButtonDebounce button3(BUTTON3_PIN, DEBOUNCE_DELAY);

typedef struct pixel {
  int r;
  int g;
  int b;
  int br;
  boolean button_state;
} pixel_t;

pixel_t st0 = {255, 255, 255, 15, HIGH};
pixel_t st1 = {255, 255, 255, 15, HIGH};
pixel_t st2 = {255, 255, 255, 15, HIGH};
pixel_t st3 = {255, 255, 255, 15, HIGH};

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(9600);
//  setup_wifi();

//  client.setServer(mqtt_server, 1883);

  pinMode(BUTTON0_PIN,INPUT_PULLUP);
  pinMode(BUTTON1_PIN,INPUT_PULLUP);
  pinMode(BUTTON2_PIN,INPUT_PULLUP);
  pinMode(BUTTON3_PIN,INPUT_PULLUP);

  strip0.begin();
  strip1.begin();
  strip2.begin();
  strip3.begin();
  strip0.show(); // Initialize all pixels to 'off'
  strip1.show();
  strip2.show();
  strip3.show();
  
}

void update_buttons(){
  button0.update();
  button1.update();
  button2.update();
  button3.update();
}


void strip_colors(int strip, int r, int g, int b, int br){

  int i;
  
  switch(strip){
    case 0:
        for (i = 0; i < PIXEL_COUNT; i++ )
          strip0.setPixelColor(i, r, g, b);
        strip0.setBrightness(br);
        strip0.show();
        break;
    case 1:
        for (i = 0; i < PIXEL_COUNT; i++ )
          strip1.setPixelColor(i, r, g, b);
        strip1.setBrightness(br);
        strip1.show();
        break;
    case 2:
        for (i = 0; i < PIXEL_COUNT; i++ )
          strip2.setPixelColor(i, r, g, b);
        strip2.setBrightness(br);
        strip2.show();
        break;
    default:
        for (i = 0; i < PIXEL_COUNT; i++ )
          strip3.setPixelColor(i, r, g, b);
        strip3.setBrightness(br);
        strip3.show();
  }
}

void loop() {
  // Get current button state.
  update_buttons();

  if(button0.state() == LOW) {
    strip_colors(0, 255, 0, 0, 255);
 
  } else if (button1.state() == LOW){
    strip_colors(1, 0, 0, 255, 255);

  } else if (button2.state() == LOW){
    strip_colors(2, 0, 255, 255, 255);
    
  } else if (button3.state() == LOW){
    strip_colors(3, 0, 255, 0, 255);

  } else {
    strip_colors(0, 255, 255, 255, 25);
    strip_colors(1, 255, 255, 255, 25);
    strip_colors(2, 255, 255, 255, 25);
    strip_colors(3, 255, 255, 255, 25);
  }
  
}


void startShow(int i) {
  
  switch(i){
    case 0: colorWipe(strip0.Color(0, 0, 0), 0);    // Black/off
            break;
    case 1: strip0.setBrightness(255);
            colorWipe(strip0.Color(255, 0, 0), 0);  // Red
            break;
    case 2: colorWipe(strip0.Color(0, 255, 0), 0);  // Green
            break;
    case 3: colorWipe(strip0.Color(0, 0, 255), 0);  // Blue
            break;
    case 4: strip1.setBrightness(255);
            colorWipe(strip0.Color(255, 255, 255), 0); // White
            strip1.show();
            break;
    case 5: theaterChase(strip0.Color(127,   0,   0), 50); // Red
            break;
    case 6: theaterChase(strip0.Color(  0,   0, 127), 50); // Blue
            break;
    case 7: rainbow(20);
            break;
    case 8: rainbowCycle(20);
            break;
    case 9: theaterChaseRainbow(50);
            break;
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip1.numPixels(); i++) {
    strip1.setPixelColor(i, c);
    strip1.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip1.numPixels(); i++) {
      strip1.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip1.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip1.numPixels(); i++) {
      strip1.setPixelColor(i, Wheel(((i * 256 / strip1.numPixels()) + j) & 255));
    }
    strip1.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip1.numPixels(); i=i+3) {
        strip1.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip1.show();

      delay(wait);

      for (int i=0; i < strip1.numPixels(); i=i+3) {
        strip1.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip1.numPixels(); i=i+3) {
        strip1.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip1.show();

      delay(wait);

      for (int i=0; i < strip1.numPixels(); i=i+3) {
        strip1.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {

  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip1.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip1.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip1.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
