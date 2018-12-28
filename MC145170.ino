// Program Issue: MC145170 PLL control
// Author: Kevin Liu
// Date: 2018/12/24

#define SCK 13
#define CS 10
#define MOSI 11
#define TX 9


void setup() {

pinMode(TX, INPUT);
pinMode(SCK, OUTPUT);
pinMode(CS, OUTPUT);
pinMode(MOSI, OUTPUT);

digitalWrite(CS, HIGH);

delay(10);
pll_init();
delay(10);

}   // end of setup()

void loop() {

unsigned int FREQ;    // Freqency = FREQ x 5kHz

if(digitalRead(TX))

    FREQ = 5205;

else

    FREQ = 5751;
  
   pll(FREQ);

   delay(1000);
   
}   // end of loop()


void pll(unsigned int COUNTER){

  digitalWrite(CS, LOW);
  
        for (int i = 0; i < 16; i++)  {

               digitalWrite(MOSI, (COUNTER >> 15-i & 1));


               digitalWrite(SCK, HIGH);
               delay(1);
               digitalWrite(SCK, LOW);     
               delay(1);       
       }

   digitalWrite(CS, HIGH);

}   // end of pll()



void pll_init(void){

        for (int i = 0; i < 4; i++)  {

               digitalWrite(MOSI, (0 >> 3-i & 1));    // write Dec value 0 with 4 bits


               digitalWrite(SCK, HIGH);
               delay(1);
               digitalWrite(SCK, LOW);     
               delay(1);       
       }  // first 4 bit init

 delay(5);

 digitalWrite(CS, LOW);
  
        for (int i = 0; i < 5; i++)  {

               digitalWrite(MOSI, (2 >> 4-i & 1));    // write Dec value 2 with 5 bits


               digitalWrite(SCK, HIGH);
               delay(1);
               digitalWrite(SCK, LOW);     
               delay(1);       
       }

   digitalWrite(CS, HIGH);

   delay(1);

   digitalWrite(CS, LOW);
  
        for (int i = 0; i < 8; i++)  {

               digitalWrite(MOSI, (96 >> 7-i & 1));   // write Dec value 96 with 8 bits


               digitalWrite(SCK, HIGH);
               delay(1);
               digitalWrite(SCK, LOW);     
               delay(1);       
       }

   digitalWrite(CS, HIGH);

   delay(1);

   digitalWrite(CS, LOW);
  
        for (int i = 0; i < 15; i++)  {

               digitalWrite(MOSI, (2048 >> 14-i & 1));   // write Dec value 2048 with 15 bits


               digitalWrite(SCK, HIGH);
               delay(1);
               digitalWrite(SCK, LOW);     
               delay(1);       
       }
/
   digitalWrite(CS, HIGH);  

}   // end of pll_init()   

