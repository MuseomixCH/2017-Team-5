
import time
import mp3play

clip = mp3play.load(r"piste_1_jimmy_saxo_basse.mp3")
clip.play()

time.sleep(min(5,clip.seconds()))
clip.stop


	
