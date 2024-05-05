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
#include "seven.h"

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

const uint8 SEVEN__pattern[16] = 
{
    63,     // '0'
    6,      // '1'
    91,     // '2'
    
    //and so on
}
    

/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/

/**
 * Will set the selection pin based on the identifier
 **/
static SEVEN__SetSelPin(SEVEN_id_t id);

/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

/**
 * Will initialise and clear the seven segment
 * \return RC_SUCCESS
 */
RC_t SEVEN_Init()
{
    //Maybe more to come in the future...
    SEVEN_Clear(SEVEN_LEFT);
    SEVEN_Clear(SEVEN_RIGHT);
    
    return RC_SUCCESS;
}

/**
 * Will clear the seven segment
 * \param SEVEN_id_t id     : IN, select left or right display
 * \return RC_SUCCESS
 */
RC_t SEVEN_Clear(SEVEN_id_t id);
{
    SEVEN__SetSelPin(id);
    Control_Seven_Write(0);
}
   
/**
 * Will write a single hexadecimal value 0...F to one of the displays 
 * \param SEVEN_id_t id     : IN, select left or right display
 * \param uint8 hexNibble   : IN, range 0...15 (F)
 * \return RC_BAD_PARAM or RC_SUCCESS
 */
RC_t SEVEN_SetSingleDisplay(SEVEN_id_t id, uint8 hexNibble)
{
    SEVEN__SetSelPin(id);
    
    if (hexNibble > 0x0F) return RC_ERROR_BAD_PARAM;
    
    //Solution 1
    switch (hexNibble)
    {
        case 0 : Control_Seven_Write(63); break
        case 1 : Control_Seven_Write(6); break
        //and so on
    }
    
    //Solution 2 - lookup table
    uint8 pattern = SEVEN__pattern[hexNibble);
    Control_Seven_Write(pattern);
}

/**
 * Will set or clear the decimal point
 * \param SEVEN_id_t id     : IN, select left or right display
 * \param uint8 onOff       : IN, range 0...1
 * \return RC_BAD_PARAM or RC_SUCCESS
 */
RC_t SEVEN_SetDP(SEVEN_id_t id, uint8 onOff);

/**
 * Will write a a value as hex value on both displays 
 * \param uint8 value   : IN, range 0...255 (FF)
 * \return RC_SUCCESS
 */
RC_t SEVEN_WriteValue(uint8 value)
{
    uint8 lowNibble = value % 16;
    uint8 highNibble = value / 16;
    
    SEVEN_SetSingleDisplay(SEVEN_LEFT, highNibble);
    SEVEN_SetSingleDisplay(SEVEN_RIGHT, lowNibble);
    
    
}

/**
 * Will set the selection pin based on the identifier
 **/
static SEVEN__SetSelPin(SEVEN_id_t id)
{
    if (SEVEN_LEFT == id)
    {
        PIN_sel_a_Write(1);
    }
    else
    {
        PIN_sel_a_Write(0);
    }
}