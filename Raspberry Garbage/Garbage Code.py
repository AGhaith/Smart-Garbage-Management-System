import time
import BlynkLib
from BlynkTimer import BlynkTimer
from gpiozero import DistanceSensor, Servo, LED
from time import sleep
import RPi.GPIO as GPIO
#Variables
full=10
close=20
fullornot='free'
status='NONE'
def update():
    global garbage_level,proximity
    garbage_level=in_sensor.distance*100
    proximity = out_sensor.distance*100
    
#Servo
GPIO.setmode(GPIO.BCM)
SERVO_PIN = 17
GPIO.setup(SERVO_PIN, GPIO.OUT)
servo = GPIO.PWM(SERVO_PIN, 50)  # 50Hz frequency
def initialize_servo():
    servo.start(2.5)
    sleep(1)
def setAngle(angle):
    duty = angle / 18 + 3
    GPIO.output(11, True)
    pwm.ChangeDutyCycle(duty)
    sleep(1)
    GPIO.output(11, False)
    pwm.ChangeDutyCycle(duty)
#Blynk
BLYNK_AUTH_TOKEN = "vYn_D6RkEcs3rnOHw3m-rYfPgJFx_08k"
blynk = BlynkLib.Blynk(BLYNK_AUTH_TOKEN)
timer = BlynkTimer()
@blynk.on("connected")
def blynk_connected():
    print("Raspberry Pi is connected to Blynk")
def send_data_to_blynk():
    global garbage_level, status,obj_distance,fullornot
    blynk.virtual_write(distance_pin, garbage_level)
    blynk.virtual_write(status_pin, fullornot)
    #blynk.virtual_write(plastic_pin, plastic_cnt)
    #blynk.virtual_write(metal_pin, metal_cnt)
    blynk.virtual_write(type_pin, 'Inavailable')
#Blynk Pins
distance_pin = 0
status_pin = 1    
type_pin = 2      
plastic_pin = 3   
metal_pin = 4     
#Components
out_sensor = DistanceSensor(echo=20, trigger=21)  
in_sensor = DistanceSensor(echo=16, trigger=12)  
red_led = LED(27)
green_led = LED(22)
#Methods
def check_object():
    if proximity < close :#CLOSE
        openbin()
        sleep(1.5)
    elif status == 'open':
        closebin()
        sleep(1.5)
def openbin():
    global status
    setAngle(90)
    status='open'
def closebin():
    global status
    setAngle(0)
    status='closed'
blynk_connected()
initialize_servo()

while True :
    update()
    if (garbage_level < full): #FULL
        if status == 'open': 
            closebin()
        fullornot='1'
        red_led.on()
        green_led.off()
        sleep(1)
    else :
        fullornot='0'
        check_object()
    blynk.run()
    timer.run()