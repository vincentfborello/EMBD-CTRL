////////////////////////////////////////////////////////////////////////
//** ENGR-2350 Template Project 
//** NAME: Vincent Borello , Eric Wing
//** RIN: 662082119
//** TEMPLATE VERSION: v.92 (2025-09-25)
////////////////////////////////////////////////////////////////////////

#include "engr2350_mspm0.h"
#include <stdlib.h>   // For srand, rand
#include <time.h>     // For time
#include <stdint.h>   // For int8_t
#include <stdio.h>    // For printf

// Function prototypes
void GPIOInit(void);
void TimerInit(void);
void gameStart(void);
void rgamesequence(int* sequence, int length);
void shuffleArray(int* array, int size);
void delayMs(int ms);

// Global variables
int arr[6] = {1, 2, 3, 4, 5, 6};
Timers_TimerConfig timg7cfg; 

int main(void) {
    srand(time(NULL));
    shuffleArray(arr, 6); // Randomize the sequence

    sysInit();
    GPIOInit();
    TimerInit();

    gameStart(); // Start the game

    while(1) {
        // Loop forever
    }
}

void GPIOInit(void) {
    // Initialize Pushbuttons
    GPIO_initDigitalInput(GPIOB, GPIO_PIN2); // Push1

    // Initialize Bumpers
    GPIO_initDigitalInput(GPIOA, GPIO_PIN7 | GPIO_PIN14);                   // BMP1, BMP2
    GPIO_initDigitalInput(GPIOB, GPIO_PIN5 | GPIO_PIN21 | GPIO_PIN23 | GPIO_PIN25); // BMP3–BMP6
    GPIO_setInternalResistor(GPIOA, GPIO_PIN7 | GPIO_PIN14,GPIO_PULL_UP);
    GPIO_setInternalResistor(GPIOB, GPIO_PIN5 | GPIO_PIN21 | GPIO_PIN23 | GPIO_PIN25,GPIO_PULL_UP);
    // Initialize BiColor LED (RGB: P22=Blue, P26=Red, P27=Green)
    GPIO_initDigitalOutput(GPIOA, GPIO_PIN12 | GPIO_PIN13); 
    GPIO_initDigitalOutput(GPIOB, GPIO_PIN22 | GPIO_PIN26 | GPIO_PIN27);
}

void TimerInit(void) {
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

void gameStart(void) {
    printf("Button Testing, press pushbutton to start game.\n");

    while(1) {
        int8_t BMP1 = GPIO_readPins(GPIOA, GPIO_PIN7) != 0;
        int8_t BMP2 = GPIO_readPins(GPIOA, GPIO_PIN14) != 0;
        int8_t BMP3 = GPIO_readPins(GPIOB, GPIO_PIN5) != 0;
        int8_t BMP4 = GPIO_readPins(GPIOB, GPIO_PIN21) != 0;
        int8_t BMP5 = GPIO_readPins(GPIOB, GPIO_PIN23) != 0;
        int8_t BMP6 = GPIO_readPins(GPIOB, GPIO_PIN25) != 0;
        int8_t push1 = GPIO_readPins(GPIOB, GPIO_PIN2) == 0;

        if (push1) {
            printf("Start\n");
            rgamesequence(arr, 6);
        }

        if (!BMP1) {
            delay_cycles(320e3);
            GPIO_clearPins(GPIOB, GPIO_PIN22 | GPIO_PIN26 | GPIO_PIN27); 
            GPIO_setPins(GPIOB, GPIO_PIN26); // RED
            printf("Pressed 1, RED\n");
            while(!GPIO_readPins(GPIOA,GPIO_PIN7)){

            }
            delay_cycles(320e3);
        }
        else if (!BMP2) {
            delay_cycles(320e3);
            GPIO_clearPins(GPIOB, GPIO_PIN22 | GPIO_PIN26 | GPIO_PIN27);
            GPIO_setPins(GPIOB, GPIO_PIN22); // BLUE
            printf("Pressed 2, BLUE\n");
            while(!GPIO_readPins(GPIOA,GPIO_PIN14)){
                
            }
            delay_cycles(320e3);
        }
        else if (!BMP3) {
            delay_cycles(320e3);
            GPIO_clearPins(GPIOB, GPIO_PIN22 | GPIO_PIN26 | GPIO_PIN27);
            GPIO_setPins(GPIOB, GPIO_PIN27); // GREEN
            printf("Pressed 3, GREEN\n");
            while(!GPIO_readPins(GPIOB,GPIO_PIN5)){
                
            }
            delay_cycles(320e3);
        }
        else if (!BMP4) {
            delay_cycles(320e3);
            GPIO_clearPins(GPIOB, GPIO_PIN22 | GPIO_PIN26 | GPIO_PIN27);
            GPIO_setPins(GPIOB, GPIO_PIN26 | GPIO_PIN27); // YELLOW
            printf("Pressed 4, YELLOW\n");
            while(!GPIO_readPins(GPIOB,GPIO_PIN21)){
                
            }
            delay_cycles(320e3);
        }
        else if (!BMP5) {
            delay_cycles(320e3);
            GPIO_clearPins(GPIOB, GPIO_PIN22 | GPIO_PIN26 | GPIO_PIN27);
            GPIO_setPins(GPIOB, GPIO_PIN26 | GPIO_PIN22); // PURPLE
            printf("Pressed 5, PURPLE\n");
            while(!GPIO_readPins(GPIOB,GPIO_PIN23)){
                
            }
            delay_cycles(320e3);
        }
        else if (!BMP6) {
            delay_cycles(320e3);
            GPIO_clearPins(GPIOB, GPIO_PIN22 | GPIO_PIN26 | GPIO_PIN27);
            GPIO_setPins(GPIOB, GPIO_PIN22 | GPIO_PIN27); // CYAN
            printf("Pressed 6, CYAN\n");
            while(!GPIO_readPins(GPIOB,GPIO_PIN25)){
                
            }
            delay_cycles(320e3);
        }

        // Wait until all buttons are released
        if (BMP1 || BMP2 || BMP3 || BMP4 || BMP5 || BMP6 || push1) {
            BMP1 = GPIO_readPins(GPIOA, GPIO_PIN7) != 0;
            BMP2 = GPIO_readPins(GPIOA, GPIO_PIN14) != 0;
            BMP3 = GPIO_readPins(GPIOB, GPIO_PIN5) != 0;
            BMP4 = GPIO_readPins(GPIOB, GPIO_PIN21) != 0;
            BMP5 = GPIO_readPins(GPIOB, GPIO_PIN23) != 0;
            BMP6 = GPIO_readPins(GPIOB, GPIO_PIN25) != 0;
            push1 = GPIO_readPins(GPIOB, GPIO_PIN2) == 0;
        }

        
    }
}

void rgamesequence(int* sequence, int length) {
    for (int i = 0; i < length; i++) {
        GPIO_clearPins(GPIOB, GPIO_PIN22 | GPIO_PIN26 | GPIO_PIN27);

        int value = sequence[i];

        if (value == 1) {
            GPIO_setPins(GPIOB, GPIO_PIN26); // RED
            printf("RED\n");
        }
        else if (value == 2) {
            GPIO_setPins(GPIOB, GPIO_PIN22); // BLUE
            printf("BLUE\n");
        }
        else if (value == 3) {
            GPIO_setPins(GPIOB, GPIO_PIN27); // GREEN
            printf("GREEN\n");
        }
        else if (value == 4) {
            GPIO_setPins(GPIOB, GPIO_PIN26 | GPIO_PIN27); // YELLOW
            printf("YELLOW\n");
        }
        else if (value == 5) {
            GPIO_setPins(GPIOB, GPIO_PIN26 | GPIO_PIN22); // PURPLE
            printf("PURPLE\n");
        }
        else if (value == 6) {
            GPIO_setPins(GPIOB, GPIO_PIN22 | GPIO_PIN27); // CYAN
            printf("CYAN\n");
        }

        delayMs(500);
        GPIO_clearPins(GPIOB, GPIO_PIN22 | GPIO_PIN26 | GPIO_PIN27);
        delayMs(100);
    }
}

void shuffleArray(int* array, int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

// Rough delay function — use SDK timer-based delay if available
void delayMs(int ms) {
    for (volatile int i = 0; i < ms * 1000; i++) {
        __asm("NOP");
    }
}
