//Create a new RTU context with proper serial parameters (in this example,
//device name /dev/ttyAMA0, baud rate 19200, no parity bit, 8 data bits, 1 stop bit)
//Compile function gcc controller.c -L /usr/local/include/modbus/ -lmodbus
// MAKE SURE YOU'RE USING LIBMODBUS 3.1.4
//  1. float - 4 bytes - 32 bits
//  2. double - 8 bytes - 64 bits
//  3. long double - 10 bytes - 80 bits

#include <modbus/modbus.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

int main(int argc, char const *argv[])
{
	// Versioning
	// printf("Compiled with libmodbus version %s\n", LIBMODBUS_VERSION_STRING);


	// Initilization
    modbus_t *ctx = modbus_new_rtu("/dev/ttyAMA0", 19200, 'O', 8, 1);


	// Need to add this line in before calling modbus_read_registers
    modbus_rtu_set_serial_mode(ctx,MODBUS_RTU_RS232);
	modbus_set_slave(ctx,1);

    if (!ctx) {
        fprintf(stderr, "Failed to create the context: %s\n", modbus_strerror(errno));
        exit(1);
    }
    // Establish Modbus connection
    if (modbus_connect(ctx) == -1) {
        fprintf(stderr, "Unable to connect: %s\n", modbus_strerror(errno));
        modbus_free(ctx);
        exit(1);
	 }

    /*Read Long*/
    uint16_t tab_reg[64];
    int i;
    int rc = modbus_read_registers(ctx, 640, 2, tab_reg);
    uint16_t* temp = tab_reg;
    float result = modbus_get_float_dcba(temp);

    if (rc == -1) {
    fprintf(stderr, "%s\n", modbus_strerror(errno));
    return -1;
}
	printf("%f", result);


	/*Read register
    uint16_t tab_reg[64];
    int i;
    int rc = modbus_read_registers(ctx, 576, 1, tab_reg);

    if (rc == -1) {
    fprintf(stderr, "%s\n", modbus_strerror(errno));
    return -1;
	}

	for (i=0; i < rc; i++) {
    printf("%d",tab_reg[i]);
	}
	*/

	//debugging (prints results of the register)
    //for (i=0; i < rc; i++) {
    //printf("reg[%d]=%d (0x%X)\n", i, tab_reg[i], tab_reg[i]);
    //}



	modbus_close(ctx);
    modbus_free(ctx);

    return 0;
}

