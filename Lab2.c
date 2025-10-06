////////////////////////////////////////////////////////////////////////
//** ENGR-2350 Template Project 
//** NAME: Vincent Borello Eric Wing
//** RIN: XXXX
//** TEMPLATE VERSION: v.92 (2025-09-25)
//** This is the base project for several activities and labs throughout
//** the course.  The outline provided below isn't necessarily *required*
//** by a C program; however, this format is required within ENGR-2350
//** to ease debugging/grading by the staff.
////////////////////////////////////////////////////////////////////////

// We'll always add this include statement. This basically takes the
// code contained within the "engr_2350_msp432.h" file and adds it here.
#include "engr2350_mspm0.h"

// Add function prototypes here as needed.


// Add global variables here as needed.


int main() {    //// Main Function ////
  printf("\r\n\n"
           "===========\r\n"
           "Lab 2 Begin\r\n"
           "===========\r\n");
    // Add local variables here as needed.

    // We always call the sysInit function first to set up the 
    // microcontroller for how we are going to use it.
    sysInit();
    GPIOInit();
    // Place initialization code (or run-once) code here
    
    while(1){  
        // Place code that runs continuously in here

    }   
    void GPIOInit() {
    // Initialize Pushbuttons
    GPIO_initDigitalInput(GPIOB, GPIO_PIN2); // Push1

    // Initialize Bumpers
    GPIO_initDigitalInput(GPIOA, GPIO_PIN7 | GPIO_PIN14);                   // BMP1, BMP2
    GPIO_initDigitalInput(GPIOB, GPIO_PIN5 | GPIO_PIN21 | GPIO_PIN23 | GPIO_PIN25); // BMP3–BMP6

    // Initialize BiColor LED
    GPIO_initDigitalOutput(GPIOA, GPIO_PIN12 | GPIO_PIN13); // BiColor LED
}

void TimerInit() {
    timg7cfg.mode = TIMER_MODE_PERIODIC_UP;
    timg7cfg.clksrc = TIMER_CLOCK_BUSCLK;
    timg7cfg.clkdivratio = TIMER_CLOCK_DIVIDE_4;
    timg7cfg.clkprescale = 6;
    timg7cfg.period = 11429;  // ~10ms (100Hz)

    Timers_initTimer(TIMG7, &timg7cfg);

    // Enable zero event interrupt
    Timers_clearInterrupt(TIMG7, TIMER_INTSRC_ZERO);
    Timers_enableInterrupt(TIMG7, TIMER_INTSRC_ZERO);

}
void gameStart(){
    fprint("Button Tesing, press pushbutton to start game.")
    while(1) {
        
        int8_t BMP1 = GPIO_readPins(GPIOA, GPIO_PIN7) != 0;
        int8_t BMP2 = GPIO_readPins(GPIOA, GPIO_PIN14) != 0;
        int8_t BMP3 = GPIO_readPins(GPIOB, GPIO_PIN5) != 0;
        int8_t BMP4 = GPIO_readPins(GPIOB, GPIO_PIN21) != 0;
        int8_t BMP5 = GPIO_readPins(GPIOB, GPIO_PIN23) != 0;
        int8_t BMP6 = GPIO_readPins(GPIOB, GPIO_PIN25) != 0;
        int8_t push1 = GPIO_readPins(GPIOB, GPIO_PIN2) == 0;
        
        if(push1){
            fprint("Start");
            rgamesequence();
        }

        if(BMP1){
            GPIO_clearPins(GPIOB,GPIO_PIN22); 
            GPIO_clearPins(GPIOB,GPIO_PIN26); 
            GPIO_clearPins(GPIOB,GPIO_PIN27); 
            GPIO_setPins(GPIOB,GPIO_PIN26);
            fprint("Pressed 1, RED");
        }
        else if(BMP2){
            GPIO_clearPins(GPIOB,GPIO_PIN22); 
            GPIO_clearPins(GPIOB,GPIO_PIN26); 
            GPIO_clearPins(GPIOB,GPIO_PIN27); 
            GPIO_setPins(GPIOB,GPIO_PIN22);
            fprint("Pressed 1, BLUE");

        }
        else if(BMP3){
            GPIO_clearPins(GPIOB,GPIO_PIN22); 
            GPIO_clearPins(GPIOB,GPIO_PIN26); 
            GPIO_clearPins(GPIOB,GPIO_PIN27); 
            GPIO_setPins(GPIOB,GPIO_PIN27);
            fprint("Pressed 1, GREEN");

        }
        else if(BMP4){
            GPIO_clearPins(GPIOB,GPIO_PIN22); 
            GPIO_clearPins(GPIOB,GPIO_PIN26); 
            GPIO_clearPins(GPIOB,GPIO_PIN27); 
            GPIO_setPins(GPIOB,GPIO_PIN26 | GPIO_PIN27);
            fprint("Pressed 1, YELLOW");

        }
        else if(BMP5){
            GPIO_clearPins(GPIOB,GPIO_PIN22); 
            GPIO_clearPins(GPIOB,GPIO_PIN26); 
            GPIO_clearPins(GPIOB,GPIO_PIN27); 
            GPIO_setPins(GPIOB,GPIO_PIN26 | GPIO_PIN22);
            fprint("Pressed 1, PURPLE");

        }
        else if(BMP6){
            GPIO_clearPins(GPIOB,GPIO_PIN22); 
            GPIO_clearPins(GPIOB,GPIO_PIN26); 
            GPIO_clearPins(GPIOB,GPIO_PIN27); 
            GPIO_setPins(GPIOB,GPIO_PIN22 | GPIO_PIN27);
            fprint("Pressed 1, CYAN");

        }
        while(BMP1 || BMP2 || BMP3 || BMP4 || BMP5 || BMP6 || push1 || push2){
                printf("None pressed... OFF");
        }
    }
    rgamesequence(){
        
    }
}
}   

 //// End Main Function ////  

// Add function declarations here as needed

// Add interrupt functions last so they are easy to find
