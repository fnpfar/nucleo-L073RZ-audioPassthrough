

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CIRC_BUFF_H
#define __CIRC_BUFF_H
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"


/* Exported types ------------------------------------------------------------*/
typedef struct { // circular buffer data structure
    uint16_t * const buffer; // constant pointer to a variable memory space
    uint32_t head;
    int32_t tail;
    const uint32_t maxlen;
} circbuff_t;



int32_t circular_buffer_stored_samples(circbuff_t *c);
uint8_t circular_buffer_check_half_full(circbuff_t *c);
int circular_buffer_push(circbuff_t *c, uint16_t *data);
int circular_buffer_pop(circbuff_t *c, uint16_t *data);
