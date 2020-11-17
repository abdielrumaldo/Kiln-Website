# Kiln-Website
Creating a web user interface for Omega PID controllers for the operation of a Kiln

My contribution to this project was the API that I provided for the communication between the Web Interface and the PID controller and populating the database with current and historcal data about the previous ramps and soaks and the temperatures.

C Files/ - Contains the extration of data from the controller and the database. This will run in the background and periodically poll the controller and push data to the database.

Python files/ - Contain the API that allows the web interface to write and read data to the PID controller with input validation.
