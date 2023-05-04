

from time import sleep
import urllib.request
import keyboard
url = "http://192.168.137.243/"  

def get_data():
	global data
	

	n = urllib.request.urlopen(url).read() 
	n = n.decode("utf-8") 

	data = n



while True:
	get_data()
	vb = str(data)
	sigs = [*vb]
	print(sigs)
'''	if sigs[0]=='8':
		keyboard.press_and_release("Down")
	elif sigs[0]=='2':
		keyboard.press_and_release("Up")
	if sigs[1]=='4':
		keyboard.press_and_release("right")
	elif sigs[1]=='6':
		keyboard.press_and_release("Left ")
	if sigs[2]=='7':
		keyboard.press_and_release("High")
	elif sigs[2]=='1':
		keyboard.press_and_release("Low")'''
