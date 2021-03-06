.model small

.stack 100h

.data    

posInFile dw 0       
degree dw 0

maxNumOfString equ 23   ;???????????? ?????????? ????? ,??????? ????? ???? ???????? ?? ??????


maxCMDSize equ 127
cmd_size              db  ?
cmd_text              db  maxCMDSize + 2 dup(0)
sourcePath            db  maxCMDSize + 2 dup(0) 
buffer2                db  maxCMDSize + 2  dup(0)
;sourcePath            db  "text.", 0
       
                      
sourceID              dw  0
                      
maxWordSize           equ 16
buffer                db  maxWordSize  dup(0)
count db 0      
firstStrPtr dw 0    ;????????? ?? ?????? ?????? ?????? (0,1,2...)
 
userIn db ?   ;????????????? ???????????????? ????
                  
countStr db 0                      ;??????? ????? (?? ???? ??????? ????? ?? ?????? ????????)
                            
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
;**************************************************
putch macro symb            ;??????? ??????? ?? ?????
    push ax
    push dx
    mov ah, 02h                      
    mov dl, symb
    int 21h 
    pop dx
    pop ax
endm    

println MACRO info          ;
	push ax                 ;
	push dx                 ;
                            ;
	mov ah, 09h             ; ??????? ?????? ?????? ?? ?????
	lea dx, info            ; ???????? ? dx ???????? ?????????? ?????????
	int 21h                 ; ????? ??????????? ??? ?????????? ??????
                            ;
	mov dl, 0Ah             ; ?????? ???????? ?? ????? ??????
	mov ah, 02h             ; ??????? ?????? ???????
	int 21h                 ; ????? ??????????
                            ;
	mov dl, 0Dh             ; ?????? ???????? ? ?????? ??????   
	mov ah, 02h             ;
	int 21h                 ;            ==//==
                            ;
	pop dx                  ;
	pop ax                  ;
ENDM

main:
	mov ax, @data           ; ????????? ??????
	mov es, ax              ;
    
	

	xor ch, ch              ; ???????? ch
	mov cl, ds:[80h]		; ??????? ??? ?????????? ?????? ? ???????? ???????
	mov cmd_size, cl 		; ? cmd_size ????????? ????? ????????? ??????
	mov si, 81h             ;
	lea di, cmd_text        ; ????????? ? di ???????? ?????? ??????????? ????? ????????? ??????
	rep movsb               ; ???????? ? ?????? ??????? ES:DI ???? ?? ?????? DS:SI
                            ;
	mov ds, ax              ; ????????? ? ds ??????
                            ;
	
                            ;
	call parseCMD           ; ????? ????????? ???????? ????????? ??????
	cmp ax, 0               ;
	jne endMain				; ???? ax != 0, ?.?. ??? ????????? ????????? ????????? ?????? - ????????? ? ????? ?????????, ?.?. ??????? ? endMain
                            ;
	call openFiles          ; ???????? ?????????, ??????? ????????? ??? ????? ??? ??????/??????
	cmp ax, 0               ;
	jne endMain2				;  ==//==
                            ;
	call displayPage     ; ??????? ?????????, ? ??????? ?????????? ???? ???????? ????????? ?????
	cmp ax, 0               ; 
	je endMain2		
	cmp ax,2 
	je endMain2
	
userInput:
mov degree,0
mov posinfile,0
    MOV AH, 0
    INT 16H
    MOV USERIN, AH 
    
    CMP USERIN, 48H        ;up
    jne next1    
    
up: 
    cmp firstStrPtr,0
    je userInput   
    
    sub firstStrPtr ,1
   
    ;cmp firstStrPtr,4096  ;2^16/16      
    mov ax,firstStrPtr
      
   
    xor dx,dx
    mov bx,4096
    div bx
    cmp ax,0 
    
    
   
    
    je nextup 
    add degree,ax   
    mov ax,dx
    jmp nextUp2
    

nextUp: 
     mov ax, firstStrPtr  
nextUp2:     
    xor dx,dx   
    mov bx,16 
    mul bx
    mov posInFile,ax  
    ;sub posInFile ,1
    
    call displayPage
     jmp userInput
    
next1: 
    CMP USERIN, 50H         ;DOWN
	JNE NEXT2   
    
down:
   
     
     add firstStrPtr ,1 
    
     
     mov ax,firstStrPtr  
    
  xor dx,dx
    mov bx,4096
    div bx
    cmp ax,0 
    
    
   
    
    
   
    je nextDown
    add degree,ax  
     mov ax,dx
    jmp nextDown2

nextDown: 
 mov ax, firstStrPtr
 nextDown2: 
    xor dx,dx   
    mov bx,16 
    mul bx
    mov posInFile,ax 
   ; sub posInfile,1
    call displayPage  
    jmp userInput
	
next2:
    CMP USERIN, 49H         ;pageUp
	JNE NEXT3
pageUp:
    cmp firstStrPtr,0
    je userInput	 
    cmp firstStrPtr, maxNumOfString 
    jb toFirstPage
    sub firstStrPtr,maxNumOfString   
    mov ax,firstStrPtr
      
   
    xor dx,dx
    mov bx,4096
    div bx
    cmp ax,0 
    
    
   
    
    je nextpageup 
    add degree,ax   
    mov ax,dx
    jmp nextPageUp2
    

nextpageUp: 
     mov ax, firstStrPtr  
nextPageUp2:     
    xor dx,dx   
    mov bx,16 
    mul bx
    mov posInFile,ax  
nextPageUP3:    
    
    call displayPage
    
     jmp userInput
toFirstPage: 
    mov firstStrPtr,0
    mov degree,0
    mov posInFile,0  
    jmp nextPageUP3
       
	
next3:	 
    CMP USERIN, 51H         ;pageDown
	JNE NEXT4     
PageDown:  
    add firstStrPtr,maxNumOfString 
      mov ax,firstStrPtr  
    
  xor dx,dx
    mov bx,4096
    div bx
    cmp ax,0 
    
    
   
    
    
   
    je nextPageDown
    add degree,ax  
     mov ax,dx
    jmp nextPageDown2

nextPageDown: 
 mov ax, firstStrPtr
 nextPageDown2: 
    xor dx,dx   
    mov bx,16 
    mul bx
    mov posInFile,ax 
  
    call displayPage  
    jmp userInput
    	
	
next4:  
cmp userIn,10H
je endMain2   
    jmp userInput
   
    
endMain2:			;  ==//==
                            ;
	call closeFiles         ; ???????? ????????? ??????????, ???????? ????????? ???????? ??????
	cmp ax, 0               ;
	jne endMain				;  ==//==
                            ;
endMain:                    ;
	       ; ??????? ????????? ? ?????????? ?????? ?????????
                            ;
	mov ah, 4Ch             ; ????????? ? ah ??? ??????? ?????????? ??????
	int 21h                 ; ????? ?????????? DOS ??? ?? ??????????


cmpWordLenWith0 MACRO textline, is0Marker       ; ????????? ?????? ? ?????, 1 ???????? - ??????, 2 ??????? ???????? ??? 0
	push si                                     ; ?????????? ???????? ???????? si
	                                            ;
	lea si, textline                            ; ????????? ? si ???????? ??????, ? ??????? ???????? ??????
	call    strlen                              ; ???????? ?-??? ?????????? ????? ?????? textline, ????????? -> ax
	                                            ;
	pop si                                      ; ??????????????? ???????? si
	cmp ax, 0                                   ; ?????????? ????????? ?????? ? ?????
	je is0Marker                                ; ???? ????? ????? ???? -> ????????? ?? ?????????? ????? is0Marker
ENDM                                            ;                               ;
                                                ; 
                                                                                        ;                               ;
                                                        
                                                ;
;**************************************************************************************************************************
parseCMD PROC                                   ;
	push bx                                     ;
	push cx                                     ;
	push dx                                     ; ?????????
                                                ;
	mov cl, cmd_size                            ; ????????? ? cl ?????? ???????? ??????
	xor ch, ch                                  ; ???????? ch
                                                ;
	lea si, cmd_text                            ; ? si ????????? ???????? ?????? ?? ???????? ??????
	                                            ;                                                          
	lea di, buffer2                              ;(?????????? ????????) ? di ????????? ???????? ??????? ??? ????????? ??????      
	call rewriteAsWord                          ;                                                           
                                                ;                                                           
	lea di, sourcePath                          ;(????) ????????? ? di ???????? sourcePath ?.?. ????????? ?????? ??? ?????????
	call rewriteAsWord                          ;
                                                ;
	cmpWordLenWith0 sourcePath, badCMDArgs      ; ???? ??????, ?????????? ???????? ???????? ????? ?????, ??????? ? badCMDArgs  
	
                                                ; 
	lea di, buffer2                              ; 
	call rewriteAsWord                          ;
                                                ;
	cmpWordLenWith0 buffer2, argsIsGood          ; ???? ?????? ?????? ???, ?.?. ????? ???????? ????????? ? ????????? ?????? ????????? ?????? ?????? ?? ????????
                                                ; ?? ????? ????????? ?????????? - ??????? ? argsIsGood
badCMDArgs:                                     ;
	println badCMDArgsMessage                   ; ??????? ????????? ? ???????? ?????????? ????????? ??????
	mov ax, 1                                   ; ?????????? ? ax ??? ??????
                                                ;
	jmp endproc                                 ; ??????? ? endproc ? ????????? ?????????
                                                ;
argsIsGood:                                     ;
	mov ax, 0                                   ; ?????????? ? ax ??? ????????? ?????????? ?????????
endproc:                                        ;
	pop dx                                      ;
	pop cx                                      ;
	pop bx                                      ; ??????????????? ???????? ????????? ? ??????? ?? ?????????
	ret	                                        ;
ENDP
;*************************************************************************************************************************  
  
;*************************************************************************************************************************
;cx - ????? ????????? ??????
;????????? - ???????????? ???????? ?? ?????????? ?????? 
rewriteAsWord PROC              ;
	push ax                     ;
	push cx                     ;
	push di                     ; ????????? ????????
	push bx
	push dx
	
	mov cx,maxCMDSize
	
loopParseWord:                  ;
	mov al, ds:[si]             ; ????????? ? al ??????? ??????
	
	cmp al, spaceSymbol         ; -------------------
    je isStoppedSymbol          ;                                 ;
	cmp al, newLineSymbol       ;
	je isStoppedSymbol          ;         ???? ???? ?????? ?????            ;
	cmp al, tabulation          ;   ???????, ?????????, 0Ah, 0Dh ??? \0
	je isStoppedSymbol          ;     ?????? ???????? ?? ????? ??  ????? ?????
	cmp al, returnSymbol        ;
	je isStoppedSymbol          ;                                        ;
	cmp al, endl                ;
	je isStoppedSymbol          ;
                                ;
	mov es:[di], al             ; ???? ?????? ?????? ?????? ? ?????, ????????? ??? ? ?????????????? ??????
	
                                ;

	inc di 
	; ??????????? di,si ?.?. ????????? ?? ????????? ??????
nextLoopParseWord:
	inc si                      ;
                                ;
	loop loopParseWord          ; ???? ?? ????????? ???????????? ????? ?????, ??????

isStoppedSymbol: 
	
	mov al, endl          ;
	mov es:[di], al             ; ????????? ?????? ????? ?????? ? ?????????????? ??????
	inc si 
	; ??????????? si ??? ???????? ?? ????????? ?????? ????????? ??????
    pop dx
	pop bx
	pop di                      ; ??????????????? ????????
	pop cx                      ;
	pop ax                      ;
	ret                         ;
ENDP   
;**************************************************************************************************************************  
  
;*************************************************************************************************************************
;ds:si - ????????, ? ??????? ????????? ?????? ??????
;????????? - ? ax ?????????? ????? ?????? 
strlen PROC                     ;
	push bx                     ;
	push si                     ;  ????????? ???????????? ????? ????????
	                            ;
	xor ax, ax                  ;  ???????? ax
                                ;
    startCalc:                  ;
	    mov bl, ds:[si]         ;  ????????? ????????? ?????? ?????? ?? ds ?? ????????? si
	    cmp bl, endl            ;  ?????????? ???? ?????? ? ???????? ????? ??????
	    je endCalc              ;  ???? ??? ?????? ????? ?????? - ??????? ? endCalc ? ??????????? ??????????
                                ;
	    inc si                  ;  ??????????? si, ?.?. ????????? ? ?????????? ???????
	    inc ax                  ;  ??????????? ax, ?.?. ????? ??????                                                     
	    jmp startCalc           ;  ??????????
	                            ;
    endCalc:                    ;
	pop si                      ;
	pop bx                      ;  ??????????????? ????????
	ret                         ;
ENDP                            ;
;*************************************************************************************************************************

;**************************************************************************************************************************
;????????? ? ax - 0 ???? ??? ??????
openFiles PROC                  ;
	push bx                     ;
	push dx                     ; ????????? ???????? ?????????          
	
	
	;;;;;;;;;
	push si                                     
	                                            
	lea si, sourcePath                          
	call    strlen               ;ax               
	    
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
	       
	checkFormat_OK:                                            ;
	pop si  
	
	;;;;;;;
                                ;
	mov ah, 3Dh			        ; ??????? 3Dh - ??????? ???????????? ????
	mov al, 02h			        ; ????? ???????? ?????
	lea dx, sourcePath          ; ????????? ? dx ???????? ????????? ?????
	mov cx, 00h			        ; ????? ????????? ?????
	int 21h                     ;
                                ;
	jb badOpenSource	        ; ???? ???? ?? ????????, ?? ??????? ? badOpenSource
                                ;
	mov sourceID, ax	        ; ????????? ? sourceId ???????? ?? ax, ?????????? ??? ???????? ?????
                                ;
	mov ax, 0			        ; ????????? ? ax 0, ?.?. ?????? ?? ????? ?????????? ????????? ?? ???????? 
	jmp endOpenProc		        ; ??????? ? endOpenProc ? ????????? ??????? ?? ?????????
                                ;
badOpenSource:                  ;
	println badSourceText       ; ??????? ?????????????? ?????????
	cmp ax, 02h                 ; ?????????? ax ? 02h
	jne errorFound              ; ???? ax != 02h - ???? ??????, ??????? ? errorFound
                                ;
	println fileNotFoundText    ; ??????? ????????? ? ???, ??? ???? ?? ?????? 
                                ;
	jmp errorFound              ; ??????? ? errorFound
                                ;       ;       ==//==                               ;
errorFound:                     ;
	mov ax, 1                   ; ????????? ? ax 1, ?.?. ????????? ??????
endOpenProc:                    ;
	pop dx                      ;
	pop bx                      ; ??????????????? ???????? ????????? ? ??????? ?? ?????????
	ret                         ;
ENDP                            ;
;******************************************************************************************************************************        
 
;**************************************************************************************************************************
closeFiles PROC                 ;
	push bx                     ;
	push cx                     ; ????????? ???????? ????????? 
                                ;
	xor cx, cx                  ; ???????? cx
                                ;
	mov ah, 3Eh                 ; ????????? ? ah ??? 3Eh - ??? ???????? ?????
	mov bx, sourceID            ; ? bx ????????? ID ?????, ??????????? ????????
	int 21h                     ; ???????? ?????????? ??? ?????????? 
                                ;
	jnb goodCloseOfSource		; ???? ?????? ??? ???????? ?? ?????????, ??????? ? goodCloseOfSource
                                ;
	println errorClosingSource  ; ????? ??????? ?????????????? ????????? ?? ??????       
	                            ;
	inc cx 			            ; now it is a counter of errors
                                ;
goodCloseOfSource:              ;               ;
	mov ax, cx 		            ; ?????????? ? ax ???????? ?? cx, ???? ?????? ?? ?????????, ?? ??? ????? 0, ????? 1 ??? 2, ? ??????????? ??
                                ; ?????????? ????????????? ??????
	pop cx                      ;
	pop bx                      ; ??????????????? ???????? ????????? ? ??????? ?? ?????????
	ret                         ;
ENDP                            ;
;******************************************************************************************************************************
SETCURSOR MACRO R, C	;????????? ??????? ? ???????? ?????????  
    push ax
    push bx
    push dx
    MOV AH, 2
    XOR BH, BH			;???????? ????? ?????????????
    MOV DH, R			;????? ??????
    MOV DL, C			;????? ???????
    INT 10H           
    pop dx
    pop bx
    pop ax
ENDM         
;******************************************************************************************************************************       
setPosInFileTo MACRO symbolsInt, symbols;
	push ax                     ;
	push bx                     ;
	push cx                     ;
	push dx                     ; ????????? ???????? ?????????
    mov bx, sourceID                        ;
	mov ah, 42h                 ; ?????????? ? ah ??? 42h - ?-??? DOS ????????? ????????? ?????
	xor al ,al 			        ; ???????? al, ?.?. al=0 - ??? ??????????? ????????? ? ?????? ?????
	mov cx, symbolsInt          ; ???????? cx, 
	mov dx, symbols			    ; ???????? dx, ?.? ????????? ????????? ?? 0 ???????? ?? ?????? ????? (cx*2^16)+dx 
	int 21h                     ; ???????? ?????????? DOS ??? ?????????? ????????   
                                ;
	pop dx                      ; ??????????????? ???????? ????????? ? ??????? ?? ?????????
	pop cx                      ;
	pop bx                      ;
	pop ax                      ;
ENDM 
;******************************************************************************************************************************
outputSymbHex proc 
push cx
push ax

	mov cl,4
	mov ch,0
	lodsb
	mov bl,16
toHex:	
    
	 xor ah,ah
	div bl
	cmp ah,10
	je A
	cmp ah,11
	je B 
	cmp ah,12
	je C 
	cmp ah,13
	je D
	cmp ah,14
	je E
	cmp ah,15
	je F  
	add ah,'0'
	mov dl,ah
	xor dh,dh
	push dx  
	inc ch
nextToHex:
	
	
	cmp al,0
	jne toHex
	
	jmp writeHex
A:
	mov dl,'A'
	xor dh,dh
	push dx
	inc ch
	jmp nextToHex
B:
	mov dl,'B'
	xor dh,dh
	push dx
	inc ch
	jmp nextToHex
C:
	mov dl,'C'
	xor dh,dh
	push dx
	inc ch
	jmp nextToHex
D:
	mov dl,'D'
	xor dh,dh
	push dx 
	inc ch
	jmp nextToHex
E:
	mov dl,'E'
	xor dh,dh
	push dx
	inc ch
	jmp nextToHex
F:
	mov dl,'F'
	xor dh,dh
	push dx
	inc ch
	jmp nextToHex
writeHex:
	
	sub cl,ch
	mov dh,'0'
loopZero:
    
	putch dh 
	
	dec cl
	cmp cl,0
jne loopZero

loopNumber:
	pop dx
	putch dl 
	dec ch
	cmp ch ,0
	jne loopNumber
	
	pop ax
	pop cx
   ret
  endp


          
;******************************************************************************************************************************



emptyPage MACRO
    push ax 
    push bx                             ;
	push cx                             ;
	push dx 
    MOV AH, 7h   	  	;??????? 6. ???????? ???? ?????.
    xor al,al
    XOR CX, CX
    MOV DX, 184FH     	;?????? ?????? ???? ??????. ??????=24 (18h), ???????=79 (4fh)
    MOV BH, 7			;????? ?? ???????
    INT 10H  
    pop dx
    pop cx
    pop bx
    pop ax
ENDM
;******************************************************************************************************************************    
displayPage PROC                     ;
	                         ;
	push bx                             ;
	push cx                             ;
	push dx                             ;
	push si                             ;
	push di                             ; ????????? ???????? ?????????
    
                                     ;
	                   ; ????????? ? bx ID ?????-????????? 
	
	               ; ???????? ???????? ???????? ??????? ? ?????? ?????
                                        ;
    call readFromFile                   ; ????? ????????? ?????? ?? ?????
	                                    ;
	cmp ax, 0                           ; ??????????? ah ? 0 ??? ???????? ?? ????? ?????
	je finishProcessing3                 ; ???? ah == 0, ?? ?????? ???? ? ?? ????? ?? ????? ?????
      setCursor 0,0 
     emptyPage
    mov countStr,0
startLoopProcessing:                                        ;
	lea si, buffer                      ; ????? ????????? ? si 
	
	mov cx, ax					        ; ? cx ????????? ax, ?.? ???-?? ????????? ? ??????? (???-?? ????????? ????????? ? ?????)
startLoopProcessing2:	

      cmp countStr,maxNumOfString 
    je finishProcessing2    
      	
     add countstr,1
	
	
	
   	
	
	mov count,0
loopProcessing:                         ;
	call outputSymbHex
	add count,1
	cmp count,16
	je goToNewLine
	mov al,' '
	putch al
	
	cmp count,8
	je twoSpace
	
nextProcessing:

	dec cx
	call checkEndBuff                   ; ???????? ????????? ???????? ????? ???????, ???? ?????? ???? - ?????????? ?????? ?? ?????
	cmp ax, 2                           ; ???? ????? ?????? ????????? checkEndBuff ? ax ????? 2, ?? ??????????? ????????? - ??????? ? ax
	je finishProcessing                 ; ??????? ? finishProcessing
	cmp ax, 1                           ; ==//== ? ax ????? 1, ?? ?????? ??? ???? ? ???? ?????????? ????? ?????? ?? ?????
	je startLoopProcessing2    
	cmp ax,0
	je loopProcessing
	
twoSpace:
	mov al,' '
	putch al
	jmp nextProcessing
goToNewLine:
	
	
    jmp nextProcessing                                    ;
	                 ;
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
   jmp finishProcessing1                                 ;
finishProcessing:                       ;
   mov ax,0  
finishProcessing1:
                                        ;
	pop di                              ; ??????????????? ???????? 
	pop si                              ;
	pop dx                              ;
	pop cx                              ;
	pop bx                              ;
	                            ;
	ret                                 ;
ENDP                                    ;
;************************************************************************************************************************** 
;*****************************************************************


   
;*****************************************************************************************************************************   
;reads to buffer maxWordSize symbols
;?????????: ? ax ?????????? ????-?? ????????? ?? ????? ????????
readFromFile PROC                   ;
	push bx                         ;
	push cx                         ;
	push dx                         ; ????????? ???????? ?????????
    setPosInFileTo degree,posInFile                              ;
	mov ah, 3Fh                     ; ????????? ? ah ??? 3Fh - ??? ?-??? ?????? ?? ?????
	mov bx, sourceID                ; ? bx ????????? ID ?????, ?? ???????? ?????????? ?????????
	mov cx, maxWordSize             ; ? cx ????????? ???????????? ?????? ?????, ?.?. ????????? ???????????? ???-?? ???????? (maxWordSize ????????)
	lea dx, buffer                  ; ? dx ????????? ???????? ???????, ? ??????? ????? ????????? ?????? ?? ?????
	int 21h                         ; ???????? ?????????? ??? ?????????? ?-???
                                    ;
	jnb goodRead					; ???? ?????? ?? ????? ??????? ?? ????????? - ??????? ? goodRead
                                    ;
	println errorReadSourceText     ; ????? ??????? ????????? ?? ?????? ?????? ?? ?????
	mov ax, 0                       ; ?????????? ? ax 0
                                    ;
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
endRead1:                         ;   
    add posInFile,ax         
endRead2:                       ;
	pop dx                          ; ??????????????? ???????? ?????????
	pop cx                          ;
	pop bx                          ;
	ret                             ;
ENDP                                ;
;*****************************************************************************************************************************
             
;*****************************************************************************************************************************             
                              ;
;******************************************************************************************************************************
               
;******************************************************************************************************************************               
;?????????: ???????? ? ax -
;	ax = 0 - ?????? ??? ?? ????, ?.?. ??? ???? ?????? ??? ?????????
;	ax = 1 - ?????? ??? ?????????, ?????? ????????, ? ????? "?????" ????? ??? ????????? ? ?????? 
;	ax = 2 - ?????? ??? ?????????, ?????? ????????, ???? ????????? ??????? ???????? ??????, ?? ????????? ??? ????? ?? ????? ?????
checkEndBuff PROC               ;
	cmp cx, 0                   ; ?????????? cx ? ?????
	jne notEndOfBuffer          ; ???? cx != 0, ?? ?????? ??? ?? ????????? ???????, ??????? ? notEndOfBuffer
                                ;
	
                                ;
skipWrite:  
    
                          ;
	call readFromFile           ; ????????? ????? ?????
	cmp ax, 0                   ; ?????????? ax ? ?????, ???? ax == 0, ?? ????????? ??????, ????????????? ????????? ? endOfProcessing
	je endOfProcessing          ;
    lea si,buffer                            ;
	
	mov cx, ax					; ?????????? ? cx ???-?? ???????? ? ??????? ?? ax
	
                                ;
	mov ax, 1                   ; ?????????? ? ax - ????? ???????
	ret                         ;
                                ;
endOfProcessing:                ;
	mov ax, 2                   ; ????? ????????? - ???????? ? ax ???????? ??? 2
	ret                         ;
                                ;
notEndOfBuffer:                 ;
	mov ax, 0                   ; ???? ?????? ??? ?? ???????? - ?????????? ???????? ??? 0
	ret                         ;
ENDP                            ;
;*******************************************************************************************************************************

end main