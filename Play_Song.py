import serial, sys, time

### FILE FORMAT ###
#first line is comma separated notes
# "+A" doulbe
# "A" normal
# "-A" flat
# "LC" low C
# "HC" high C
# "***" start
# "NNN" end, stop playing and release servo and stepper
#second line is comma separated delays (in seconds)
#this forms a 2 line CSV file

#note to keyboard dictonary
noteverter = {
	"LC": 'a',
	"D": 's',
	"E": 'd',
	"F": 'f',
	"G": 'j',
	"A": 'k',
	"B": 'l',
	"HC": ';',
	"-LC": 'z',
	"-D": 'x',
	"-E": 'c',
	"-F": 'v',
	"-G": 'm',
	"-A": ',',
	"-B": ',',
	"-HC": '.',
	"+LC": 'q',
	"+D": 'w',
	"+E": 'e',
	"+F": 'r',
	"+G": 'u',
	"+A": 'i',
	"+B": 'o',
	"+HC": 'p',
	"NNN": '1',
	"***": '0'
}

#defaults
file_folder = "" #leaving this empty uses current folder
serial_port = "/dev/ttyACM0"

#read args
if (len(sys.argv) != 2):
	exit()

try:
	#get song file name
	file_name = sys.argv[1]
	
	#open file
	song = open(file_folder + file_name, 'r')
except:
	print "File not found"
	exit()

#load arrays
print "Loading file"
lines = song.readlines() #an array containing 2 strings
note_string = lines[0].strip() #removes new line
delays_string = lines[1].strip()

#separate elements and create arrays
notes = note_string.split(',')
delays = delays_string.split(',')

if len(notes) != len(delays):
	print "File error"
	exit()

#close file
song.close()
print "Closed file"

#just for debugging
#print notes
#print delays

#open serial port
try:
	ser = serial.Serial(serial_port)
except:
	print "Arduino not detected"
	exit()

#send
print "Sending song"
for i in range(len(notes)):
	print notes[i]
	val = noteverter[notes[i]]
	ser.write(val) #get value from dict and send
	
	time.sleep(float(delays[i])) #wait
time.sleep(1) #allow travel arm and striker to settle
print "Done playing song"
