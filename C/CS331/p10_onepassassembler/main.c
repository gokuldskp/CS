/* 
	Implement a single pass assembler
	Code courtesy of https://forgetcode.com/c/105-one-pass-assembler
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void itoa(int i, char *a)
{
	sprintf(a, "%d", i);
}

int main()
{
	FILE *input, *optab, *symtab, *symtab2, *output;
	char label[10], opcode[10], operand[10], name[10], optab_code[10], optab_addr[10];
	char symbol[10], symbol_addr[10], locctrs[10], ms[10], q[10], obj1[10], obj2[10];
	int start_address, locctr, prog_len, m[10], i = 0, j = 0, l = 0, k = 0;

	if(! (input = fopen("input.txt", "r")))
	{
		printf("Please make sure input.txt exists\n");
		exit(0);
	}

	if(! (optab = fopen("optab.txt", "r")))
	{
		printf("Please make sure optab.txt exists\n");
		exit(0);
	}

	symtab = fopen("symtab.txt", "w+");
	symtab2 = fopen("symtab2.txt", "w+");
	output = fopen("output.txt", "w+");

	// Checking if input file starts with a START
	fscanf(input, "%s %s %s", label, opcode, operand);
	if(strcmp(opcode, "START") == 0)
	{
		start_address = atoi(operand);
		strcpy(name, label);
		locctr = start_address;
	}

	fscanf(input, "%s %s %s", label, opcode, operand);
	while(strcmp(opcode, "END") != 0)
	{
		if(strcmp(label, "**") == 0)
		{
			while(! feof(optab))
			{
				fscanf(optab, "%s %s", optab_code, optab_addr);
				if(strcmp(optab_code, opcode) == 0)
				{
					m[i++] = locctr + 1;
					fprintf(symtab, "%s **\n", operand);
					fprintf(output, "%s 0000\n", optab_addr);
					locctr += 3;
					break;
				}
			}	
		}
		else
		{
			rewind(symtab);
			while(! feof(symtab))
			{
				fscanf(symtab, "%s %s", symbol, symbol_addr);
				if(strcmp(symbol, label) == 0)
				{
					fprintf(symtab2, "%s %d\n", label, locctr);
					fprintf(output, "%d %d\n", m[j++], locctr);
					++i;
					break;
				}
			}

			if(strcmp(opcode, "RESW") == 0)
				locctr = locctr + 3 * atoi(operand);

			else if(strcmp(opcode, "BYTE") == 0)
			{
				locctr += strlen(operand) - 2;
				for(k = 0; k < strlen(operand); ++k)
					q[l++] = operand[k];

				fprintf(output, "%s **\n", q);
				break; 
			}

			else if(strcmp(opcode, "RESB") == 0)
				locctr += atoi(operand);

			else if(strcmp(opcode, "WORD") == 0)
			{
				locctr += 3;
				fprintf(output, "%s #\n", operand);
				break;
			}
		}

		rewind(optab);
		fscanf(input, "%s %s %s", label, opcode, operand);
	}
	
	fclose(output);
	output = fopen("output.txt", "r");
	prog_len = locctr - start_address;

	printf("H^%s^%d^0%x\n", name, start_address, prog_len);
	printf("T^");
	printf("00%d^0%x", start_address, prog_len);

	while (! feof(output))
	{
		fscanf(output, "%s %s", obj1, obj2);
		if(strcmp(obj2, "0000") == 0)
			printf("^%s%s", obj1, obj2);
		
		else if(strcmp(obj2, "**") == 0)
		{
			printf("^");
			for(k = 0; k < strlen(obj1); k++)
				printf("%d", obj1[k]);
		}

		else if(strcmp(obj2, "#") == 0)
			printf("^%s", obj1);
	}

	rewind(output);
	while (! feof(output))
	{
		fscanf(output, "%s %s", obj1, obj2);
		if(
			strcmp(obj2, "0000") != 0 
			&& strcmp(obj2, "**") != 0 
			&& strcmp(obj2, "#") != 0
		)
			printf("\nT^%s^02^%s", obj1, obj2);
	}
	printf("\nE^00%d\n", start_address);
	return 0;
}