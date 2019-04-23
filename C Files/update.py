import MySQLdb as sql
import datetime
import time
import subprocess


# subprocess.check_output(['ls','-l']) #all that is technically needed...
#
# View https://github.com/PyMySQL/mysqlclient-python for installation 
# instructions for the MySQLdb package



while 1:
    
    cnx = sql.connect(
    host="chip.swau.edu",
    user="rumaldoa",
    passwd="Jantex1513!",
    db="KilnProject"
    )
    
    # Cursor creates an object that allows us to run commands
    cursor = cnx.cursor()
    time.sleep(5)
    # This is the timestamp
    ts = time.time()
    st = datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d %H:%M:%S')
    # Prints timestamp
    # print(st)

    log_time = st

    result = subprocess.run(['./control.c', '1', '2', '1'], stdout=subprocess.PIPE)
    output = result.stdout.decode('utf-8')
    print("temperature: {}".format(output))
    temperature = output

    result = subprocess.run(['./control.c', '1', '2', '2'], stdout=subprocess.PIPE)
    output = result.stdout.decode('utf-8')
    print("setpoint: {}".format(output))
    setpoint = output

    result = subprocess.run(['./control.c', '1', '2', '3'], stdout=subprocess.PIPE)
    output = result.stdout.decode('utf-8')
    print("control setpoint: {}".format(output))
    control_setpoint = output

    result = subprocess.run(['./control.c', '1', '2', '4'], stdout=subprocess.PIPE)
    output = result.stdout.decode('utf-8')
    print("PID output: {}".format(output))
    pid_output = output

    result = subprocess.run(['./control.c', '1', '1', '1'], stdout=subprocess.PIPE)
    output = result.stdout.decode('utf-8')
    print("runmode: {}".format(output))
    runmode = output

    result = subprocess.run(['./control.c', '1', '1', '2'], stdout=subprocess.PIPE)
    output = result.stdout.decode('utf-8')
    print("rampsoak state: {}".format(output))
    ramp_soak_state = output

    result = subprocess.run(['./control.c', '1', '1', '4'], stdout=subprocess.PIPE)
    output = result.stdout.decode('utf-8')
    print("profile select {}".format(output))
    ramp_soak_profile_select = output

    result = subprocess.run(['./control.c', '1', '1', '5'], stdout=subprocess.PIPE)
    output = result.stdout.decode('utf-8')
    print("current profile: {}".format(output))
    current_profile = output

    result = subprocess.run(['./control.c', '1', '1', '6'], stdout=subprocess.PIPE)
    output = result.stdout.decode('utf-8')
    print("current segment: {}".format(output))
    current_segment = output

    result = subprocess.run(['./control.c', '1', '1', '7'], stdout=subprocess.PIPE)
    output = result.stdout.decode('utf-8')
    print("segments per profile: {}".format(output))
    segment_per_profile = output

    result = subprocess.run(['./control.c', '1', '1', '8'], stdout=subprocess.PIPE)
    output = result.stdout.decode('utf-8')
    print("soak action: {}".format(output))
    soak_action = output

    result = subprocess.run(['./control.c', '1', '2', '10'], stdout=subprocess.PIPE)
    output = result.stdout.decode('utf-8')
    print("temperature: {}".format(output))
    tracking_type = output

    operation = "INSERT INTO `controller_info` (`log_id`, `log_time`, `temperature`, `setpoint`, `control_setpoint`, `pid_output`, `runmode`, `ramp_soak_state`, `ramp_soak_profile_select`, `current_profile`, `current_segment`, `segment_per_profile`, `soak_action`, `tracking_type`) VALUES ('', '{}', '{}', '{}', '{}', '{}', '{}', '{}', '{}', '{}', '{}', '{}', '{}', '{}');".format(log_time, temperature, setpoint, control_setpoint, pid_output, runmode, ramp_soak_state, ramp_soak_profile_select, current_profile, current_segment, segment_per_profile, soak_action, tracking_type)
                       
    cursor.execute(operation)

    cnx.commit()
    cursor.close()
    cnx.close()


