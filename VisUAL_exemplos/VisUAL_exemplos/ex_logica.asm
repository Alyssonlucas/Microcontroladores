		;ES422	- MICROCOMPUTADORES -  2026.1
		;AUTOR:	Jose R. de Oliveira Neto,
		;OBJETIVO:	Utilizando algumas funcoes logicas
		MOV		R1, #8 ; carregando um imediato em R1
		MOV		R2, #2 ; carregando um imediato em R2
		MOV		R3, #2147483648 ; Quando o imediato e uma potencia de 2, voce consegue carregar
		;		essa carecteristica e o do simulador.
		;AND		bit-a-bit
		AND		R0, R1, R2
		AND		R0, R1, R1
		;XOR		bit-a-bit
		EOR		R0, R1, R2
		EOR		R0, R1, R1
		;OR		bit-a-bit
		ORR		R0, R1, R2
		ORR		R0, R1, R1
		;Logical	Shift Left
		LSL		R0, R1, R2
		LSL		R0, R1, #16
		;Logical	Shift Right
		LSR		R0, R1, R2
		LSR		R0, R1, #1
		;Arithmetic	Shift Right
		ASR		R0, R3, R2
		ASR		R0, R3, #8
		;Rotate	Right
		ROR		R0, R1, R2
		ROR		R0, R1, #3
		;
		;
		;
		;
		
