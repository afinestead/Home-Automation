
from Tkinter import *
import tkFont
import requests
import time


URL = "http://10.0.1.128/"
BLUE_ON = "BLUE=ON"
BLUE_OFF = "BLUE=OFF"
GREEN_ON = "GREEN=ON"
GREEN_OFF = "GREEN=OFF"


window = Tk()
window.title("Welcome")


bl_button = IntVar()
bl_button.set(1)

gr_button = IntVar()
gr_button.set(1)

data = StringVar()

lights = [("BLUE ON", 1), ("BLUE OFF", 2), ("GREEN ON", 1), ("GREEN OFF", 2)]


def read():

        request = URL

        if (bl_button.get() == 1):
                request += BLUE_ON
        else:
                request += BLUE_OFF

        request += '&'

        if (gr_button.get() == 1):
                request += GREEN_ON
        else:
                request += GREEN_OFF

        print request
        requests.get(request)


def exit():
        window.quit()

Label(window, text = "Select an option:").grid(row=0)

count = 1
for light, num in lights:
        var = IntVar()
        if light.startswith("BLUE"):
                var = bl_button
        else:
                var = gr_button
 
        Radiobutton(window, text = light, variable = var, value = num).grid(row$
        count = count + 1


Button(window, text = "OK", fg = "black", bg = "white", command = read).grid(ro$
Button(window, text = "QUIT", fg = "black", bg = "white", command = exit).grid($

mainloop()