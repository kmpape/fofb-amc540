;******************************************************************************
;* void touch *
;* ( *
;* const void *array, /* Pointer to array to touch */ *
;* int length /* Length array in bytes */ *
;* ); *
;******************************************************************************
	.global touch
	.sect ".text:touch"
touch:
	B .S2 loop ; Pipe up the loop
|| 	MVK .S1 128, A2 ; Step by two cache lines
|| 	ADDAW .D2 B4, 31, B4 ; Round up # of iters
	B .S2 loop ; Pipe up the loop
|| 	CLR .S1 A4, 0, 6, A4 ; Align to cache line
|| 	MV .L2X A4, B0 ; Twin the pointer
	B .S1 loop ; Pipe up the loop
|| 	CLR .S2 B0, 0, 6, B0 ; Align to cache line
|| 	MV .L2X A2, B2 ; Twin the stepping constant
	B .S2 loop ; Pipe up the loop
|| 	SHR .S1X B4, 7, A1 ; Divide by 128 bytes
|| 	ADDAW .D2 B0, 17, B0 ; Offset by one line + one word
	[A1] BDEC .S1 loop, A1 ; Step by 128s through array
|| 	[A1] LDBU .D1T1 *A4++[A2], A3 ; Load from [128*i + 0]
|| 	[A1] LDBU .D2T2 *B0++[B2], B4 ; Load from [128*i + 68]
|| 	SUB .L1 A1, 7, A0
loop:
	[A0] BDEC .S1 loop, A0 ; Step by 128s through array
|| 	[A1] LDBU .D1T1 *A4++[A2], A3 ; Load from [128*i + 0]
|| 	[A1] LDBU .D2T2 *B0++[B2], B4 ; Load from [128*i + 68]
|| 	[A1] SUB .L1 A1, 1, A1
	BNOP .S2 B3, 5 ; Return
