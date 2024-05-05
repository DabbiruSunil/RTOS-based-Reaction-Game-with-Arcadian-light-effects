/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "button.h"
#include "game.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        
        //We translate various inputs from user and system into a logical event
        
        BUTTON_id_t button = BUTTON_NONE;
        RC_t error = BUTTON_Get(&button);
        
        GAME_event_t ev = GAME_NOEVENT;
        
        if (BUTTON_NONE != button)
        {
            ev =   GAME_BUTTON;
        }
        else if (TIMER_CheckTimeout())
        {
            ev = GAME_TIMEOUT;
        }
            
        //Event is given to the game
        if (GAME_NOEVENT != ev)
        {
            GAME_Play(ev); 
        }
        
    }
}

CY_ISR(isr_button)
{
    //Will be called by the physical button
    //Attention: We might lose data due to a race condition
    if (Pin_Button_1_Read() == 1) BUTTON_Set(BUTTON_1);
    if (Pin_Button_2_Read() == 1) BUTTON_Set(BUTTON_2);
    if (Pin_Button_3_Read() == 1) BUTTON_Set(BUTTON_3);
    if (Pin_Button_4_Read() == 1) BUTTON_Set(BUTTON_4);
    
}

CY_ISR(isr_uart_rx)
{
    //Todo some error flags must be checked
    uint8 data = UART_LOG_GetByte();
    
    BUTTON_SetFromUart(data);
   
}
/* [] END OF FILE */
