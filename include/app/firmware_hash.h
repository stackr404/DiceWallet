#pragma once

#include <stdbool.h>
#include <stdint.h>

// SHA-256 of the running app image, excluding the 32-byte trailer.
// This is the value esp_partition_get_sha256() returns and the value
// scripts/firmware_hash.py prints for firmware.bin.
bool firmware_partition_sha256(uint8_t out[32]);

// 64 hex chars and a NUL. out must hold 65 bytes.
void firmware_hash_hex(char out[65]);