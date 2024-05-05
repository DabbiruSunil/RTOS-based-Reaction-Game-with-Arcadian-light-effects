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
#include "project.h"
#include "button.h"
/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/

static volatile BUTTON_id_t BUTTON_state = BUTTON_NONE;

/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

    /**
     * Will initialise the UART port for smulation
     * \return RC_SUCCESS
     */
    RC_t BUTTON_Init()
    {
        UART_LOG_Start();   
    }
    
    /**
     * Will return the id of the button which was pressed last
     * It will also clear the button state
     * \param BUTTON_id_t * const id    : OUT, will return the identifier of the last button pressed or BUTTON_NONE
     * \return RC_SUCCESS
     */
    RC_t BUTTON_Get(BUTTON_id_t * const id)
    {
        *id = BUTTON_state;
        
        BUTTON_state = BUTTON_NONE;
        
        return RC_SUCCESS;
    }
    
    /**
     * Will set our button object
     * Will be called from the "real" Pin ISR
     * \param BUTTON_id_t id        : IN, The button which was detetected
     * \return RC_ERROR_BADPARAM or RC_SUCCESS
     */
    RC_t BUTTON_Set(BUTTON_id_t id)
    {
        uint32 idAsInteger = (uint32)id;
        if (idAsInteger > (uint32)BUTTON_4) return RC_ERROR_BAD_PARAM;
        
        BUTTON_state = id;
        
        return RC_SUCCESS;
    }
        
    
    /**
     * Will set our button object
     * Will be called from the simulated UART ISR
     * \param uint8 uartdata        : IN, the character representing the button
     * \return RC_ERROR_BADPARAM or RC_SUCCESS
     */    
    RC_t BUTTON_SetFromUart(uint8 uartdata)
    {
        if (uartdata < '1' || uartdata > '4') return RC_ERROR_BAD_PARAM;
        
        return BUTTON_Set(uartdata - '0');
    }
