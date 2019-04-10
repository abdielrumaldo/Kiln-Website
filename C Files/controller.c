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

float read_float(modbus_t *ctx, int command);
void read_register(modbus_t *ctx, int command);

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
	 
	float temperature = read_float(ctx, 1);
	float setpoint = read_float(ctx, 2);
	float pid_output =  read_float(ctx, 3);
	printf("Temperature: %.0f \nSetpoint: %.0f\nPID Output: %.0f\n", temperature, setpoint, pid_output );


	modbus_close(ctx);
    modbus_free(ctx);

    if(argc>1){
        printf("Greetings, %s!n",argv[1]);
        return(0);
    }
        
    return 0;
}

// reads float
float read_float(modbus_t *ctx, int command){

    uint16_t tab_reg[16];
    uint16_t* temp = tab_reg;
    float result;
    int rc;
    int address;

    switch (command){

        case 1:
        //READ_TEMPERATURE
            address = 640;
            break;

        case 2:
        //READ_SETPOINT
            address = 544;
            break;

        case 3:
        //READ_CONTROL_SETPOINT
            address = 548;
            break;

        case 4:
        //READ_PID_OUTPUT
            address = 554;
            break;

        default:
        address = 640;
    }

    rc = modbus_read_registers(ctx, address, 4, tab_reg);


    if (rc == -1) {
        fprintf(stderr, "%s\n", modbus_strerror(errno));
        return -1;
    }
    else {
      result = modbus_get_float_dcba(temp);
      return result;
    }
}

//reads register
void read_register(modbus_t *ctx, int command){

    uint16_t tab_reg[64];
    int rc;
    int address;

    switch (command){

        case 1:
        //READ_RUNMODE
            address = 576;
            break;

        case 2:
        //READ_RAMP_SOAK_STATE
            address = 558;
            break;

        case 3:
        //READ_RAMP_SOAK_MODE NON-VOLATILE
            address = 608;
            break;

        case 4:
        //READ_RAMP_SOAK_PROFILE_SELECT
            address = 609;
            break;

        case 5:
        //READ_CURRENT_PROFILE
            address = 610;
            break;

        case 6:
        //READ_CURRENT_SEGMENT
            address = 611;
            break;

        case 7:
        //READ_SEGMENTS_PER_PROFILE
            address = 612;
            break;

        case 8:
        //READ_SOAK_ACTION
            address = 613;
            break;

        case 9:
        //READ_SOAK_LINK DEPRICADED FEATURE
            address = 614;
            break;

        case 10:
        //READ_TRACKING_TYPE
            address = 615;
            break;

        default:
            address = 576;
    }

    rc = modbus_read_registers(ctx, address, 1, tab_reg);

    if (rc == -1) {
    fprintf(stderr, "%s\n", modbus_strerror(errno));
    }
    else {
        printf("%d", rc);
    }
}

