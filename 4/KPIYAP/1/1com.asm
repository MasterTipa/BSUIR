.model tiny
.code
org 0x100              ;IP = 100h
start: 
    mov ah,0x9
    mov dx,offset message
    int 0x21
    ret                ;or int 0x20 
    message db "Hello World! I see you",0xD,0xA,'$'
end start         
