import threading
import time
import tkinter
import serial
from tkinter import *
from tkinter import ttk

in_list = []                                                            
out_flag = 0                                                            
ser = None
start_flag = 0
error_flag = 0

def com_connect():
    global start_flag
    global ser
    global tr_in
    global error_flag
    global com_n
    try:
        #debugListbox.insert(END,"Try to open COM1")
        ser=serial.Serial('COM1',int(combo_speed.get()),timeout=0)
    except:
        debugListbox.insert(END,"Ошибка подключения к COM1")
        try:
            #debugListbox.insert(END,"Try to open COM2")
            ser=serial.Serial('COM2',int(combo_speed.get()),timeout=0)
        except:
            debugListbox.insert(END,"Откройте порты и перезапустите приложение")
        else:
            debugListbox.insert(END,"Вы подключились к COM2")
            tr_in.start()
            com_n = 2
            start_flag = 1
    else:
        debugListbox.insert(END,"Вы подключились к COM1")
        tr_in.start()                                                       
        com_n = 1
        start_flag = 1

def fn_in():                                                                
    global ser
    global start_flag
    global in_list 
    global com_n                                                            
    while 1:                                                                
            #debugListbox.insert(END,"Waiting message")
            in_len = 0                                                      
            while in_len<1:
                in_st = ser.readline()                                      
                in_len = len(in_st)                                         
            in_list.append(in_st)                                           
            time.sleep(1)
#доп поток
tr_in = threading.Thread(target = fn_in)                                    
tr_in.daemon = True                                                         
#основной поток
def fn_out():
    global out_flag                                                         
    out_flag =1

def fn_send():                                                              
    global ser
    out_st = inputEntity.get()                                                       
    if len(out_st)>0:                                                       
        ser.write(out_st.encode())                                          
        #debugListbox.insert(END,">>>"+out_st)                                         
    inputEntity.delete(0,END)                                                        
#вывести строки в листбокс
def fn_disp():
    global out_flag
    while len(in_list)>0:                                                           
        st = in_list.pop(0)                                                 
        outputLisbox.insert(END,st.decode())                                          
    if out_flag:                                                            
        fn_send()                                                           
        out_flag = 0
    root.after(100,fn_disp)                                                 

#ГУИ
fl1=0

def fn_get_com():
    global fl1
    global com_n
    if fl1 == 0:
        com_connect()
        fl1=1
    else:
        debugListbox.insert(END,"Порты уже открыты")    
                            
root = Tk()                                                                 
root.geometry("600x400")

input = LabelFrame( text="Ввод")
input.pack()

output = LabelFrame( text="Вывод")
output.pack()

debug = LabelFrame( text="Программные сообщения")
debug.pack()

settings = LabelFrame( text="Настройки")
settings.pack()

scrollbarI = Scrollbar(input,orient=HORIZONTAL)
scrollbarI.pack(side=BOTTOM, fill=X)

scrollbarY = Scrollbar(output)
scrollbarY.pack(side=RIGHT, fill=Y)

scrollbarX = Scrollbar(output,orient=HORIZONTAL)
scrollbarX.pack(side=BOTTOM, fill=X)

outputLisbox = Listbox(output,yscrollcommand=scrollbarY.set,xscrollcommand=scrollbarX.set,width=80,height=6,font=('Calibri',10))                  
outputLisbox.pack(side=LEFT)                                                          

scrollbarX.config(command=outputLisbox.xview)
scrollbarY.config(command=outputLisbox.yview)

inputEntity = Entry(input,xscrollcommand=scrollbarI.set,width = 80,font=('Calibri',10))                            
inputEntity.pack(side=LEFT)                                                          

scrollbarI.config(command=inputEntity.xview)

debugListbox = Listbox(debug,width=80,height=6,font=('Calibri',10))
debugListbox.pack(side=LEFT)

combo_speed = ttk.Combobox(settings,values=[115200,76800,57600,38400,28800,19200,9600,4800,2400,1200,600,300])
combo_speed.current(0)
combo_speed.pack()

bt_chose_com = ttk.Button(settings, text = "Выбрать", command = fn_get_com)
bt_chose_com.pack(side=LEFT)

bt_send = Button(settings,text = "Отправить", command = fn_out)                   
bt_send.pack(side=RIGHT)                                                       

root.after(10,fn_disp)                                                      
root.mainloop() 