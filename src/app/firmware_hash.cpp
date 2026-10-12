#include "app/firmware_hash.h"

#include <esp_ota_ops.h>
#include <esp_partition.h>
#include <stdio.h>

bool firmware_partition_sha256(uint8_t out[32]) {
  if (out == nullptr) return false;
  const esp_partition_t *running = esp_ota_get_running_partition();
  if (running == nullptr || esp_partition_get_sha256(running, out) != ESP_OK) {
    for (int i = 0; i < 32; i++) out[i] = 0;
    return false;
  }
  return true;
}

void firmware_hash_hex(char out[65]) {
  uint8_t hash[32];
  const bool ok = firmware_partition_sha256(hash);
  for (int i = 0; i < 32; i++) {
    snprintf(out + (i * 2), 3, "%02x", ok ? hash[i] : 0);
  }
  out[64] = '\0';
}