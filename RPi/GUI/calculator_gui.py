from Tkinter import *
import Tkinter as tk
from tkMessageBox import *
from tkFileDialog import asksaveasfilename
import tkFont

window = tk.Tk()
window.title("Calculator")

currency = IntVar()
currency.set(0)

def calc():

        if not pay.get() and not hours.get():
                showerror(title="Error!", message="Enter values for hourly pay \nand number of hours worked")
        elif not hours.get():
                showerror(title="Error!", message="Enter a value for number of hours worked")
        elif not pay.get():
                showerror(title="Error!", message="Enter a value for hourly pay")

        #error check for if nothing is entered in "Tax" but other vals are nega$
        if pay.get() and hours.get():
                err = FALSE
                if not tax.get():
                        tax.set("0")
                if float(tax.get())<0 or float(hours.get())<0 or float(pay.get($
                        showerror(title="Error!", message="Values cannot be negative")
                        err = TRUE
                if not err:
                        total = 4 * float(pay.get()) * float(hours.get()) *(100$
                        if currency.get() == 0:
                                var.set("$" + str(total))
                        else:
                                var.set(str(total))

def get_pref():
        new_win = tk.Toplevel(window)

        Label(new_win, text = "Currency:", relief = RIDGE).pack()
        options = [("USD ($)", 0), ("Other?", 1)]
        for type, num in options:
                Radiobutton(new_win, text = type, variable = currency, value = $

def save():
        asksaveasfilename()


def exit():
        window.quit()


#Add menu bar
menu = Menu(window, bg = "white", fg = "black", relief = SUNKEN)
window.config(menu = menu)

#Add cascading file menu
file_menu = Menu(menu)
menu.add_cascade(label = "File", menu = file_menu)

file_menu.add_command(label = "Preferences", command = get_pref)
file_menu.add_command(label = "Save...", command = save)
file_menu.add_command(label = "Quit", command = exit)

#String variables
pay = StringVar()
hours = StringVar()
tax = StringVar()
var = StringVar()
var.set(" ")

labels = [("Hourly rate:", pay), ("Hours per week:", hours), ("Tax rate (%):", $


#Set fonts for calculator
my_font = tkFont.Font(family = "Arial", size = 8)


#Make labels and entry boxes
count = 1
for label, entry in labels:
        tk.Label(window, text = label, relief = RIDGE, width = 18, font = my_fo$
        if count != 4:
                tk.Entry(window, textvariable = entry, relief = SUNKEN, font = $
        else:
                income = Label(window, textvariable = var, relief = SUNKEN, fon$
        count += 1

tk.Button(window, text = "Calculate", command = calc).grid(row = count, column $
tk.Button(window, text = "Quit", command = exit).grid(row = count, column = 1)

mainloop()