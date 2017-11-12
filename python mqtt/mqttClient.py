import paho.mqtt.client as mqtt
import time
import sys
import pygame
from pygame import mixer
pygame.init()
pygame.mixer.init()
broker_address="192.168.1.103"

                     
nbcapteurs = 0
def on_message(client, userdata, message):
	
	print(message.topic)
	print(str(message.payload.decode("utf-8")))
	if(message.topic == "/device1"):
		check_nbcapteurs(1,str(message.payload.decode("utf-8")))	
	if(message.topic == "/device2"):
		check_nbcapteurs(2,str(message.payload.decode("utf-8")))	
	if(message.topic == "/device3"):
		check_nbcapteurs(3,str(message.payload.decode("utf-8")))	
	if(message.topic == "/device4"):
		check_nbcapteurs(4,str(message.payload.decode("utf-8")))	
		

def launch_song (id_device):
	init(id_device)
	
def check_nbcapteurs (id_device,activated):
	global nbcapteurs
	print("nb_capteur = ")
	print(nbcapteurs)
	if (activated == "1"):			
			if(nbcapteurs == 0):
				print("launch all songs and unmute n "+str(id_device))
				launch_song(id_device)
			else:
				print("unmute n "+str(id_device))
				unmute_a_song(id_device)
			nbcapteurs+=1
	else:
		if(nbcapteurs > 0):
			nbcapteurs-=1
			mute_a_song(id_device)

		if(nbcapteurs == 0):
			print("stop the music")
			mute()
			
sound1 = pygame.mixer.Sound("./piste_1_jimmy_saxo_basse.wav")
sound2 = pygame.mixer.Sound("./piste2_jimmy_batterie.wav")
sound4 = pygame.mixer.Sound("./piste4_jimmy_piano.wav")
sound3 = pygame.mixer.Sound("./piste3_jimmy_voix.wav")

def init(device_changed):
	global sound1
	global sound2
	global sound3
	global sound4
	sound1.play()
	sound2.play()
	sound3.play()
	sound4.play()
	mute()
	if(device_changed == 1):
		sound1.set_volume(100)
	elif(device_changed == 2):
		sound2.set_volume(100)
	elif(device_changed == 3):
		sound3.set_volume(100)
	elif(device_changed == 4):
		sound5.set_volume(100)
	
	
	
def unmute_a_song (device_id):
	global sound1
	global sound2
	global sound3
	global sound4
	if(device_id == 1):
		sound1.set_volume(100)
	elif(device_id == 2):
		sound2.set_volume(100)
	elif(device_id == 3):
		sound3.set_volume(100)
	elif(device_id == 4):
		sound4.set_volume(100)
	
def mute_a_song (device_id):
	global sound1
	global sound2
	global sound3
	global sound4
	if(device_id == 1):
		sound1.set_volume(0)
	elif(device_id == 2):
		sound2.set_volume(0)
	elif(device_id == 3):
		sound3.set_volume(0)
	elif(device_id == 4):
		sound4.set_volume(0)
	
def mute ():
	global sound1
	global sound2
	global sound3
	global sound4
	sound1.set_volume(0)
	sound2.set_volume(0)
	sound3.set_volume(0)
	sound4.set_volume(0)
		

print("creating new new instance")
client = mqtt.Client("P1")
client.on_message = on_message
print("connecting to broker")
client.connect(broker_address,port=1883)
print("Suscribing to topics")
client.subscribe("/device1",0)
client.subscribe("/device2",0)
client.subscribe("/device3",0)
client.subscribe("/device4",0)
while(1):
	client.loop_forever()
