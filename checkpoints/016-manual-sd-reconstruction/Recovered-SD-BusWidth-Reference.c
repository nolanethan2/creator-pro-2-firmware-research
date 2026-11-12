/* Read-only analysis reference, not firmware or a complete driver.
 * Reconstructed from 0x08002EE8 (boot) and 0x08018A54 (application).
 * Ghidra fails to structure these two functions. Original instructions passed
 * 18 offline cases with all card/device interfaces intercepted.
 * Hook contracts preserve observed return values, not HAL error-bit definitions.
 */
#include <stdint.h>
typedef struct {
    uint32_t argument, command, response, wait, command_path_enable;
} RecoveredSDCommand;
typedef struct {
    uint32_t (*read_response)(void);
    uint32_t (*read_scr)(uint16_t rca, uint32_t scr[2]);
    void (*send_command)(const RecoveredSDCommand *command);
    uint32_t (*check_response)(uint32_t command);
} RecoveredSDInterfaces;

uint32_t recovered_sd_set_bus_width(const RecoveredSDInterfaces *io,
                                    uint16_t rca, uint32_t wide_selector)
{
    uint32_t scr[2] = {0, 0};
    if (io->read_response() & 0x02000000u) return 14;
    uint32_t error = io->read_scr(rca, scr);
    if (error) return error;
    uint32_t required = wide_selector == 1 ? 0x00040000u : 0x00010000u;
    if (!(scr[1] & required)) return 37;
    RecoveredSDCommand command = {
        (uint32_t)rca << 16, 55, 0x40, 0, 0x400
    };
    io->send_command(&command);
    error = io->check_response(55);
    if (error) return error;
    command.argument = wide_selector == 1 ? 2 : 0;
    command.command = 6;
    io->send_command(&command);
    return io->check_response(6);
}
