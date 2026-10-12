#pragma once

#include <stddef.h>

// Volatile wipe. The compiler is not allowed to delete this.
void secure_wipe(void *ptr, size_t len);

// Overwrite free heap blocks so freed label text and String copies do not remain.
void secure_scrub_free_heap(void);

// Overwrite the calling task's recently abandoned stack frames.
void secure_scrub_abandoned_stack(void);

// Zero every known secret holder: rolls, word indexes, passphrase, import state.
// Does not delete widgets. Call before leaving a secret screen.
void device_wipe_secrets(void);

// After the secret screen has been deleted: scrub freed heap, stack, framebuffer, panel GRAM.
void device_scrub_residue(void);
