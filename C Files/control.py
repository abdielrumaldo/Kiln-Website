#!/usr/bin/env python
import sys
sys.path.append('/usr/lib/')
import minimalmodbus
import serial
import struct


instrument = minimalmodbus.Instrument('/dev/ttyAMA0', 1)

instrument.serial.baudrate = 19200
instrument.serial.bytesize = 8
instrument.serial.parity = serial.PARITY_ODD
instrument.serial.stopbits = 1
instrument.serial.timeout = 1
# Used to DEBUG
# instrument.debug = True
# print(instrument) # Will print all the settings on the onject instrument

def swap32(x):
	return struct.unpack('>i', x)[0]

def temperature(instrument):
	try: 
		temp = instrument.read_float(0x0280)
	except:
		print("Unexpected error with Setpoint 1", sys.exc_info()[0])
		
	else:
		return int(temp)	
		
def read_runmode(instrument):
	try:
		runmode = instrument.read_register(0x0240)
	except:
		print("Unexpected error with System Status", sys.exc_info()[0])
	else: 
		return runmode

def read_system_status(instrument):
	try:
		runmode = instrument.read_long(0x0204)
	except:
		print("Unexpected error with System Status", sys.exc_info()[0])
	else: 
		return runmode
		
		
def write_run_mode(instrument, mode):
	if mode > 12 or mode <= 0:
		return "Invalid Input: System State are from intergers 1-12"
	try:
		runmode = instrument.write_register(0x0240,mode,functioncode=6)
	except:
		print("Unexpected error with System Status", sys.exc_info()[0])
	else: 
		return read_runmode(instrument)

def read_setpoint_1(intrument):
	try:
		setpoint = instrument.read_float(0x0220)
	except:
		print("Unexpected error with System Status", sys.exc_info()[0])
	else: 
		return setpoint	
		
def write_setpoint_1(instrument, value):
	if  value <= 0:
		return "Invalid Input: Setpoint can not be <= 0"
	try:
		setpoint = instrument.write_register(0x0220,value,functioncode=6)
	except:
		print("Unexpected error with System Status", sys.exc_info()[0])
	else: 
		return read_setpoint_1(instrument)
		
def read_control_setpoint(instrument):
	try:
		controlsetpoint = instrument.read_float(0x0224)
	except:
		print("Unexpected error with System Status", sys.exc_info()[0])
	else: 
		return controlsetpoint	
		
def write_control_setpoint(instrument, value):
	if  value <= 0:
		return "Invalid Input: Setpoint can not be <= 0"
	try:
		setpoint = instrument.write_register(0x0224, value, functioncode=6)
	except:
		print("Unexpected error with System Status", sys.exc_info()[0])
	else: 
		return read_control_setpoint(instrument)

def read_pid_output(intrument):
	try:
		pidoutput = instrument.read_float(0x022a)
	except:
		print("Unexpected error with System Status", sys.exc_info()[0])
	else: 
		return pidoutput
		
def read_ramp_soak_state_e(instrument):
	try:
		pidoutput = instrument.read_register(0x022e)
	except:
		print("Unexpected error with System Status", sys.exc_info()[0])
	else: 
		return pidoutput
		
def read_ramp_soak_mode(instrument):
	try:
		pidoutput = instrument.read_register(0x0260)
	except:
		print("Unexpected error with System Status", sys.exc_info()[0])
	else: 
		return pidoutput

def read_ramp_soak_profile_select(instrument):
	try:
		pidoutput = instrument.read_register(0x0261)
	except:
		print("Unexpected error with System Status", sys.exc_info()[0])
	else: 
		return pidoutput
		
def write_ramp_soak_profile_select(instrument, value):
	if value > 99 or value <= 0:
		return "Invalid profile value, select between 1 and 99"
	try:
		pidoutput = instrument.write_register(0x0261, value, functioncode=6)
	except:
		print("Unexpected error with System Status", sys.exc_info()[0])
	else: 
		return pidoutput

def read_current_profile(instrument):
	try:
		pidoutput = instrument.read_register(0x0262)
	except:
		print("Unexpected error with System Status", sys.exc_info()[0])
	else: 
		return pidoutput
		
def write_current_profile(instrument, value):
	if value >9 or value <=0:
		return "Invalid value you can only select profile between 1 and 9"
	try:
		pidoutput = instrument.read_register(0x0262, value, functioncode=6)
	except:
		print("Unexpected error with System Status", sys.exc_info()[0])
	else: 
		return pidoutput
		
def read_current_segment(instrument):
	try:
		pidoutput = instrument.read_register(0x0263)
	except:
		print("Unexpected error with System Status", sys.exc_info()[0])
	else: 
		return pidoutput
		
def write_current_segment(instrument, value):
	if value >8 or value <=0:
		return "Invalid value you can only select segment between 1 and 9"
	try:
		pidoutput = instrument.read_register(0x0262, value, functioncode=6)
	except:
		print("Unexpected error with System Status", sys.exc_info()[0])
	else: 
		return pidoutput
		
def read_segments_per_profile(instrument):
	try:
		pidoutput = instrument.read_register(0x0264)
	except:
		print("Unexpected error with System Status", sys.exc_info()[0])
	else: 
		return pidoutput
		
def read_soak_action(instrument):
	try:
		pidoutput = instrument.read_register(0x0265)
	except:
		print("Unexpected error with System Status", sys.exc_info()[0])
	else: 
		return pidoutput
		
def read_soak_link(instrument):
	try:
		pidoutput = instrument.read_register(0x0266)
	except:
		print("Unexpected error with System Status", sys.exc_info()[0])
	else: 
		return pidoutput

# Action {0:stop, 1:hold, 2:link }	
def write_soak_link(instrument, action):
	try:
		pidoutput = instrument.read_register(0x0266, action, functioncode=6)
	except:
		print("Unexpected error with System Status", sys.exc_info()[0])
	else: 
		return pidoutput
		
def read_tracking_type(instrument):
	try:
		pidoutput = instrument.read_register(0x0267)
	except:
		print("Unexpected error with System Status", sys.exc_info()[0])
	else: 
		return pidoutput

# Action {0: fixed ramp, 1: fixed soak, 2: fixed cycle}
def write_tracking_type(instrument, action):
	try:
		pidoutput = instrument.write_register(0x0267, action, functioncode=6)
	except:
		print("Unexpected error with System Status", sys.exc_info()[0])
	else: 
		return pidoutput	

def read_ramp_soak_remaining_time(instrument):
	try:
		pidoutput = instrument.read_long(0x0272)
	except:
		print("Unexpected error with System Status", sys.exc_info()[0])
	else: 
		return pidoutput
		
def read_ramp_soak_state(instrument):
	try:
		pidoutput = instrument.read_register(0x0274)
	except:
		print("Unexpected error with System Status", sys.exc_info()[0])
	else: 
		return pidoutput
		
def read_control_setpoint_x(instrument):
	try:
		pidoutput = instrument.read_float(0x0270)
	except:
		print("Unexpected error with System Status", sys.exc_info()[0])
	else: 
		return pidoutput		
	
'''	
q = read_pid_output(instrument)
print("Read PID OUTPUT: " + str(q))

q = read_setpoint_1(instrument)
print("Read Setpoint 1: " + str(q))

#q = write_setpoint_1(instrument, 190)
#print("Write Setpoint 1 to 190: " + str(q))

#q = write_run_mode(instrument, 1)
#print("Set Runmode to 1: " + str(q))

q = read_control_setpoint(instrument)
print("Read Control Setpoint: " + str(q))

#q = write_control_setpoint(instrument, 190)
#print("Write control setpoint to 190: " + str(q))

q = read_ramp_soak_state_e(instrument)
print("Read ramp soak state E: " + str(bin(q)))

q = read_ramp_soak_state(instrument)
print("Read ramp soak state: " + str(bin(q)))

q = read_ramp_soak_mode(instrument)
print("Read ramp soak mode: " + str(q))

q = read_ramp_soak_profile_select(instrument)
print("Read ramp soak profile select: " + str(q))

#q = write_ramp_soak_profile_select(instrument, 1)
#print("Write ramp soak profile select to 1: " + str(q))

q = read_current_profile(instrument)
print("Read curent profile: " + str(q))

q = read_current_segment(instrument)
print("Read curent segment: " + str(q))

q = read_ramp_soak_remaining_time(instrument)
print("Read ramp or soak time remaining: " + str(q))

q = read_ramp_soak_state(instrument)
print("Read ramp soak state: " + str(q))

q = read_tracking_type(instrument)
print("Read Tracking Type: " + str(q))

q = read_segments_per_profile(instrument)
print("Read Segments per profile: " + str(q))

q = read_control_setpoint_x(instrument)
print("Read Control Setpoint X: " + str(q))

q = read_runmode(instrument)
print("Read Run Mode: " + str(q))

'''

