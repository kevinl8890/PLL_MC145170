// Program Issue: MC145170 PLL control
// Author: Kevin Liu
// Date: 2018/12/24
// Last Modify: 2019/01/02

#define TX_SCK 13
#define TX_CS 10
#define TX_MOSI 11
//#define TX 9
#define RX_SCK 8
#define RX_CS 7
#define RX_MOSI 6
#define BOOT_DELAY 2850

void setup() {

//pinMode(TX, INPUT);
pinMode(TX_SCK, OUTPUT);
pinMode(TX_CS, OUTPUT);
pinMode(TX_MOSI, OUTPUT);

pinMode(RX_SCK, INPUT);
pinMode(RX_CS, INPUT);
pinMode(RX_MOSI, INPUT);

digitalWrite(TX_CS, HIGH);

delay(BOOT_DELAY);

pll_init();

while(digitalRead(RX_CS))
  ;

}   // end of setup()


void loop() {


if(!digitalRead(RX_CS))
  
     write_pll(read_pll()-2139);    // read pic rx pll and recalculate write to tx pll **(10.695MHz)(2139) Freqency = COUNTER x 5kHz

}   // end of loop()



unsigned int read_pll(void){

unsigned int COUNTER = 0;
unsigned int BIT = 0;

  for(int i = 1; i < 17; i++){

  while(!digitalRead(RX_SCK))
    ;

  BIT = digitalRead(RX_MOSI);
  
  COUNTER |= BIT << 16-i;

  while(digitalRead(RX_SCK))
    ;
  }   // end of for()

return COUNTER;  
}   // end of read_pll()


void write_pll(unsigned int COUNTER){

  digitalWrite(TX_CS, LOW);
  
        for (int i = 0; i < 16; i++)  {

               digitalWrite(TX_MOSI, (COUNTER >> 15-i & 1));


               digitalWrite(TX_SCK, HIGH);
               delayMicroseconds(100);
               digitalWrite(TX_SCK, LOW);     
               delayMicroseconds(100);       
       }

   digitalWrite(TX_CS, HIGH);

}   // end of write_pll()



void pll_init(void){

        for (int i = 0; i < 4; i++)  {

               digitalWrite(TX_MOSI, (0 >> 3-i & 1));    // write Dec value 0 with 4 bits

               digitalWrite(TX_SCK, HIGH);
               delayMicroseconds(100);
               digitalWrite(TX_SCK, LOW);     
               delayMicroseconds(100);       
       }  // first 4 bit init

 delay(5);

 digitalWrite(TX_CS, LOW);
  
        for (int i = 0; i < 5; i++)  {

               digitalWrite(TX_MOSI, (2 >> 4-i & 1));    // write Dec value 2 with 5 bits

               digitalWrite(TX_SCK, HIGH);
               delayMicroseconds(100); 
               digitalWrite(TX_SCK, LOW);     
               delayMicroseconds(100);       
       }

   digitalWrite(TX_CS, HIGH);

   delayMicroseconds(100); 

   digitalWrite(TX_CS, LOW);
  
        for (int i = 0; i < 8; i++)  {

               digitalWrite(TX_MOSI, (96 >> 7-i & 1));   // write Dec value 96 with 8 bits

               digitalWrite(TX_SCK, HIGH);
               delayMicroseconds(100); 
               digitalWrite(TX_SCK, LOW);     
               delayMicroseconds(100);       
       }

   digitalWrite(TX_CS, HIGH);

   delayMicroseconds(100); 

   digitalWrite(TX_CS, LOW);
  
        for (int i = 0; i < 15; i++)  {

               digitalWrite(TX_MOSI, (2048 >> 14-i & 1));   // write Dec value 2048 with 15 bits


               digitalWrite(TX_SCK, HIGH);
               delayMicroseconds(100); 
               digitalWrite(TX_SCK, LOW);     
               delayMicroseconds(100);        
       }

   digitalWrite(TX_CS, HIGH);  

}   // end of pll_init()   
