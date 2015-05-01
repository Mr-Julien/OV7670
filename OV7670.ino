// this program only send in serial, data as it arrived in  YCbCr422.

int hrefPin = 13;
int vsyncPin = 12;
int d0Pin = 3;
int d1Pin = 4;
int d2Pin = 5;
int d3Pin = 6;
int d4Pin = 7;
int d5Pin = 8;
int d6Pin = 9;
int d7Pin = 10;
int d0 = 0;
int d1 = 0;
int d2 = 0;
int d3 = 0;
int d4 = 0;
int d5 = 0;
int d6 = 0;
int d7 = 0;
byte buf[614400]; // Buffer an image 640x480 with 2 bytes by pixels in average
int clockPin = A0;
int k = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(vsyncPin, INPUT);
  pinMode(hrefPin, INPUT);
  pinMode(d0Pin, INPUT);
  pinMode(d1Pin, INPUT);
  pinMode(d2Pin, INPUT);
  pinMode(d3Pin, INPUT);
  pinMode(d4Pin, INPUT);
  pinMode(d5Pin, INPUT);
  pinMode(d6Pin, INPUT);
  pinMode(d7Pin, INPUT);
  pinMode(clockPin, OUTPUT);
  attachInterrupt(0, blink, RISING); // Detect any rising edge on PCLK
}

void loop()
{
  analogWrite(clockPin, 160); // 10MHz on XCLK 
  if(k >= 614400)             // I an image is complete 
  {
    for (int i=0; i <= 614400; i++)
    {
      Serial.println(buf[i]); // write the image on the serial port
    } 
    k = 0; // Reset k for a new image capture

  }  
}

void blink()
{
  if (digitalRead(vsyncPin) == 0)  // meaning we are on a frame
  {
    if (digitalRead(hrefPin) == 1) // meaning we are on a line
    {
      d0 = digitalRead(d0Pin);
      d1 = digitalRead(d1Pin);
      d2 = digitalRead(d2Pin);
      d3 = digitalRead(d3Pin);
      d4 = digitalRead(d4Pin);
      d5 = digitalRead(d5Pin);
      d6 = digitalRead(d6Pin);
      d7 = digitalRead(d7Pin);
      buf[k++] = (d0 + d1*2 + d2*4 + d3*8 + d4*16 + d5*32 + d6*64 + d7*128); 

    }
  }
}

