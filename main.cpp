#include "mbed.h"

// Declare variables to track button presses
volatile uint32_t buttonPressCount = 0;

// Prototype for GPIO Initialization
void GPIO_Init(void);

int main(void) {
    // Initialize the HAL Library
    HAL_Init();

    // Initialize GPIO
    GPIO_Init();

    while (1) {
        // Check if button PC_13 is pressed
        if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET) { // Assuming the button is active low
            // Debouncing delay
            HAL_Delay(200); // Simple debouncing
            
            // Check if button is still pressed
            if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET) {
                // Increment the count of button presses
                buttonPressCount++;
                
                // Print the count of button presses
                printf("Button pressed %lu times\n", buttonPressCount);
            }
        }
    }
}

void GPIO_Init(void) {
    // GPIO Init structure
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Enable the GPIO Clock for GPIOC
    __HAL_RCC_GPIOC_CLK_ENABLE();

    // Configure GPIO pin : PC_13 
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL; // Adjust pull type according to your setup
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

// If using retargeting of printf to USART or another method, define it here