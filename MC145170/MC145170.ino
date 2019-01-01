// Program Issue: MC145170 PLL control
// Author: Kevin Liu
// Date: 2018/12/24
// Last Modify: 2019/01/02

#define TX_SCK 13
#define TX_CS 10
#define TX_MOSI 11
#define TX 9
#define RX_SCK 8
#define RX_CS 7
#define RX_MOSI 6

void setup() {

pinMode(TX, INPUT);
pinMode(TX_SCK, OUTPUT);
pinMode(TX_CS, OUTPUT);
pinMode(TX_MOSI, OUTPUT);

pinMode(RX_SCK, INPUT);
pinMode(RX_CS, INPUT);
pinMode(RX_MOSI, INPUT);

digitalWrite(TX_CS, HIGH);

delay(10);
pll_init();
delay(10);

}   // end of setup()

void loop() {

unsigned int FREQ;    // Freqency = FREQ x 5kHz

if(!digitalRead(RX_CS)){
/*
    FREQ = 5205;

else

    FREQ = 5751;

   delay(1000);
*/  
     write_pll(read_pll()-2139);    // read pic rx pll and recalculate write to tx pll **(10.695MHz)

     delay(10);
     
  }   // end of if()
}   // end of loop()

unsigned int read_pll(void){

unsigned int COUNTER = 0;

  for(int i = 0; i < 16; i++){

  while(digitalRead(RX_SCK))
    ;
  
  COUNTER = COUNTER << i | digitalRead(RX_MOSI);

  while(!digitalRead(RX_SCK))
    ;

  }

return COUNTER;  
}   // end of read_pll()


void write_pll(unsigned int COUNTER){

  digitalWrite(TX_CS, LOW);
  
        for (int i = 0; i < 16; i++)  {

               digitalWrite(TX_MOSI, (COUNTER >> 15-i & 1));


               digitalWrite(TX_SCK, HIGH);
               delay(1);
               digitalWrite(TX_SCK, LOW);     
               delay(1);       
       }

   digitalWrite(TX_CS, HIGH);

}   // end of write_pll()



void pll_init(void){

        for (int i = 0; i < 4; i++)  {

               digitalWrite(TX_MOSI, (0 >> 3-i & 1));    // write Dec value 0 with 4 bits


               digitalWrite(TX_SCK, HIGH);
               delay(1);
               digitalWrite(TX_SCK, LOW);     
               delay(1);       
       }  // first 4 bit init

 delay(5);

 digitalWrite(TX_CS, LOW);
  
        for (int i = 0; i < 5; i++)  {

               digitalWrite(TX_MOSI, (2 >> 4-i & 1));    // write Dec value 2 with 5 bits


               digitalWrite(TX_SCK, HIGH);
               delay(1);
               digitalWrite(TX_SCK, LOW);     
               delay(1);       
       }

   digitalWrite(TX_CS, HIGH);

   delay(1);

   digitalWrite(TX_CS, LOW);
  
        for (int i = 0; i < 8; i++)  {

               digitalWrite(TX_MOSI, (96 >> 7-i & 1));   // write Dec value 96 with 8 bits


               digitalWrite(TX_SCK, HIGH);
               delay(1);
               digitalWrite(TX_SCK, LOW);     
               delay(1);       
       }

   digitalWrite(TX_CS, HIGH);

   delay(1);

   digitalWrite(TX_CS, LOW);
  
        for (int i = 0; i < 15; i++)  {

               digitalWrite(TX_MOSI, (2048 >> 14-i & 1));   // write Dec value 2048 with 15 bits


               digitalWrite(TX_SCK, HIGH);
               delay(1);
               digitalWrite(TX_SCK, LOW);     
               delay(1);       
       }

   digitalWrite(TX_CS, HIGH);  

}   // end of pll_init()   
