﻿; Listing generated by Microsoft (R) Optimizing Compiler Version 16.00.40219.01 

	TITLE	C:\Users\pa\repos\spengine\Antlr\antlr3commontreeadaptor.c
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB MSVCRTD
INCLUDELIB OLDNAMES

PUBLIC	_ANTLR3_TREE_ADAPTORNew
EXTRN	_antlr3TokenFactoryNew:PROC
EXTRN	_antlr3ArboretumNew:PROC
EXTRN	_antlr3BaseTreeAdaptorInit:PROC
EXTRN	__imp__malloc:PROC
EXTRN	__RTC_CheckEsp:PROC
EXTRN	__RTC_Shutdown:PROC
EXTRN	__RTC_InitBase:PROC
;	COMDAT rtc$TMZ
; File c:\users\pa\repos\spengine\antlr\antlr3commontreeadaptor.c
rtc$TMZ	SEGMENT
__RTC_Shutdown.rtc$TMZ DD FLAT:__RTC_Shutdown
rtc$TMZ	ENDS
;	COMDAT rtc$IMZ
rtc$IMZ	SEGMENT
__RTC_InitBase.rtc$IMZ DD FLAT:__RTC_InitBase
; Function compile flags: /Odtp /RTCsu /ZI
rtc$IMZ	ENDS
;	COMDAT _ANTLR3_TREE_ADAPTORNew
_TEXT	SEGMENT
_cta$ = -8						; size = 4
_strFactory$ = 8					; size = 4
_ANTLR3_TREE_ADAPTORNew PROC				; COMDAT
; Line 85
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
; Line 90
	mov	esi, esp
	push	180					; 000000b4H
	call	DWORD PTR __imp__malloc
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	DWORD PTR _cta$[ebp], eax
; Line 92
	cmp	DWORD PTR _cta$[ebp], 0
	jne	SHORT $LN1@ANTLR3_TRE
; Line 94
	xor	eax, eax
	jmp	$LN2@ANTLR3_TRE
$LN1@ANTLR3_TRE:
; Line 99
	push	0
	mov	eax, DWORD PTR _cta$[ebp]
	add	eax, 4
	push	eax
	call	_antlr3BaseTreeAdaptorInit
	add	esp, 8
; Line 105
	mov	eax, DWORD PTR _cta$[ebp]
	mov	DWORD PTR [eax+84], OFFSET _dupNode
; Line 107
	mov	eax, DWORD PTR _cta$[ebp]
	mov	DWORD PTR [eax+68], OFFSET _create
; Line 109
	mov	eax, DWORD PTR _cta$[ebp]
	mov	DWORD PTR [eax+136], OFFSET _createToken
; Line 111
	mov	eax, DWORD PTR _cta$[ebp]
	mov	DWORD PTR [eax+140], OFFSET _createTokenFromToken
; Line 113
	mov	eax, DWORD PTR _cta$[ebp]
	mov	DWORD PTR [eax+148], OFFSET _setTokenBoundaries
; Line 115
	mov	eax, DWORD PTR _cta$[ebp]
	mov	DWORD PTR [eax+152], OFFSET _getTokenStartIndex
; Line 117
	mov	eax, DWORD PTR _cta$[ebp]
	mov	DWORD PTR [eax+156], OFFSET _getTokenStopIndex
; Line 119
	mov	eax, DWORD PTR _cta$[ebp]
	mov	DWORD PTR [eax+96], OFFSET _getText
; Line 121
	mov	eax, DWORD PTR _cta$[ebp]
	mov	DWORD PTR [eax+88], OFFSET _getType
; Line 123
	mov	eax, DWORD PTR _cta$[ebp]
	mov	DWORD PTR [eax+108], OFFSET _getChild
; Line 125
	mov	eax, DWORD PTR _cta$[ebp]
	mov	DWORD PTR [eax+112], OFFSET _setChild
; Line 127
	mov	eax, DWORD PTR _cta$[ebp]
	mov	DWORD PTR [eax+40], OFFSET _setParent
; Line 129
	mov	eax, DWORD PTR _cta$[ebp]
	mov	DWORD PTR [eax+44], OFFSET _getParent
; Line 131
	mov	eax, DWORD PTR _cta$[ebp]
	mov	DWORD PTR [eax+120], OFFSET _setChildIndex
; Line 133
	mov	eax, DWORD PTR _cta$[ebp]
	mov	DWORD PTR [eax+116], OFFSET _deleteChild
; Line 135
	mov	eax, DWORD PTR _cta$[ebp]
	mov	DWORD PTR [eax+128], OFFSET _getChildCount
; Line 137
	mov	eax, DWORD PTR _cta$[ebp]
	mov	DWORD PTR [eax+124], OFFSET _getChildIndex
; Line 139
	mov	eax, DWORD PTR _cta$[ebp]
	mov	DWORD PTR [eax+172], OFFSET _ctaFree
; Line 141
	mov	eax, DWORD PTR _cta$[ebp]
	mov	DWORD PTR [eax+160], OFFSET _setDebugEventListener
; Line 143
	mov	eax, DWORD PTR _cta$[ebp]
	mov	DWORD PTR [eax+168], OFFSET _replaceChildren
; Line 145
	mov	eax, DWORD PTR _cta$[ebp]
	mov	DWORD PTR [eax+48], OFFSET _errorNode
; Line 149
	mov	eax, DWORD PTR _cta$[ebp]
	mov	ecx, DWORD PTR _cta$[ebp]
	mov	DWORD PTR [eax+4], ecx
; Line 153
	mov	eax, DWORD PTR _strFactory$[ebp]
	push	eax
	call	_antlr3ArboretumNew
	add	esp, 4
	mov	ecx, DWORD PTR _cta$[ebp]
	mov	DWORD PTR [ecx+176], eax
; Line 159
	push	0
	call	_antlr3TokenFactoryNew
	add	esp, 4
	mov	ecx, DWORD PTR _cta$[ebp]
	mov	DWORD PTR [ecx+12], eax
; Line 160
	mov	eax, DWORD PTR _cta$[ebp]
	mov	ecx, DWORD PTR [eax+12]
	mov	edx, DWORD PTR _strFactory$[ebp]
	mov	DWORD PTR [ecx+24], edx
; Line 164
	mov	eax, DWORD PTR _cta$[ebp]
	mov	ecx, DWORD PTR _strFactory$[ebp]
	mov	DWORD PTR [eax+8], ecx
; Line 168
	mov	eax, DWORD PTR _cta$[ebp]
	add	eax, 4
$LN2@ANTLR3_TRE:
; Line 169
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_ANTLR3_TREE_ADAPTORNew ENDP
_TEXT	ENDS
PUBLIC	_ANTLR3_TREE_ADAPTORDebugNew
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT _ANTLR3_TREE_ADAPTORDebugNew
_TEXT	SEGMENT
_ta$ = -8						; size = 4
_strFactory$ = 8					; size = 4
_debugger$ = 12						; size = 4
_ANTLR3_TREE_ADAPTORDebugNew PROC			; COMDAT
; Line 178
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
; Line 183
	mov	eax, DWORD PTR _strFactory$[ebp]
	push	eax
	call	_ANTLR3_TREE_ADAPTORNew
	add	esp, 4
	mov	DWORD PTR _ta$[ebp], eax
; Line 185
	cmp	DWORD PTR _ta$[ebp], 0
	je	SHORT $LN1@ANTLR3_TRE@2
; Line 189
	mov	eax, DWORD PTR _debugger$[ebp]
	push	eax
	mov	ecx, DWORD PTR _ta$[ebp]
	push	ecx
	call	_antlr3BaseTreeAdaptorInit
	add	esp, 8
; Line 191
	mov	eax, DWORD PTR _ta$[ebp]
	mov	DWORD PTR [eax+64], OFFSET _dbgCreate
; Line 193
	mov	eax, DWORD PTR _ta$[ebp]
	mov	DWORD PTR [eax+144], OFFSET _dbgSetTokenBoundaries
$LN1@ANTLR3_TRE@2:
; Line 196
	mov	eax, DWORD PTR _ta$[ebp]
; Line 197
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_ANTLR3_TREE_ADAPTORDebugNew ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _setDebugEventListener
_TEXT	SEGMENT
_adaptor$ = 8						; size = 4
_debugger$ = 12						; size = 4
_setDebugEventListener PROC				; COMDAT
; Line 203
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
; Line 206
	mov	eax, DWORD PTR _debugger$[ebp]
	push	eax
	mov	ecx, DWORD PTR _adaptor$[ebp]
	push	ecx
	call	_antlr3BaseTreeAdaptorInit
	add	esp, 8
; Line 209
	mov	eax, DWORD PTR _adaptor$[ebp]
	mov	DWORD PTR [eax+64], OFFSET _dbgCreate
; Line 211
	mov	eax, DWORD PTR _adaptor$[ebp]
	mov	DWORD PTR [eax+144], OFFSET _dbgSetTokenBoundaries
; Line 213
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 192				; 000000c0H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_setDebugEventListener ENDP
_TEXT	ENDS
EXTRN	__imp__free:PROC
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT _ctaFree
_TEXT	SEGMENT
_cta$ = -8						; size = 4
_adaptor$ = 8						; size = 4
_ctaFree PROC						; COMDAT
; Line 217
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
; Line 220
	mov	eax, DWORD PTR _adaptor$[ebp]
	mov	ecx, DWORD PTR [eax]
	mov	DWORD PTR _cta$[ebp], ecx
; Line 224
	mov	eax, DWORD PTR _adaptor$[ebp]
	mov	ecx, DWORD PTR [eax]
	mov	esi, esp
	mov	edx, DWORD PTR [ecx+176]
	push	edx
	mov	eax, DWORD PTR _cta$[ebp]
	mov	ecx, DWORD PTR [eax+176]
	mov	edx, DWORD PTR [ecx+188]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 228
	mov	esi, esp
	mov	eax, DWORD PTR _adaptor$[ebp]
	mov	ecx, DWORD PTR [eax+8]
	push	ecx
	mov	edx, DWORD PTR _adaptor$[ebp]
	mov	eax, DWORD PTR [edx+8]
	mov	ecx, DWORD PTR [eax+176]
	call	ecx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 233
	mov	esi, esp
	mov	eax, DWORD PTR _adaptor$[ebp]
	mov	ecx, DWORD PTR [eax]
	push	ecx
	call	DWORD PTR __imp__free
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 234
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_ctaFree ENDP
_TEXT	ENDS
PUBLIC	??_C@_0BA@IPNBIIJO@Tree?5Error?5Node?$AA@	; `string'
;	COMDAT ??_C@_0BA@IPNBIIJO@Tree?5Error?5Node?$AA@
CONST	SEGMENT
??_C@_0BA@IPNBIIJO@Tree?5Error?5Node?$AA@ DB 'Tree Error Node', 00H ; `string'
; Function compile flags: /Odtp /RTCsu /ZI
CONST	ENDS
;	COMDAT _errorNode
_TEXT	SEGMENT
_adaptor$ = 8						; size = 4
_ctnstream$ = 12					; size = 4
_startToken$ = 16					; size = 4
_stopToken$ = 20					; size = 4
_e$ = 24						; size = 4
_errorNode PROC						; COMDAT
; Line 240
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
; Line 246
	mov	esi, esp
	push	OFFSET ??_C@_0BA@IPNBIIJO@Tree?5Error?5Node?$AA@
	push	0
	mov	eax, DWORD PTR _adaptor$[ebp]
	push	eax
	mov	ecx, DWORD PTR _adaptor$[ebp]
	mov	edx, DWORD PTR [ecx+76]
	call	edx
	add	esp, 12					; 0000000cH
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 248
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 192				; 000000c0H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_errorNode ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _dupNode
_TEXT	SEGMENT
tv68 = -196						; size = 4
_adaptor$ = 8						; size = 4
_treeNode$ = 12						; size = 4
_dupNode PROC						; COMDAT
; Line 254
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
; Line 255
	cmp	DWORD PTR _treeNode$[ebp], 0
	jne	SHORT $LN3@dupNode
	mov	DWORD PTR tv68[ebp], 0
	jmp	SHORT $LN4@dupNode
$LN3@dupNode:
	mov	esi, esp
	mov	eax, DWORD PTR _treeNode$[ebp]
	push	eax
	mov	ecx, DWORD PTR _treeNode$[ebp]
	mov	edx, DWORD PTR [ecx+44]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	DWORD PTR tv68[ebp], eax
$LN4@dupNode:
	mov	eax, DWORD PTR tv68[ebp]
; Line 256
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 196				; 000000c4H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_dupNode ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _create
_TEXT	SEGMENT
_ct$ = -8						; size = 4
_adaptor$ = 8						; size = 4
_payload$ = 12						; size = 4
_create	PROC						; COMDAT
; Line 260
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
; Line 265
	mov	esi, esp
	mov	eax, DWORD PTR _payload$[ebp]
	push	eax
	mov	ecx, DWORD PTR _adaptor$[ebp]
	mov	edx, DWORD PTR [ecx]
	mov	eax, DWORD PTR [edx+176]
	push	eax
	mov	ecx, DWORD PTR _adaptor$[ebp]
	mov	edx, DWORD PTR [ecx]
	mov	eax, DWORD PTR [edx+176]
	mov	ecx, DWORD PTR [eax+184]
	call	ecx
	add	esp, 8
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	DWORD PTR _ct$[ebp], eax
; Line 269
	mov	eax, DWORD PTR _ct$[ebp]
; Line 270
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_create	ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _dbgCreate
_TEXT	SEGMENT
_ct$ = -8						; size = 4
_adaptor$ = 8						; size = 4
_payload$ = 12						; size = 4
_dbgCreate PROC						; COMDAT
; Line 273
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
; Line 276
	mov	eax, DWORD PTR _payload$[ebp]
	push	eax
	mov	ecx, DWORD PTR _adaptor$[ebp]
	push	ecx
	call	_create
	add	esp, 8
	mov	DWORD PTR _ct$[ebp], eax
; Line 277
	mov	esi, esp
	mov	eax, DWORD PTR _ct$[ebp]
	push	eax
	mov	ecx, DWORD PTR _adaptor$[ebp]
	mov	edx, DWORD PTR [ecx+12]
	push	edx
	mov	eax, DWORD PTR _adaptor$[ebp]
	mov	ecx, DWORD PTR [eax+12]
	mov	edx, DWORD PTR [ecx+140]
	call	edx
	add	esp, 8
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 279
	mov	eax, DWORD PTR _ct$[ebp]
; Line 280
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_dbgCreate ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _createToken
_TEXT	SEGMENT
_newToken$ = -8						; size = 4
_adaptor$ = 8						; size = 4
_tokenType$ = 12					; size = 4
_text$ = 16						; size = 4
_createToken PROC					; COMDAT
; Line 292
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
; Line 295
	mov	esi, esp
	mov	eax, DWORD PTR _adaptor$[ebp]
	mov	ecx, DWORD PTR [eax+8]
	push	ecx
	mov	edx, DWORD PTR _adaptor$[ebp]
	mov	eax, DWORD PTR [edx+8]
	mov	ecx, DWORD PTR [eax+164]
	call	ecx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	DWORD PTR _newToken$[ebp], eax
; Line 297
	cmp	DWORD PTR _newToken$[ebp], 0
	je	SHORT $LN1@createToke
; Line 299
	mov	eax, DWORD PTR _newToken$[ebp]
	mov	DWORD PTR [eax+44], 1
; Line 300
	mov	eax, DWORD PTR _newToken$[ebp]
	mov	ecx, DWORD PTR _text$[ebp]
	mov	DWORD PTR [eax+48], ecx
; Line 301
	mov	esi, esp
	mov	eax, DWORD PTR _tokenType$[ebp]
	push	eax
	mov	ecx, DWORD PTR _newToken$[ebp]
	push	ecx
	mov	edx, DWORD PTR _newToken$[ebp]
	mov	eax, DWORD PTR [edx+88]
	call	eax
	add	esp, 8
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 302
	mov	eax, DWORD PTR _adaptor$[ebp]
	mov	ecx, DWORD PTR [eax+8]
	mov	edx, DWORD PTR _newToken$[ebp]
	mov	eax, DWORD PTR [ecx+160]
	mov	DWORD PTR [edx+28], eax
; Line 303
	mov	eax, DWORD PTR _newToken$[ebp]
	mov	ecx, DWORD PTR _adaptor$[ebp]
	mov	edx, DWORD PTR [ecx+4]
	mov	DWORD PTR [eax+8], edx
$LN1@createToke:
; Line 305
	mov	eax, DWORD PTR _newToken$[ebp]
; Line 306
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_createToken ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _createTokenFromToken
_TEXT	SEGMENT
_text$35424 = -20					; size = 4
_newToken$ = -8						; size = 4
_adaptor$ = 8						; size = 4
_fromToken$ = 12					; size = 4
_createTokenFromToken PROC				; COMDAT
; Line 328
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
; Line 331
	mov	esi, esp
	mov	eax, DWORD PTR _adaptor$[ebp]
	mov	ecx, DWORD PTR [eax+8]
	push	ecx
	mov	edx, DWORD PTR _adaptor$[ebp]
	mov	eax, DWORD PTR [edx+8]
	mov	ecx, DWORD PTR [eax+164]
	call	ecx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	DWORD PTR _newToken$[ebp], eax
; Line 333
	cmp	DWORD PTR _newToken$[ebp], 0
	je	$LN3@createToke@2
; Line 340
	mov	eax, DWORD PTR _newToken$[ebp]
	mov	ecx, DWORD PTR _fromToken$[ebp]
	mov	edx, DWORD PTR [ecx+140]
	mov	DWORD PTR [eax+140], edx
; Line 342
	mov	eax, DWORD PTR _fromToken$[ebp]
	cmp	DWORD PTR [eax+44], 1
	jne	SHORT $LN2@createToke@2
; Line 344
	mov	eax, DWORD PTR _newToken$[ebp]
	mov	DWORD PTR [eax+44], 1
; Line 345
	mov	eax, DWORD PTR _newToken$[ebp]
	mov	ecx, DWORD PTR _fromToken$[ebp]
	mov	edx, DWORD PTR [ecx+48]
	mov	DWORD PTR [eax+48], edx
; Line 347
	jmp	SHORT $LN1@createToke@2
$LN2@createToke@2:
; Line 349
	mov	esi, esp
	mov	eax, DWORD PTR _fromToken$[ebp]
	push	eax
	mov	ecx, DWORD PTR _fromToken$[ebp]
	mov	edx, DWORD PTR [ecx+72]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	DWORD PTR _text$35424[ebp], eax
; Line 350
	mov	eax, DWORD PTR _newToken$[ebp]
	mov	DWORD PTR [eax+44], 2
; Line 351
	mov	esi, esp
	mov	eax, DWORD PTR _text$35424[ebp]
	mov	ecx, DWORD PTR [eax+8]
	push	ecx
	mov	edx, DWORD PTR _text$35424[ebp]
	mov	eax, DWORD PTR [edx+4]
	push	eax
	mov	ecx, DWORD PTR _adaptor$[ebp]
	mov	edx, DWORD PTR [ecx+4]
	push	edx
	mov	eax, DWORD PTR _adaptor$[ebp]
	mov	ecx, DWORD PTR [eax+4]
	mov	edx, DWORD PTR [ecx+16]
	call	edx
	add	esp, 12					; 0000000cH
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	ecx, DWORD PTR _newToken$[ebp]
	mov	DWORD PTR [ecx+48], eax
$LN1@createToke@2:
; Line 354
	mov	esi, esp
	mov	eax, DWORD PTR _fromToken$[ebp]
	push	eax
	mov	ecx, DWORD PTR _fromToken$[ebp]
	mov	edx, DWORD PTR [ecx+92]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	esi, esp
	push	eax
	mov	eax, DWORD PTR _newToken$[ebp]
	push	eax
	mov	ecx, DWORD PTR _newToken$[ebp]
	mov	edx, DWORD PTR [ecx+96]
	call	edx
	add	esp, 8
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 355
	mov	esi, esp
	mov	eax, DWORD PTR _fromToken$[ebp]
	push	eax
	mov	ecx, DWORD PTR _fromToken$[ebp]
	mov	edx, DWORD PTR [ecx+116]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	esi, esp
	push	eax
	mov	eax, DWORD PTR _newToken$[ebp]
	push	eax
	mov	ecx, DWORD PTR _newToken$[ebp]
	mov	edx, DWORD PTR [ecx+120]
	call	edx
	add	esp, 8
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 356
	mov	esi, esp
	mov	eax, DWORD PTR _fromToken$[ebp]
	push	eax
	mov	ecx, DWORD PTR _fromToken$[ebp]
	mov	edx, DWORD PTR [ecx+100]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	esi, esp
	push	eax
	mov	eax, DWORD PTR _newToken$[ebp]
	push	eax
	mov	ecx, DWORD PTR _newToken$[ebp]
	mov	edx, DWORD PTR [ecx+104]
	call	edx
	add	esp, 8
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 357
	mov	esi, esp
	mov	eax, DWORD PTR _fromToken$[ebp]
	push	eax
	mov	ecx, DWORD PTR _fromToken$[ebp]
	mov	edx, DWORD PTR [ecx+108]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	esi, esp
	push	eax
	mov	eax, DWORD PTR _newToken$[ebp]
	push	eax
	mov	ecx, DWORD PTR _newToken$[ebp]
	mov	edx, DWORD PTR [ecx+112]
	call	edx
	add	esp, 8
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 358
	mov	esi, esp
	mov	eax, DWORD PTR _fromToken$[ebp]
	push	eax
	mov	ecx, DWORD PTR _fromToken$[ebp]
	mov	edx, DWORD PTR [ecx+84]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	esi, esp
	push	eax
	mov	eax, DWORD PTR _newToken$[ebp]
	push	eax
	mov	ecx, DWORD PTR _newToken$[ebp]
	mov	edx, DWORD PTR [ecx+88]
	call	edx
	add	esp, 8
	cmp	esi, esp
	call	__RTC_CheckEsp
$LN3@createToke@2:
; Line 361
	mov	eax, DWORD PTR _newToken$[ebp]
; Line 362
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 216				; 000000d8H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_createTokenFromToken ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _setTokenBoundaries
_TEXT	SEGMENT
_ct$ = -32						; size = 4
_stop$ = -20						; size = 4
_start$ = -8						; size = 4
_adaptor$ = 8						; size = 4
_t$ = 12						; size = 4
_startToken$ = 16					; size = 4
_stopToken$ = 20					; size = 4
_setTokenBoundaries PROC				; COMDAT
; Line 373
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
; Line 379
	cmp	DWORD PTR _t$[ebp], 0
	jne	SHORT $LN5@setTokenBo
; Line 381
	jmp	SHORT $LN6@setTokenBo
$LN5@setTokenBo:
; Line 384
	cmp	DWORD PTR _startToken$[ebp], 0
	je	SHORT $LN4@setTokenBo
; Line 386
	mov	esi, esp
	mov	eax, DWORD PTR _startToken$[ebp]
	push	eax
	mov	ecx, DWORD PTR _startToken$[ebp]
	mov	edx, DWORD PTR [ecx+116]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	DWORD PTR _start$[ebp], eax
; Line 388
	jmp	SHORT $LN3@setTokenBo
$LN4@setTokenBo:
; Line 390
	mov	DWORD PTR _start$[ebp], 0
$LN3@setTokenBo:
; Line 393
	cmp	DWORD PTR _stopToken$[ebp], 0
	je	SHORT $LN2@setTokenBo
; Line 395
	mov	esi, esp
	mov	eax, DWORD PTR _stopToken$[ebp]
	push	eax
	mov	ecx, DWORD PTR _stopToken$[ebp]
	mov	edx, DWORD PTR [ecx+116]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	DWORD PTR _stop$[ebp], eax
; Line 397
	jmp	SHORT $LN1@setTokenBo
$LN2@setTokenBo:
; Line 399
	mov	DWORD PTR _stop$[ebp], 0
$LN1@setTokenBo:
; Line 402
	mov	eax, DWORD PTR _t$[ebp]
	mov	ecx, DWORD PTR [eax]
	mov	DWORD PTR _ct$[ebp], ecx
; Line 404
	mov	eax, DWORD PTR _ct$[ebp]
	mov	ecx, DWORD PTR _start$[ebp]
	mov	DWORD PTR [eax+4], ecx
; Line 405
	mov	eax, DWORD PTR _ct$[ebp]
	mov	ecx, DWORD PTR _stop$[ebp]
	mov	DWORD PTR [eax+8], ecx
$LN6@setTokenBo:
; Line 407
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 228				; 000000e4H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_setTokenBoundaries ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _dbgSetTokenBoundaries
_TEXT	SEGMENT
_adaptor$ = 8						; size = 4
_t$ = 12						; size = 4
_startToken$ = 16					; size = 4
_stopToken$ = 20					; size = 4
_dbgSetTokenBoundaries PROC				; COMDAT
; Line 410
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
; Line 411
	mov	eax, DWORD PTR _stopToken$[ebp]
	push	eax
	mov	ecx, DWORD PTR _startToken$[ebp]
	push	ecx
	mov	edx, DWORD PTR _t$[ebp]
	push	edx
	mov	eax, DWORD PTR _adaptor$[ebp]
	push	eax
	call	_setTokenBoundaries
	add	esp, 16					; 00000010H
; Line 413
	cmp	DWORD PTR _t$[ebp], 0
	je	SHORT $LN2@dbgSetToke
	cmp	DWORD PTR _startToken$[ebp], 0
	je	SHORT $LN2@dbgSetToke
	cmp	DWORD PTR _stopToken$[ebp], 0
	je	SHORT $LN2@dbgSetToke
; Line 415
	mov	esi, esp
	mov	eax, DWORD PTR _stopToken$[ebp]
	push	eax
	mov	ecx, DWORD PTR _stopToken$[ebp]
	mov	edx, DWORD PTR [ecx+116]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	esi, esp
	push	eax
	mov	edi, esp
	mov	eax, DWORD PTR _startToken$[ebp]
	push	eax
	mov	ecx, DWORD PTR _startToken$[ebp]
	mov	edx, DWORD PTR [ecx+116]
	call	edx
	add	esp, 4
	cmp	edi, esp
	call	__RTC_CheckEsp
	push	eax
	mov	eax, DWORD PTR _t$[ebp]
	push	eax
	mov	ecx, DWORD PTR _adaptor$[ebp]
	mov	edx, DWORD PTR [ecx+12]
	push	edx
	mov	eax, DWORD PTR _adaptor$[ebp]
	mov	ecx, DWORD PTR [eax+12]
	mov	edx, DWORD PTR [ecx+156]
	call	edx
	add	esp, 16					; 00000010H
	cmp	esi, esp
	call	__RTC_CheckEsp
$LN2@dbgSetToke:
; Line 417
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 192				; 000000c0H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_dbgSetTokenBoundaries ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _getTokenStartIndex
_TEXT	SEGMENT
_adaptor$ = 8						; size = 4
_t$ = 12						; size = 4
_getTokenStartIndex PROC				; COMDAT
; Line 421
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
; Line 422
	mov	eax, DWORD PTR _t$[ebp]
	mov	ecx, DWORD PTR [eax]
	mov	eax, DWORD PTR [ecx+4]
; Line 423
	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
_getTokenStartIndex ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _getTokenStopIndex
_TEXT	SEGMENT
_adaptor$ = 8						; size = 4
_t$ = 12						; size = 4
_getTokenStopIndex PROC					; COMDAT
; Line 427
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
; Line 428
	mov	eax, DWORD PTR _t$[ebp]
	mov	ecx, DWORD PTR [eax]
	mov	eax, DWORD PTR [ecx+8]
; Line 429
	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
_getTokenStopIndex ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _getText
_TEXT	SEGMENT
_adaptor$ = 8						; size = 4
_t$ = 12						; size = 4
_getText PROC						; COMDAT
; Line 433
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
; Line 434
	mov	esi, esp
	mov	eax, DWORD PTR _t$[ebp]
	push	eax
	mov	ecx, DWORD PTR _t$[ebp]
	mov	edx, DWORD PTR [ecx+92]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 435
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
;	COMDAT _getType
_TEXT	SEGMENT
_adaptor$ = 8						; size = 4
_t$ = 12						; size = 4
_getType PROC						; COMDAT
; Line 439
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
; Line 440
	mov	esi, esp
	mov	eax, DWORD PTR _t$[ebp]
	push	eax
	mov	ecx, DWORD PTR _t$[ebp]
	mov	edx, DWORD PTR [ecx+80]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 441
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 192				; 000000c0H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_getType ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _replaceChildren
_TEXT	SEGMENT
_adaptor$ = 8						; size = 4
_parent$ = 12						; size = 4
_startChildIndex$ = 16					; size = 4
_stopChildIndex$ = 20					; size = 4
_t$ = 24						; size = 4
_replaceChildren PROC					; COMDAT
; Line 446
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
; Line 447
	cmp	DWORD PTR _parent$[ebp], 0
	je	SHORT $LN2@replaceChi
; Line 449
	mov	esi, esp
	mov	eax, DWORD PTR _t$[ebp]
	push	eax
	mov	ecx, DWORD PTR _stopChildIndex$[ebp]
	push	ecx
	mov	edx, DWORD PTR _startChildIndex$[ebp]
	push	edx
	mov	eax, DWORD PTR _parent$[ebp]
	push	eax
	mov	ecx, DWORD PTR _parent$[ebp]
	mov	edx, DWORD PTR [ecx+40]
	call	edx
	add	esp, 16					; 00000010H
	cmp	esi, esp
	call	__RTC_CheckEsp
$LN2@replaceChi:
; Line 451
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 192				; 000000c0H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_replaceChildren ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _getChild
_TEXT	SEGMENT
_adaptor$ = 8						; size = 4
_t$ = 12						; size = 4
_i$ = 16						; size = 4
_getChild PROC						; COMDAT
; Line 455
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
; Line 456
	mov	esi, esp
	mov	eax, DWORD PTR _i$[ebp]
	push	eax
	mov	ecx, DWORD PTR _t$[ebp]
	push	ecx
	mov	edx, DWORD PTR _t$[ebp]
	mov	eax, DWORD PTR [edx+56]
	call	eax
	add	esp, 8
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 457
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 192				; 000000c0H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_getChild ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _setChild
_TEXT	SEGMENT
_adaptor$ = 8						; size = 4
_t$ = 12						; size = 4
_i$ = 16						; size = 4
_child$ = 20						; size = 4
_setChild PROC						; COMDAT
; Line 460
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
; Line 461
	mov	esi, esp
	mov	eax, DWORD PTR _child$[ebp]
	push	eax
	mov	ecx, DWORD PTR _i$[ebp]
	push	ecx
	mov	edx, DWORD PTR _t$[ebp]
	push	edx
	mov	eax, DWORD PTR _t$[ebp]
	mov	ecx, DWORD PTR [eax+100]
	call	ecx
	add	esp, 12					; 0000000cH
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 462
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 192				; 000000c0H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_setChild ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _deleteChild
_TEXT	SEGMENT
_adaptor$ = 8						; size = 4
_t$ = 12						; size = 4
_i$ = 16						; size = 4
_deleteChild PROC					; COMDAT
; Line 466
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
; Line 467
	mov	esi, esp
	mov	eax, DWORD PTR _i$[ebp]
	push	eax
	mov	ecx, DWORD PTR _t$[ebp]
	push	ecx
	mov	edx, DWORD PTR _t$[ebp]
	mov	eax, DWORD PTR [edx+36]
	call	eax
	add	esp, 8
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 468
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 192				; 000000c0H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_deleteChild ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _getChildCount
_TEXT	SEGMENT
_adaptor$ = 8						; size = 4
_t$ = 12						; size = 4
_getChildCount PROC					; COMDAT
; Line 472
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
; Line 473
	mov	esi, esp
	mov	eax, DWORD PTR _t$[ebp]
	push	eax
	mov	ecx, DWORD PTR _t$[ebp]
	mov	edx, DWORD PTR [ecx+68]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 474
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 192				; 000000c0H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_getChildCount ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _setChildIndex
_TEXT	SEGMENT
_adaptor$ = 8						; size = 4
_t$ = 12						; size = 4
_i$ = 16						; size = 4
_setChildIndex PROC					; COMDAT
; Line 478
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
; Line 479
	mov	esi, esp
	mov	eax, DWORD PTR _i$[ebp]
	push	eax
	mov	ecx, DWORD PTR _t$[ebp]
	push	ecx
	mov	edx, DWORD PTR _t$[ebp]
	mov	eax, DWORD PTR [edx+60]
	call	eax
	add	esp, 8
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 480
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 192				; 000000c0H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_setChildIndex ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _getChildIndex
_TEXT	SEGMENT
_adaptor$ = 8						; size = 4
_t$ = 12						; size = 4
_getChildIndex PROC					; COMDAT
; Line 484
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
; Line 485
	mov	esi, esp
	mov	eax, DWORD PTR _t$[ebp]
	push	eax
	mov	ecx, DWORD PTR _t$[ebp]
	mov	edx, DWORD PTR [ecx+64]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 486
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 192				; 000000c0H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_getChildIndex ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _setParent
_TEXT	SEGMENT
_adaptor$ = 8						; size = 4
_child$ = 12						; size = 4
_parent$ = 16						; size = 4
_setParent PROC						; COMDAT
; Line 489
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
; Line 490
	mov	esi, esp
	mov	eax, DWORD PTR _parent$[ebp]
	push	eax
	mov	ecx, DWORD PTR _child$[ebp]
	push	ecx
	mov	edx, DWORD PTR _child$[ebp]
	mov	eax, DWORD PTR [edx+76]
	call	eax
	add	esp, 8
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 491
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 192				; 000000c0H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_setParent ENDP
; Function compile flags: /Odtp /RTCsu /ZI
_TEXT	ENDS
;	COMDAT _getParent
_TEXT	SEGMENT
_adaptor$ = 8						; size = 4
_child$ = 12						; size = 4
_getParent PROC						; COMDAT
; Line 494
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
; Line 495
	mov	esi, esp
	mov	eax, DWORD PTR _child$[ebp]
	push	eax
	mov	ecx, DWORD PTR _child$[ebp]
	mov	edx, DWORD PTR [ecx+72]
	call	edx
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
; Line 496
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 192				; 000000c0H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_getParent ENDP
_TEXT	ENDS
END