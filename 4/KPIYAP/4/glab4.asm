;          ||| 2048 GAME  |||           ;
.MODEL SMALL
.STACK 100H
.DATA
columns equ 5
rows equ 5
fieldSize equ rows * columns
ARR DB (rows*columns+2) DUP(0)
SCORE DW 0
CSR DB 0		;CURSOR ROW POSITION
CSC DB 0 		;CURSOR COLUMN POSITION
CHOISE DB 0		;FOR GAME MODE
LEN DB 0
FLAG DB 'A'     ;если A то генерируется 2, если В -4
BEG DB 0        ;с этого элемеента начинаем поиск свободной клетки
DONE DB 0       ;1-были изменения при нажатии клавиш, 0-не было
TSC DW 1
USERIN DB ?
TMP DW ?
TMP1 DB ?
TMP2 DB ?
TMP3 DB ?
FLAG2 DB 0
MODE DB 0
STR1 DB "YOU LOSE...$"
STR2 DB "YOU WIN!$"
STR5 DB "GAME ENDED$"
STR7 DB "SCORE: $"
STR8 DB "2048 GAME$"
STR9 DB "START GAME$"
STR11 DB "EXIT$"
STRZ DB 2 DUP("$")
.CODE         
 .386
NEW_LINE macro          ;переход на следующую строку
    mov AH, 2H			;вывод на дисплей
    mov DL, 0DH			;символ, выводимый в стандартный вывод
    int 21H
    mov DL, 0AH
    int 21H
endm
CLRSCR macro
    mov AH, 6h   	  	;функция 6. Очистить весь экран.
    xor AL, AL			;пустое, поэтому всё очищаем
    xor CX, CX			;пустое, поэтому начинаем с нуля (0,0)
    mov DX, 184FH     	;правый нижний угол экрана. Строка=24 (18h), столбец=79 (4fh)
    mov BH, 7			;белый по черному
    int 10H
endm
MOVCURSOR_R macro		;смещение курсора вправо
    mov AH, 3			;запоминаем текущее положение курсора
    xor BH, BH
    int 10H				;записываем в DX строку и столбец текущего положения, в CX размер курсора
    mov AH, 2			;установка курсора
    INC DL				;увеличиваем позицию столбца
    int 10H
endm
SETCURSOR macro R, C	;установка курсора в заданное положение
    mov AH, 2
    xor BH, BH			;зануляем номер видеостраницы
    mov DH, R			;номер строки
    mov DL, C			;номер столбца
    int 10H
endm
NUMS proc
NUMBERS:
	mov DL,done      ;текущий элемент масссива
    mov CX, 4        ;в сх заносим 4 , так как надо вывести 4 символа   
    cmp DL, 0        ;если текущий элемент пустая ячейка , то выводим 4 пробела
    JE LP4           
    mov AX, 1            
    xor CX,CX
    mov CL, DL
    sub CL, 'A'
    add CL, 1                        
    sal AX, CL                 ;A,B,C,D...K   сдвигаем число, сод в AX на CL элементов
	                           ;1,2,3,4...11
      						 ;циклический сдвиг влево числа 1 на число элемеентов сверху
	                           ;10,100,1000,10000....
							   ;2,4,8,16...2048
    mov LEN, 0     		;счетчик количества цифр
    mov BL, 10          ;будем делить на 10 а остаток от деления очередная цифра числа с конца
LP1:
	div BL
	xor CX,CX
	mov CL, AH
	add CL, '0'
	push CX          ;найденные цифры заносим в стек
	add LEN, 1		;inc len
	xor AH,AH
	cmp AL, 0             ;пока целая часть от делеения не ноль продолжаем делить
	JNE LP1
	mov AL, 4            ;число имеет максимум 4 цифры
	sub AL, LEN              ;вычитаем реальное количество,чтобы недостающие цифры вывести пробелами
	cmp AL, 0
	JE CNT
	xor CX,CX
	mov CL, AL
	mov AH, 2
	mov DL, ' '
LP2:
    int 21H
    LOOP LP2                     ;выводим недостающие пробелы
CNT:
LP3:
	sub LEN, 1		;dec len
	pop AX          ;в AL символ-цифра
	mov AH, 9
	xor BH, BH
	mov CX, 1
	mov BL, 25H          ;цвет (00100101) 001 - цвет символа (синий) 0 - символ яркого цвета 010 - цвет фона (зеленый) 1 - мигание символа или фон яркого цвета 
	int 10H
	MOVCURSOR_R
	cmp LEN, 0
	JNE LP3
	mov DL, ' '
	int 21H
	JMP OUTStr
	mov CX, 4
LP4:            ;если 0 то выводим пустоую клетку то есть пробелы
	mov AH, 2H
	mov DL, ' '
	int 21H
	LOOP LP4
    int 21H
OUTStr:
ret
endp
 C_SCORE proc
   mov AX, SCORE
   mov DX, 0
   mov BX, 10
   mov LEN, 0
L1:
    mov DX, 0
    div BX
    push DX
    add LEN, 1 			; inc len	
    cmp AX, 0			
    JNE L1
	SETCURSOR 23, 25	; устанавливаем положение курсора для вывода сообщения score:
	mov AH, 9
	lea DX, STR7
	int 21H
L2:
    pop DX				
    add DL, 48			; '0'
    sub LEN, 1			; dec len
    mov AH, 2
    int 21H
    cmp LEN, 0
    JNE L2
ret
endp
 UNDERLINE proc          ;рисуем линию подчеркивания
    mov LEN, 10
UND:
	sub LEN, 1			;dec len
	mov AH, 2
	mov DL, '_'
	int 21H
	cmp LEN, 0
	JNE UND
	ret
endp
 UNUNDERLINE proc      ;стираем линию подчеркивания
    mov LEN, 10
UNUND:
	sub LEN, 1			;dec len
	mov AH, 2
	mov DL, ' '
	int 21H
	cmp LEN, 0
	JNE UNUND
	ret
endp
output_video_column proc  
    push CX
	mov DH,00100000b             ;_x______x______x______x______x______x___ 0-2 - цвет(синий) 3 - яркий?мигающий 4-6 - фон(черный) 7 - мигающий?яркий 
	mov DL,' '
	mov word ptr ES:[BX],DX
	add BX,2
	mov CX,columns
loop_output_video_column:
	mov DH,00100000b
	mov DL,219					; классный символ, рекомендую
	mov word ptr ES:[BX],DX
	add BX,2
	push CX
	mov CX,6
loop_output_video_column2:
	mov DH,00100000b
	mov DL,' '
	mov word ptr ES:[BX],DX
	add BX,2	
	loop loop_output_video_column2
	pop CX
	loop loop_output_video_column
	mov DH,00100000b
	mov DL,219
	mov word ptr ES:[BX],DX
	add BX,2
	mov CX,40
	dec CX
	sub CL,tmp1
loop_output_video_column3:
	mov DH,00100000b
	mov DL,' '
	mov word ptr ES:[BX],DX
	add BX,2
	loop loop_output_video_column3     
	pop CX
	ret
	endp
output_video_row proc	
    push CX
	mov DH,00100000b              ;_xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx___
	mov DL,' '
	mov word ptr ES:[BX],DX
	add BX,2
	xor CX,CX
	mov CL,tmp1
loop_output_video_row:
	mov DH,00100000b
	mov DL,219
	mov word ptr ES:[BX],DX
	add BX,2
	loop loop_output_video_row
	mov CX,40
	dec CX
	sub CL,tmp1
	loop_output_video_row2:
	mov DH,00100000b
	mov DL,' '
	mov word ptr ES:[BX],DX
	add BX,2
	loop loop_output_video_row2  
	pop CX
ret
endp
MAIN PROC				; начало
    mov AX, @DATA
    mov DS, AX
SETWINDOW:				;SET WINDOW SIZE TO 40*25 16 COLOR
    xor AH, AH
	mov AL, 1H
	int 10H
INITIALIZE:				;PRINT HOME PAGE
	mov SCORE, 0   
	mov flag2,0       
    mov AH, 9
	mov AL, ' '
	xor BH, BH 			;SET TEXT COLOUR FOR STR8
	mov BL, 10
	mov CX, 200
	int 10H
    SETCURSOR 4, 14 
    mov AH, 9
    lea DX, STR8		; название игры
    int 21H
    SETCURSOR 8, 12
    mov AH, 9
	mov AL, ' '
	xor BH, BH 			;SET TEXT COLOUR FOR STR9
	mov BL, 15			
	mov CX, 251			; В сх помещается число х ( х >=1 ). При выводе символ распространяется на х позиций вправо от курсора.
	int 10H
    mov AH, 9
    lea DX, STR9
    int 21H
    SETCURSOR 12, 12
    mov AH,9
	mov AL, ' '
	xor BH, BH
	mov BL, 12
	mov CX, 100			;SET TEXT COLOUR FOR STR11
	int 10H
    mov AH, 9
    lea DX, STR11
    int 21H
    mov CSR, 9                      ;следующая строка после start game
    SETCURSOR CSR, 12
    mov CHOISE, 1
MENU:						;CREATE THE MENU
	SETCURSOR CSR, 12
	call UNDERLINE			;UNDERLINE CURRENT SELECTION
	mov AH, 0               ;считываем нажатие с клавиатуры
	int 16H
	cmp AH, 50H 		;DOWN (сканкод)
	JE LOWER
	cmp AH, 48H 		;UP		(сканкод)
	JE UPPER
	cmp AH, 1CH			; ESC (сканкод)
	JE BACKGROUND
	JMP MENU
LOWER:					;movES UNDERLINE LOWER IF POSSIBLE
	cmp CSR, 13
	JE MENU
	SETCURSOR CSR, 12
	call UNUNDERLINE 
	add CSR, 4			;смещение курсора вниз
	add CHOISE, 1 		;DETERMINES THE SELECTION
	SETCURSOR CSR, 12
	JMP MENU
UPPER:					;movES UNDRLINE UPPER IF POSSIBLE
	cmp CSR, 9
	JE MENU
	SETCURSOR CSR, 12
	call UNUNDERLINE
	sub CSR, 4			;смещение курсора вверх
	sub CHOISE, 1 		;DETERMINES THE SELECTION
	SETCURSOR CSR, 12
	JMP MENU
BACKGROUND:				;SET BACKGROUND
	cmp CHOISE, 2
	JE EXIT
    mov AH, 6
    mov CX, 0			;левый верхний угол (0,0)
    mov DH, 24			;правый нижний угол 
    mov DL, 39
    mov BH, 25H
    mov AL, 0
    int 10H
    lea SI, ARR
	add SI,2
    mov CX, fieldSize
SET_0:					;RESET ARRAY TO ZERO
	mov byte ptr [SI], 0
	inc SI
	LOOP SET_0
BEGIN:					;GAME BEGINS

begin2:
	mov AH, 2CH			;GET THE TIME
	int 21H

RANDOM_LOOP:
	xor AX,AX
	xor CX,CX
	mov AL, DL			;запишем в AX текущее времм в милисекундах
	mov DL, 3
	div DL
	add AH,2
	mov CL,AH

RANDOMIZE:				;SELECTS RANDOM POSITION AND VALUE
	push CX
	mov AH, 2CH			;GET THE TIME
	int 21H

	xor AX,AX
	mov AL, DL			;запишем в AX текущее времм в милисекундах
	push AX
	mov DL, fieldSize
	div DL				;в AH рандом от 0 до 24(остаток от деления сотыъ доли секунд текущего времени на 25)
	mov BEG, AH			;с этого элемента начинаем искать свободную клетку по кругу
	pop AX
	mov DL,10   ;в 90% случаев 2, в 10 % - 4
	div DL
	cmp AH,9
	je FOUR
	mov FLAG, 'A'
	JMP SEARCHING

FOUR:
	mov FLAG, 'B'

SEARCHING:				;поиск пустой позиции
	lea BX,arr
	add BX,2
	mov AX,fieldSize
	dec AX              ;fieldSize-1
	add BX,AX           ;в вх адрес последнего элемента массива	
	lea SI, ARR			;начинаем с этой позиции
	add SI ,2
	xor AX,AX     ;REPRESENTED BY BEG
	mov AL, BEG	
	add SI,AX
	mov CX, fieldSize
ROUND:
	cmp byte ptr [SI], 0
	JE PLACEVAL
	cmp SI, BX            ;если BX указывает на последний элемент, то переходим к просмотру начала
	JNE NORESET
RESET:
	lea SI, ARR
	add SI,2
	JMP LAST
NORESET:
    inc SI
LAST:
    LOOP ROUND
	
    JMP NEXT
PLACEVAL:				;помещает значение в [SI]
	mov DL, FLAG
	mov [SI], DL
	JMP NEXT
NEXT:
	pop CX
	LOOP RANDOMIZE
GRID:					;PRintS THE GRID    
    mov AL, flag2  
    cmp AL,1
    je print
    mov AL,flag2
    inc AL
    mov  flag2,AL
	mov AX,0B800h		;физический адрес виденопамяти
	mov ES,AX
	mov AX,columns
	xor CX,CX
	mov CL,7
	mul CL
	inc AX
	mov tmp1,AL
	xor BX,BX
	mov CX,rows
loop_output_grid:
	 call output_video_row
	 push CX
	 mov CX,3 
	 loop_output_grid2:  
	 call output_video_column   
	 loop loop_output_grid2
	 pop CX
	loop loop_output_grid
 call output_video_row
PRint:					;PRintS THE NUMBERS IN THE GRID   
    lea SI, ARR
    add SI,2
	mov tmp2,columns
    mov TMP1, 0
    mov FLAG, 0
    mov CSR, 2 ;&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
ROWP:
	sub TMP2, 1 ;dec tmp2
	mov tmp3,rows
	mov CSC, 3
COLUMN:
	sub TMP3, 1	;dec tmp3
	mov DL, [SI]
	mov DONE, DL
	cmp DL, 0
	JNE CONT1
	mov FLAG, 1				;проверка пустой позиции
CONT1:
	cmp DL, 'K' 			;WINNING CONDITION
	JNE CONT2
	mov TMP1, 'K'
CONT2:
	SETCURSOR CSR, CSC
	mov DL,done
	call NUMS 
	INC SI
	add CSC, 7
	cmp TMP3, 0
	JNE COLUMN
	NEW_LINE
	add CSR, 4
	cmp TMP2, 0
	JNE ROWP
    NEW_LINE
    call C_SCORE					;вывод счета
    cmp TMP1, 'K'		;проверка выйгрышной ситуации(2048)
    JE WIN 
	lea SI, ARR
    add SI,2
	xor CX,CX
	xor BX,BX
	mov CL, fieldSize        ;проверяем есть ли пустые ячейки
check_empty:
	mov AL ,[SI]
	cmp AL,0
	je null_element_find
	next_check_empty:
	inc SI
	loop check_empty
	cmp BX,0                   ;если нет то проверяем есть ли рядом одинаковые элементы, то есть можно ли сдвинуть
	je check_shift_rows 
	jmp input
null_element_find:
	inc BX
	jmp next_check_empty 
;***********************************************	 
check_shift_rows:             ;смотрим есть ли в строке одинаковые элементы рядом
    mov CX,rows 
    mov BX,0 
loop_check_shift_rows:   
 mov DL,columns
    dec DL 
    lea SI, ARR
    add SI,2
    add SI,BX  
    add BX,columns
    mov di ,SI
    inc di
metka_check_shift_rows:
    mov AL,[SI]
    mov AH,[di] 
    cmp AL,AH 
    je input            ;если есть то можем продолжать игру
    inc SI
    inc di  
    dec DL
    cmp DL ,0
    jne metka_check_shift_rows
loop loop_check_shift_rows   
check_shift_columns:
    mov CX,columns               ;проверка одинаковых рядом в столбце
    mov BX,0 
loop_check_shift_columns:  
 	mov DL,rows
    dec DL  
    lea SI, ARR
    add SI,2
    add SI,BX  
    inc BX
    mov di ,SI
    add di,columns
metka_check_shift_columns:
    mov AL,[SI]
    mov AH,[di] 
    cmp AL,AH 
    je input 
    add SI,columns
    add di,columns  
    dec DL
    cmp DL ,0
    jne metka_check_shift_columns 
loop loop_check_shift_columns  
   jmp lose                         ;если сдвинуть никак нельзя, то мы проиграли
INPUT:						;TAKES USER INPUT
    SETCURSOR 23, 0
    mov DONE, 0
    mov AH, 0
    int 16H
    mov USERIN, AH
    cmp USERIN, 4BH			;LEFT
    JNE NEXT1
LEFT:
	mov CX, rows
	mov BX, 0
ROWSL:
	lea SI, ARR
	add SI,2
	add SI, BX
	add BX, columns
	mov DI, SI
	INC DI         ;di указывает на  элемент после SI
	mov DL, columns   ;?????
	dec DL          ;n-1 проверок
WHILEL:
	mov AL, [SI]
	mov AH, [DI]
	cmp SI, DI
	JE NOWORKL      
	cmp AH, 0
	JNE WORKL
NOWORKL:
	INC DI
	DEC DL
	JMP END_WORKL
WORKL:
	cmp AL, 0
	JE REPLACEL
	NOREPLACEL:
	cmp AL, AH
	JE MERGEL
NOMERGEL:
	INC SI
	JMP END_WORKL
MERGEL:
	mov DONE, 1
	inc AL	
	push BX
	push CX
	mov BX,1
	mov CL,AH
	sub CL,'A'
	inc CL
	sal BX, CL 
	add SCORE,BX
	pop CX
	pop BX
	mov [SI], AL
	mov byte ptr [DI], 0
	INC SI
	INC DI
	DEC DL
	JMP END_WORKL
REPLACEL:
	mov DONE, 1  
	mov [SI], AH
	mov byte ptr [DI], 0
	cmp DL,1
	je  metka_lastl 
	jmp end_workl
	metka_lastl:
	   dec DL
END_WORKL:
	cmp DL, 0
	JE END_WHILEL
	JMP WHILEL ;LOOP
END_WHILEL: 
dec CX
	cmp CX,0
	jne ROWSL
; LOOP ROWSL
    cmp done,0
	je print
    JMP BEGIN
NEXT1:
    cmp USERIN, 4DH         ;RIGHT
    JNE NEXT2
RIGHT:
	mov CX, rows
	mov BX, columns 
	dec BX
;***********************************
ROWSR:   
	lea SI, ARR
	add SI,2
	add SI, BX
	add BX, columns
	mov DI, SI
	DEC DI                 ;предыдущий элемент
	mov DL, columns  
	dec DL
WHILER:
	mov AL, [SI]
	mov AH, [DI]
	cmp SI, DI
	JE NOWORKR
	cmp AH, 0
	JNE WORKR
NOWORKR:
	DEC DI
	DEC DL
	JMP END_WORKR
WORKR:
	cmp AL, 0
	JE REPLACER
NOREPLACER:
	cmp AL, AH
	JE MERGER
NOMERGER:
	DEC SI
	JMP END_WORKR
MERGER:
	mov DONE, 1
	inc AL
	push BX
	push CX
	mov BX,1
	mov CL,AH
	sub CL,'A'
	inc CL
	sal BX, CL 
	add SCORE,BX
	pop CX
	pop BX
	mov [SI], AL
	mov byte ptr [DI], 0
	DEC SI
	DEC DI
	DEC DL
	JMP END_WORKR
REPLACER:
	mov DONE, 1 
	mov [SI], AH
	mov byte ptr [DI], 0 
	cmp DL,1
	je  metka_lastr 
	jmp end_workr
	metka_lastr:
	dec DL
END_WORKR: 	
	cmp DL,0
	je end_whiler
	JMP WHILER
END_WHILER: 
;*****************************
    dec CX
	cmp CX,0
	jne ROWSR
    ;LOOP ROWSR
   cmp done,0
	je print
    JMP BEGIN
NEXT2:
    cmp USERIN, 48H         ;UP
    JNE NEXT3
UP:
	mov CX, columns
	mov BX, 0
ROWSU:
	lea SI, ARR
	add SI,2
	add SI, BX
	add BX, 1
	mov DI, SI
	add DI, columns        ;jn column
	mov DL, rows
	dec DL
WHILEU:
	mov AL, [SI]
	mov AH, [DI]
	cmp SI, DI
	JE NOWORKU
	cmp AH, 0
	JNE WORKU
NOWORKU:
	add DI, columns
	DEC DL
	JMP END_WORKU
WORKU:
	cmp AL, 0
	JE REPLACEU
NOREPLACEU:
	cmp AL, AH
	JE MERGEU
NOMERGEU:
	add SI, columns
	JMP END_WORKU
MERGEU:
	mov DONE, 1 
	inc AL
	push BX
	push CX
	mov BX,1
	mov CL,AH
	sub CL,'A'
	inc CL
	sal BX, CL 
	add SCORE,BX
	pop CX
	pop BX
	mov [SI], AL
	mov byte ptr [DI], 0
	add SI, columns
	add DI, columns
	DEC DL
	JMP END_WORKU
REPLACEU:
	mov DONE, 1 
	mov [SI], AH
	mov byte ptr [DI], 0 
	cmp DL,1
	je  metka_lastu 
	jmp end_worku
metka_lastu:
	dec DL
END_WORKU:
	cmp DL, 0
	JE END_WHILEU
	JMP WHILEU
END_WHILEU: 
	dec CX
	cmp CX,0
	jne rowsu
	;LOOP ROWSU
	cmp done,0
	je print
    JMP BEGIN
NEXT3:
	cmp USERIN, 50H         ;DOWN
	JNE NEXT4
DOWN:
	mov CX, columns 
	xor AX,AX
	xor BX,BX
	mov AL,rows
	dec AL 
	mov bl,columns   ;BX = (rows-1)*columns(first element last row)
	mul bl    
	mov BX,AX
ROWSD:
	lea SI, ARR
	add SI,2
	add SI, BX
	add BX, 1
	mov DI, SI
	sub DI, columns             ;predidushij element
    mov DL, rows
    dec DL
WHILED:
	mov AL, [SI]
	mov AH, [DI]
	cmp SI, DI
	JE NOWORKD
	cmp AH, 0
	JNE WORKD
NOWORKD:
	sub DI, columns
	DEC DL
	JMP END_WORKD
WORKD:
	cmp AL, 0
	JE REPLACED
NOREPLACED:
	cmp AL, AH
	JE MERGED
NOMERGED:
	sub SI, columns
	JMP END_WORKD
MERGED:
	mov DONE, 1
    inc AL
	push BX
	push CX
	mov BX,1
	mov CL,AH
	sub CL,'A'
	inc CL
	sal BX, CL 
	add SCORE,BX
	pop CX
	pop BX
	mov [SI], AL
	mov byte ptr [DI], 0
	sub SI, columns
	sub DI, columns
	DEC DL
	JMP END_WORKD
REPLACED:
	mov DONE, 1   
	mov [SI], AH
	mov byte ptr [DI], 0     
	cmp DL,1
	je  metka_lastd 
	jmp end_workd
	metka_lastd:
	dec DL
END_WORKD:
	cmp DL, 0
	JE END_WHILED
	JMP WHILED
END_WHILED: 
	dec CX
	cmp CX,0
	jne rowsd
	;LOOP ROWSD
	cmp done,0
	je print
	JMP BEGIN
NEXT4:					    ;нажата не та клавиша
	cmp USERIN, 01H
	JNE NEXT5
	CLRSCR
	JMP INITIALIZE
NEXT5:					    ;неверный ввод
    JMP INPUT
LOSE:
	SETCURSOR 10, 14
    mov AH, 9
    lea DX, STR5
    int 21H
	mov AH, 0
	int 16H
	cmp AH, 01H
	JNE LOSE
	CLRSCR
LOSE1:
	mov BX, 6
	mov CSR, 10
	mov CSC, 14
	SETCURSOR CSR, CSC
    mov AH, 9
    lea DX, STR1
    int 21H
	mov AH, 0
	int 16H
	cmp AH, 01H
	JNE LOSE1
	CLRSCR
	JMP INITIALIZE
WIN:
	SETCURSOR 10, 15
    mov AH, 9
    lea DX, STR5
    int 21H
	mov AH, 0
	int 16H
	cmp AH, 01H
	JNE WIN
	CLRSCR
WIN1:
	lea DI, STR2
	mov BX, 5
	mov CSR, 5
	mov CSC, 10
	SETCURSOR CSR, CSC
MSG1:
    cmp byte ptr [DI], '$'
    JE END_MSG1
    mov AL, [DI]
    lea SI, STRZ
    mov [SI], AL    
    mov AH, 9
    lea DX, STRZ
    int 21H
    INC BX
    INC DI
    cmp BX, 16
    JNE MSG1
    mov BX, 10
    JMP MSG1
END_MSG1:
    mov AH, 0
    int 16H
    cmp AH, 01H
    JNE WIN1
    CLRSCR
    JMP INITIALIZE
EXIT:
    CLRSCR
    mov AH,4CH
    int 21H
    MAIN endp
END MAIN