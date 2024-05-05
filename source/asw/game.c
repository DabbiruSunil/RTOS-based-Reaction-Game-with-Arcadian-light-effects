/**
* \file <filename>
* \author <author-name>
* \date <date>
*
* \brief <Symbolic File name>
*
* \copyright Copyright ©2016
* Department of electrical engineering and information technology, Hochschule Darmstadt - University of applied sciences (h_da). All Rights Reserved.
* Permission to use, copy, modify, and distribute this software and its documentation for educational, and research purposes in the context of non-commercial
* (unless permitted by h_da) and official h_da projects, is hereby granted for enrolled students of h_da, provided that the above copyright notice,
* this paragraph and the following paragraph appear in all copies, modifications, and distributions.
* Contact Prof.Dr.-Ing. Peter Fromm, peter.fromm@h-da.de, Birkenweg 8 64295 Darmstadt - GERMANY for commercial requests.
*
* \warning This software is a PROTOTYPE version and is not designed or intended for use in production, especially not for safety-critical applications!
* The user represents and warrants that it will NOT use or redistribute the Software for such purposes.
* This prototype is for research purposes only. This software is provided "AS IS," without a warranty of any kind.
*/

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include "seven.h"
#include "game.h"
#include "led.h"

/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/

typedef enum {
    GAME__ISIDLE,
    GAME_ISWAITINGRANDOMTIME,
    GAME_ISWAITINGBUTTON} GAME__State_t;
    

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/

static GAME__State_t GAME__State = GAME__ISIDLE;

/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/

//All state machine action are static functions
//e.g. GAME__StartRandomTimer

/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

RC_t GAME_Play(GAME_event_t ev)
{
    switch (GAME__State)
    {
        case GAME__ISIDLE :
            if (GAME_BUTTON == ev)
            {
                GAME__StartRandomTimer(3000);
                GAME__State = GAME_ISWAITINGRANDOMTIME;
            }
                
            break;
        case GAME_ISWAITINGRANDOMTIME:
            if (GAME_TIMEOUT == ev)
            {
                GAME__ShowRandomPattern();
                GAME__State = GAME_ISWAITINGBUTTON;
            }
            
            break;
            
        case GAME_ISWAITINGBUTTON:
            if (GAME_BUTTON == ev)
            {
                if (GAME__CorrectButton())
                {
                    time = GAME__GetUserTime();
                    GAME__Show("Great job!");
                    GAME__ShowTime(time);
                }
                else
                {
                    GAME__Show("Wrong Button!");
                }
                
                GAME__State = GAME__ISIDLE;
                
                GAME__Show("Next round - please press a button to start");
            }
                    
                    
            
    }
}

GAME__StartRandomTimer(uint16 mintimeInms, uint16 maxtimeInms)
{
    
    //First get a random number
    uint32 randomTime = rand() % (maxtimeInms - mintimeInms) + mintimeInms;
    
    //Then set the timout in our tiner module
    TIME_SetAlarm(randomTime);
    