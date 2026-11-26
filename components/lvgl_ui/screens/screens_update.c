#include "screens_update.h"
#include "lvgl.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "entrada.h"

#define UPDATE_QUEUE_DEPTH 16

static const char *TAG = "screens_update";

typedef struct {
    ui_update_cmd_t cmd;
    void           *data;
} ui_cmd_msg_t;

static QueueHandle_t s_queue = NULL;

/* ------------------------------------------------------------------ */
/* Handler table — one static function per ui_update_cmd_t value.
 * Add new handlers here and register them in s_handlers[].           */
/* ------------------------------------------------------------------ */

typedef void (*handler_fn_t)(void *data);

/* Ya estamos dentro de LVGL: ahora si se puede apretar el boton de la pantalla */
static void al_apretar_boton_fisico(void *data)
{
    (void)data;
    entrada_apretar();
}

static const handler_fn_t s_handlers[UI_UPDATE_MAX] = {
    [UI_UPDATE_BOTON_FISICO] = al_apretar_boton_fisico,
};

/* ------------------------------------------------------------------ */

void ui_update_init(void)
{
    s_queue = xQueueCreate(UPDATE_QUEUE_DEPTH, sizeof(ui_cmd_msg_t));
    ESP_ERROR_CHECK(s_queue ? ESP_OK : ESP_FAIL);
}

void ui_update_cmd(ui_update_cmd_t cmd, void *data)
{
    if (!s_queue) return;
    ui_cmd_msg_t msg = { .cmd = cmd, .data = data };
    if (xQueueSend(s_queue, &msg, 0) != pdTRUE) {
        ESP_LOGW(TAG, "queue full, dropping cmd %d", (int)cmd);
    }
}

void ui_update_screens(void)
{
    if (!s_queue) return;
    ui_cmd_msg_t msg;
    while (xQueueReceive(s_queue, &msg, 0) == pdTRUE) {
        if (msg.cmd < UI_UPDATE_MAX && s_handlers[msg.cmd]) {
            s_handlers[msg.cmd](msg.data);
        }
    }
}
