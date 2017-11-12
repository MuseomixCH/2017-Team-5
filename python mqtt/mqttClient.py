import paho.mqtt.client as mqtt
import time
import sys
broker_address="10.1.6.243"

nbcapteurs = 0
def on_message(client, userdata, message):
	print(message.topic)
	print(str(message.payload.decode("utf-8")))
	if(message.topic == "/device1":
		check_nbcapteurs(1,str(message.payload.decode("utf-8")))	
	if(message.topic == "/device2":
		check_nbcapteurs(2,str(message.payload.decode("utf-8")))	
	if(message.topic == "/device3":
		check_nbcapteurs(3,str(message.payload.decode("utf-8")))	
	if(message.topic == "/device4":
		check_nbcapteurs(4,str(message.payload.decode("utf-8")))	
		

def launch_song (id_device):
	init()
	
def check_nbcapteurs (id_device,activated):
	print("nb_capteur = "+nb_capteurs)
	if (activated == "true"):			
			if(nbcapteurs == 0):
				print("launch all songs and unmute n°"+id_device)
				launch_song(id_device)
			else:
				print("unmute n°"+id_device)
				unmute_a_song(id_device)
			nbcapteurs++
	else:
		if(nbcapteurs > 0):
			nbcapteurs--

		if(nbcapteurs == 0):
			print("stop the music")
			mute()
			
sound1
sound2
sound3
sound4

def init(device_changed):
	sound1 = pygame.mixer.Sound("./piste_1_jimmy_saxo_basse.mp3")
	sound2 = pygame.mixer.Sound("./piste2_jimmy_batterie.mp3")
	sound3 = pygame.mixer.Sound("./piste4_jimmy_piano.mp3")
	sound4 = pygame.mixer.Sound("./piste3_jimmy_voix.mp3")
	sound1.play()
	sound1.play()
	sound3.play()
	sound4.play()
	mute()
	if(device_changed == 1):
		sound1.set_volume(100)
	else if(device_changed == 2):
		sound2.set_volume(100)
	else if(device_changed == 3):
		sound3.set_volume(100)
	else if(device_changed == 4):
		sound5.set_volume(100)
	
	while pygame.mixer.music.get_busy(): 
		pygame.time.Clock().tick(10)
	
def unmute_a_song (device_id):
	if(device_id == 1):
		sound1.set_volume(100)
	else if(device_id == 2):
		sound2.set_volume(100)
	else if(device_id == 3):
		sound3.set_volume(100)
	else if(device_id == 4):
		sound4.set_volume(100)
		
def mute ():
	sound1.set_volume(0)
	sound2.set_volume(0)
	sound3.set_volume(0)
	sound4.set_volume(0)
		

print("creating new new instance")
client = mqtt.Client("P1")
client.on_message = on_message
print("connecting to broker")
client.connect(broker_address,port=1883)
print("Suscribing to topic","sound1")
client.suscribe("/sound1",0)
while(1)
	client.loop_start()
	time.sleep(4)
	client.loop_stop()