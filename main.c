/********************************************
 *
 *  Name: Carson Matz
 *  Email: cmatz@usc.edu
 *  Section: Friday, 12:30
 *  Assignment: Lab 7 - Rotary Encoder
 *
 ********************************************/

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "lcd.h"

#include <avr/interrupt.h>

void variable_delay_us(int);
void play_note(unsigned short);

//my own clear function
void clearTop();
void clearBot();

// Frequencies for natural notes from middle C (C4)
// up one octave to C5.
unsigned short frequency[8] =
    { 262, 294, 330, 349, 392, 440, 494, 523 };

volatile unsigned char new_state, old_state;
volatile unsigned char changed = 0;  // Flag for state change
volatile int count = 0;		// Count to display
volatile unsigned char a, b;

int main(void) {
    

    // Initialize DDR and PORT registers and LCD
    lcd_init(); //initialize lcd
    DDRB |= (1<<4); //initialize port b4 to output
    PORTB &= ~(1<<4); //initialize ouput of b4 to low
    PORTC |= (1 << 1)|(1 << 5); //initialize pullup resistors
    //enable interupts
    PCMSK1 |= (1 << PCINT9) | (1 << PCINT13); 
    PCICR |= (1 << PCIE1);
    sei();

    // Write a spash screen to the LCD
    clearTop();
    clearBot();
    lcd_moveto(1,0);
    lcd_stringout("EE109 Lab 7");
    lcd_moveto(0, 0);
    lcd_stringout("Carson");
    _delay_ms(1000);
    clearBot();
    lcd_moveto(1, 6);

    // Read the A and B inputs to determine the intial state.
    // In the state number, B is the MSB and A is the LSB.
    // Warning: Do NOT read A and B separately.  You should read BOTH inputs
    // at the same time, then determine the A and B values from that value.
    unsigned char both = PINC & ((1<<5)|(1<<1));
    a = both & (1<<5);
    b = both & (1<<1);    

    if (!b && !a)
	old_state = 0;
    else if (!b && a)
	old_state = 1;
    else if (b && !a)
	old_state = 2;
    else
	old_state = 3;

    new_state = old_state;

    // Output count to LCD
	char s[10];
	snprintf(s, 10, "%d", count);
	lcd_stringout(s);

    while (1) {                 // Loop forever
        if (changed) { // Did state change?
	    changed = 0;        // Reset changed flag

	    // Output count to LCD
	    clearBot();
    	lcd_moveto(1, 6);
	    snprintf(s, 10, "%d", count);
	    lcd_stringout(s);
	    // Do we play a note?
	    if ((count % 8) == 0) {
		// Determine which note (0-7) to play
	    int note;
	    if(count > 0){
	    	note = (count % 64) / 8;
	    }
	    else{
	    	note = (-count % 64) / 8;
	    } 
		// Find the frequency of the note
	    int freq = frequency[note];
		// Call play_note and pass it the frequency
	    play_note(freq);
	    }
        }
    }
}

ISR(PCINT1_vect){
	// Read the input bits and determine A and B.
    unsigned char both = PINC & ((1<<5)|(1<<1));
    a = both & (1<<5);
    b = both & (1<<1);
	// For each state, examine the two input bits to see if state
	// has changed, and if so set "new_state" to the new state,
	// and adjust the count value.
	if (old_state == 0) {

	    // Handle A and B inputs for state 0
	    if(a){
	    	new_state = 1;
	    	count++;
	    }
	    else if(b){
	    	new_state = 2;
	    	count--;
	    }

	}
	else if (old_state == 1) {

	    // Handle A and B inputs for state 1
	    if(!a){
	    	new_state = 0;
	    	count--;
	    }
	    else if(b){
	    	new_state = 3;
	    	count++;
	    }

	}
	else if (old_state == 2) {

	    // Handle A and B inputs for state 2
	    if(a){
	    	new_state = 3;
	    	count--;
	    }
	    else if(!b){
	    	new_state = 0;
	    	count++;
	    }

	}
	else {   // old_state = 3

	    // Handle A and B inputs for state 3
		if(!a){
	    	new_state = 2;
	    	count++;
	    }
	    else if(!b){
	    	new_state = 1;
	    	count--;
	    }
	}

	// If state changed, update the value of old_state,
	// and set a flag that the state has changed.
	if (new_state != old_state) {
	    changed = 1;
	    old_state = new_state;
	}
}

/*
  Play a tone at the frequency specified for one second
*/
void play_note(unsigned short freq)
{
    unsigned long period;

    period = 1000000 / freq;      // Period of note in microseconds

    while (freq--) {
	// Make PB4 high
    PORTB |= (1 << PB4);
	// Use variable_delay_us to delay for half the period
    variable_delay_us(period/2);
	// Make PB4 low
    PORTB &= ~(1 << PB4);
	// Delay for half the period again
    variable_delay_us(period/2);
    }
}

/*
    variable_delay_us - Delay a variable number of microseconds
*/
void variable_delay_us(int delay)
{
    int i = (delay + 5) / 10;

    while (i--)
        _delay_us(10);
}

//my clear function
void clearTop(){
    char clear[20] = "                   ";
    lcd_moveto(0,0);
    lcd_stringout(clear);
}

void clearBot(){
    char clear[20] = "                   ";
    lcd_moveto(2,0);
    lcd_stringout(clear);
}
