#!/usr/bin/env python2.7
import control
import sys

def read_fuctions(command):
	if command == 'TEMP':
		q = control.temperature(control.instrument)
		print(str(q))
	if command == 'READ_RUNMODE':
		q = control.read_runmode(control.instrument)
		print(str(q))
	if command == 'READ_SYSTEM_STATUS':
		q = control.read_system_status(control.instrument)
		print(str(q))
	if command == 'READ_SETPOINT_1':
		q = control.read_setpoint_1(control.instrument)
		print(str(q))
	if command == 'READ_CONTROL_SETPOINT':
		q = control.read_control_setpoint(control.instrument)
		print(str(q))
	if command == 'READ_PID_OUTPUT':
		q = control.read_pid_output(control.instrument)
		print(str(q))
	if command == 'READ_RAMP_SOAK_STATE_E':
		q = control.read_ramp_soak_state_e(control.instrument)
		print(str(q))
	if command == 'READ_RAMP_SOAK_MODE':
		q = control.read_ramp_soak_mode(control.instrument)
		print(str(q))
	if command == 'READ_RAMP_SOAK_PROFILE_SELECT':
		q = control.read_ramp_soak_profile_selects(control.instrument)
		print(str(q))
	if command == 'READ_CURRENT_PROFILE':
		q = control.read_current_profile(control.instrument)
		print(str(q))
	if command == 'READ_CURRENT_SEGMENT':
		q = control.read_current_segment(control.instrument)
		print(str(q))
	if command == 'READ_SEGMENTS_PER_PROFILE':
		q = control.read_segments_per_profile(control.instrument)
		print(str(q))
	if command == 'READ_SOAK_ACTION':
		q = control.read_soak_action(control.instrument)
		print(str(q))
	if command == 'READ_SOAK_LINK':
		q = control.read_soak_link(control.instrument)
		print(str(q))
	if command == 'READ_TRACKING_TYPE':
		q = control.read_tracking_type(control.instrument)
		print(str(q))
	if command == 'READ_RAMP_SOAK_REMAINING_TIME':
		q = control.read_ramp_soak_remaining_time(control.instrument)
		print(str(q))
	if command == 'READ_RAMP_SOAK_STATE':
		q = control.read_ramp_soak_state(control.instrument)
		print(str(q))
	if command == 'READ_CONTROL_SETPOINT_X':
		q = control.read_control_setpoint_x(control.instrument)
		print(str(q))

def write_fuctions(command, variable):
	if command == 'WRITE_RUN_MODE':
		q = control.write_run_mode(control.instrument, variable)
		print(str(q))
	if command == 'WRITE_SETPOINT_1':
		q = control.write_setpoint_1(control.instrument, variable)
		print(str(q))
	if command == 'WRITE_CONTROL_SETPOINT':
		q = control.write_control_setpoint(control.instrument, variable)
		print(str(q))
	if command == 'WRITE_RAMP_SOAK_PROFILE_SELECT':
		q = control.write_ramp_soak_profile_select(control.instrument, variable)
		print(str(q))
	if command == 'WRITE_CURRENT_PROFILE':
		q = control.write_current_profile(control.instrument, variable)
		print(str(q))
	if command == 'WRITE_CURRENT_SEGMENT':
		q = control.write_current_segment(control.instrument, variable)
		print(str(q))
	if command == 'WRITE_SOAK_LINK':
		q = control.write_soak_link(control.instrument, variable)
		print(str(q))
	if command == 'WRITE_TRACKING_TYPE':
		q = control.write_tracking_type(control.instrument, variable)
		print(str(q))




if len(sys.argv) == 3:
	print("There is a second variable " +  str(sys.argv[2]))
	command = str(sys.argv[1])
	variable = int(sys.argv[2])
	write_fuctions(command, variable)
	
elif len(sys.argv) == 2:
	# print("There is only 1 variable: " + str(sys.argv[1]))
	command = str(sys.argv[1])
	read_fuctions(command)	
	
else:
	print("Input Error: INCORRECT NUMBER OF ARGUMENTS")

