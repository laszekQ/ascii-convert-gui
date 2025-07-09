import ascii_convert
import tkinter as tk
from tkinter import filedialog as fd
import os

def selectInputFile(filename_var : tk.StringVar):
    filetypes = (
        ('JPG', '*.jpg'),
        ('JPEG', '*.jpeg'),
        ('PNG', '*.png'),
        ('BMP', '*.bmp'),
        ('All files', '*.*')
    )

    filename = fd.askopenfilename(title='Open a file',
                                  filetypes=filetypes)
    
    filename_var.set(filename)

def saveToFile(filename_var : tk.StringVar, text : tk.Text):
    file = open(filename_var.get(), 'w')
    file.write(text.get('1.0', tk.END))
    file.close()

def convertAndWrite(conv_text_var : str, out_textfield : tk.Text, file : str, c_mode : int, gradient : str, grad_len : int, mode : int):
    if not os.path.exists(file):
        print('Invalid filepath!')
        return
    
    if len(gradient) < grad_len:
        print('The gradient is too short!')
        return

    try:
        conv_text_var = ascii_convert.convert(file, c_mode, gradient, grad_len, mode)
        out_textfield.delete('1.0', tk.END)
        out_textfield.insert('1.0', conv_text_var)
    except Exception as e:
        print(e)