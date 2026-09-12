#include <stdio.h>
#include <stdint.h>
#include <windows.h>
#include "libplctag.h"

int main(void) {
    const char *level_attr = "protocol=modbus-tcp&gateway=127.0.0.1:5020&path=1&name=hr0";
    const char *pump_attr  = "protocol=modbus-tcp&gateway=127.0.0.1:5020&path=1&name=co0";

    int32_t level_tag = plc_tag_create(level_attr, 1000);
    int32_t pump_tag  = plc_tag_create(pump_attr, 1000);

    while (1) {
        plc_tag_read(level_tag, 100);
        int level = plc_tag_get_uint16(level_tag, 0);

        int pump_on = (level < 200) ? 1 : (level > 800 ? 0 : -1);
        if (pump_on != -1) {
            plc_tag_set_uint8(pump_tag, 0, pump_on);
            plc_tag_write(pump_tag, 100);
        }

        FILE *f = fopen("www/status.json", "w");
        fprintf(f, "{\"level\": %d}", level);
        fclose(f);

        Sleep(250);
    }
    return 0;
}
