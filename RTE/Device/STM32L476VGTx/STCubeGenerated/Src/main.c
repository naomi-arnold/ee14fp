/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  * oled is 64 x 128
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "test.h"
#include "ssd1306.h"
#include "fonts.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1; 
char grid[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);

void draw_board(char player);
void clear_board(void);

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config();

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_I2C1_Init();

    /* USER CODE BEGIN */
    SSD1306_Init (); // initialize the display 
	SSD1306_GotoXY (0, 0); 
    SSD1306_Clear();
	
	 char currentPlayer = 'x';

   // SSD1306_GotoXY (10,10); // goto 10, 10 
    //SSD1306_Puts ("HELLO", &Font_11x18, 1); // print Hello 
  //  SSD1306_UpdateScreen();
    //SSD1306_GotoXY (10, 30); 
   // SSD1306_Puts ("WORLD :)", &Font_11x18, 1); 
   // SSD1306_UpdateScreen();
		SSD1306_GotoXY (0, 0); 
	//	SSD1306_Puts ("bye", &Font_11x18, 1); // print Hello 
		//SSD1306_UpdateScreen();
		draw_board(currentPlayer);
		SSD1306_UpdateScreen();


   /* // Game logic start

    // Initialize NES controller
    NES_Init();

    // Draw Tic-Tac-Toe grid
    draw_board();

    // Initialize game state
    char grid[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    // 0 | 1 | 2
    // 3 | 4 | 5
    // 6 | 7 | 8
    char currentPlayer = 'X';

    while (1)
    {  
        // Read NES controller input
        uint8_t input = NES_ReadInput();

        // Handle player move
        if (handlePlayerMove(input, grid, currentPlayer)) {
            // Draw updated grid
            draw_board();

            // Check for win condition
            if (checkWin(grid, currentPlayer)) {
                // Handle win condition
                SSD1306_GotoXY (10, 30); 
                if (currentPlayer == 'X') 
                    SSD1306_Puts ("X wins", &Font_11x18, 1); 
                else 
                    SSD1306_Puts ("O wins", &Font_11x18, 1);
                SSD1306_ScrollRight(3, 6);
                break;
            }

            // Switch player
            currentPlayer = (currentPlayer == 'x') ? 'o' : 'x';
        } 
      
    } */

  
}


void draw_board(char player)
{
    // Clear the OLED display
    SSD1306_Clear();
	

    // Draw horizontal lines
    SSD1306_DrawLine(0, 21, 128, 21, 1);
    SSD1306_DrawLine(0, 42, 128, 42, 1);

    // Draw vertical lines
    SSD1306_DrawLine(42, 0, 42, 128, 1);
    SSD1306_DrawLine(84, 0, 84, 128, 1);
	
	
/*	for (uint8_t i = 0; i < 9; i++) {
		uint16_t x = i;
		uint16_t y = 0;
		SSD1306_GotoXY (x, y);
	  SSD1306_Puts (&grid[i], &Font_11x18, 1);
		
	} */
    // first col	
	  SSD1306_GotoXY (15, 0);
	  SSD1306_Puts (&player, &Font_11x18, 1);
	  SSD1306_GotoXY (15, 22);
	  SSD1306_Puts ("x", &Font_11x18, 1);
	  SSD1306_GotoXY (15, 44);
	  SSD1306_Puts ("x", &Font_11x18, 1);
	//second col
	  SSD1306_GotoXY (57, 0);
	  SSD1306_Puts ("o", &Font_11x18, 1);
	  SSD1306_GotoXY (57, 22);
	  SSD1306_Puts ("x", &Font_11x18, 1);
	  SSD1306_GotoXY (57, 44);
	  SSD1306_Puts ("x", &Font_11x18, 1);
	//third col
	  SSD1306_GotoXY (99, 0);
	  SSD1306_Puts ("o", &Font_11x18, 1);
	  SSD1306_GotoXY (99, 22);
	  SSD1306_Puts ("x", &Font_11x18, 1);
	  SSD1306_GotoXY (99, 44);
	  SSD1306_Puts ("x", &Font_11x18, 1);

    SSD1306_UpdateScreen();
}

void clear_board(void)
{
    // Clear the OLED display
    SSD1306_Clear();
    //draw_board();
}

/*
bool handlePlayerMove(uint8_t cell, char *grid, char player)
{

    // Check if the cell is empty
    if (grid[cell] == ' ') {
        grid[cell] = player;
        return true;
    } else {
        return false; // Cell already occupied
    }

}

bool checkWin(char *grid, char player) {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (grid[i * 3] == player && grid[i * 3 + 1] == player && grid[i * 3 + 2] == player)
            return true;
    }

    // Check columns
    for (int i = 0; i < 3; i++) {
        if (grid[i] == player && grid[i + 3] == player && grid[i + 6] == player)
            return true;
    }

    // Check diagonals
    if ((grid[0] == player && grid[4] == player && grid[8] == player) ||
        (grid[2] == player && grid[4] == player && grid[6] == player))
        return true;

    // No win condition found
    return false;
}

 // first col	
	  SSD1306_GotoXY (15, 0);
	  SSD1306_Puts ("o", &Font_11x18, 1);
	  SSD1306_GotoXY (15, 22);
	  SSD1306_Puts ("x", &Font_11x18, 1);
	  SSD1306_GotoXY (15, 44);
	  SSD1306_Puts ("x", &Font_11x18, 1);
	//second col
	  SSD1306_GotoXY (57, 0);
	  SSD1306_Puts ("o", &Font_11x18, 1);
	  SSD1306_GotoXY (57, 22);
	  SSD1306_Puts ("x", &Font_11x18, 1);
	  SSD1306_GotoXY (57, 44);
	  SSD1306_Puts ("x", &Font_11x18, 1);
	//third col
	  SSD1306_GotoXY (99, 0);
	  SSD1306_Puts ("o", &Font_11x18, 1);
	  SSD1306_GotoXY (99, 22);
	  SSD1306_Puts ("x", &Font_11x18, 1);
	  SSD1306_GotoXY (99, 44);
	  SSD1306_Puts ("x", &Font_11x18, 1);
*/



/* DO NOT EDIT BELOW */

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
    */
    if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
    RCC_OscInitStruct.MSIState = RCC_MSI_ON;
    RCC_OscInitStruct.MSICalibrationValue = 0;
    RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
      Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
    hi2c1.Instance = I2C1;
    hi2c1.Init.Timing = 0x00000004;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2 = 0;
    hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init(&hi2c1) != HAL_OK)
    {
        Error_Handler();
    }

    /** Configure Analogue filter
    */
    if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
    {
        Error_Handler();
    }

    /** Configure Digital filter
    */
    if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN I2C1_Init 2 */

    /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void){
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
