from Tkinter import *
import tkFont

window = Tk()

s1 = IntVar()
s2 = IntVar()
s1.set(50)

def show():
        print str(s1.get()) + ", " + str(s2.get())

def exit():
        print "exit"
        show()
        window.quit()


Scale(window, from_=100, to=0, orient = VERTICAL, variable = s1, tickinterval = 25, length = 200).pack(side = LEFT)
Scale(window, from_=0, to=10, orient = VERTICAL, variable = s2).pack(side = LEFT)
Button(window, text = "Show Values", command = show).pack(side=BOTTOM)

mainloop()