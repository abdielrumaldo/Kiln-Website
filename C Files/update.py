import MySQLdb as sql
import datetime
import time

# subprocess.check_output(['ls','-l']) #all that is technically needed...
#
# View https://github.com/PyMySQL/mysqlclient-python for installation 
# instructions for the MySQLdb package

cnx = sql.connect(
    host="chip.swau.edu",
    user="rumaldoa",
    passwd="Jantex1513!",
    db="KilnProject"
    )

# Cursor creates an object that allows us to run commands
cursor = cnx.cursor()

# This is the timestamp 
ts = time.time()
st = datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d %H:%M:%S')
# Prints timestamp
# print(st)

log_time = st
temperature = "2"
setpoint = "3"
control_setpoint = "4"
pid_output = "5"
runmode = "6"
ramp_soak_state = "7"
ramp_soak_profile_select = "8"
current_profile = "9"
current_segment = "10"
segment_per_profile = "11"
soak_action = "12"
tracking_type = "13"

operation = "INSERT INTO `controller_info` (`log_id`, `log_time`, `temperature`, `setpoint`, `control_setpoint`, `pid_output`, `runmode`, `ramp_soak_state`, `ramp_soak_profile_select`, `current_profile`, `current_segment`, `segment_per_profile`, `soak_action`, `tracking_type`) VALUES ('', '{}', '{}', '{}', '{}', '{}', '{}', '{}', '{}', '{}', '{}', '{}', '{}', '{}');".format(log_time, temperature, setpoint, control_setpoint, pid_output, runmode, ramp_soak_state, ramp_soak_profile_select, current_profile, current_segment, segment_per_profile, soak_action, tracking_type)

cursor.execute(operation)

rows = cursor.fetchall()

for item in rows:
    print(item)

cursor.close()
cnx.commit()
cnx.close()
