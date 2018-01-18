// ATtiny85 outputs
const int LED1 = 0;
const int LED2 = 1;
const int LED3 = 4;
const int LED4 = 3;
volatile uint8_t* Port[] = {&OCR0A, &OCR0B, &OCR1A, &OCR1B};
  int dir1 = 1;
  int dir2 = 1;
  int dir3 = 1;
  int dir4 = 1;

 int  tempOCR0A = 255;
 int  tempOCR0B = 255;
 int  tempOCR1A = 255;
 int  tempOCR1B = 255;
      
void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  // Configure counter/timer0 for fast PWM on PB0 and PB1
  TCCR0A = 3<<COM0A0 | 3<<COM0B0 | 3<<WGM00;
  TCCR0B = 0<<WGM02 | 3<<CS00; // Optional; already set
  // Configure counter/timer1 for fast PWM on PB4
  TCCR1 = 1<<CTC1 | 1<<PWM1A | 3<<COM1A0 | 7<<CS10;
  GTCCR = 1<<PWM1B | 3<<COM1B0;
  // Interrupts on OC1A match and overflow
  TIMSK = TIMSK | 1<<OCIE1A | 1<<TOIE1;



}

ISR(TIMER1_COMPA_vect) {
  if (!bitRead(TIFR,TOV1)) bitSet(PORTB, LED4);
}

ISR(TIMER1_OVF_vect) {
  bitClear(PORTB, LED4);
}

/*
void SET(int temp, int place){
  switch(place){
    case 1:
      OCR0A = temp;
    break;

    case 2:
      OCR0B = temp;
    break;

    case 3:
      OCR1A = temp;
    break;

    case 4:
      OCR1B = temp;
    break;
  }
  
}
*/

void loop() {

switch(dir1){
  case 1:
      if(OCR0A > 0){
        tempOCR0A--;
        if(tempOCR0A <= 255){
        OCR0A = tempOCR0A;
        }
      }
      else{
        dir1=2;
      }
    break;
  case 2:
      if(OCR0A < 255){
        tempOCR0A++;
        OCR0A = tempOCR0A;
      }
      else{
        OCR0A = 255;
        dir1 = 1;
        tempOCR0A = random(255,1000);
      }
    break;
    }

switch(dir2){
  case 1:
      if(OCR0B > 0){
        tempOCR0B--;
        if(tempOCR0B <= 255){
        OCR0B = tempOCR0B;
        }
      }
      else{
        dir2=2;
      }
    break;
  case 2:
      if(OCR0B < 255){
        tempOCR0B++;
        OCR0B = tempOCR0B;
      }
      else{
        OCR0B = 255;
        dir2 = 1;
        tempOCR0B = random(255,1000);
      }
    break;
    }

switch(dir3){
  case 1:
      if(OCR1A > 0){
        tempOCR1A--;
        if(tempOCR1A <= 255){
        OCR1A = tempOCR1A;
        }
      }
      else{
        dir3=2;
      }
    break;
  case 2:
      if(OCR1A < 255){
        tempOCR1A++;
        OCR1A = tempOCR1A;
      }
      else{
        OCR1A = 255;
        dir3 = 1;
        tempOCR1A = random(255,1000);
      }
    break;
    }

 
/*
switch(dir4){
  case 1:
      if(OCR1B > 0){
        tempOCR1B--;
        if(tempOCR1B <= 255){
        OCR1B = tempOCR1B;
        }
      }
      else{
        dir4=2;
      }
    break;
  case 2:
      if(OCR1B < 255){
        tempOCR1B++;
        OCR1B = tempOCR1B;
      }
      else{
        OCR1B = 255;
        dir4 = 1;
        tempOCR1B = random(510,255);
      }
    break;
    }
/*
*/    
delay(100);
}
