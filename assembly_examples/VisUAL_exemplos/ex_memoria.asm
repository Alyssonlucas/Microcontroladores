		;ES422	- MICROCOMPUTADORES -  2026.1
		;Exemplo	de acesso a memoria de dados
		;AUTOR:	Jose R. de Oliveira Neto,
		;
		MOV		R0, #0x100 ;salva no registrador R0 o endereco inicial da memoria de dados
		MOV		R1, #32768  ;salva valor alatorio a ser guardado na memoria
		STR		R1, [R0,#0]  ;salva no primeiro endereco da memoria
		LDR		R10, [R0,#0] ;carrega o valor da memoria para o registrador R10
		ADD		R11, R1, R10 ;R11 = R1 + R10
		STR		R11, [R0,#4] ;salva o resultado no segundo endereco da memoria
