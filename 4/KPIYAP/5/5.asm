.model small
.stack 100h
.data    
	posInFile dw 0       
	degree dw 0
	maxNumOfString equ 23
	maxCMDSize equ 127
	cmd_size              db  ?
	cmd_text              db  maxCMDSize + 2 dup(0)
	sourcePath            db  maxCMDSize + 2 dup(0) 
	;sourcePath           db  "text.", 0
	buffer2               db  maxCMDSize + 2  dup(0)
	sourceID              dw  0             
	maxWordSize           equ 16
	buffer                dw  maxWordSize+1  dup(?)
	count 				  db 0      
	firstStrPtr 		  dw 0
	userIn 				  db ?       
	countStr 			  db 0           
	flag				  db 0
	EmptyStr			  dw 0

	spaceSymbol           equ ' '
	newLineSymbol         equ 0Dh
	returnSymbol          equ 0Ah
	tabulation            equ 9
	endl                  equ 0
    
	badCMDArgsMessage     db  "Bad command-line arguments. Only 1 argument required: source path",'$'
	badSourceText         db  "Cannot open source file", '$'
	fileNotFoundText      db  "File not found", '$'
	errorClosingSource    db  "Cannot close source file",'$' 
	errorReadSourceText   db  "Error reading from source file", '$'
.code  
.386
;*****************************************************************************************************************************
;putch macro symb            
;    push ax
;    push dx
;    mov ah, 02h                      
;    mov dl, symb
;    int 21h 
;    pop dx
;    pop ax
;endm
;*****************************************************************************************************************************
println MACRO info          
	push ax                 
	push dx         
	mov ah, 09h              
	lea dx, info             
	int 21h                                              
	mov dl, 0Ah              
	mov ah, 02h              
	int 21h                  
	mov dl, 0Dh                 
	mov ah, 02h             
	int 21h                  
	pop dx                  
	pop ax                  
ENDM
;*****************************************************************************************************************************
cmpWordLenWith0 MACRO textline, is0Marker       
	push si                                     
	lea si, textline                            
	call strlen                              
	pop si                                      
	cmp ax, 0                                   
	je is0Marker                                
ENDM
;*****************************************************************************************************************************
SETCURSOR MACRO R, C	  
    push ax
    push bx
    push dx
    MOV AH, 2
    XOR BH, BH			
    MOV DH, R			
    MOV DL, C			
    INT 10H           
    pop dx
    pop bx
    pop ax
ENDM         
;******************************************************************************************************************************       
setPosInFileTo MACRO symbolsInt, symbols;
	push ax                     
	push bx                     
	push cx                     
	push dx                     
    mov bx, sourceID                        
	mov ah, 42h                 
	xor al ,al 			        
	mov cx, symbolsInt           
	mov dx, symbols			     
	int 21h                     
	pop dx                      
	pop cx                      
	pop bx                      
	pop ax                      
ENDM 
;******************************************************************************************************************************
emptyPage MACRO
    push ax 
    push bx                             
	push cx                             
	push dx 
    MOV AH, 7h   	  	
    xor al,al
    XOR CX, CX
    MOV DX, 184FH     	
    MOV BH, 7			
    INT 10H  
    pop dx
    pop cx
    pop bx
    pop ax
ENDM
;******************************************************************************************************************************    
main:
		mov ax, @data            
		mov es, ax              
	    xor ch, ch               
		mov cl, ds:[80h]		 
		mov cmd_size, cl 		 
		mov si, 81h             
		lea di, cmd_text         
		rep movsb                                
		mov ds, ax                                                    
		call parseCMD            
		cmp ax, 0               
		jne endMain				 
		call openFiles           
		cmp ax, 0               
		jne endMain2			
		call displayPage     ;Редачить с этого места!!!!    
		cmp ax, 0                
		je endMain2		
		cmp ax,2 
		je endMain2	
	endMain2:                   
		call closeFiles         
		cmp ax, 0               
		jne endMain				
	endMain:    
		mov ah, 4Ch             
		int 21h                                             
;**************************************************************************************************************************
parseCMD PROC                                   
		push bx                                     
		push cx                                     
		push dx                                     
		mov cl, cmd_size                            
		xor ch, ch                                  
		lea si, cmd_text                                                                                      
		lea di, buffer2                                   
		call rewriteAsWord                                                                                     
		lea di, sourcePath                          
		call rewriteAsWord                          
		cmpWordLenWith0 sourcePath, badCMDArgs       
		lea di, buffer2                              
		call rewriteAsWord                          
		cmpWordLenWith0 buffer2, argsIsGood         
	badCMDArgs:                                     
		println badCMDArgsMessage                   
		mov ax, 1                                   
		jmp endproc                                 
	argsIsGood:                                     
		mov ax, 0                                   
	endproc:                                        
		pop dx                                      
		pop cx                                      
		pop bx                                      
		ret	                                        
ENDP
;*************************************************************************************************************************  
rewriteAsWord PROC              
		push ax                     
		push cx                     
		push di                     
		push bx
		push dx
		mov cx, maxCMDSize
	loopParseWord:                  
		mov al, ds:[si]             
		cmp al, spaceSymbol         
	    je isStoppedSymbol          
		cmp al, newLineSymbol       
		je isStoppedSymbol          
		cmp al, tabulation          
		je isStoppedSymbol          
		cmp al, returnSymbol        
		je isStoppedSymbol          
		cmp al, endl                
		je isStoppedSymbol          
		mov es:[di], al             
		inc di 
	nextLoopParseWord:
		inc si                      
		loop loopParseWord          
	isStoppedSymbol: 
		mov al, endl          
		mov es:[di], al             
		inc si 
	    pop dx
		pop bx
		pop di                      
		pop cx                      
		pop ax                      
		ret                         
ENDP   
;**************************************************************************************************************************  
strlen PROC                     
		push bx                     
		push si                     
		xor ax, ax                  
    startCalc:                  
	    mov bl, ds:[si]         
	    cmp bl, endl            
	    je endCalc              
	    inc si                  
	    inc ax                                                                       
	    jmp startCalc           
    endCalc:                    
		pop si                      
		pop bx                      
		ret                         
ENDP                            
;*************************************************************************************************************************
openFiles PROC                  
		push bx                     
		push dx                     
		push si                                     
		lea si, sourcePath                          
		call strlen              
		xor si, si         
		mov si, ax 
		sub si, 1                   
		cmp sourcePath[si], '.' 
		je checkFormat_Error   
		mov cx, ax
		sub cx,2
	loopDot:   
		sub si, 1
		cmp sourcePath[si], '.' 
		je checkFormat_OK  
		loop loopDot 
	checkFormat_Error: 
		pop si
		jmp badOpenSource       
	checkFormat_OK:                                            
		pop si  
		mov ah, 3Dh			        
		mov al, 02h			        
		lea dx, sourcePath          
		mov cx, 00h			        
		int 21h                     
		jb badOpenSource	        
		mov sourceID, ax	        
		mov ax, 0			         
		jmp endOpenProc		        
	badOpenSource:                  
		println badSourceText       
		cmp ax, 02h                 
		jne errorFound              
		println fileNotFoundText    
		jmp errorFound              
	errorFound:                     
		mov ax, 1                   
	endOpenProc:                    
		pop dx                      
		pop bx                      
		ret                         
ENDP                            
;******************************************************************************************************************************        
closeFiles PROC                 
		push bx                     
		push cx                     
		xor cx, cx                  
		mov ah, 3Eh                 
		mov bx, sourceID            
		int 21h                     
		jnb goodCloseOfSource		
		println errorClosingSource  
		inc cx 			            
	goodCloseOfSource:              
		mov ax, cx 		            
		pop cx                      
		pop bx                      
		ret                         
ENDP                            
;******************************************************************************************************************************
searchingEmptyStrings proc 
		pop ax
		inc ax
		push ax
	MyPain:	
		cmp buffer[0], 0dh
		je end_of_line
		cmp buffer[0], 0ah
		je clear

		jmp read_data
	
	clear:
	    pop ax
		cmp ax,1	
	    ;cmp flag, 1
	    je n1
	    jmp n2
	    n1: 
	        push 0
			;mov flag,0
	        jmp read_data               
	    n2:
	        inc EmptyStr
			;mov flag,0
	        push 0
	        jmp read_data
	
	end_of_line:
	    pop ax
	    dec ax
		;dec flag
	    ;cmp flag, 0 
		cmp ax, 0 
	    push 0
		;mov flag,0
	    je positive
	    jmp read_data
	positive:
	    inc EmptyStr
	    jmp read_data	
	read_data:
	
	    ret
endp
;******************************************************************************************************************************
displayPage PROC        
		push bx                             
		push cx                             
		push dx                             
		push si                             
		push di                             
    	call readFromFile                   
		cmp ax, 0                           
		je finishProcessing3                
    	setCursor 0,0 
    	emptyPage
    	mov countStr,0
	startLoopProcessing:                                        
		lea si, buffer
		mov cx, ax					        
	startLoopProcessing2:	
	    cmp countStr,maxNumOfString 
	    je finishProcessing2    
	    add countstr,1
		mov count,0
		mov ax,0
		push ax
	loopProcessing:                         
		call searchingEmptyStrings
		
	nextProcessing:
		dec cx
		call checkEndBuff                   
		cmp ax, 2                           
		je finishProcessing                 
		cmp ax, 1                           
		je startLoopProcessing2    
		cmp ax,0
		je loopProcessing
	finishProcessing2:
		mov ax,1   
		jmp finishProcessing1
	finishProcessing3:
	    cmp userIn,51h
	    je  finishProcessing4
	    mov ax,2 
	    sub firstStrPtr,1
	    jmp finishProcessing1
	finishProcessing4:
	    mov ax,2 
	    sub firstStrPtr, maxNumOfString
	    jmp finishProcessing1                                 
	finishProcessing:                       
	    mov ax,0  
	
	finishProcessing1:
		mov ax, EmptyStr
		mov bx,10
    	mov cx,0
    
    _loop:
        mov dx,0
        div bx          ;/ (IDIV)
        cmp ax,0    
        je dxing
        add dx,'0'
        push dx
        inc cx
        jmp _loop
    
    dxing:
        cmp dx,0
        je stringing
        add dx,'0'
        push dx
        inc cx
        jmp stringing    
    
    stringing:
        pop dx
        mov ah, 02h;
        int 21h
		loop stringing
    
	    pop di                               
		pop si                              
		pop dx                              
		pop cx                              
		pop bx                              
		ret                                 
ENDP                                    
;************************************************************************************************************************** 
readFromFile PROC                   
		push bx                         
		push cx                         
		push dx                         
    	;setPosInFileTo degree,posInFile                              
		mov ah, 3Fh                     
		mov bx, sourceID                
		mov cx, 1             
		lea dx, buffer                  
		int 21h 
		;add posInFile,ax                        
		jnb goodRead					
		println errorReadSourceText     
		mov ax, 0                       
	goodRead:

	    cmp posInFile,65520
	    je checkRead
	    jmp endRead1
	checkRead:   
	    cmp ax,maxWordSize
	    jne endRead1
	    add degree,1
	    mov posInFile,0
	    jmp endRead2
	endRead1:                            
	    add posInFile,ax         
	endRead2:                       
		pop dx                          
		pop cx                          
		pop bx                          
		inc flag
		ret                             
ENDP                                
;*****************************************************************************************************************************
checkEndBuff PROC               
		cmp cx, 0                   
		jne notEndOfBuffer          
	skipWrite:  
		call readFromFile           
		cmp ax, 0                   
		je endOfProcessing          
	    lea si,buffer               
		mov cx, ax					
		mov ax, 1                   
		ret                         
	endOfProcessing:                
		mov ax, 2                   
		ret                         
	notEndOfBuffer:                 
		mov ax, 0                   
		ret                         
ENDP                            
;*******************************************************************************************************************************
;_output_number proc
;
;    mov bx,10
;    mov cx,0
;    
;    _loop:
;        mov dx,0
;        div bx          ;/ (IDIV)
;        cmp ax,0    
;        je dxing
;        add dx,'0'
;        push dx
;        inc cx
;        jmp _loop
;    
;    dxing:
;        cmp dx,0
;        je stringing
;        add dx,'0'
;        push dx
;        inc cx
;        jmp stringing    
;    
;    stringing:
;        pop dx
;        mov ah, 02h;
;        int 21h
;		loop stringing
;    return:
;        ret    
;    
;endp     
end main