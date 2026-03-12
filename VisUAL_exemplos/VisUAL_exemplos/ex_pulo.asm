		;ES422	- MICROCOMPUTADORES -  2026.1
		;Exemplo	de salto
		;AUTOR:	Jose R. de Oliveira Neto,
		;
loop1	ADD		R0, R0, #0x0001 ; adiciona o imeditato 0x1 em R0
		SUB		R1, R1, #0x0010 ; subtrai o imediato 0x10 de R1
		ADD		R2, R2, #0x0100 ; adiciona o imediato 0x100 em R2
		SUB		R3, R3, #0x1000 ; subtrai 0x1000 do registrador R3
		B		loop1           ; faz um salto para o label 'loop1'
