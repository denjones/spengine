﻿; Listing generated by Microsoft (R) Optimizing Compiler Version 16.00.40219.01 

	TITLE	C:\Users\pa\repos\spengine\Antlr\antlr3parser.c
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB MSVCRTD
INCLUDELIB OLDNAMES

PUBLIC	_antlr3ParserNewStream
PUBLIC	_antlr3ParserNewStreamDbg
EXTRN	__RTC_CheckEsp:PROC
EXTRN	__RTC_Shutdown:PROC
EXTRN	__RTC_InitBase:PROC
;	COMDAT rtc$TMZ
; File c:\users\pa\repos\spengine\antlr\antlr3parser.c
rtc$TMZ	SEGMENT
__RTC_Shutdown.rtc$TMZ DD FLAT:__RTC_Shutdown
rtc$TMZ	ENDS
;	COMDAT rtc$IMZ
rtc$IMZ	SEGMENT
__RTC_InitBase.rtc$IMZ DD FLAT:__RTC_InitBase
; Function compile flags: /Odtp /RTCsu /ZI
rtc$IMZ	ENDS
;	COMDAT _antlr3ParserNewStreamDbg
_TEXT	SEGMENT
_parser$ = -8						; size = 4
_sizeHint$ = 8						; size = 4
_tstream$ = 12						; size = 4
_dbg$ = 16						; size = 4
_state$ = 20						; size = 4
_antlr3ParserNewStreamDbg PROC				; COMDAT
; Line 45
	push	ebp
	mov	ebp, esp
	sub	esp, 204				; 000000ccH
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-204]
	mov	ecx, 51					; 00000033H
	mov	eax, -858993460				; ccccccccH
	rep stosd
; Line 48
	mov	eax, DWORD PTR _state$[ebp]
	push	eax
	mov	ecx, DWORD PTR _tstream$[ebp]
	push	ecx
	mov	edx, DWORD PTR _sizeHint$[ebp]
	push	edx
	call	_antlr3ParserNewStream
	add	esp, 12					; 0000000cH
	mov	DWORD PTR _parser$[ebp], eax
; Line 50
	cmp	DWORD PTR _parser$[ebp], 0
	jne	SHORT $LN1@antlr3Pars
; Line 52
	xor	eax, eax
	jmp	SHORT $LN2@antlr3Pars
$LN1@antlr3Pars:
; Line 55
	mov	esi, esp
	mov	eax, DWORD PTR _dbg$[ebp]
	push	eax
	mov	ecx, DWORD PTR _parser$[ebp]
	push	ecx
	mov	edx, DWORD PTR _parser$[ebp]
	mov	eax, DWORD PTR [edx+12]
	call	eax
	add	esp, 8
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 57
	mov	eax, DWORD PTR _parser$[ebp]
$LN2@antlr3Pars:
; Line 58
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_antlr3ParserNewStreamDbg ENDP
_TEXT	ENDS
PUBLIC	_antlr3ParserNew
EXTRN	_antlr3MTExceptionNew:PROC
EXTRN	_antlr3BaseRecognizerNew:PROC
EXTRN	__imp__malloc:PROC
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT _antlr3ParserNew
_TEXT	SEGMENT
_parser$ = -8						; size = 4
_sizeHint$ = 8						; size = 4
_state$ = 12						; size = 4
_antlr3ParserNew PROC					; COMDAT
; Line 62
	push	ebp
	mov	ebp, esp
	sub	esp, 204				; 000000ccH
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-204]
	mov	ecx, 51					; 00000033H
	mov	eax, -858993460				; ccccccccH
	rep stosd
; Line 67
	mov	esi, esp
	push	28					; 0000001cH
	call	DWORD PTR __imp__malloc
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	DWORD PTR _parser$[ebp], eax
; Line 69
	cmp	DWORD PTR _parser$[ebp], 0
	jne	SHORT $LN2@antlr3Pars@2
; Line 71
	xor	eax, eax
	jmp	$LN3@antlr3Pars@2
$LN2@antlr3Pars@2:
; Line 76
	mov	eax, DWORD PTR _state$[ebp]
	push	eax
	mov	ecx, DWORD PTR _sizeHint$[ebp]
	push	ecx
	push	2
	call	_antlr3BaseRecognizerNew
	add	esp, 12					; 0000000cH
	mov	edx, DWORD PTR _parser$[ebp]
	mov	DWORD PTR [edx+4], eax
; Line 78
	mov	eax, DWORD PTR _parser$[ebp]
	cmp	DWORD PTR [eax+4], 0
	jne	SHORT $LN1@antlr3Pars@2
; Line 80
	mov	esi, esp
	mov	eax, DWORD PTR _parser$[ebp]
	push	eax
	mov	ecx, DWORD PTR _parser$[ebp]
	mov	edx, DWORD PTR [ecx+24]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 81
	xor	eax, eax
	jmp	SHORT $LN3@antlr3Pars@2
$LN1@antlr3Pars@2:
; Line 84
	mov	eax, DWORD PTR _parser$[ebp]
	mov	ecx, DWORD PTR [eax+4]
	mov	edx, DWORD PTR _parser$[ebp]
	mov	DWORD PTR [ecx], edx
; Line 88
	mov	eax, DWORD PTR _parser$[ebp]
	mov	ecx, DWORD PTR [eax+4]
	mov	DWORD PTR [ecx+136], OFFSET _antlr3MTExceptionNew
; Line 92
	mov	eax, DWORD PTR _parser$[ebp]
	mov	DWORD PTR [eax+12], OFFSET _setDebugListener
; Line 93
	mov	eax, DWORD PTR _parser$[ebp]
	mov	DWORD PTR [eax+16], OFFSET _setTokenStream
; Line 94
	mov	eax, DWORD PTR _parser$[ebp]
	mov	DWORD PTR [eax+20], OFFSET _getTokenStream
; Line 96
	mov	eax, DWORD PTR _parser$[ebp]
	mov	DWORD PTR [eax+24], OFFSET _freeParser
; Line 98
	mov	eax, DWORD PTR _parser$[ebp]
$LN3@antlr3Pars@2:
; Line 99
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_antlr3ParserNew ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _antlr3ParserNewStream
_TEXT	SEGMENT
_parser$ = -8						; size = 4
_sizeHint$ = 8						; size = 4
_tstream$ = 12						; size = 4
_state$ = 16						; size = 4
_antlr3ParserNewStream PROC				; COMDAT
; Line 103
	push	ebp
	mov	ebp, esp
	sub	esp, 204				; 000000ccH
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-204]
	mov	ecx, 51					; 00000033H
	mov	eax, -858993460				; ccccccccH
	rep stosd
; Line 106
	mov	eax, DWORD PTR _state$[ebp]
	push	eax
	mov	ecx, DWORD PTR _sizeHint$[ebp]
	push	ecx
	call	_antlr3ParserNew
	add	esp, 8
	mov	DWORD PTR _parser$[ebp], eax
; Line 108
	cmp	DWORD PTR _parser$[ebp], 0
	jne	SHORT $LN1@antlr3Pars@3
; Line 110
	xor	eax, eax
	jmp	SHORT $LN2@antlr3Pars@3
$LN1@antlr3Pars@3:
; Line 116
	mov	esi, esp
	mov	eax, DWORD PTR _tstream$[ebp]
	push	eax
	mov	ecx, DWORD PTR _parser$[ebp]
	push	ecx
	mov	edx, DWORD PTR _parser$[ebp]
	mov	eax, DWORD PTR [edx+16]
	call	eax
	add	esp, 8
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 118
	mov	eax, DWORD PTR _parser$[ebp]
$LN2@antlr3Pars@3:
; Line 119
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_antlr3ParserNewStream ENDP
_TEXT	ENDS
EXTRN	__imp__free:PROC
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT _freeParser
_TEXT	SEGMENT
_parser$ = 8						; size = 4
_freeParser PROC					; COMDAT
; Line 123
	push	ebp
	mov	ebp, esp
	sub	esp, 192				; 000000c0H
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-192]
	mov	ecx, 48					; 00000030H
	mov	eax, -858993460				; ccccccccH
	rep stosd
; Line 124
	mov	eax, DWORD PTR _parser$[ebp]
	cmp	DWORD PTR [eax+4], 0
	je	$LN3@freeParser
; Line 130
	mov	eax, DWORD PTR _parser$[ebp]
	mov	ecx, DWORD PTR [eax+4]
	cmp	DWORD PTR [ecx+8], 0
	je	SHORT $LN2@freeParser
; Line 132
	mov	eax, DWORD PTR _parser$[ebp]
	mov	ecx, DWORD PTR [eax+4]
	mov	edx, DWORD PTR [ecx+8]
	cmp	DWORD PTR [edx+12], 0
	je	SHORT $LN2@freeParser
; Line 134
	mov	eax, DWORD PTR _parser$[ebp]
	mov	ecx, DWORD PTR [eax+4]
	mov	edx, DWORD PTR [ecx+8]
	mov	esi, esp
	mov	eax, DWORD PTR [edx+12]
	push	eax
	mov	ecx, DWORD PTR _parser$[ebp]
	mov	edx, DWORD PTR [ecx+4]
	mov	eax, DWORD PTR [edx+8]
	mov	ecx, DWORD PTR [eax+12]
	mov	edx, DWORD PTR [ecx+8]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 135
	mov	eax, DWORD PTR _parser$[ebp]
	mov	ecx, DWORD PTR [eax+4]
	mov	edx, DWORD PTR [ecx+8]
	mov	DWORD PTR [edx+12], 0
$LN2@freeParser:
; Line 138
	mov	esi, esp
	mov	eax, DWORD PTR _parser$[ebp]
	mov	ecx, DWORD PTR [eax+4]
	push	ecx
	mov	edx, DWORD PTR _parser$[ebp]
	mov	eax, DWORD PTR [edx+4]
	mov	ecx, DWORD PTR [eax+144]
	call	ecx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 139
	mov	eax, DWORD PTR _parser$[ebp]
	mov	DWORD PTR [eax+4], 0
$LN3@freeParser:
; Line 142
	mov	esi, esp
	mov	eax, DWORD PTR _parser$[ebp]
	push	eax
	call	DWORD PTR __imp__free
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 143
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 192				; 000000c0H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_freeParser ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _setDebugListener
_TEXT	SEGMENT
_parser$ = 8						; size = 4
_dbg$ = 12						; size = 4
_setDebugListener PROC					; COMDAT
; Line 147
	push	ebp
	mov	ebp, esp
	sub	esp, 192				; 000000c0H
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-192]
	mov	ecx, 48					; 00000030H
	mov	eax, -858993460				; ccccccccH
	rep stosd
; Line 157
	mov	eax, DWORD PTR _parser$[ebp]
	mov	ecx, DWORD PTR [eax+4]
	mov	edx, DWORD PTR _dbg$[ebp]
	mov	DWORD PTR [ecx+12], edx
; Line 162
	mov	eax, DWORD PTR _parser$[ebp]
	cmp	DWORD PTR [eax+8], 0
	je	SHORT $LN2@setDebugLi
; Line 164
	mov	esi, esp
	mov	eax, DWORD PTR _dbg$[ebp]
	push	eax
	mov	ecx, DWORD PTR _parser$[ebp]
	mov	edx, DWORD PTR [ecx+8]
	push	edx
	mov	eax, DWORD PTR _parser$[ebp]
	mov	ecx, DWORD PTR [eax+8]
	mov	edx, DWORD PTR [ecx+48]
	call	edx
	add	esp, 8
	cmp	esi, esp
	call	__RTC_CheckEsp
$LN2@setDebugLi:
; Line 166
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 192				; 000000c0H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_setDebugListener ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _setTokenStream
_TEXT	SEGMENT
_parser$ = 8						; size = 4
_tstream$ = 12						; size = 4
_setTokenStream PROC					; COMDAT
; Line 170
	push	ebp
	mov	ebp, esp
	sub	esp, 192				; 000000c0H
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-192]
	mov	ecx, 48					; 00000030H
	mov	eax, -858993460				; ccccccccH
	rep stosd
; Line 171
	mov	eax, DWORD PTR _parser$[ebp]
	mov	ecx, DWORD PTR _tstream$[ebp]
	mov	DWORD PTR [eax+8], ecx
; Line 172
	mov	esi, esp
	mov	eax, DWORD PTR _parser$[ebp]
	mov	ecx, DWORD PTR [eax+4]
	push	ecx
	mov	edx, DWORD PTR _parser$[ebp]
	mov	eax, DWORD PTR [edx+4]
	mov	ecx, DWORD PTR [eax+140]
	call	ecx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 173
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 192				; 000000c0H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_setTokenStream ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _getTokenStream
_TEXT	SEGMENT
_parser$ = 8						; size = 4
_getTokenStream PROC					; COMDAT
; Line 177
	push	ebp
	mov	ebp, esp
	sub	esp, 192				; 000000c0H
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-192]
	mov	ecx, 48					; 00000030H
	mov	eax, -858993460				; ccccccccH
	rep stosd
; Line 178
	mov	eax, DWORD PTR _parser$[ebp]
	mov	eax, DWORD PTR [eax+8]
; Line 179
	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
_getTokenStream ENDP
_TEXT	ENDS
END