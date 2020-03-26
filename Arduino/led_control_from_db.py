#!/usr/bin/python
# -*- coding: utf-8 -*-

import MySQLdb as mdb
import sys

import RPi.GPIO as GPIO # Import GPIO Library
import time # Import 'time' library.  Allows us to use 'sleep'

GPIO.setwarnings (False)	# these are annoying

GPIO.setmode(GPIO.BCM) # Use BOARD pin numbering
# Setup GPIO pin outputs
GPIO.setup(4, GPIO.OUT)
GPIO.setup(17, GPIO.OUT)
GPIO.setup(27, GPIO.OUT)
GPIO.setup(22, GPIO.OUT)

con = mdb.connect('localhost', 'testuser', 'test623', 'testdb');

def check_database (pin, ID):
	with con:
		# fetch enable
		cur = con.cursor ()
		cur.execute ("select enable from gpio where id = %s", (str(ID)))
		enable = cur.fetchone ()
		cur.close ()
		if enable [0] == 1:	# turn output on
			# fetch time
			cur1 = con.cursor ()
			cur1.execute ("select time from gpio where id = %s", (str(ID)))
			length = cur1.fetchone ()
			cur1.close ()
			# turn output on, sleep for time, and turn output off
			print "Pin " + str(pin) + " turned on for " + str(length [0]) + " seconds"
			GPIO.output (pin, True) 
			time.sleep (length [0])
			GPIO.output (pin, False)
			# reset bit in database
			cur2 = con.cursor ()
			cur2.execute ("update gpio set enable = 0 where id = %s", (str(ID)))
			cur2.close ()

while True:
	check_database (4, 1)
	check_database (17, 2)
	check_database (27, 3)
	check_database (22, 4)
	
#GPIO.cleanup ()
