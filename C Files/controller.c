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

int main(int argc, char const *argv[]){
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

	modbus_close(ctx);
    modbus_free(ctx);

    return 0;
}

// reads float
void read_float(modbus_t *ctx, char command[]){

    uint16_t tab_reg[64];
    uint16_t* temp = tab_reg;
    float result;
    int rc;
    int address;

    switch (command){

        case READ_TEMPERATURE:
            address = 640;
            break;

        case READ_SETPOINT:
            address = 544;
            break;

        case READ_CONTROL_SETPOINT:
            address = 548;
            break;

        case READ_PID_OUTPUT:
            address = 554
            break;

        default:
        address = 640;
    }

    rc = modbus_read_registers(ctx, address, 2, tab_reg);

    if (rc == -1) {
        fprintf(stderr, "%s\n", modbus_strerror(errno));
        return -1;
    }
    else {
      result = modbus_get_float_dcba(temp);
      prinf("%f", result);
    }
}

//reads register
void read_register(modbus_t *ctx, char command[]){

    uint16_t tab_reg[64];
    int rc;
    int address;

    switch (command){

        case READ_RUNMODE:
            address = 576;
            break;

        case READ_RAMP_SOAK_STATE:
            address = 558;
            break;

        case READ_RAMP_SOAK_MODE:
            address = 608;
            break;

        case READ_RAMP_SOAK_PROFILE_SELECT:
            address = 609
            break;

        case READ_CURRENT_PROFILE:
            address = 610;
            break;

        case READ_CURRENT_SEGMENT:
            address = 611;
            break;

        case READ_SEGMENTS_PER_PROFILE:
            address = 612:
            break;

        case READ_SOAK_ACTION:
            address = 613;
            break;

        case READ_SOAK_LINK:
            address = 614;
            break;

        case READ_TRACKING_TYPE:
            address = 615;
            break;

        case READ_RAMP_SOAK_STATE:
            address = 628;
            break;

        default:
            address = 576;
    }

    rc = modbus_read_registers(ctx, address, 1, tab_reg);

    if (rc == -1) {
    fprintf(stderr, "%s\n", modbus_strerror(errno));
    return -1;
    }
    else {
        fprint("%d", rc);
    }
}


