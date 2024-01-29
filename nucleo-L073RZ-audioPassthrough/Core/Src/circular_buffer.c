


/* Includes ------------------------------------------------------------------*/
#include "circular_buffer.h"




/**
 * Returns buffer occupation in samples
 */
int32_t circular_buffer_stored_samples(circbuff_t *c) {
	int32_t samples_in_buffer = c->head - c->tail;
	if (samples_in_buffer < 0) {
		samples_in_buffer = c->maxlen + samples_in_buffer; // calculates complementary
	}
	return samples_in_buffer;
}
/**
 * Returns 1 iff the buffer is half full
 */
uint8_t circular_buffer_check_half_full(circbuff_t *c) {
	if(circular_buffer_stored_samples(c) == (c->maxlen > 1)){
		return 1;
	}
	return 0;
}
/**
 * Pushes a sample into a circular buffer
 */
int circular_buffer_push(circbuff_t *c, uint16_t *data) {
	int32_t next = (c->head + 1) % c->maxlen; //next is where head will point to after this write
	if (next == c->tail) {
		return -1; //throw error if buffer is full
	} else {
		c->buffer[c->head] = (uint16_t) *data;  //load data in head position
		c->head = next;                        //update head pointer
		return 0;
	}
}
/**
 * Pops a sample from a circular buffer
 */
int circular_buffer_pop(circbuff_t *c, uint16_t *data) {
	if (c->head == c->tail) { //the buffer is empty
		return -1;
	}
	*data = c->buffer[c->tail];  //read data in tail position
	c->tail = (c->tail + 1) % c->maxlen; //update tail pointer
	return 0;
}

/*
int fir_filtered_pop(circbuff_t *c, uint16_t *coeffs, uint16_t order,
		uint16_t *data) {
	if (circular_buffer_stored_samples(c) < order) { //not enough samples
		return -1;
	}
	int32_t next = (c->tail + 1) % c->maxlen; //next is where tail will point to after this read.
	*data = 0; // FIR accumulator
	for (uint16_t i = 0; i < order; i++) { // update output
		*data += ((c->buffer[(c->tail + i)]) * coeffs[i]) >> 1;
	}
	c->tail = next;              //update tail pointer
	return 0;
}
*/

