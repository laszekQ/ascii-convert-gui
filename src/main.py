import tkinter as tk
from tkinter.font import Font
import func

def zoom(size):
    out_font.configure(size=size)

def invertColors():
    if inverted_cl.get() == 0:
        output_text.configure(bg='black', fg='white')
    else:
        output_text.configure(bg='white', fg='black')
    triggerReConv_noargs()

root = tk.Tk()
root.title('ascii-convert')
root.geometry('1920x1080')

file_in = tk.StringVar()
file_out = tk.StringVar()

c_mode = tk.StringVar(value='d')
gradient = tk.StringVar(value=' .:-=+*#%@')
gradient_len = tk.IntVar(value=10)
mode = tk.IntVar(value=2)

font_size = tk.IntVar(value=10)
out_font = Font(family='Courier New', size=10)

conv_text = tk.StringVar()
output_text = tk.Text(root, width=382, height=200, bg = 'white', fg='black', wrap='none')
output_text.configure(font=out_font)
inverted_cl = tk.IntVar(value=1)

out_font_scale = tk.Scale(root, from_=2, to_=48, orient='horizontal', variable=font_size, command=zoom)
out_text_invert_cl = tk.Checkbutton(root, text='Invert colors', variable=inverted_cl, onvalue=1, offvalue=0, command=invertColors)

triggerReConv_noargs = lambda : func.convertAndWrite(conv_text.get(), output_text, file_in.get(), c_mode.get(), gradient.get(), gradient_len.get(), mode.get())
triggerReConv_arg = lambda x : func.convertAndWrite(conv_text.get(), output_text, file_in.get(), c_mode.get(), gradient.get(), gradient_len.get(), mode.get())

filename_in_label = tk.Label(root, text='Input file:')
filename_in_entry = tk.Entry(root, textvariable=file_in)
filedialog_in_button = tk.Button(root, text='Open', command= lambda: func.selectInputFile(file_in))

convert_button = tk.Button(root, text='Draw', command=triggerReConv_noargs)

clr_mode_d_rb = tk.Radiobutton(root, text='Dark',  value='d', variable=c_mode, command=triggerReConv_noargs )
clr_mode_l_rb = tk.Radiobutton(root, text='Light', value='l', variable=c_mode, command=triggerReConv_noargs)

gradient_entry = tk.Entry(root, textvariable=gradient)
gradient_len_slider = tk.Scale(root, from_=2, to=len(gradient.get()), orient='horizontal', variable=gradient_len, command=triggerReConv_arg)
gradient.trace_add(
    'write',
    lambda *args : gradient_len_slider.configure(to=len(gradient.get()))
)


mode_1_rb = tk.Radiobutton(root, text='1:1',  value=1, variable=mode, command=triggerReConv_noargs)
mode_2_rb = tk.Radiobutton(root, text='2:1',  value=2, variable=mode, command=triggerReConv_noargs)
mode_3_rb = tk.Radiobutton(root, text='1:2',  value=3, variable=mode, command=triggerReConv_noargs)

filename_out_label = tk.Label(root, text='Output file:')
filename_out_entry = tk.Entry(root, textvariable=file_out)
save_button = tk.Button(root, text='Save to file', command= lambda: func.saveToFile(filename_out_entry, output_text))

filename_in_label.place(relx=0, rely=0.025)
filename_in_entry.place(relx=0, rely=0.05)
filedialog_in_button.place(relx=0.12, rely = 0.05)
convert_button.place(relx=0.16, rely=0.05)
clr_mode_d_rb.place(relx=0, rely=0.08)
clr_mode_l_rb.place(relx=0, rely=0.13)
gradient_entry.place(relx=0, rely=0.16)
gradient_len_slider.place(relx=0.025, rely=0.19)
mode_1_rb.place(relx=0, rely=0.25)
mode_2_rb.place(relx=0, rely=0.30)
mode_3_rb.place(relx=0, rely=0.35)
filename_out_label.place(relx=0, rely=0.40)
filename_out_entry.place(relx=0, rely=0.425)
save_button.place(relx=0.025, rely=0.46)
out_font_scale.place(relx=0.025, rely=0.5)
out_text_invert_cl.place(relx = 0.020, rely=0.6)
output_text.place(relx=0.2, rely=0, width=1500, height=1000)

root.mainloop()

