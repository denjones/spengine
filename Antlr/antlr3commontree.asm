﻿; Listing generated by Microsoft (R) Optimizing Compiler Version 16.00.40219.01 

	TITLE	C:\Users\pa\repos\spengine\Antlr\antlr3commontree.c
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB MSVCRTD
INCLUDELIB OLDNAMES

PUBLIC	_antlr3SetCTAPI
PUBLIC	_antlr3ArboretumNew
EXTRN	_antlr3StackNew:PROC
EXTRN	__imp__free:PROC
EXTRN	_antlr3VectorFactoryNew:PROC
EXTRN	__imp__malloc:PROC
EXTRN	__RTC_CheckEsp:PROC
EXTRN	__RTC_Shutdown:PROC
EXTRN	__RTC_InitBase:PROC
;	COMDAT rtc$TMZ
; File c:\users\pa\repos\spengine\antlr\antlr3commontree.c
rtc$TMZ	SEGMENT
__RTC_Shutdown.rtc$TMZ DD FLAT:__RTC_Shutdown
rtc$TMZ	ENDS
;	COMDAT rtc$IMZ
rtc$IMZ	SEGMENT
__RTC_InitBase.rtc$IMZ DD FLAT:__RTC_InitBase
; Function compile flags: /Odtp /RTCsu /ZI
rtc$IMZ	ENDS
;	COMDAT _antlr3ArboretumNew
_TEXT	SEGMENT
_factory$ = -8						; size = 4
_strFactory$ = 8					; size = 4
_antlr3ArboretumNew PROC				; COMDAT
; Line 66
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
; Line 71
	mov	esi, esp
	push	192					; 000000c0H
	call	DWORD PTR __imp__malloc
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	DWORD PTR _factory$[ebp], eax
; Line 72
	cmp	DWORD PTR _factory$[ebp], 0
	jne	SHORT $LN2@antlr3Arbo
; Line 74
	xor	eax, eax
	jmp	$LN3@antlr3Arbo
$LN2@antlr3Arbo:
; Line 80
	push	0
	call	_antlr3VectorFactoryNew
	add	esp, 4
	mov	ecx, DWORD PTR _factory$[ebp]
	mov	DWORD PTR [ecx+168], eax
; Line 81
	mov	eax, DWORD PTR _factory$[ebp]
	cmp	DWORD PTR [eax+168], 0
	jne	SHORT $LN1@antlr3Arbo
; Line 83
	mov	esi, esp
	mov	eax, DWORD PTR _factory$[ebp]
	push	eax
	call	DWORD PTR __imp__free
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 84
	xor	eax, eax
	jmp	$LN3@antlr3Arbo
$LN1@antlr3Arbo:
; Line 93
	push	0
	call	_antlr3StackNew
	add	esp, 4
	mov	ecx, DWORD PTR _factory$[ebp]
	mov	DWORD PTR [ecx+172], eax
; Line 97
	mov	eax, DWORD PTR _factory$[ebp]
	mov	DWORD PTR [eax+176], OFFSET _newPoolTree
; Line 98
	mov	eax, DWORD PTR _factory$[ebp]
	mov	DWORD PTR [eax+180], OFFSET _newFromTree
; Line 99
	mov	eax, DWORD PTR _factory$[ebp]
	mov	DWORD PTR [eax+184], OFFSET _newFromToken
; Line 100
	mov	eax, DWORD PTR _factory$[ebp]
	mov	DWORD PTR [eax+188], OFFSET _factoryClose
; Line 104
	mov	eax, DWORD PTR _factory$[ebp]
	mov	DWORD PTR [eax+4], -1
; Line 105
	mov	eax, DWORD PTR _factory$[ebp]
	mov	DWORD PTR [eax], 0
; Line 106
	mov	eax, DWORD PTR _factory$[ebp]
	push	eax
	call	_newPool
	add	esp, 4
; Line 111
	mov	eax, DWORD PTR _factory$[ebp]
	add	eax, 12					; 0000000cH
	push	eax
	call	_antlr3SetCTAPI
	add	esp, 4
; Line 116
	mov	eax, DWORD PTR _factory$[ebp]
	mov	ecx, DWORD PTR _factory$[ebp]
	mov	DWORD PTR [eax+36], ecx
; Line 117
	mov	eax, DWORD PTR _factory$[ebp]
	mov	ecx, DWORD PTR _strFactory$[ebp]
	mov	DWORD PTR [eax+56], ecx
; Line 119
	mov	eax, DWORD PTR _factory$[ebp]
$LN3@antlr3Arbo:
; Line 121
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_antlr3ArboretumNew ENDP
_TEXT	ENDS
EXTRN	__imp__realloc:PROC
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT _newPool
_TEXT	SEGMENT
_factory$ = 8						; size = 4
_newPool PROC						; COMDAT
; Line 125
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
; Line 128
	mov	eax, DWORD PTR _factory$[ebp]
	mov	ecx, DWORD PTR [eax+4]
	add	ecx, 1
	mov	edx, DWORD PTR _factory$[ebp]
	mov	DWORD PTR [edx+4], ecx
; Line 135
	mov	eax, DWORD PTR _factory$[ebp]
	mov	ecx, DWORD PTR [eax+4]
	lea	edx, DWORD PTR [ecx*4+4]
	mov	esi, esp
	push	edx
	mov	eax, DWORD PTR _factory$[ebp]
	mov	ecx, DWORD PTR [eax]
	push	ecx
	call	DWORD PTR __imp__realloc
	add	esp, 8
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	edx, DWORD PTR _factory$[ebp]
	mov	DWORD PTR [edx], eax
; Line 141
	mov	esi, esp
	push	159744					; 00027000H
	call	DWORD PTR __imp__malloc
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	ecx, DWORD PTR _factory$[ebp]
	mov	edx, DWORD PTR [ecx+4]
	mov	ecx, DWORD PTR _factory$[ebp]
	mov	ecx, DWORD PTR [ecx]
	mov	DWORD PTR [ecx+edx*4], eax
; Line 146
	mov	eax, DWORD PTR _factory$[ebp]
	mov	DWORD PTR [eax+8], 0
; Line 151
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 192				; 000000c0H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_newPool ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _newPoolTree
_TEXT	SEGMENT
_tree$ = -8						; size = 4
_factory$ = 8						; size = 4
_newPoolTree PROC					; COMDAT
; Line 155
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
; Line 160
	mov	esi, esp
	mov	eax, DWORD PTR _factory$[ebp]
	mov	ecx, DWORD PTR [eax+172]
	push	ecx
	mov	edx, DWORD PTR _factory$[ebp]
	mov	eax, DWORD PTR [edx+172]
	mov	ecx, DWORD PTR [eax+28]
	call	ecx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	DWORD PTR _tree$[ebp], eax
; Line 162
	cmp	DWORD PTR _tree$[ebp], 0
	je	SHORT $LN2@newPoolTre
; Line 169
	mov	esi, esp
	mov	eax, DWORD PTR _factory$[ebp]
	mov	ecx, DWORD PTR [eax+172]
	push	ecx
	mov	edx, DWORD PTR _factory$[ebp]
	mov	eax, DWORD PTR [edx+172]
	mov	ecx, DWORD PTR [eax+12]
	call	ecx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 170
	mov	eax, DWORD PTR _tree$[ebp]
	jmp	SHORT $LN3@newPoolTre
$LN2@newPoolTre:
; Line 175
	mov	eax, DWORD PTR _factory$[ebp]
	cmp	DWORD PTR [eax+8], 1024			; 00000400H
	jb	SHORT $LN1@newPoolTre
; Line 179
	mov	eax, DWORD PTR _factory$[ebp]
	push	eax
	call	_newPool
	add	esp, 4
$LN1@newPoolTre:
; Line 185
	mov	eax, DWORD PTR _factory$[ebp]
	mov	ecx, DWORD PTR [eax+4]
	mov	edx, DWORD PTR _factory$[ebp]
	mov	eax, DWORD PTR [edx]
	mov	edx, DWORD PTR _factory$[ebp]
	mov	edx, DWORD PTR [edx+8]
	imul	edx, 156				; 0000009cH
	add	edx, DWORD PTR [eax+ecx*4]
	mov	DWORD PTR _tree$[ebp], edx
; Line 186
	mov	eax, DWORD PTR _factory$[ebp]
	mov	ecx, DWORD PTR [eax+8]
	add	ecx, 1
	mov	edx, DWORD PTR _factory$[ebp]
	mov	DWORD PTR [edx+8], ecx
; Line 190
	mov	eax, DWORD PTR _tree$[ebp]
	push	eax
	call	_antlr3SetCTAPI
	add	esp, 4
; Line 195
	mov	eax, DWORD PTR _tree$[ebp]
	mov	ecx, DWORD PTR _factory$[ebp]
	mov	DWORD PTR [eax+24], ecx
; Line 196
	mov	eax, DWORD PTR _tree$[ebp]
	mov	ecx, DWORD PTR _factory$[ebp]
	mov	edx, DWORD PTR [ecx+56]
	mov	DWORD PTR [eax+44], edx
; Line 203
	mov	eax, DWORD PTR _tree$[ebp]
	mov	ecx, DWORD PTR _tree$[ebp]
	mov	DWORD PTR [eax+28], ecx
; Line 208
	mov	eax, DWORD PTR _tree$[ebp]
	add	eax, 28					; 0000001cH
$LN3@newPoolTre:
; Line 209
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_newPoolTree ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _newFromTree
_TEXT	SEGMENT
_newTree$ = -8						; size = 4
_factory$ = 8						; size = 4
_tree$ = 12						; size = 4
_newFromTree PROC					; COMDAT
; Line 214
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
; Line 217
	mov	esi, esp
	mov	eax, DWORD PTR _factory$[ebp]
	push	eax
	mov	ecx, DWORD PTR _factory$[ebp]
	mov	edx, DWORD PTR [ecx+176]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	DWORD PTR _newTree$[ebp], eax
; Line 219
	cmp	DWORD PTR _newTree$[ebp], 0
	jne	SHORT $LN1@newFromTre
; Line 221
	xor	eax, eax
	jmp	SHORT $LN2@newFromTre
$LN1@newFromTre:
; Line 226
	mov	eax, DWORD PTR _newTree$[ebp]
	mov	ecx, DWORD PTR [eax]
	mov	edx, DWORD PTR _tree$[ebp]
	mov	eax, DWORD PTR [edx+12]
	mov	DWORD PTR [ecx+12], eax
; Line 227
	mov	eax, DWORD PTR _newTree$[ebp]
	mov	ecx, DWORD PTR _tree$[ebp]
	mov	edx, DWORD PTR [ecx+32]
	mov	DWORD PTR [eax+4], edx
; Line 229
	mov	eax, DWORD PTR _newTree$[ebp]
$LN2@newFromTre:
; Line 230
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_newFromTree ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _newFromToken
_TEXT	SEGMENT
_newTree$ = -8						; size = 4
_factory$ = 8						; size = 4
_token$ = 12						; size = 4
_newFromToken PROC					; COMDAT
; Line 234
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
; Line 237
	mov	esi, esp
	mov	eax, DWORD PTR _factory$[ebp]
	push	eax
	mov	ecx, DWORD PTR _factory$[ebp]
	mov	edx, DWORD PTR [ecx+176]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	DWORD PTR _newTree$[ebp], eax
; Line 239
	cmp	DWORD PTR _newTree$[ebp], 0
	jne	SHORT $LN1@newFromTok
; Line 241
	xor	eax, eax
	jmp	SHORT $LN2@newFromTok
$LN1@newFromTok:
; Line 246
	mov	eax, DWORD PTR _newTree$[ebp]
	mov	ecx, DWORD PTR [eax]
	mov	edx, DWORD PTR _token$[ebp]
	mov	DWORD PTR [ecx+12], edx
; Line 248
	mov	eax, DWORD PTR _newTree$[ebp]
$LN2@newFromTok:
; Line 249
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_newFromToken ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _factoryClose
_TEXT	SEGMENT
_poolCount$ = -8					; size = 4
_factory$ = 8						; size = 4
_factoryClose PROC					; COMDAT
; Line 253
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
; Line 259
	mov	esi, esp
	mov	eax, DWORD PTR _factory$[ebp]
	mov	ecx, DWORD PTR [eax+168]
	push	ecx
	mov	edx, DWORD PTR _factory$[ebp]
	mov	eax, DWORD PTR [edx+168]
	mov	ecx, DWORD PTR [eax+196]
	call	ecx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 261
	mov	eax, DWORD PTR _factory$[ebp]
	cmp	DWORD PTR [eax+172], 0
	je	SHORT $LN4@factoryClo
; Line 263
	mov	esi, esp
	mov	eax, DWORD PTR _factory$[ebp]
	mov	ecx, DWORD PTR [eax+172]
	push	ecx
	mov	edx, DWORD PTR _factory$[ebp]
	mov	eax, DWORD PTR [edx+172]
	mov	ecx, DWORD PTR [eax+8]
	call	ecx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
$LN4@factoryClo:
; Line 269
	mov	DWORD PTR _poolCount$[ebp], 0
	jmp	SHORT $LN3@factoryClo
$LN2@factoryClo:
	mov	eax, DWORD PTR _poolCount$[ebp]
	add	eax, 1
	mov	DWORD PTR _poolCount$[ebp], eax
$LN3@factoryClo:
	mov	eax, DWORD PTR _factory$[ebp]
	mov	ecx, DWORD PTR _poolCount$[ebp]
	cmp	ecx, DWORD PTR [eax+4]
	jg	SHORT $LN1@factoryClo
; Line 273
	mov	eax, DWORD PTR _factory$[ebp]
	mov	ecx, DWORD PTR [eax]
	mov	esi, esp
	mov	edx, DWORD PTR _poolCount$[ebp]
	mov	eax, DWORD PTR [ecx+edx*4]
	push	eax
	call	DWORD PTR __imp__free
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 274
	mov	eax, DWORD PTR _factory$[ebp]
	mov	ecx, DWORD PTR [eax]
	mov	edx, DWORD PTR _poolCount$[ebp]
	mov	DWORD PTR [ecx+edx*4], 0
; Line 275
	jmp	SHORT $LN2@factoryClo
$LN1@factoryClo:
; Line 280
	mov	esi, esp
	mov	eax, DWORD PTR _factory$[ebp]
	mov	ecx, DWORD PTR [eax]
	push	ecx
	call	DWORD PTR __imp__free
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 284
	mov	esi, esp
	mov	eax, DWORD PTR _factory$[ebp]
	push	eax
	call	DWORD PTR __imp__free
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 285
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_factoryClose ENDP
_TEXT	ENDS
EXTRN	_antlr3BaseTreeNew:PROC
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT _antlr3SetCTAPI
_TEXT	SEGMENT
_tree$ = 8						; size = 4
_antlr3SetCTAPI PROC					; COMDAT
; Line 290
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
; Line 293
	mov	eax, DWORD PTR _tree$[ebp]
	add	eax, 28					; 0000001cH
	push	eax
	call	_antlr3BaseTreeNew
	add	esp, 4
; Line 299
	mov	eax, DWORD PTR _tree$[ebp]
	mov	ecx, DWORD PTR _tree$[ebp]
	mov	DWORD PTR [eax+28], ecx
; Line 303
	mov	eax, DWORD PTR _tree$[ebp]
	mov	DWORD PTR [eax+124], OFFSET _isNilNode
; Line 304
	mov	eax, DWORD PTR _tree$[ebp]
	mov	DWORD PTR [eax+136], OFFSET _toString
; Line 305
	mov	eax, DWORD PTR _tree$[ebp]
	mov	DWORD PTR [eax+72], OFFSET _dupNode
; Line 306
	mov	eax, DWORD PTR _tree$[ebp]
	mov	DWORD PTR [eax+116], OFFSET _getLine
; Line 307
	mov	eax, DWORD PTR _tree$[ebp]
	mov	DWORD PTR [eax+80], OFFSET _getCharPositionInLine
; Line 308
	mov	eax, DWORD PTR _tree$[ebp]
	mov	DWORD PTR [eax+136], OFFSET _toString
; Line 309
	mov	eax, DWORD PTR _tree$[ebp]
	mov	DWORD PTR [eax+108], OFFSET _getType
; Line 310
	mov	eax, DWORD PTR _tree$[ebp]
	mov	DWORD PTR [eax+120], OFFSET _getText
; Line 311
	mov	eax, DWORD PTR _tree$[ebp]
	mov	DWORD PTR [eax+48], OFFSET _getToken
; Line 312
	mov	eax, DWORD PTR _tree$[ebp]
	mov	DWORD PTR [eax+100], OFFSET _getParent
; Line 313
	mov	eax, DWORD PTR _tree$[ebp]
	mov	DWORD PTR [eax+104], OFFSET _setParent
; Line 314
	mov	eax, DWORD PTR _tree$[ebp]
	mov	DWORD PTR [eax+88], OFFSET _setChildIndex
; Line 315
	mov	eax, DWORD PTR _tree$[ebp]
	mov	DWORD PTR [eax+92], OFFSET _getChildIndex
; Line 316
	mov	eax, DWORD PTR _tree$[ebp]
	mov	DWORD PTR [eax+60], OFFSET _createChildrenList
; Line 317
	mov	eax, DWORD PTR _tree$[ebp]
	mov	DWORD PTR [eax+148], OFFSET _reuse
; Line 318
	mov	eax, DWORD PTR _tree$[ebp]
	mov	DWORD PTR [eax+152], 0
; Line 319
	mov	eax, DWORD PTR _tree$[ebp]
	mov	DWORD PTR [eax+32], 0
; Line 321
	mov	eax, DWORD PTR _tree$[ebp]
	mov	DWORD PTR [eax+36], 0
; Line 323
	mov	eax, DWORD PTR _tree$[ebp]
	mov	DWORD PTR [eax+12], 0
; Line 324
	mov	eax, DWORD PTR _tree$[ebp]
	mov	DWORD PTR [eax+4], 0
; Line 325
	mov	eax, DWORD PTR _tree$[ebp]
	mov	DWORD PTR [eax+8], 0
; Line 326
	mov	eax, DWORD PTR _tree$[ebp]
	mov	DWORD PTR [eax+16], 0
; Line 327
	mov	eax, DWORD PTR _tree$[ebp]
	mov	DWORD PTR [eax+20], -1
; Line 330
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 192				; 000000c0H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_antlr3SetCTAPI ENDP
_TEXT	ENDS
PUBLIC	_antlr3CommonTreeNew
EXTRN	__imp__calloc:PROC
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT _antlr3CommonTreeNew
_TEXT	SEGMENT
_tree$ = -8						; size = 4
_antlr3CommonTreeNew PROC				; COMDAT
; Line 338
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
; Line 340
	mov	esi, esp
	push	156					; 0000009cH
	push	1
	call	DWORD PTR __imp__calloc
	add	esp, 8
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	DWORD PTR _tree$[ebp], eax
; Line 342
	cmp	DWORD PTR _tree$[ebp], 0
	jne	SHORT $LN1@antlr3Comm
; Line 344
	xor	eax, eax
	jmp	SHORT $LN2@antlr3Comm
$LN1@antlr3Comm:
; Line 347
	mov	eax, DWORD PTR _tree$[ebp]
	push	eax
	call	_antlr3SetCTAPI
	add	esp, 4
; Line 349
	mov	eax, DWORD PTR _tree$[ebp]
$LN2@antlr3Comm:
; Line 350
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_antlr3CommonTreeNew ENDP
_TEXT	ENDS
PUBLIC	_antlr3CommonTreeNewFromToken
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT _antlr3CommonTreeNewFromToken
_TEXT	SEGMENT
_newTree$ = -8						; size = 4
_token$ = 8						; size = 4
_antlr3CommonTreeNewFromToken PROC			; COMDAT
; Line 354
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
; Line 357
	call	_antlr3CommonTreeNew
	mov	DWORD PTR _newTree$[ebp], eax
; Line 359
	cmp	DWORD PTR _newTree$[ebp], 0
	jne	SHORT $LN1@antlr3Comm@2
; Line 361
	xor	eax, eax
	jmp	SHORT $LN2@antlr3Comm@2
$LN1@antlr3Comm@2:
; Line 366
	mov	eax, DWORD PTR _newTree$[ebp]
	mov	ecx, DWORD PTR _token$[ebp]
	mov	DWORD PTR [eax+12], ecx
; Line 367
	mov	eax, DWORD PTR _newTree$[ebp]
$LN2@antlr3Comm@2:
; Line 368
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_antlr3CommonTreeNewFromToken ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _createChildrenList
_TEXT	SEGMENT
_tree$ = 8						; size = 4
_createChildrenList PROC				; COMDAT
; Line 375
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
; Line 376
	mov	eax, DWORD PTR _tree$[ebp]
	mov	ecx, DWORD PTR [eax]
	mov	edx, DWORD PTR [ecx+24]
	mov	esi, esp
	mov	eax, DWORD PTR [edx+168]
	push	eax
	mov	ecx, DWORD PTR _tree$[ebp]
	mov	edx, DWORD PTR [ecx]
	mov	eax, DWORD PTR [edx+24]
	mov	ecx, DWORD PTR [eax+168]
	mov	edx, DWORD PTR [ecx+200]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	ecx, DWORD PTR _tree$[ebp]
	mov	DWORD PTR [ecx+8], eax
; Line 377
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 192				; 000000c0H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_createChildrenList ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _getToken
_TEXT	SEGMENT
_tree$ = 8						; size = 4
_getToken PROC						; COMDAT
; Line 382
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
; Line 389
	mov	eax, DWORD PTR _tree$[ebp]
	mov	ecx, DWORD PTR [eax]
	mov	eax, DWORD PTR [ecx+12]
; Line 390
	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
_getToken ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _dupNode
_TEXT	SEGMENT
_theOld$ = -8						; size = 4
_tree$ = 8						; size = 4
_dupNode PROC						; COMDAT
; Line 394
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
; Line 400
	mov	eax, DWORD PTR _tree$[ebp]
	mov	ecx, DWORD PTR [eax]
	mov	DWORD PTR _theOld$[ebp], ecx
; Line 404
	mov	esi, esp
	mov	eax, DWORD PTR _theOld$[ebp]
	push	eax
	mov	ecx, DWORD PTR _theOld$[ebp]
	mov	edx, DWORD PTR [ecx+24]
	push	edx
	mov	eax, DWORD PTR _theOld$[ebp]
	mov	ecx, DWORD PTR [eax+24]
	mov	edx, DWORD PTR [ecx+180]
	call	edx
	add	esp, 8
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 405
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_dupNode ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _isNilNode
_TEXT	SEGMENT
_tree$ = 8						; size = 4
_isNilNode PROC						; COMDAT
; Line 409
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
; Line 412
	mov	eax, DWORD PTR _tree$[ebp]
	mov	ecx, DWORD PTR [eax]
	cmp	DWORD PTR [ecx+12], 0
	jne	SHORT $LN2@isNilNode
; Line 414
	mov	al, 1
	jmp	SHORT $LN3@isNilNode
; Line 416
	jmp	SHORT $LN3@isNilNode
$LN2@isNilNode:
; Line 418
	xor	al, al
$LN3@isNilNode:
; Line 420
	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
_isNilNode ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _getType
_TEXT	SEGMENT
_theTree$ = -8						; size = 4
_tree$ = 8						; size = 4
_getType PROC						; COMDAT
; Line 424
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
; Line 427
	mov	eax, DWORD PTR _tree$[ebp]
	mov	ecx, DWORD PTR [eax]
	mov	DWORD PTR _theTree$[ebp], ecx
; Line 429
	mov	eax, DWORD PTR _theTree$[ebp]
	cmp	DWORD PTR [eax+12], 0
	jne	SHORT $LN2@getType
; Line 431
	xor	eax, eax
	jmp	SHORT $LN3@getType
; Line 433
	jmp	SHORT $LN3@getType
$LN2@getType:
; Line 435
	mov	esi, esp
	mov	eax, DWORD PTR _theTree$[ebp]
	mov	ecx, DWORD PTR [eax+12]
	push	ecx
	mov	edx, DWORD PTR _theTree$[ebp]
	mov	eax, DWORD PTR [edx+12]
	mov	ecx, DWORD PTR [eax+84]
	call	ecx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
$LN3@getType:
; Line 437
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_getType ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _getText
_TEXT	SEGMENT
_tree$ = 8						; size = 4
_getText PROC						; COMDAT
; Line 441
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
; Line 442
	mov	esi, esp
	mov	eax, DWORD PTR _tree$[ebp]
	push	eax
	mov	ecx, DWORD PTR _tree$[ebp]
	mov	edx, DWORD PTR [ecx+108]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 443
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 192				; 000000c0H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_getText ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _getLine
_TEXT	SEGMENT
_child$34865 = -32					; size = 4
_token$ = -20						; size = 4
_cTree$ = -8						; size = 4
_tree$ = 8						; size = 4
_getLine PROC						; COMDAT
; Line 446
	push	ebp
	mov	ebp, esp
	sub	esp, 228				; 000000e4H
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-228]
	mov	ecx, 57					; 00000039H
	mov	eax, -858993460				; ccccccccH
	rep stosd
; Line 450
	mov	eax, DWORD PTR _tree$[ebp]
	mov	ecx, DWORD PTR [eax]
	mov	DWORD PTR _cTree$[ebp], ecx
; Line 452
	mov	eax, DWORD PTR _cTree$[ebp]
	mov	ecx, DWORD PTR [eax+12]
	mov	DWORD PTR _token$[ebp], ecx
; Line 454
	cmp	DWORD PTR _token$[ebp], 0
	je	SHORT $LN2@getLine
	mov	esi, esp
	mov	eax, DWORD PTR _token$[ebp]
	push	eax
	mov	ecx, DWORD PTR _token$[ebp]
	mov	edx, DWORD PTR [ecx+92]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
	test	eax, eax
	jne	SHORT $LN3@getLine
$LN2@getLine:
; Line 456
	mov	esi, esp
	mov	eax, DWORD PTR _tree$[ebp]
	push	eax
	mov	ecx, DWORD PTR _tree$[ebp]
	mov	edx, DWORD PTR [ecx+68]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
	test	eax, eax
	jbe	SHORT $LN1@getLine
; Line 460
	mov	esi, esp
	push	0
	mov	eax, DWORD PTR _tree$[ebp]
	push	eax
	mov	ecx, DWORD PTR _tree$[ebp]
	mov	edx, DWORD PTR [ecx+56]
	call	edx
	add	esp, 8
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	DWORD PTR _child$34865[ebp], eax
; Line 461
	mov	esi, esp
	mov	eax, DWORD PTR _child$34865[ebp]
	push	eax
	mov	ecx, DWORD PTR _child$34865[ebp]
	mov	edx, DWORD PTR [ecx+88]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
	jmp	SHORT $LN4@getLine
$LN1@getLine:
; Line 463
	xor	eax, eax
	jmp	SHORT $LN4@getLine
$LN3@getLine:
; Line 465
	mov	esi, esp
	mov	eax, DWORD PTR _token$[ebp]
	push	eax
	mov	ecx, DWORD PTR _token$[ebp]
	mov	edx, DWORD PTR [ecx+92]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
$LN4@getLine:
; Line 466
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 228				; 000000e4H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_getLine ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _getCharPositionInLine
_TEXT	SEGMENT
_child$34876 = -20					; size = 4
_token$ = -8						; size = 4
_tree$ = 8						; size = 4
_getCharPositionInLine PROC				; COMDAT
; Line 469
	push	ebp
	mov	ebp, esp
	sub	esp, 216				; 000000d8H
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-216]
	mov	ecx, 54					; 00000036H
	mov	eax, -858993460				; ccccccccH
	rep stosd
; Line 472
	mov	eax, DWORD PTR _tree$[ebp]
	mov	ecx, DWORD PTR [eax]
	mov	edx, DWORD PTR [ecx+12]
	mov	DWORD PTR _token$[ebp], edx
; Line 474
	cmp	DWORD PTR _token$[ebp], 0
	je	SHORT $LN2@getCharPos
	mov	esi, esp
	mov	eax, DWORD PTR _token$[ebp]
	push	eax
	mov	ecx, DWORD PTR _token$[ebp]
	mov	edx, DWORD PTR [ecx+100]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
	cmp	eax, -1
	jne	SHORT $LN3@getCharPos
$LN2@getCharPos:
; Line 476
	mov	esi, esp
	mov	eax, DWORD PTR _tree$[ebp]
	push	eax
	mov	ecx, DWORD PTR _tree$[ebp]
	mov	edx, DWORD PTR [ecx+68]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
	test	eax, eax
	jbe	SHORT $LN1@getCharPos
; Line 480
	mov	esi, esp
	push	0
	mov	eax, DWORD PTR _tree$[ebp]
	push	eax
	mov	ecx, DWORD PTR _tree$[ebp]
	mov	edx, DWORD PTR [ecx+56]
	call	edx
	add	esp, 8
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	DWORD PTR _child$34876[ebp], eax
; Line 482
	mov	esi, esp
	mov	eax, DWORD PTR _child$34876[ebp]
	push	eax
	mov	ecx, DWORD PTR _child$34876[ebp]
	mov	edx, DWORD PTR [ecx+52]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
	jmp	SHORT $LN4@getCharPos
$LN1@getCharPos:
; Line 484
	xor	eax, eax
	jmp	SHORT $LN4@getCharPos
$LN3@getCharPos:
; Line 486
	mov	esi, esp
	mov	eax, DWORD PTR _token$[ebp]
	push	eax
	mov	ecx, DWORD PTR _token$[ebp]
	mov	edx, DWORD PTR [ecx+100]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
$LN4@getCharPos:
; Line 487
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 216				; 000000d8H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_getCharPositionInLine ENDP
_TEXT	ENDS
PUBLIC	??_C@_03ILAMHENH@nil?$AA@			; `string'
;	COMDAT ??_C@_03ILAMHENH@nil?$AA@
CONST	SEGMENT
??_C@_03ILAMHENH@nil?$AA@ DB 'nil', 00H			; `string'
; Function compile flags: /Odtp /RTCsu /ZI
CONST	ENDS
;	COMDAT _toString
_TEXT	SEGMENT
_nilNode$34882 = -8					; size = 4
_tree$ = 8						; size = 4
_toString PROC						; COMDAT
; Line 490
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
; Line 491
	mov	esi, esp
	mov	eax, DWORD PTR _tree$[ebp]
	push	eax
	mov	ecx, DWORD PTR _tree$[ebp]
	mov	edx, DWORD PTR [ecx+96]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
	movzx	eax, al
	cmp	eax, 1
	jne	SHORT $LN1@toString
; Line 495
	mov	esi, esp
	push	3
	push	OFFSET ??_C@_03ILAMHENH@nil?$AA@
	mov	eax, DWORD PTR _tree$[ebp]
	mov	ecx, DWORD PTR [eax+16]
	push	ecx
	mov	edx, DWORD PTR _tree$[ebp]
	mov	eax, DWORD PTR [edx+16]
	mov	ecx, DWORD PTR [eax+16]
	call	ecx
	add	esp, 12					; 0000000cH
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	DWORD PTR _nilNode$34882[ebp], eax
; Line 497
	mov	eax, DWORD PTR _nilNode$34882[ebp]
	jmp	SHORT $LN2@toString
$LN1@toString:
; Line 500
	mov	eax, DWORD PTR _tree$[ebp]
	mov	ecx, DWORD PTR [eax]
	mov	esi, esp
	mov	edx, DWORD PTR [ecx+12]
	push	edx
	mov	eax, DWORD PTR _tree$[ebp]
	mov	ecx, DWORD PTR [eax]
	mov	edx, DWORD PTR [ecx+12]
	mov	eax, DWORD PTR [edx+72]
	call	eax
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
$LN2@toString:
; Line 501
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_toString ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _getParent
_TEXT	SEGMENT
_tree$ = 8						; size = 4
_getParent PROC						; COMDAT
; Line 505
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
; Line 506
	mov	eax, DWORD PTR _tree$[ebp]
	mov	ecx, DWORD PTR [eax]
	mov	eax, DWORD PTR [ecx+16]
	add	eax, 28					; 0000001cH
; Line 507
	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
_getParent ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _setParent
_TEXT	SEGMENT
tv67 = -196						; size = 4
_tree$ = 8						; size = 4
_parent$ = 12						; size = 4
_setParent PROC						; COMDAT
; Line 511
	push	ebp
	mov	ebp, esp
	sub	esp, 196				; 000000c4H
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-196]
	mov	ecx, 49					; 00000031H
	mov	eax, -858993460				; ccccccccH
	rep stosd
; Line 512
	cmp	DWORD PTR _parent$[ebp], 0
	jne	SHORT $LN3@setParent
	mov	DWORD PTR tv67[ebp], 0
	jmp	SHORT $LN4@setParent
$LN3@setParent:
	mov	eax, DWORD PTR _parent$[ebp]
	mov	ecx, DWORD PTR [eax]
	mov	edx, DWORD PTR [ecx+16]
	mov	DWORD PTR tv67[ebp], edx
$LN4@setParent:
	mov	eax, DWORD PTR _tree$[ebp]
	mov	ecx, DWORD PTR [eax]
	mov	edx, DWORD PTR tv67[ebp]
	mov	DWORD PTR [ecx+16], edx
; Line 513
	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
_setParent ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _setChildIndex
_TEXT	SEGMENT
_tree$ = 8						; size = 4
_i$ = 12						; size = 4
_setChildIndex PROC					; COMDAT
; Line 517
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
; Line 518
	mov	eax, DWORD PTR _tree$[ebp]
	mov	ecx, DWORD PTR [eax]
	mov	edx, DWORD PTR _i$[ebp]
	mov	DWORD PTR [ecx+20], edx
; Line 519
	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
_setChildIndex ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _getChildIndex
_TEXT	SEGMENT
_tree$ = 8						; size = 4
_getChildIndex PROC					; COMDAT
; Line 522
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
; Line 523
	mov	eax, DWORD PTR _tree$[ebp]
	mov	ecx, DWORD PTR [eax]
	mov	eax, DWORD PTR [ecx+20]
; Line 524
	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
_getChildIndex ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _reuse
_TEXT	SEGMENT
_cTree$ = -8						; size = 4
_tree$ = 8						; size = 4
_reuse	PROC						; COMDAT
; Line 531
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
; Line 534
	mov	eax, DWORD PTR _tree$[ebp]
	mov	ecx, DWORD PTR [eax]
	mov	DWORD PTR _cTree$[ebp], ecx
; Line 536
	mov	eax, DWORD PTR _cTree$[ebp]
	cmp	DWORD PTR [eax+24], 0
	je	SHORT $LN3@reuse
; Line 539
	mov	eax, DWORD PTR _cTree$[ebp]
	cmp	DWORD PTR [eax+36], 0
	je	SHORT $LN1@reuse
; Line 542
	mov	esi, esp
	mov	eax, DWORD PTR _cTree$[ebp]
	mov	ecx, DWORD PTR [eax+36]
	push	ecx
	mov	edx, DWORD PTR _cTree$[ebp]
	mov	eax, DWORD PTR [edx+36]
	mov	ecx, DWORD PTR [eax+160]
	call	ecx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
$LN1@reuse:
; Line 544
	mov	esi, esp
	push	0
	mov	eax, DWORD PTR _tree$[ebp]
	push	eax
	mov	ecx, DWORD PTR _cTree$[ebp]
	mov	edx, DWORD PTR [ecx+24]
	mov	eax, DWORD PTR [edx+172]
	push	eax
	mov	ecx, DWORD PTR _cTree$[ebp]
	mov	edx, DWORD PTR [ecx+24]
	mov	eax, DWORD PTR [edx+172]
	mov	ecx, DWORD PTR [eax+20]
	call	ecx
	add	esp, 12					; 0000000cH
	cmp	esi, esp
	call	__RTC_CheckEsp
$LN3@reuse:
; Line 547
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_reuse	ENDP
_TEXT	ENDS
END