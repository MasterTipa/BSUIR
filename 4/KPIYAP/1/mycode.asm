.model tiny
.code
org 0x100
start: mov ah,0x9
mov dx,offset message
int 0x21
ret
message db "Hello World! Gay, I see you",0xD,0xA,'$'
end start         

;.model small
;.stack 0x100
;.code
;start: mov ax,@data
;mov ds,ax
;mov dx,offset message
;mov ah,0x9
;int 0x21
;mov ax,0x4C00
;int 0x21
;.data
;message db "Hello World! Gay, I see you",0xD,0xA,'$'
;end start  
