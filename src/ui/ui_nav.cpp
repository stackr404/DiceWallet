#include <string.h>
#include <esp_heap_caps.h>
#include <esp_memory_utils.h>
#include "ui/ui_nav.h"
#include "app/secure_mem.h"

static void wipe_ram_text(char *text)
{
  if (text == nullptr)
    return;
  if (!esp_ptr_internal(text) && !esp_ptr_external_ram(text))
    return;
  secure_wipe(text, strlen(text));
}

static void wipe_obj_text(lv_obj_t *obj)
{
  if (obj == nullptr)
    return;
  if (lv_obj_check_type(obj, &lv_label_class))
  {
    wipe_ram_text(lv_label_get_text(obj));
  }
  else if (lv_obj_check_type(obj, &lv_textarea_class))
  {
    wipe_ram_text(const_cast<char *>(lv_textarea_get_text(obj)));
  }
  const uint32_t count = lv_obj_get_child_count(obj);
  for (uint32_t i = 0; i < count; ++i)
    wipe_obj_text(lv_obj_get_child(obj, i));
}

void ui_wipe_screen_text(lv_obj_t *screen)
{
  wipe_obj_text(screen);
}

void ui_screen_replace(lv_obj_t *next)
{
  lv_obj_t *previous = lv_screen_active();
  lv_screen_load(next);
  if (previous != nullptr && previous != next)
  {
    ui_wipe_screen_text(previous);
    lv_obj_delete(previous);
  }
}