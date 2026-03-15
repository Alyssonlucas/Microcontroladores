		;ES422	- MICROCOMPUTADORES -  2025.2
		;Exemplo	de salto condicional
		;AUTOR:	Jose R. de Oliveira Neto,
		;
loop2	MOV		R4, #8
loop1	ADD		R2, R2, #1  ;incremneta R2
		SUBS		R3, R4, R2
		;CMP		R4, R2 ; instrucao a mais apenas para comparacao; 
		BGE		loop1
		ANDS		R2, R2, #0  ;reinicia R2
		BEQ		loop2
