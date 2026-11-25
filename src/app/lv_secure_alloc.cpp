// LVGL memory backend (LV_USE_STDLIB_MALLOC == LV_STDLIB_CUSTOM in lv_conf.h).
//
// LVGL's builtin allocator keeps a static pool. Freed blocks there still held
// old label and textarea text (seed words, indexes, passphrase), and
// secure_scrub_free_heap() cannot reach that pool. This backend allocates from
// the ESP heap with a small size header so every block is wiped when it is
// freed or moved by realloc. Freed LVGL memory therefore never holds old text.

#include <lvgl.h>

#if LV_USE_STDLIB_MALLOC == LV_STDLIB_CUSTOM

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <esp_heap_caps.h>

#include "app/secure_mem.h"

namespace {

// 16 bytes keeps the user pointer at the heap's own alignment.
struct alignas(16) block_header {
  size_t size;
};

constexpr size_t kHeader = sizeof(block_header);
constexpr uint32_t kCaps = MALLOC_CAP_8BIT;

block_header *header_of(void *p) {
  return reinterpret_cast<block_header *>(static_cast<uint8_t *>(p) - kHeader);
}

void *user_of(block_header *h) {
  return reinterpret_cast<uint8_t *>(h) + kHeader;
}

void wipe_and_free(block_header *h) {
  secure_wipe(h, kHeader + h->size);
  heap_caps_free(h);
}

}  // namespace

void lv_mem_init(void) {}

void lv_mem_deinit(void) {}

lv_mem_pool_t lv_mem_add_pool(void *mem, size_t bytes) {
  LV_UNUSED(mem);
  LV_UNUSED(bytes);
  return NULL;
}

void lv_mem_remove_pool(lv_mem_pool_t pool) {
  LV_UNUSED(pool);
}

void *lv_malloc_core(size_t size) {
  if (size > SIZE_MAX - kHeader) return NULL;
  auto *h = static_cast<block_header *>(heap_caps_malloc(kHeader + size, kCaps));
  if (h == NULL) return NULL;
  h->size = size;
  return user_of(h);
}

void lv_free_core(void *p) {
  if (p == NULL) return;
  wipe_and_free(header_of(p));
}

// Never realloc in place: the heap could shrink or move the block and leave
// the old bytes behind. Copy to a new block, then wipe and free the old one.
void *lv_realloc_core(void *p, size_t new_size) {
  if (p == NULL) return lv_malloc_core(new_size);
  if (new_size == 0) {
    lv_free_core(p);
    return NULL;
  }
  block_header *old_h = header_of(p);
  void *fresh = lv_malloc_core(new_size);
  if (fresh == NULL) return NULL;  // old block untouched, as realloc requires
  memcpy(fresh, p, old_h->size < new_size ? old_h->size : new_size);
  wipe_and_free(old_h);
  return fresh;
}

void lv_mem_monitor_core(lv_mem_monitor_t *mon_p) {
  if (mon_p == NULL) return;
  multi_heap_info_t info;
  heap_caps_get_info(&info, kCaps);
  mon_p->total_size = info.total_free_bytes + info.total_allocated_bytes;
  mon_p->free_size = info.total_free_bytes;
  mon_p->free_biggest_size = info.largest_free_block;
  mon_p->free_cnt = info.free_blocks;
  mon_p->max_used = info.total_free_bytes + info.total_allocated_bytes - info.minimum_free_bytes;
  mon_p->used_cnt = info.allocated_blocks;
  mon_p->used_pct = mon_p->total_size
      ? static_cast<uint8_t>(100 - (100 * info.total_free_bytes) / mon_p->total_size)
      : 0;
  mon_p->frag_pct = info.total_free_bytes
      ? static_cast<uint8_t>(100 - (100 * info.largest_free_block) / info.total_free_bytes)
      : 0;
}

lv_result_t lv_mem_test_core(void) {
  return heap_caps_check_integrity(kCaps, false) ? LV_RESULT_OK : LV_RESULT_INVALID;
}

#endif  // LV_STDLIB_CUSTOM
