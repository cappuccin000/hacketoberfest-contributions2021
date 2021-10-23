from tkinter import *
import random
import string
from typing import Generator
import pyperclip

# Initialization of Window
root = Tk()
root.geometry("400x400")
root.resizable(width=0, height=0)
root.title("Password Generator")

# Setting Label
Label (root, text= 'Password Generator', font='sans-serif 15 bold').pack()
Label (root, text='Generated!', font='sans-serif 15 bold').pack(side = BOTTOM)

# Setting Password length
pass_label = Label(root, text= 'Password Length', font='sans-serif 10 bold').pack()
pass_len = IntVar()
length = Spinbox(root, from_= 8, to_ = 16, textvariable=pass_len, width = 15).pack()


# function to generate password
pass_str = StringVar()
def generator():
    password = ''

    for i in range(0,4):
        password = random.choice(string.ascii_uppercase) + random.choice(string.ascii_lowercase) + random.choice(string.ascii_letters) + random.choice(string.digits) + random.choice(string.capwords)
    
    for j in range(pass_len.get() - 4):
        password = password + random.choice(string.ascii_letters + string.ascii_lowercase + string.punctuation + string.capwords)

        pass_str.set(password)


Button(root, text="Generated!", command= Generator).pack(pady=5)

Entry(root, textvariable = pass_str).pack()

# func to copy password

def copy_pass():
    pyperclip.copy(pass_str.get())

Button(root, text = 'Copy!', command=copy_pass).pack(pady=5)