/*************************************************************************************
  Edits by Cushing Anderson and Mike Ladam, June 2023

  1. Removed commented-out blocks such as vibrate()
  2. Corrected spelling of diSplay_timer
  3. Kept what_sound_relay_pin as global, but initialized it in activate_sound() and deactivate_sound
  4. Moved viarable declarations outside of code blocks and put at start of functions
  5. Changed initiation of non-array variables from occuring in their declaration, to explicitly in setup() or function
  6. Moved acd_key_in to the only function that uses it, read_LCD_buttons()
  7. Moved lcd_key(0 to only function using it, loop()
  8. prev_mode, mode and prev_s are unused: deleted
  9.  Renamed boolean 'toggle' to 'toggle53' since it toggles between 5 and 3 minute modes
  10. Put the two lines of my_menu() inline in setup() -- the only place that called it
  11. Moved setup() just above loop()
  12. Changed index_3, index_5, ctdwn_3 and ctdwn_5 from integer variables to manifest constants, which is how they are used.
  13. Changed my_start to counting_down for understandability
  14. Placed entries in both arrays into fixed, five-entry lines to make counting easier
  15. Created time variables to make reading  "Sound_Schedule" easier (Sec, ThirtySec, Min)
  16. Made warning signal consistent throughout (5 seconds before)
  17. Made "Alert" horn (before sequence starts) rapid, short horns to distinguish from start of sequence horn (OBE - no longer any ALERT horns, use MANUAL horn
  18. Shortened delay between sequence start button push and first warning buzzer
  19. added beeps to indicate which sequence was "current" (each subsequent button push, increments to next sequence option)
  20. Nov 2023 - Removed "Alert" horns before both sequences. First beeps are warning before sequence begins.

  Leveraged:  Jose Berengueres 4-8th Feb  2015, Dubai for Sound_Schedule and Sound_Type_Length structure (clever!)
  (They leveraged LCD sample code by Mark Bramwell, July 2010)

  This is an Arduino based Ollie box implmentation used for regatta starts

  Components:
  DF ROBOT LCD PANEL,  RELAY Module, Arduino
  connect the relay of the horn to D11 of LCD shield. This relay drives aircompressor (12VDC battery)
  connect the relay that controls buzzer/beeper to D2.

**************************************************************************************/

#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);           // select the pins used on the LCD panel


// define some values used by the panel and buttons
int what_sound_relay_pin = 0;

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

#define RELAY_HORN    11   // horn relay  
#define RELAY_BEEP   2  // Piezo 
#define STD_DELAY 300

#define SHORT_BEEP_LENGTH 500

#define WARNING_BEEP 0
#define SHORT_HORN 1
#define LONG_HORN 2
#define SUPER_LONG_HORN 3

// Used for Time  (tenths of seconds)
#define HalfSec 5
#define Sec 10
#define ThirtySec 300
#define Min 600



bool toggle53;        // IF we are counting down, are we in a five minute sequence or a 3 minute sequence?
bool counting_down;   // Has a 5- or 3-minute sequence been selected?  Starts as No.
bool sound_on;

unsigned long  len_of_note[] = {500, 400, 800, 1500}; // in ms index value will be Warning_beep=0, Short_horn=1, Long_horn=2, Super_long_horn=3, defined above

long time_of_sequence_start;
long ctdwn;
long sound_start;

unsigned long *sound_schedule;              //formerly called sch variable
int *sound_type_length;                     //formerly called h_or_b variable
int index;

/************************************* THREE MIN SEQ ********************************
  These two arrays establish when (sound_schedule) and how (sound_type_length) to blow the horn/buzzer. Horn type_lengths are identified in variables defined above.
  Its arrayed BACKWARDS. For example: the first entry is the last horn signal (zero seconds from end of countdown), long horn (type "3")
  to indicate "START!"). The last entries, 3 Minutes and 5 Seconds and "0", indicate the very first warning buzzer ("0")in the sequence. 
  THERE ARE NO "ALERT/ATTENTION" horns before a sequence. 5 seconds of warning beepers will sound before each horn signal
   */

unsigned long sound_schedule_3[] =   {
0, 1*Sec, 2*Sec, 3*Sec, 4*Sec,
5*Sec, 10*Sec, 19*Sec, 20*Sec, ThirtySec - 2*Sec, 
ThirtySec - Sec, ThirtySec,  Min, Min + Sec, Min + 2*Sec, 
Min + 3*Sec, Min + 4*Sec, Min + 5*Sec, Min+ThirtySec - 3*Sec, Min+ThirtySec -2*Sec, 
Min+ThirtySec - Sec, Min+ThirtySec , 2*Min - 15, 2 * Min, 2*Min + Sec, 
2*Min + 2*Sec, 2*Min + 3*Sec, 2*Min + 4*Sec, 2*Min + 5*Sec, 3*Min - 2*Sec, 
3*Min - Sec, 3*Min, 3*Min + 1*Sec, 3*Min + 2*Sec, 3*Min + 3*Sec, 
3*Min + 4*Sec, 3*Min + 5*Sec
};

int sound_type_length3[] =  {
  3, 1, 1, 1, 1,
  1, 1, 1, 1, 1,
  1, 1, 2, 0, 0,
  0, 0, 0, 1, 1,
  1, 2, 2, 2, 0,
  0, 0, 0, 0, 2,
  2, 2, 0, 0, 0, 
  0, 0
};

#define INDEX_3 (36)
#define CTDWN_3 (3 * 60 + 6)


/* to shorten sequence for debug, change INDEX size and CTDWN starting seconds ...
and commend out above
#define INDEX_3 (11) //debug
#define CTDWN_3 (66) //debug 
... will start at CTDWN seconds and count to zero
 */


/************************************* FIVE MIN SEQ ********************************
  These two arrays establish when (sound_schedule) and how (sound_type_length) to blow the horn/buzzer. Horn type_lengths are identified in variables defined above.
THERE ARE NO "ALERT/ATTENTION" horns before a sequence. 5 seconds of warning beepers will sound before each horn*/



unsigned long sound_schedule_5[] =   {
0, 1*Sec, 2*Sec, 3*Sec, 4*Sec,  
5*Sec, 1*Min, 1*Min + 1*Sec, 1*Min + 2*Sec, 1*Min + 3*Sec, 
1*Min + 4*Sec, 1*Min + 5*Sec,  4*Min,  4*Min + 1*Sec, 4*Min + 2*Sec, 
4*Min + 3*Sec, 4*Min + 4*Sec, 4*Min + 5*Sec, 5*Min, 5*Min + 1*Sec, 
5*Min + 2*Sec, 5*Min + 3*Sec, 5*Min + 4*Sec, 5*Min + 5*Sec
}
;


int sound_type_length5[] = {
  3, 0, 0, 0, 0,
  0, 2, 0, 0, 0,
  0, 0, 2, 0, 0,
  0, 0, 0, 2, 0,
  0, 0, 0, 0
};

#define INDEX_5 (23)            
#define CTDWN_5 (5 * 60 + 6)



/* to shorten sequence for debug, change INDEX size and CTDWN starting seconds ... 
and comment out above 
#define INDEX_5 (5) //debug
#define CTDWN_5 (15) //debug 
... will start in the at CTDWN seconds and count to zero
*/

int read_LCD_buttons() {              // read the buttons
  int adc_key_in;

  adc_key_in = analogRead(0);       // read the value from the sensor

  // buttons when read are centered at these valies: 0, 144, 329, 504, 741
  // we add approx 50 to those values and check to see if we are close
  // We make this the 1st option for speed reasons since it will be the most likely result

  if (adc_key_in > 1000) return btnNONE;

  // For V1.1 use this threshold
  if (adc_key_in < 50)   return btnRIGHT;
  if (adc_key_in < 250)  return btnUP;
  if (adc_key_in < 450)  return btnDOWN;
  if (adc_key_in < 650)  return btnLEFT;
  if (adc_key_in < 850)  return btnSELECT;

  return btnNONE;                // when all others fail, return this.
}

// utility to print two lines on LCD
void lcd_w(char a[16], char b[16]) {
  lcd.setCursor(0, 0);
  lcd.print("                 ");
  lcd.setCursor(0, 1);
  lcd.print("                 ");
  lcd.setCursor(0, 0);
  lcd.print(a);
  delay(STD_DELAY);
  delay(STD_DELAY);
  lcd.setCursor(0, 1);
  lcd.print(b);
  delay(STD_DELAY);
  delay(STD_DELAY);
}

void activate_sound(int a) {
  // check what instrument to sound

  lcd.setCursor(7, 1);
  if (a == WARNING_BEEP) {  
    what_sound_relay_pin = RELAY_BEEP;
    lcd.print("B");                     //visual indication of which sound is active
  }
  else {
    what_sound_relay_pin = RELAY_HORN;
    lcd.print("H");                     //visual indication of which sound is active
  }

  digitalWrite(what_sound_relay_pin, HIGH);
  sound_start = millis();
  //lcd.print(what_sound_relay_pin);   // debug
}

void de_activate_sound(int a) {
  what_sound_relay_pin = RELAY_HORN;      // assume / contradict
  if (a == WARNING_BEEP) {
    what_sound_relay_pin = RELAY_BEEP;
  }
  digitalWrite(what_sound_relay_pin, LOW);
  lcd.setCursor(7, 1);
  lcd.print("        ");
}

void horn_or_beep(long time_remaining) {
  unsigned long v;

  if (sound_on) {
    if ( ((millis() - sound_start) > len_of_note[sound_type_length[index]] ) ) {
      // Sound has been ON a little longer than the duration called for in the current array slot: turn off
      de_activate_sound(sound_type_length[index]);
      sound_on = false;
      index = index - 1;
    }
  } else {
    v = (sound_schedule[index] * 100);
    if ( time_remaining < v + 1000  ) { 
      activate_sound(sound_type_length[index]);
      sound_on = true;
    //  lcd.print(sound_type_length[index]);           //debug trying to ID which sound should be playing (works)
    }
  }
}

void display_timer(long time_remaining) {
  int ss, m, s_pos;


  if (time_remaining > -1) {
    ss = (time_remaining / 1000) % 60;
    m =  (time_remaining / 1000) / 60;
    s_pos = 3;

    if (ss < 10)
    { s_pos = s_pos + 1;
      lcd.setCursor(3, 1);
      lcd.print("0");
    }

    lcd.setCursor(1, 1);
    lcd.print(m);

    lcd.setCursor(2, 1);
    lcd.print(":");

    lcd.setCursor(s_pos, 1);
    lcd.print(ss);
  } else {
    // Clock has ticked down--announce!
    lcd.setCursor(7, 1);
    lcd.print("START!");
    counting_down= false;
    digitalWrite(RELAY_HORN, LOW);

  }

}

void setup() {
  Serial.begin(9600);
  Serial.println("hello");
  pinMode(RELAY_HORN, OUTPUT);
  pinMode(RELAY_BEEP, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd_w("Ollie-style", "Regatta Timer");
  lcd_w("BY C. Anderson", "& M. Ladam");
  lcd_w("SELECT 5 OR 3 ", "MINUTE SEQUENCE ");

  // Initialize variables:
  toggle53 = true;
  counting_down = false;
  sound_on = false;
}


void loop() {
  int lcd_key;
  long time_from_sequence_start, time_remaining;

  /* In the loop function:
    .  a) IFF the user has previously started the sequence by pressing the LEFT button, we call horn_or_beep() to
    .     check the elapsed time since the button was pressed, and work through the sound array.
    .  b) We check to see if a button is newly-pressed, and if so respond to it.
  */

  if ( counting_down ) {
    // User previously started the timer.  That set time_of_sequence_start. Get time since:

    time_from_sequence_start =  millis() - time_of_sequence_start ; // Time_of_sequence_start is uninitialized!

    time_remaining = ctdwn * 1000 - time_from_sequence_start ;
    horn_or_beep( time_remaining );
    display_timer( time_remaining );
  }


  lcd_key = read_LCD_buttons();   // read the buttons
  delay(50);
  switch (lcd_key) {              // depending on which button was pushed, we perform an action
    case btnLEFT: {               // Activates the selected sequence
        counting_down = ! counting_down;
        if (counting_down) {
          if (toggle53) {
            lcd_w(" ...STARTING... ", "FIVE MINUTE SEQ ");
            ctdwn = CTDWN_5 ;
            sound_schedule = sound_schedule_5;
            sound_type_length = sound_type_length5;
            index = INDEX_5;

          } else {
            lcd_w(" ...STARTING... ", "THREE MINUTE SEQ");
            ctdwn = CTDWN_3;
            sound_schedule = sound_schedule_3;
            sound_type_length = sound_type_length3;
            index = INDEX_3;
          }
          lcd.setCursor(0, 1);
          lcd.print("00:00                        ");
          sound_on = false;
          time_of_sequence_start = millis();
          break;
        } else {
          // stop
          digitalWrite(RELAY_HORN, LOW);
          digitalWrite(RELAY_BEEP, LOW);
          lcd.setCursor(0, 0);
          lcd.print("SEQ. CANCELLED         ");
          counting_down = false;

        }
        delay(400);
        break;
      }

    case btnSELECT: {                // Toggles between the possible sequences
        if (! counting_down) {               // If not counting down, toggle to next sequence, if counting down fall through and do nothing
          toggle53 = !toggle53;
          lcd.setCursor(0, 0);

          if ( toggle53 ) {
            lcd.print("5-Minute Start      ");
            //5 beeps to indicate the 5-minute sequence is selected
            digitalWrite(RELAY_BEEP, HIGH);delay(STD_DELAY/2);digitalWrite(RELAY_BEEP, LOW);
            delay(STD_DELAY/2);
            digitalWrite(RELAY_BEEP, HIGH);delay(STD_DELAY/2);digitalWrite(RELAY_BEEP, LOW);
            delay(STD_DELAY);
            digitalWrite(RELAY_BEEP, HIGH);delay(STD_DELAY/2);digitalWrite(RELAY_BEEP, LOW);
            delay(STD_DELAY/2);
            digitalWrite(RELAY_BEEP, HIGH);delay(STD_DELAY/2);digitalWrite(RELAY_BEEP, LOW);
            delay(STD_DELAY);
            digitalWrite(RELAY_BEEP, HIGH);delay(STD_DELAY/2);digitalWrite(RELAY_BEEP, LOW);
          }
          else {
            lcd.print("3-Minute Start     ");
            //3 beeps to indicate the 3-minute sequence is selected
            digitalWrite(RELAY_BEEP, HIGH);delay(STD_DELAY/2);digitalWrite(RELAY_BEEP, LOW);
            delay(STD_DELAY/2);
            digitalWrite(RELAY_BEEP, HIGH);delay(STD_DELAY/2);digitalWrite(RELAY_BEEP, LOW);
            delay(STD_DELAY);
            digitalWrite(RELAY_BEEP, HIGH);delay(STD_DELAY/2);digitalWrite(RELAY_BEEP, LOW);
          }

          lcd.setCursor(0, 1);
          lcd.print("                        ");

          delay(400);
          break;
        }

      }

    case btnNONE: {
        break;
      }
  }
}
