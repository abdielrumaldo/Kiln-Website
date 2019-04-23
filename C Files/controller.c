//Create a new RTU context with proper serial parameters (in this example,
//device name /dev/ttyAMA0, baud rate 19200, no parity bit, 8 data bits, 1 stop bit)
//Compile function gcc controller.c -L /usr/local/include/modbus/ -lmodbus
// MAKE SURE YOU'RE USING LIBMODBUS 3.1.4
//  1. float - 4 bytes - 32 bits
//  2. double - 8 bytes - 64 bits
//  3. long double - 10 bytes - 80 bits


/*
 * READ THIS FOR USAGE
 * FORMAT: CONTROL.C [INT] [INT] [COMMAND]
 * 
 * COMMANDS
 * 
 * CONTROL.C 1[READ] 2[FLOAT] [1-4]
 * --------------------------
 * 1 - READ_TEMPERATURE
 * 2 - READ_SETPOINT_1
 * 3 - READ_CONTROL_SETPOINT
 * 4 - READ_PID_OUTPUT
 * 
 * CONTROL.C 1[READ] 1[REGISTER] [1-11]
 * ------------------------------
 * 
 * 1 - READ_RUNMODE
 * 2 - READ_RAMP_SOAK_STATE
 * 3 - READ_RAMP_SOAK_MODE NON-VOLATILE
 * 4 - READ_RAMP_SOAK_PROFILE_SELECT
 * 5 - READ_CURRENT_PROFILE
 * 6 - READ_CURRENT_SEGMENT
 * 7 - READ_SEGMENTS_PER_PROFILE
 * 8 - READ_SOAK_ACTION
 * 9 - READ_SOAK_LINK
 * 10 - READ_TRACKING_TYPE
 * 11 - READ_RAMP_SOAK_STATE
 * 
 * CONTROL.C 2[WRITE] 2[FLOAT] [1-2] [value]
 * ---------------------------
 * 
 * 1 - WRITE_SETPOINT_1
 * 2 - WRITE_CONTROL_SETPOINT
 * 
 * CONTROL.C 2[WRITE] 1[REGISTER] [1-5] [value]
 * ------------------------------
 * 
 * 1 - WRITE_RUNMODE
 * 2 - WRITE_RAMP_SOAK_PROFILE_SELECT
 * 3 - WRITE_CURRENT_PROFILE
 * 4 - WRITE_CURRENT_SEGMENT
 * 5 - WRITE_SEGMENTS_PER_PROFILE
 * 
 * 
 * */

#include <modbus/modbus.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

float read_float(modbus_t *ctx, int command);
float read_register(modbus_t *ctx, int command);
void write_register(modbus_t *ctx, int command, float value);
void write_float(modbus_t *ctx, int command, float value);

int main(int argc, char *argv[]){
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
	 
	 /*float setpoint = read_float(ctx, 2);
	 float pid_output = read_float(ctx, 3);
	 
	 printf("Setpoint: %.0f\nControl Setpoint: %.0f\n\n",setpoint, pid_output );
	 
	 write_register(ctx, 1, 4);
	 float temp = 300.0;
	 write_float(ctx, 2, temp);
	 write_register(ctx, 1, 6);
	 
	 setpoint = read_float(ctx, 2);
	 pid_output = read_float(ctx, 3);
	 
	 printf("Setpoint: %.0f\nControl Setpoint: %.0f\n",setpoint, pid_output );
	*/
	
	//handling a read
	if (argc == 4){
	int command = atof(argv[1]);
	int type = atof(argv[2]);
	int address = atof(argv[3]);
	
	//handle reading float
	if ((command == 1) && (type == 2)){
		
		float value;
		value = read_float(ctx, address);
		printf("%.0f", value);
	}
	
	//handle reading register
	if ((command == 1) && (type == 1)){
		
		float value;
		value = read_register(ctx, address);
		printf("%.0f", value);
	}
	
	//printf("Your command was: %i", command);
	
	
	}else 
	//handle writting float
	if (argc == 5){
	int command = atof(argv[1]);
	int type = atof(argv[2]);
	int address = atof(argv[3]);
	int value = atof(argv[4]);
	
	//handle writing float
	if ((command == 2) && (type == 2)){
		
		float final_value = (float)value;
		write_float(ctx, address, final_value);
	}
	
	//handle writing register
	if ((command == 2) && (type == 1)){
		
		write_register(ctx, address, value);
	}
	
	} else return -1;
	
	modbus_close(ctx);
    modbus_free(ctx);

    return 0;
}

// reads float
float read_float(modbus_t *ctx, int command){

    uint16_t tab_reg[16];
    float result;
    int rc;
    int address;

    switch (command){

        case 1:
        //READ_TEMPERATURE
            address = 640;
            break;

        case 2:
        //READ_SETPOINT_1
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

    rc = modbus_read_registers(ctx, address, 2, tab_reg);


    if (rc == -1) {
        fprintf(stderr, "%s\n", modbus_strerror(errno));
        return -1;
    }
    else {
      result = modbus_get_float_dcba(tab_reg);
      return result;
    }
}

//reads register
float read_register(modbus_t *ctx, int command){

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
        //READ_SOAK_LINK
            address = 614;
            break;

        case 10:
        //READ_TRACKING_TYPE
            address = 615;
            break;

        case 11:
        //READ_RAMP_SOAK_STATE
            address = 628;
            break;

        default:
            address = 576;
    }

    rc = modbus_read_registers(ctx, address, 1, tab_reg);

    if (rc == -1) {
    fprintf(stderr, "%s\n", modbus_strerror(errno));
    }
    else {
        return tab_reg[0];
    }
}

//write float
void write_float(modbus_t *ctx, int command, float value){

    uint16_t number[16];
    modbus_set_float_dcba(value, number);
    int rc;
    int address;

    switch (command){
        case 1:
        //WRITE_SETPOINT 1
            address = 544;
            break;

        case 2:
        //WRITE_CONTROL_SETPOINT
            address = 548;
            break;


        default:
            address = 544;
    }

    rc = modbus_write_registers(ctx, address, 2, number);
	number[0] = 0;
	number[1] = 0;
    if (rc == -1) {
    fprintf(stderr, "%s\n", modbus_strerror(errno));
    }
    else {
        printf("Returned %i, location: %i, value: %f \n", rc, address, value);
    }
}

//write register
void write_register(modbus_t *ctx, int command, float value){

    int rc;
    int address;

    switch (command){

        case 1:
        //WRITE_RUNMODE
            address = 576;
            break;

        case 2:
        //WRITE_RAMP_SOAK_PROFILE_SELECT
            address = 609;
            break;

        case 3:
        //WRITE_CURRENT_PROFILE
            address = 610;
            break;

        case 4:
        //WRITE_CURRENT_SEGMENT
            address = 611;
            break;

        case 5:
        //WRITE_SEGMENTS_PER_PROFILE
            address = 612;
            break;

        default:
            address = 544;
    }

    rc = modbus_write_register(ctx, address, value);

    if (rc == -1) {
    fprintf(stderr, "%s\n", modbus_strerror(errno));
    }
 
}
