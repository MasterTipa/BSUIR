.model small                                         ;claim model
.stack 0x100                                         ;16 (h)
.code
start: 
    mov ax,@data                                     ;
    mov ds,ax                                        ;
    mov dx,offset message                            ;claim size of message
    mov ah,0x9                                       ;output command
    int 0x21                                         ;complite command
    mov ax,0x4C00                                    ;end command
    int 0x21                                         ;complite end
.data
    message db "Hello World! I see you ",0x1," ",0x3," ",0x15,0xD,0xA,'$'  ;temp message
end start                               