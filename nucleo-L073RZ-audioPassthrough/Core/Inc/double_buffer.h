

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DOUBLE_BUFF_H
#define __DOUBLE_BUFF_H
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"


/* Exported types ------------------------------------------------------------*/

typedef struct { // double buffer data structure
    uint16_t * const buffer; // constant pointer to a variable memory space
    uint8_t first_half_ready;  // 1 == yes, 0 == no
    uint8_t second_half_ready; // 1 == yes, 0 == no
    uint32_t next_pos_to_process;
    const uint32_t maxlen;
} doublebuff_t;



int32_t adc_double_buffer_pop(doublebuff_t *d, uint16_t *data);
int32_t dac_double_buffer_push(doublebuff_t *d, uint16_t *data);
