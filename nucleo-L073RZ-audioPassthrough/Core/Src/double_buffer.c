
/* Includes ------------------------------------------------------------------*/
#include "double_buffer.h"

/* Methods ------------------------------------------------------------------*/

/**
 * Pops a sample from an adc double buffer
 * Returns 0  if the sample has been pop successfully
 * Returns 1  if the buffer is empty
 * Returns -1 if the adc tries to write but the buffer hasn't been emptied (buffer overrun)
 */
int32_t adc_double_buffer_pop(doublebuff_t *d, uint16_t *data) {

	if (d->first_half_ready) { // interrupt flag signaling first half buffer is ready
		if (d->next_pos_to_process != 0) { // checks buffer overrun
			return -1; // buffer overrun
		}
		d->first_half_ready = 0; //resets flag
		*data = d->buffer[d->next_pos_to_process]; // reads data
		d->next_pos_to_process++;
		return 0;
	}

	if (d->second_half_ready) { // interrupt flag signaling first half buffer is ready
		if (d->next_pos_to_process != d->maxlen / 2) { // checks buffer overrun
			return -1; // buffer overrun
		}
		d->second_half_ready = 0; //resets flag
		d->buffer[d->next_pos_to_process] = *data; // reads data
		d->next_pos_to_process++;
		return 0;
	}

	// case of d->first_half_ready == 0 and d->second_half_ready == 0:

	if (d->next_pos_to_process == 0
			|| d->next_pos_to_process == d->maxlen / 2) {
		return 1; // buffer empty. wait until next flag is raised
	}

	*data = d->buffer[d->next_pos_to_process]; // reads data
	d->next_pos_to_process++; // increment next_pos_to_process
	if (d->next_pos_to_process == d->maxlen) {
		d->next_pos_to_process = 0;
	}
	return 0;

}

/**
 * Pushes a sample into a dac double buffer
 * Returns 0  if the sample has been pushed successfully
 * Returns 1  if the buffer is full
 * Returns -1 if the dac tries to read but the buffer is not full (buffer underrun)
 */
int32_t dac_double_buffer_push(doublebuff_t *d, uint16_t *data) {

	if (d->first_half_ready) { // interrupt flag signaling first half buffer is ready
		if (d->next_pos_to_process != 0) { // checks buffer underrun
			return -1; // buffer underrun
		}
		d->first_half_ready = 0; //resets flag
		d->buffer[d->next_pos_to_process] = *data; // stores data
		d->next_pos_to_process++;
		return 0;
	}

	if (d->second_half_ready) { // interrupt flag signaling first half buffer is ready
		if (d->next_pos_to_process != d->maxlen / 2) { // checks buffer underrun
			return -1; // buffer underrun
		}
		d->second_half_ready = 0; //resets flag
		d->buffer[d->next_pos_to_process] = *data; // stores data
		d->next_pos_to_process++;
		return 0;
	}

	// case of d->first_half_ready == 0 and d->second_half_ready == 0:

	if (d->next_pos_to_process == 0
			|| d->next_pos_to_process == d->maxlen / 2) {
		return 1; // buffer full. wait until next flag is raised
	}

	d->buffer[d->next_pos_to_process] = *data; // stores data
	d->next_pos_to_process++; // increment next_pos_to_process
	if (d->next_pos_to_process == d->maxlen) {
		d->next_pos_to_process = 0;
	}
	return 0;
}

