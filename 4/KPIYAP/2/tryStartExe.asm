.model small                                         
.stack 0x100
.code
start: 
    mov ax,@data                                     
    mov ds,ax                                        


    mov ah,0x4C                                    
    int 0x21                                         
.data
    message db "Hello World! I see you",0xD,0xA,'$' 
end start  