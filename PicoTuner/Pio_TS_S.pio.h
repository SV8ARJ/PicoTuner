// -------------------------------------------------- //
// This file is autogenerated by pioasm; do not edit! //
// -------------------------------------------------- //

#pragma once

#if !PICO_NO_HARDWARE
#include "hardware/pio.h"
#endif



#pragma once

#if !PICO_NO_HARDWARE
#include "hardware/pio.h"
#endif

// -------- //
// Pio_TS_S //
// -------- //

#define Pio_TS_S_wrap_target 0
#define Pio_TS_S_wrap 7

static const uint16_t Pio_TS_S_program_instructions[] = {
            //     .wrap_target
    0x20a2, //  0: wait   1 pin, 2                   
    0x2022, //  1: wait   0 pin, 2                   
    0x20a2, //  2: wait   1 pin, 2                   
    0x20a1, //  3: wait   1 pin, 1                   
    0x4001, //  4: in     pins, 1                    
    0x2021, //  5: wait   0 pin, 1                   
    0x00c3, //  6: jmp    pin, 3                     
    0x0002, //  7: jmp    2                          
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program Pio_TS_S_program = {
    .instructions = Pio_TS_S_program_instructions,
    .length = 8,
    .origin = -1,
};

static inline pio_sm_config Pio_TS_S_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + Pio_TS_S_wrap_target, offset + Pio_TS_S_wrap);
    return c;
}

static inline void  Pio_TS_S_init(PIO pio, uint sm, uint offset, uint pin) 
{
    // Define a structure 'c' that contains the default configuration
    pio_sm_config c = Pio_TS_S_program_get_default_config(offset);
    // Map the state machine's 'IN' pin group to the starting pin for that group.
    sm_config_set_in_pins(&c, pin);
    //map the p[in used by the jmp instruction. (only one pin allowed.)
    sm_config_set_jmp_pin(&c, pin+2); // pin+2 is the TSvalid pin
    // Set the pin directions to input at the PIO
    pio_sm_set_consecutive_pindirs(pio, sm, pin, 3, false);
	  // Configure the IN shifts to left, autopush after 32 bits
    sm_config_set_in_shift(&c, false, true, 32);
    // Set the pin's GPIO function (connect PIO to the pad)	Need to repeat this (with a loop) for every pin used.
    for(int p=0;p<3;p++) 
    {
        pio_gpio_init(pio, pin+p);
    }
    // We only receive, so disable the TX FIFO to make the RX FIFO deeper.
    sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_RX);
    // Load our configuration to the state machine
	  pio_sm_init(pio, sm, offset, &c);
    // Set the state machine running	
    pio_sm_set_enabled(pio, sm, true);
}

#endif

