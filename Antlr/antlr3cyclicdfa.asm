﻿; Listing generated by Microsoft (R) Optimizing Compiler Version 16.00.40219.01 

	TITLE	C:\Users\Ken\Documents\GitHub\spengine\Antlr\antlr3cyclicdfa.c
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB MSVCRTD
INCLUDELIB OLDNAMES

PUBLIC	_antlr3dfapredict
EXTRN	__RTC_CheckEsp:PROC
EXTRN	__RTC_Shutdown:PROC
EXTRN	__RTC_InitBase:PROC
;	COMDAT rtc$TMZ
; File c:\users\ken\documents\github\spengine\antlr\antlr3cyclicdfa.c
rtc$TMZ	SEGMENT
__RTC_Shutdown.rtc$TMZ DD FLAT:__RTC_Shutdown
rtc$TMZ	ENDS
;	COMDAT rtc$IMZ
rtc$IMZ	SEGMENT
__RTC_InitBase.rtc$IMZ DD FLAT:__RTC_InitBase
; Function compile flags: /Odtp /RTCsu /ZI
rtc$IMZ	ENDS
;	COMDAT _antlr3dfapredict
_TEXT	SEGMENT
_snext$35955 = -56					; size = 4
_c$ = -44						; size = 4
_specialState$ = -32					; size = 4
_s$ = -20						; size = 4
_mark$ = -8						; size = 4
_ctx$ = 8						; size = 4
_rec$ = 12						; size = 4
_is$ = 16						; size = 4
_cdfa$ = 20						; size = 4
_antlr3dfapredict PROC					; COMDAT
; Line 80
	push	ebp
	mov	ebp, esp
	sub	esp, 252				; 000000fcH
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-252]
	mov	ecx, 63					; 0000003fH
	mov	eax, -858993460				; ccccccccH
	rep stosd
; Line 86
	mov	esi, esp
	mov	eax, DWORD PTR _is$[ebp]
	push	eax
	mov	ecx, DWORD PTR _is$[ebp]
	mov	edx, DWORD PTR [ecx+28]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	DWORD PTR _mark$[ebp], eax
; Line 87
	mov	DWORD PTR _s$[ebp], 0
$LN11@antlr3dfap:
; Line 93
	mov	eax, DWORD PTR _cdfa$[ebp]
	mov	ecx, DWORD PTR [eax+40]
	mov	edx, DWORD PTR _s$[ebp]
	mov	eax, DWORD PTR [ecx+edx*4]
	mov	DWORD PTR _specialState$[ebp], eax
; Line 97
	cmp	DWORD PTR _specialState$[ebp], 0
	jl	$LN9@antlr3dfap
; Line 99
	mov	esi, esp
	mov	eax, DWORD PTR _specialState$[ebp]
	push	eax
	mov	ecx, DWORD PTR _cdfa$[ebp]
	push	ecx
	mov	edx, DWORD PTR _is$[ebp]
	push	edx
	mov	eax, DWORD PTR _rec$[ebp]
	push	eax
	mov	ecx, DWORD PTR _ctx$[ebp]
	push	ecx
	mov	edx, DWORD PTR _cdfa$[ebp]
	mov	eax, DWORD PTR [edx+8]
	call	eax
	add	esp, 20					; 00000014H
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	DWORD PTR _s$[ebp], eax
; Line 103
	cmp	DWORD PTR _s$[ebp], 0
	jge	SHORT $LN8@antlr3dfap
; Line 108
	mov	eax, DWORD PTR _rec$[ebp]
	mov	ecx, DWORD PTR [eax+8]
	movzx	edx, BYTE PTR [ecx]
	cmp	edx, 1
	je	SHORT $LN7@antlr3dfap
; Line 110
	mov	eax, DWORD PTR _s$[ebp]
	push	eax
	mov	ecx, DWORD PTR _cdfa$[ebp]
	push	ecx
	mov	edx, DWORD PTR _rec$[ebp]
	push	edx
	call	_noViableAlt
	add	esp, 12					; 0000000cH
$LN7@antlr3dfap:
; Line 112
	mov	esi, esp
	mov	eax, DWORD PTR _mark$[ebp]
	push	eax
	mov	ecx, DWORD PTR _is$[ebp]
	push	ecx
	mov	edx, DWORD PTR _is$[ebp]
	mov	eax, DWORD PTR [edx+36]
	call	eax
	add	esp, 8
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 113
	xor	eax, eax
	jmp	$LN12@antlr3dfap
$LN8@antlr3dfap:
; Line 115
	mov	esi, esp
	mov	eax, DWORD PTR _is$[ebp]
	push	eax
	mov	ecx, DWORD PTR _is$[ebp]
	mov	edx, DWORD PTR [ecx+20]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 116
	jmp	$LN11@antlr3dfap
$LN9@antlr3dfap:
; Line 121
	mov	eax, DWORD PTR _cdfa$[ebp]
	mov	ecx, DWORD PTR [eax+36]
	mov	edx, DWORD PTR _s$[ebp]
	cmp	DWORD PTR [ecx+edx*4], 1
	jl	SHORT $LN6@antlr3dfap
; Line 123
	mov	esi, esp
	mov	eax, DWORD PTR _mark$[ebp]
	push	eax
	mov	ecx, DWORD PTR _is$[ebp]
	push	ecx
	mov	edx, DWORD PTR _is$[ebp]
	mov	eax, DWORD PTR [edx+36]
	call	eax
	add	esp, 8
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 124
	mov	eax, DWORD PTR _cdfa$[ebp]
	mov	ecx, DWORD PTR [eax+36]
	mov	edx, DWORD PTR _s$[ebp]
	mov	eax, DWORD PTR [ecx+edx*4]
	jmp	$LN12@antlr3dfap
$LN6@antlr3dfap:
; Line 129
	mov	esi, esp
	push	1
	mov	eax, DWORD PTR _is$[ebp]
	push	eax
	mov	ecx, DWORD PTR _is$[ebp]
	mov	edx, DWORD PTR [ecx+24]
	call	edx
	add	esp, 8
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	DWORD PTR _c$[ebp], eax
; Line 133
	mov	eax, DWORD PTR _cdfa$[ebp]
	mov	ecx, DWORD PTR [eax+28]
	mov	edx, DWORD PTR _s$[ebp]
	mov	eax, DWORD PTR _c$[ebp]
	cmp	eax, DWORD PTR [ecx+edx*4]
	jl	$LN5@antlr3dfap
	mov	eax, DWORD PTR _cdfa$[ebp]
	mov	ecx, DWORD PTR [eax+32]
	mov	edx, DWORD PTR _s$[ebp]
	mov	eax, DWORD PTR _c$[ebp]
	cmp	eax, DWORD PTR [ecx+edx*4]
	jg	$LN5@antlr3dfap
; Line 139
	mov	eax, DWORD PTR _cdfa$[ebp]
	mov	ecx, DWORD PTR [eax+44]
	mov	edx, DWORD PTR _cdfa$[ebp]
	mov	eax, DWORD PTR [edx+28]
	mov	edx, DWORD PTR _s$[ebp]
	mov	esi, DWORD PTR _c$[ebp]
	sub	esi, DWORD PTR [eax+edx*4]
	mov	eax, DWORD PTR _s$[ebp]
	mov	ecx, DWORD PTR [ecx+eax*4]
	mov	edx, DWORD PTR [ecx+esi*4]
	mov	DWORD PTR _snext$35955[ebp], edx
; Line 141
	cmp	DWORD PTR _snext$35955[ebp], 0
	jge	SHORT $LN4@antlr3dfap
; Line 148
	mov	eax, DWORD PTR _cdfa$[ebp]
	mov	ecx, DWORD PTR [eax+20]
	mov	edx, DWORD PTR _s$[ebp]
	cmp	DWORD PTR [ecx+edx*4], 0
	jl	SHORT $LN3@antlr3dfap
; Line 150
	mov	eax, DWORD PTR _cdfa$[ebp]
	mov	ecx, DWORD PTR [eax+20]
	mov	edx, DWORD PTR _s$[ebp]
	mov	eax, DWORD PTR [ecx+edx*4]
	mov	DWORD PTR _s$[ebp], eax
; Line 151
	mov	esi, esp
	mov	eax, DWORD PTR _is$[ebp]
	push	eax
	mov	ecx, DWORD PTR _is$[ebp]
	mov	edx, DWORD PTR [ecx+20]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 152
	jmp	$LN11@antlr3dfap
$LN3@antlr3dfap:
; Line 154
	mov	eax, DWORD PTR _s$[ebp]
	push	eax
	mov	ecx, DWORD PTR _cdfa$[ebp]
	push	ecx
	mov	edx, DWORD PTR _rec$[ebp]
	push	edx
	call	_noViableAlt
	add	esp, 12					; 0000000cH
; Line 155
	mov	esi, esp
	mov	eax, DWORD PTR _mark$[ebp]
	push	eax
	mov	ecx, DWORD PTR _is$[ebp]
	push	ecx
	mov	edx, DWORD PTR _is$[ebp]
	mov	eax, DWORD PTR [edx+36]
	call	eax
	add	esp, 8
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 156
	xor	eax, eax
	jmp	$LN12@antlr3dfap
$LN4@antlr3dfap:
; Line 161
	mov	eax, DWORD PTR _snext$35955[ebp]
	mov	DWORD PTR _s$[ebp], eax
; Line 162
	mov	esi, esp
	mov	eax, DWORD PTR _is$[ebp]
	push	eax
	mov	ecx, DWORD PTR _is$[ebp]
	mov	edx, DWORD PTR [ecx+20]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 163
	jmp	$LN11@antlr3dfap
$LN5@antlr3dfap:
; Line 167
	mov	eax, DWORD PTR _cdfa$[ebp]
	mov	ecx, DWORD PTR [eax+20]
	mov	edx, DWORD PTR _s$[ebp]
	cmp	DWORD PTR [ecx+edx*4], 0
	jl	SHORT $LN2@antlr3dfap
; Line 169
	mov	eax, DWORD PTR _cdfa$[ebp]
	mov	ecx, DWORD PTR [eax+20]
	mov	edx, DWORD PTR _s$[ebp]
	mov	eax, DWORD PTR [ecx+edx*4]
	mov	DWORD PTR _s$[ebp], eax
; Line 170
	mov	esi, esp
	mov	eax, DWORD PTR _is$[ebp]
	push	eax
	mov	ecx, DWORD PTR _is$[ebp]
	mov	edx, DWORD PTR [ecx+20]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 171
	jmp	$LN11@antlr3dfap
$LN2@antlr3dfap:
; Line 175
	cmp	DWORD PTR _c$[ebp], -1
	jne	SHORT $LN1@antlr3dfap
	mov	eax, DWORD PTR _cdfa$[ebp]
	mov	ecx, DWORD PTR [eax+24]
	mov	edx, DWORD PTR _s$[ebp]
	cmp	DWORD PTR [ecx+edx*4], 0
	jl	SHORT $LN1@antlr3dfap
; Line 177
	mov	esi, esp
	mov	eax, DWORD PTR _mark$[ebp]
	push	eax
	mov	ecx, DWORD PTR _is$[ebp]
	push	ecx
	mov	edx, DWORD PTR _is$[ebp]
	mov	eax, DWORD PTR [edx+36]
	call	eax
	add	esp, 8
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 178
	mov	eax, DWORD PTR _cdfa$[ebp]
	mov	ecx, DWORD PTR [eax+24]
	mov	edx, DWORD PTR _s$[ebp]
	mov	eax, DWORD PTR [ecx+edx*4]
	mov	ecx, DWORD PTR _cdfa$[ebp]
	mov	edx, DWORD PTR [ecx+36]
	mov	eax, DWORD PTR [edx+eax*4]
	jmp	SHORT $LN12@antlr3dfap
$LN1@antlr3dfap:
; Line 183
	mov	eax, DWORD PTR _s$[ebp]
	push	eax
	mov	ecx, DWORD PTR _cdfa$[ebp]
	push	ecx
	mov	edx, DWORD PTR _rec$[ebp]
	push	edx
	call	_noViableAlt
	add	esp, 12					; 0000000cH
; Line 184
	mov	esi, esp
	mov	eax, DWORD PTR _mark$[ebp]
	push	eax
	mov	ecx, DWORD PTR _is$[ebp]
	push	ecx
	mov	edx, DWORD PTR _is$[ebp]
	mov	eax, DWORD PTR [edx+36]
	call	eax
	add	esp, 8
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 185
	xor	eax, eax
	jmp	SHORT $LN12@antlr3dfap
; Line 186
	jmp	$LN11@antlr3dfap
$LN12@antlr3dfap:
; Line 188
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 252				; 000000fcH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_antlr3dfapredict ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _noViableAlt
_TEXT	SEGMENT
_rec$ = 8						; size = 4
_cdfa$ = 12						; size = 4
_s$ = 16						; size = 4
_noViableAlt PROC					; COMDAT
; Line 54
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
; Line 59
	mov	eax, DWORD PTR _rec$[ebp]
	mov	ecx, DWORD PTR [eax+8]
	cmp	DWORD PTR [ecx+32], 0
	jle	SHORT $LN2@noViableAl
; Line 61
	mov	eax, DWORD PTR _rec$[ebp]
	mov	ecx, DWORD PTR [eax+8]
	mov	BYTE PTR [ecx+24], 1
; Line 63
	jmp	SHORT $LN3@noViableAl
$LN2@noViableAl:
; Line 65
	mov	esi, esp
	mov	eax, DWORD PTR _rec$[ebp]
	push	eax
	mov	ecx, DWORD PTR _rec$[ebp]
	mov	edx, DWORD PTR [ecx+136]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 66
	mov	eax, DWORD PTR _rec$[ebp]
	mov	ecx, DWORD PTR [eax+8]
	mov	edx, DWORD PTR [ecx+4]
	mov	DWORD PTR [edx], 3
; Line 67
	mov	eax, DWORD PTR _rec$[ebp]
	mov	ecx, DWORD PTR [eax+8]
	mov	edx, DWORD PTR [ecx+4]
	mov	eax, DWORD PTR _cdfa$[ebp]
	mov	ecx, DWORD PTR [eax+4]
	mov	DWORD PTR [edx+8], ecx
; Line 68
	mov	eax, DWORD PTR _rec$[ebp]
	mov	ecx, DWORD PTR [eax+8]
	mov	edx, DWORD PTR [ecx+4]
	mov	eax, DWORD PTR _cdfa$[ebp]
	mov	ecx, DWORD PTR [eax]
	mov	DWORD PTR [edx+52], ecx
; Line 69
	mov	eax, DWORD PTR _rec$[ebp]
	mov	ecx, DWORD PTR [eax+8]
	mov	edx, DWORD PTR [ecx+4]
	mov	eax, DWORD PTR _s$[ebp]
	mov	DWORD PTR [edx+56], eax
$LN3@noViableAl:
; Line 71
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 192				; 000000c0H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_noViableAlt ENDP
_TEXT	ENDS
PUBLIC	_antlr3dfaspecialStateTransition
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT _antlr3dfaspecialStateTransition
_TEXT	SEGMENT
_ctx$ = 8						; size = 4
_recognizer$ = 12					; size = 4
_is$ = 16						; size = 4
_dfa$ = 20						; size = 4
_s$ = 24						; size = 4
_antlr3dfaspecialStateTransition PROC			; COMDAT
; Line 194
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
; Line 195
	or	eax, -1
; Line 196
	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
_antlr3dfaspecialStateTransition ENDP
_TEXT	ENDS
PUBLIC	_antlr3dfaspecialTransition
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT _antlr3dfaspecialTransition
_TEXT	SEGMENT
_ctx$ = 8						; size = 4
_recognizer$ = 12					; size = 4
_is$ = 16						; size = 4
_dfa$ = 20						; size = 4
_s$ = 24						; size = 4
_antlr3dfaspecialTransition PROC			; COMDAT
; Line 202
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
; Line 203
	xor	eax, eax
; Line 204
	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
_antlr3dfaspecialTransition ENDP
_TEXT	ENDS
END
