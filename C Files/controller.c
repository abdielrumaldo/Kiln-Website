//Create a new RTU context with proper serial parameters (in this example,
//device name /dev/ttyAMA0, baud rate 19200, no parity bit, 8 data bits, 1 stop bit)
//Compile function gcc controller.c -L /usr/local/include/modbus/ -lmodbus

#include <modbus/modbus.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char const *argv[])
{

    modbus_t *ctx = modbus_new_rtu("/dev/ttyAMA0", 19200, 'N', 8, 1);

    if (!ctx) {
        fprintf(stderr, "Failed to create the context: %s\n", modbus_strerror(errno));
        exit(1);
    }

    if (modbus_connect(ctx) == -1) {
        fprintf(stderr, "Unable to connect: %s\n", modbus_strerror(errno));
        modbus_free(ctx);
        exit(1);
    }
    return 0;
}

