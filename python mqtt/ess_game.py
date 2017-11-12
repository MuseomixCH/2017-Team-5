import pygame
from pygame import mixer
pygame.init()
pygame.mixer.init()


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



	


