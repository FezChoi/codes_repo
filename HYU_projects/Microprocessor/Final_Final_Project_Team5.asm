;DEFINE DATANAME
SEG1      EQU   0FFC3H 	;7 SEGMENT - RIGHT
SEG2      EQU   0FFC2H	;MIDDILE
SEG3      EQU   0FFC1H	;LEFT
COLGREEN  EQU   0FFC5H	;DOT MATRIX
COLRED    EQU   0FFC6H
ROW       EQU   0FFC7H
DATAOUT EQU   0FFF0H	;KEY INTERFACE
DATAIN  EQU   0FFF1H
VSEG1   EQU   30H	;7 SEGMENT BUFFER
VSEG2   EQU   31H
VSEG3   EQU   32H
VCOLG   EQU   33H	;DOT MATRIX BUFFER
VROWG   EQU   34H
VCOLR   EQU   35H
VROWR   EQU   36H
BUFF    EQU   37H	;KEY BUFFER
TEMP1   EQU   38H	;GENERAL BUFFER
TEMP2   EQU   39H

;DEFINE REGISTER
;R0 COLG
;R1 ROWG
;R2 DOTCOLG TEMP, COUNTER
;R3 TEMP
;R4 LENGTH
;R5 TIME_REPS
;R6 DELAY, TEMP
;R7 DELAY, TEMP


;THE SNAKE GAEM
;-------------------------------------------------------
; INITIALIZE
;-------------------------------------------------------
   	ORG   	8000H

   	MOV   	SP, #60
      	SETB    PS
INITIAL:
INITSEG:
      	MOV   	A, #0
      	MOV     VSEG3, A
      	MOV     VSEG2, A
      	MOV     VSEG1, A
      	MOV     DPTR, #SEG1
      	MOVX    @DPTR, A   
      	MOV     DPTR, #SEG2
      	MOVX    @DPTR, A   
      	MOV     DPTR, #SEG3
      	MOVX    @DPTR, A      
INITVAR:
      	MOV    	BUFF, #02H
      	MOV     VCOLG, #1
      	MOV     VROWG, #1  
      	MOV     VCOLR, #2  
      	MOV     VROWR, #1
      	MOV     R0, #50H
      	MOV     R1, #60H
   	MOV   	@R0, #1
   	MOV   	@R1, #1
   	MOV   	VCOLG, @R0
   	MOV   	VROWG, @R1
   	MOV   	R4, #1H
   	MOV   	R5, #8
INITTIME:
   	MOV   	TMOD,#00000001B
      	ORL     IE,#10000010B   
      	MOV     TH0,#00H
      	MOV     TL0,#00H
      	CLR     C
      	SETB    TCON.TR0

;-------------------------------------------------------
; MAIN ROUTINE
;-------------------------------------------------------
MAIN:   MOV     R3, TL0  
   	CALL    DOTCOLR
      	CALL    DOTCOLG
      	JMP     MAIN

;-------------------------------------------------------
; TIMER INTERRUPT ROUTINE
;-------------------------------------------------------
SERVICE:
      	CLR    	TCON.TR0
      	DJNZ    R5, ENDSERV
      	CALL    GETKEY
      	CALL 	DIRECTION
   	CALL   	EATEN
   	CALL   	COLLISION
      	MOV     R5, #8
ENDSERV:
      	SETB    TCON.TR0
RETI

;-------------------------------------------------------
; READ KEY
;-------------------------------------------------------
GETKEY:   
      	PUSH     PSW
      	SETB     PSW.4
      	SETB     PSW.3
INIT:   MOV      R5, #00H
      	MOV      A, #11101111B
      	SETB     C
COLSCAN:
      	MOV      R6,A
      	INC      R5
      	CALL     SUBKEY
      	CJNE     A,#0FFH,RSCAN
      	MOV      A, R6
      	SETB     C
      	RRC      A
      	JNC      NOKEY
      	JMP      COLSCAN
RSCAN:  MOV      R6,#00H
ROWSCAN:
      	RRC      A
      	JNC      MATRIX
      	INC      R6
      	JMP      ROWSCAN
MATRIX: MOV      A, R6
      	MOV      B, #05H
      	MUL      AB
      	ADD      A, R5
      	CALL      INDEX
      	CLR      C

   	MOV   	R7, A
   	SUBB   	A, BUFF
   	CJNE   	A, #02H, JP1
   	JMP   	GAMEOVER
JP1:   	CJNE   	A, #04H, JP2
   	JMP   	GAMEOVER
JP2:   	CPL   	A
   	INC   	A
   	CJNE   	A, #02H, JP3
   	JMP   	GAMEOVER
JP3:   	CJNE   	A, #04H, JP4
   	JMP   	GAMEOVER
JP4:   	MOV   	A, R7
      	MOV     BUFF,A

NOKEY:  POP     PSW
RET         			;GETKEY 끝

SUBKEY: MOV     DPTR,#DATAOUT
        MOVX   	@DPTR,A
        MOV    	DPTR,#DATAIN
        MOVX   	A,@DPTR
RET

;-------------------------------------------------------
; GET DIRECTION & NEW HEAD
;-------------------------------------------------------
DIRECTION:
      	MOV     R7, BUFF
   	MOV   	R0, #50H
   	MOV   	R1, #60H
      	CJNE    R7,#00H,LP1
   	MOV   	A, @R0
      	DEC     A
      	CJNE    A,#0,LP4
      	CALL    GAMEOVER
LP1:    CJNE    R7,#01H,LP2
   	MOV   	A, @R1
      	INC     A
      	CJNE    A,#9,LP5
      	CALL    GAMEOVER
LP2:    CJNE    R7,#02H,LP3
   	MOV   	A, @R0
      	INC     A
      	CJNE    A,#9,LP4
      	CALL    GAMEOVER
LP3:    CJNE    R7,#05H,LP4
   	MOV   	A, @R1
      	DEC     A
      	CJNE    A,#0,LP5
      	CALL    GAMEOVER
RET

LP4:   	MOV   	VCOLG, A
   	MOV   	VROWG, @R1
RET

LP5:   	MOV   	VCOLG, @R0
   	MOV   	VROWG, A   
RET         

;-------------------------------------------------------
; CHECK EATEN & UPDATE
;-------------------------------------------------------
EATEN:  MOV     A, VCOLG
      	CJNE    A,35H,EATX
      	MOV     A, VROWG
      	CJNE    A,36H,EATX
      	MOV     A, #0
      	MOV     DPTR, #COLRED
      	MOVX    @DPTR, A
      	CALL    SEGDIS
   	CALL   	EATUPDATE
      	CALL  	RAND
RET
EATX:   CALL   	EATXUPDATE
RET

;-------------------------------------------------------
; GET RANDOM POSITION & CHECK
;-------------------------------------------------------   
RAND:      
   	MOV   	A, R3
RD:   	ADD   	A, #17
   	MOV   	B, #101
   	MUL   	AB
      	CLR     C 
   	MOV   	R7, A
   	MOV     B, #64
      	DIV     AB   
      	MOV     A, B
      	MOV     B, #8
      	DIV     AB
      	INC     A
   
      	MOV     VCOLR, A
      	MOV     A, B
      	INC     A   
      	MOV     VROWR, A   

RANDCHECK:
   	MOV   	TEMP1, R2
CHECK1:
   	MOV   	R2, #00H
AGA:   	MOV   	A, #50H
   	ADD   	A, R2
   	MOV   	R0, A
   	MOV   	A, @R0
   	CJNE   	A, 35H, RPT
   	JMP   	CHECK2
RPT:   	INC   	R2
   	MOV   	A, R2	
   	MOV   	B, R4
   	CJNE   	A, B, AGA
   	MOV   	R2, TEMP1
RET
CHECK2:
   	MOV   	R2, #00H
AGA2:   MOV   	A, #60H
   	ADD   	A, R2
   	MOV   	R1, A
   	MOV   	A, @R1
   	CJNE   	A, 36H, RPT2
   	MOV   	A, R7
   	JMP   	RD
RPT2:   INC   	R2
   	MOV   	A, R2
   	MOV   	B, R4
   	CJNE   	A, B, AGA2
   	MOV   	R2, TEMP1
RET

;-------------------------------------------------------
; (DEBUG IN DETERMINISTIC ROUTINE)
;-------------------------------------------------------
DETER:
   	MOV   	A, VCOLR
   	CJNE   	A, #08H, NOTYET
   	MOV   	A, VROWR
   	CJNE   	A, #08H, NOTYET2
   	MOV   	A, #01H
   	MOV   	VCOLR, A
   	MOV   	VROWR, A
RET
NOTYET: 
	INC   	A
   	MOV   	VCOLR, A   
RET
NOTYET2:
	INC  	A
   	MOV   	VROWR, A
RET

;-------------------------------------------------------
; UPDATE ROUTINE
;-------------------------------------------------------
; UPDATE IF EATEN
;-------------------------------------------------------
EATUPDATE:
   	MOV   	B, R4
LOOP1:  MOV   	A, B
  	DEC   	A
   	ADD   	A, #50H
   	MOV   	R0, A
   	ADD   	A, #10H
   	MOV   	R1, A
   	MOV   	TEMP1, @R0
   	MOV   	TEMP2, @R1
   	INC   	R0
   	INC   	R1
   	MOV   	@R0, TEMP1
   	MOV   	@R1, TEMP2
   	MOV   	A, B
   	DEC   	A
   	MOV   	B, A
   	JNZ   	LOOP1
   	INC   	R4
   
   	MOV   	50H, VCOLG
   	MOV   	60H, VROWG
RET
;-------------------------------------------------------
; UPDATE IF NOT EATEN
;-------------------------------------------------------
EATXUPDATE:
   	MOV   	B, R4
   	MOV   	A, B
   	DEC   	A
   	JZ   	LOOP4
   
LOOP3:  MOV   	A, B
   	DEC   	A
   	DEC   	A
   	ADD   	A, #50H
   	MOV   	R0, A
   	ADD   	A, #10H
   	MOV   	R1, A
   	MOV   	TEMP1, @R0
   	MOV   	TEMP2, @R1
   	INC   	R0
   	INC   	R1
   	MOV   	@R0, TEMP1
   	MOV   	@R1, TEMP2
   	MOV   	A, B
   	DEC   	A
   	MOV   	B, A
   	JNZ   	LOOP3

LOOP4:  MOV   	50H, VCOLG
   	MOV   	60H, VROWG
RET   

;-------------------------------------------------------
; CHECK COLLISION
;-------------------------------------------------------
COLLISION:
   	MOV   	TEMP2, R2
	MOV   	A, R4     ;10
   	DEC   	A         ;9
   	JZ   	NEXT2
   	DEC   	A         ;8
   	JZ   	NEXT2
   	DEC   	A         ;7
   	JZ   	NEXT2
   	DEC   	A      	  ;6
   	JZ   	NEXT2
   	MOV   	TEMP1, A  ;6

CHECKCOL:
   	MOV   	R2, #00H
AGAIN:  MOV   	A, #54H   ;54H
   	ADD   	A, R2     ;54 ;55
   	MOV   	R0, A   
   	MOV   	A, @R0
   	CJNE   	A, 50H, REPT
   	JMP   	CHECKROW
REPT:   INC   	R2        ;1 ;2 ;3 ;4 ;5 ;6
   	MOV   	A, R2      
   	CJNE   	A, 38H, AGAIN
RET

CHECKROW:
   	MOV   	R2, #00H 
AGAIN2: MOV   	A, #64H
   	ADD   	A, R2
   	MOV   	R1, A
   	MOV   	A, @R1
   	CJNE   	A, 60H, REPT2
   	MOV    	A, #54H
   	ADD    	A, R2
   	MOV    	R0,A
   	MOV    	A, @R0
   	CJNE   	A,50H NEXT2   
   	JMP   	GAMEOVER
REPT2:  INC   	R2
   	MOV   	A, R2
   	CJNE   	A, 38H, AGAIN2

NEXT2:	MOV   	R2, TEMP2
RET


;-------------------------------------------------------
; DOT MATRIX LED CONTROL
;-------------------------------------------------------
; GREEN LED FOR SNAKE
;-------------------------------------------------------
DOTCOLG:
	MOV   	R2, #00H   
LOOP:
      	MOV     A, #0
      	MOV     DPTR, #COLRED
      	MOVX    @DPTR, A
   	MOV   	DPTR, #ROW
   	MOVX   	@DPTR, A

   	MOV   	A, #50H
   	ADD   	A, R2
   	MOV   	R0, A
   	MOV     A, @R0
      	CALL    CINDEX
      	MOV     DPTR, #COLGREEN
      	MOVX    @DPTR, A

   	MOV   	A, #60H
   	ADD   	A, R2
   	MOV   	R1, A
      	MOV     A, @R1
      	CALL    RINDEX
      	MOV     DPTR, #ROW
      	MOVX    @DPTR, A

   	INC   	R2
   	MOV   	A, R2
   	MOV   	B, R4
   	CJNE   	A, B, LOOP
 	MOV   	DPTR, #0
RET
;-------------------------------------------------------
; RED LED FOR PREY
;-------------------------------------------------------
DOTCOLR:
      	MOV   	A, #0
      	MOV   	DPTR, #COLGREEN
      	MOVX   	@DPTR, A
   	MOV   	DPTR, #ROW
   	MOVX   	@DPTR, A

      	MOV   	A, VCOLR
      	CALL   	CINDEX
      	MOV    	DPTR, #COLRED
      	MOVX   	@DPTR, A
      	MOV   	A, VROWR
      	CALL   	RINDEX
      	MOV   	DPTR, #ROW
      	MOVX   	@DPTR, A
    	MOV   	DPTR, #0
RET 
;-------------------------------------------------------
; GAMEOVER DISPLAY
;-------------------------------------------------------
GAMEOVER:
      	MOV    	A, #0
      	MOV     DPTR, #COLGREEN
      	MOVX    @DPTR, A
      	MOV     A, #11111111B
      	MOV     DPTR, #COLRED
      	MOVX    @DPTR, A
      	MOV     DPTR, #ROW
      	MOVX    @DPTR, A
      	CLR     TCON.TR0
   	JMP   	$
NOTOVER: 
RET

;-------------------------------------------------------
; SCORE DISPLAY
;-------------------------------------------------------
; SEVEN SEGMENT LED DISPLAY
;-------------------------------------------------------
SEGDIS:
	MOV   	VSEG3,R4
      	MOV    	A, VSEG3
      	DA      A
   	MOV   	VSEG3, A


   	MOV   	DPTR, #SEG3
   	MOVX   	@DPTR, A
   	MOV   	A, R4
   	MOV   	DPTR, #0
   	CJNE   	A, #00H, NEXT
   
      	MOV     A, VSEG2
      	ADD     A, #1H
      	DA      A
   	MOV   	R7, A
      	MOV     VSEG2, A
      	MOV     DPTR, #SEG2
      	MOVX    @DPTR, A   
      	CJNE    A,#00H,NEXT
   
      	MOV     A, VSEG1
      	ADD     A, #1H
      	DA      A
   	MOV   	R7, A
      	MOV     VSEG1, A
      	MOV     DPTR, #SEG1
      	MOVX    @DPTR, A   
      	CJNE    A,#00H,NEXT
   
      	MOV     A, #00H
      	MOV     VSEG3, A
      	MOV     VSEG2, A
      	MOV     VSEG1, A
NEXT:   
RET

;-------------------------------------------------------
; DELAY ROUTINE
;-------------------------------------------------------
DELAY:  MOV    	R7, #0FFH
DELAY1: MOV     R6, #0FFH
DELAY2:	DJNZ    R6, DELAY2
      	DJNZ    R7, DELAY1
RET

;-------------------------------------------------------
; INDEX & DATABASE
;-------------------------------------------------------
; FUNCTION KEY INDEX
;-------------------------------------------------------
RWKEY   EQU 10H ;READ AND WRITE KEY
COMMA   EQU 11H ;INCRESE KEY(COMMA ,)
PERIOD  EQU 12H ;END KEY (PERIOD . )
GO      EQU 13H ;GO-KEY
REG     EQU 14H ;REGISTER KEY
CD      EQU 15H ;DECRESE KEY
INCR    EQU 16H ;CODE KEY
ST      EQU 17H ;SINGLE STEP KEY
RST     EQU 18H ;RST KEY

INDEX:  MOVC   A, @A+PC
RET
KEYBASE:
	DB    	ST 
      	DB    	INCR
      	DB    	CD
      	DB    	REG
      	DB    	GO
      	DB    	0CH
      	DB    	0DH
      	DB    	0EH
      	DB    	0FH
      	DB    	COMMA
      	DB    	08H
      	DB    	09H
      	DB    	0AH
      	DB    	0BH
      	DB    	PERIOD
      	DB    	04H
      	DB    	05H ; 위
      	DB    	06H
      	DB    	07H
      	DB    	RWKEY
      	DB    	00H ; 왼쪽
      	DB    	01H ; 아래
      	DB    	02H ; 오른쪽
      	DB    	03H
;-------------------------------------------------------
; DOT MATRIX COLUMN LINE INDEX
;-------------------------------------------------------
CINDEX:	MOV   	DPTR,#CBASE
      	MOVC   	A, @A+DPTR
RET
CBASE:  DB   	00H,01H,02H,04H,08H,10H,20H,40H,80H
;-------------------------------------------------------
; DOT MATRIX ROW LINE INDEX
;-------------------------------------------------------
RINDEX: MOV   	DPTR,#RBASE
      	MOVC   	A, @A+DPTR
RET
RBASE:  DB   	00H,01H,02H,04H,08H,10H,20H,40H,80H
;-------------------------------------------------------
; SEVEN SEGMENT INDEX
;-------------------------------------------------------
SINDEX: MOV   	DPTR,#SBASE
      	MOVC   	A, @A+DPTR
RET
SBASE:  DB   	00000000B
   	DB   	00000001B ;1
   	DB   	00000010B
   	DB   	00000011B
   	DB   	00000100B
   	DB   	00000101B
   	DB   	00000110B
   	DB   	00000111B
   	DB   	00001000B
   	DB   	00001001B ;9
   	DB   	00010000B
   	DB   	00010001B
   	DB   	00010010B
   	DB   	00010011B
   	DB   	00010100B
   	DB   	00010101B
   	DB   	00010110B ;16

;-------------------------------------------------------
; TIMER INTERRUPT OCCURANCE
;-------------------------------------------------------
      	ORG   	9F0BH
      	JMP     SERVICE

;-------------------------------------------------------
END