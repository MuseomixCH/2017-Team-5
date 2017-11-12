import paho.mqtt.client as mqtt
import time
import sys
broker_address="10.1.1.35"

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
	execfile("ess_game.py",[true,idDevice])
	
def check_nbcapteurs (id_device,activated):
	print("nb_capteur = "+nb_capteurs)
	if (activated == "true"):			
			if(nbcapteurs == 0):
				print("launch all songs and unmute n°"+id_device)
				launch_song(id_device)
			else:
				print("unmute n°"+id_device)
				unmute_song(id_device)
			nbcapteurs++
	else:
		if(nbcapteurs > 0):
			nbcapteurs--

		if(nbcapteurs == 0):
			print("stop the music")
			stop_music
		

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