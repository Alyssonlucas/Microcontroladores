		;ES422	- MICROCOMPUTADORES -  2026.1
		;codigo	para tentar usar o BL
		;AUTOR:	Jose R. de Oliveira Neto,
		;
		MOV		R0, #0x100 ; carrega o endereco inicial da memoria de dados no registrador R0
		MOV		R1, #0x003 ; carrega o imediato 0x3 no registrador R1
		MOV		R2, #0x001 ; carrega o imediado 0x1 no registrador R2
		BL		loop       ; Branch with link para o label 'loop'
loop		SUBS		R1, R1, R2 ; decrementa R1 de R2
		;CMP		R1, R2     ; na duvida, usa a instrucao CMP que compara dois valores
		BEQ		reinicia   ; Se R1 == R2, salta para o label reinicia
		B		loop       ; caso contrario, salta para o label loop
		
reinicia	MOV		R1, #0x003 ; carrega o imediato 0x3 no registrador R1
		MOV		R2, #0x001 ; carrega o imediato 0x3 no registrador R1
		MOV		PC, LR     ; vai para instrucao depois do BL
