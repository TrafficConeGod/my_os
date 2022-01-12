#pragma once
#include <cstdint>
#include <cstddef>
#include "function.h"

/**
 * @brief This function doesn't work
 */
void move_csr();

/**
 * @brief Global descriptor table namespace
 */
namespace gdt {
    void main();
};

/**
 * @brief Interrupt descriptor table namespace
 */
namespace idt {
    void main();

    /**
     * @brief Sets an idt gate
     * 
     * @param num The interrupt number
     * @param base The base address
     * @param sel ???
     * @param flags The flags for the interrupt
     */
    void set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
};

/**
 * @brief Interrupt service routine namespace
 */
namespace isr {
    void main();

    /**
     * @brief All captured registers at the point of an interrupt
     */
    struct registers {
        uint32_t gs, fs, es, ds;
        uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
        uint32_t int_no, err_code;
        uint32_t eip, cs, eflags, useresp, ss;
    };

    /**
     * @brief Sets an isr handler
     * 
     * @param interrupt_id The id for the interrupt
     */
    void set_handler(uint32_t interrupt_id, function<void(const registers&)> handler);

    /**
     * @brief Removes an isr handler
     * 
     * @param interrupt_id The id for the interrupt
     */
    void remove_handler(uint32_t interrupt_id);
};

namespace timer {
    void main(uint32_t frequency);
};

namespace keyboard {
    void main();
};

namespace syscall {
    void main();
};