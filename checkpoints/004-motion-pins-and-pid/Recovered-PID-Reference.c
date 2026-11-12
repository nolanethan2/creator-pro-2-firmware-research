/* Analytical reference for finite, ordinary-range inputs only.
 * Reconstructed from 0x08015C10; NOT original or flashable source.
 * 128 deterministic samples were compared with the original instructions.
 * NaN/Inf, overflow, scheduling, and hardware behavior are outside this model.
 */
#include <stdint.h>
typedef struct {
    float kp, ki, kd, history[4], delta_sum;
    uint8_t index;
    float last_error, integral;
    int32_t target, output;
} PID_Reference; /* Logical fields, not a binary layout declaration. */

int32_t pid_reference(PID_Reference *p, float measured) {
    float error = (float)p->target - measured;
    p->integral += error;
    if (p->integral > 256.0f) p->integral = 256.0f;
    else if (p->integral < -256.0f) p->integral = -256.0f;
    float delta = error - p->last_error;
    p->delta_sum -= p->history[p->index];
    p->history[p->index] = delta;
    p->delta_sum += delta;
    p->index = (p->index + 1) % 4;
    p->last_error = error;
    float weighted = (p->kp * error + p->ki * p->integral) + p->kd * p->delta_sum;
    /* Conversion truncates BEFORE doubling. Caller later clamps to 0..255. */
    p->output = (int32_t)weighted * 2;
    return p->output;
}
