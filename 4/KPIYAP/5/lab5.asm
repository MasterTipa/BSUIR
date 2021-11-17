.model small
.stack 100h
.data
   
    counter dw 0
    buffer db 5 dup('$')
    file_path db 256 dup(0)
    result db "Number of blank lines is ", "$"
    number db 20 dup("$")
    error db "No args", 0ah, 0dh, "$"	
	errorPath db "No file", 0ah, 0dh, "$"	
	errorString db "So long str", 0ah, 0dh, "$"
	firstFlag dw 0	 								
	
.code  
.386   
setTwoAx proc
    mov ax,2
    ret
endp
main:
    mov ax,@data
	mov ds,ax
	
	mov bl, es:[80h]
	add bx, 80h
	mov si, 82h
	mov di, offset file_path
	
	cmp si, bx
    ja bad_arguments
    
get_path:
    cmp     BYTE PTR es:[si], '$' 
    je      n99
          
    mov     al, es:[si]
    mov     [di], al      
          
    inc     di
    inc     si
    cmp     si, bx
    jbe get_path

n99:        	
	lea dx, file_path
	mov ah, 3dh
	mov al, 00h
	int 21h
	jc exitWithout
	mov bx, ax
	            
    mov ax, 0
    push ax	            
	          
read_data:
    mov cx, 1
    lea dx, buffer
    mov ah, 3fh
    int 21h
    jc close_file1
	mov cx, ax
	jcxz close_file1

read_data_after:	
	pop ax
    inc ax
	push ax
	
	cmp buffer[0], 0dh ;flag 1 agree
	je end_of_line
	cmp buffer[0], 0ah
	je clear
	
	jmp searchEOS
           
clear:
    pop ax
    cmp ax, 1
    je n1
    cmp ax, 2
    je n2
    jmp n3
    n1: 
        push 0
        mov firstFlag,0
        push 0
        inc counter
        jmp read_data               
    n2:
        cmp firstFlag,0
        je n3
        mov firstFlag,0
        inc counter
        push 0
        jmp read_data
    n3:    
        push 0
        jmp read_data   
end_of_line:
    pop ax
    mov firstFlag,0
    cmp ax, 1  
    ;push 0    
    push ax
    je positive
    jmp read_data
positive:
    ;inc counter
    mov firstFlag,1
    jmp read_data	
close_file1:
    jmp close_file    
searchEOS:
    mov cx, 1
    lea dx, buffer
    mov ah, 3fh
    int 21h
    jc close_file
	mov cx, ax
	jcxz close_file
    mov ax, 2
    cmp buffer[0], 0dh
	je read_data_after
	cmp buffer[0], 0ah
	je read_data_after
    jmp searchEOS    

close_file:
    
    pop ax
    dec ax
    cmp ax, 0 
    jne positive2
    jmp @1
        
    positive2:
        inc counter
        
    @1:        
	mov ah, 3eh
	int 21h
	jmp exit	

exit: 
    lea dx, result
    call puts
    mov bx, counter
    call tostr 
    mov dx, si
    call puts
    mov ah,4ch
	int 21h
	ret
bad_arguments:
    lea dx, error
    call puts
    mov ah,4ch
	int 21h
	ret
close_file_error:   
	mov ah, 3eh
	int 21h
    lea dx, errorString
    call puts
	mov ah,4ch
	int 21h
	ret
exitWithout:
    lea dx, errorPath
    call puts
    mov ah,4ch
	int 21h
	ret

puts proc
    mov ah, 9
    int 21h
    ret
puts endp

gets proc
    mov ah, 0ah
    int 21h
    ret
gets endp  

tostr proc
        cmp bx, 0
        je zeroNum        
        mov ax, bx
        mov bx, 10
        mov dx, 0 
        lea si, number[10]
        toS:  
            cmp ax, 0
            je e1
            div bx                   
            add dx, "0"
            mov [si], dl
            mov dx, 0
            dec si
            jmp toS
         zeroNum:
            lea si, number[2]
            mov [si], "0"
            dec si
         e1:
            inc si      
    
    ret
tostr endp 
end main