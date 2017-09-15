#include <avr/io.h>
#include <avr/interrupt.h>

#define RX PB4
#define TX PB3
#define BUTTON PB2

#define DATA_LENGTH 8

const char send_data[32] = {0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,1};
char recv_data[32];

volatile int receiving = 0;
volatile int bits = 0;

volatile int d = 0;

/* Interrupt scheduler for external interrupt on RX pin */
/* Occurs when RX pin gets pulled low */
ISR(PCINT0_vect) 
{   
  TIMSK |= (1 << OCIE1A); // Enable compare matching for timer interrupt
  PCMSK &= (0 << PCINT4) | (0 << PCINT2); // Mask interrupts on both pins
  GIMSK &= (0 << PCIE); // Disable pin change interrupts temporarily
  
  //if (digitalRead(BUTTON)) // If send signal isn't high means RX line changed
    //receiving = 1;
} 

/* Interrupt scheduler for defining bit rate */
ISR(TIMER1_COMPA_vect)
{ 

  receiving = 1;
  if (receiving)
  {
    digitalWrite(0, 1);
    //recv_data[bits] = digitalRead(RX); 
    //digitalWrite(0, recv_data[bits]); // For debugging
  }
  else // If not receiving then sending
  {
    digitalWrite(TX, send_data[bits]);
  }


  if (bits == (DATA_LENGTH - 1)) // If all data has been received or sent
  {
    
    bits = 0;
    TIMSK &= (0 << OCIE1A); // Disable timer interrupt
    digitalWrite(1, 0); // Turn off receiving indicator

    if (receiving)
      playback();

    receiving = 0; // Will always be 0 even if we weren't receiving anyway
    PCMSK |= (1 << PCINT4) | (1 << PCINT2);
    GIMSK |= (1 << PCIE); // Re-enable pin change interrupts 
  }
  else
  {
    bits += 1;
  }
  
  
}

void setup() 
{ 
  /* divide by 8, multiply by 13 for a 9600 baud */
  TCCR1 |= (1 << CTC1);                               /* clear timer on compare match */
  //TCCR1 |= (1 << CS12);                               /*clock prescaler 8 */
  //OCR1C = 13;                                         /* compare match value */ 

  /* FOR 1 SEC INTERRUPTS */
  TCCR1 |= (1 << CS13) | (1 << CS12) | (1 << CS11);
  OCR1C = 122;
 
  PORTB |= (1 << PB4) | (1 << PB2);                   /* Pullup resistor on pin 4 (RX) and pin 2 (send) */
  PCMSK |= (1 << PCINT4)| (1 << PCINT2);             /* pin change interrupt on pin 4 (RX) and pin 2 (send) */                                           
  DDRB = 0x0b;                                        /* Only pins 3 & 0 are output (TX and onboard LED) and now 1 too */
  GIMSK |= (1 << PCIE);                               /* pin change interrupt enabled */

  sei();                                              /* enable interrupts*/
}

void loop() 
{
  digitalWrite(1, receiving);
}

void playback()
{
  int i;
  for (i = 0; i < DATA_LENGTH; i++)
  {
    delay(5000);
    digitalWrite(0, recv_data[i]);
  }
  delay(5000);
  digitalWrite(0, 0);
}






