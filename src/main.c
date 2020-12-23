#include <stdio.h>
#include <stdlib.h>

#include "main.h"

s_error* main_menu()
{

	s_error* error;

	unsigned int op;

	int single_size;
	int unique_holder_size;
	int two_holders_size;

	char* single_str;
	char* unique_holder_str;
	char* two_holders_str;

	s_array* single_table;
	s_array* unique_holder_table;
	s_array* two_holders_table;

	/*
	 * IRS: Tabela I - Não Casado
	 * ---------------------------------------------------------------------------------------------------------
	 */
	single_size = 0;
	single_str = h_util_file_read(H_PATH_SINGLE, &single_size);
	if (single_str == NULL)
	{
		error = h_error_create(H_ERROR_READ, H_PATH_SINGLE);
		return error;
	}

	single_table = h_irs_alloc(single_size);
	if (single_table == NULL)
	{
		error = h_error_create(H_ERROR_ALLOCATION, H_PATH_SINGLE);
		free(single_str);
		return error;
	}

	error = h_irs_parse(single_table, single_str, h_irs_build);
	if (error)
	{
		free(single_str);
		free(single_table);
		return error;
	}

	free(single_str);

	/*
	 * IRS: Tabela II - Casado Unico Titular
	 * ---------------------------------------------------------------------------------------------------------
	 */
	unique_holder_size = 0;
	unique_holder_str = h_util_file_read(H_PATH_UNIQUE_HOLDER, &unique_holder_size);
	if (unique_holder_str == NULL)
	{
		error = h_error_create(H_ERROR_READ, H_PATH_UNIQUE_HOLDER);
		free(single_table);
		return error;
	}

	unique_holder_table = h_irs_alloc(unique_holder_size);
	if (unique_holder_table == NULL)
	{
		error = h_error_create(H_ERROR_ALLOCATION, H_PATH_UNIQUE_HOLDER);
		free(single_table);
		free(unique_holder_str);
		return error;
	}

	error = h_irs_parse(unique_holder_table, unique_holder_str, h_irs_build);
	if (error)
	{
		free(single_table);
		free(unique_holder_str);
		free(unique_holder_table);
		return error;
	}

	free(unique_holder_str);

	/*
	 * IRS: Tabela III - Casado Dois Titulares
	 * ---------------------------------------------------------------------------------------------------------
	 */
	two_holders_size = 0;
	two_holders_str = h_util_file_read(H_PATH_TWO_HOLDERS, &two_holders_size);
	if (two_holders_str == NULL)
	{
		error = h_error_create(H_ERROR_READ, H_PATH_TWO_HOLDERS);
		free(single_table);
		free(unique_holder_table);
		return error;
	}

	two_holders_table = h_irs_alloc(two_holders_size);
	if (two_holders_table == NULL)
	{
		error = h_error_create(H_ERROR_ALLOCATION, H_PATH_TWO_HOLDERS);
		free(single_table);
		free(unique_holder_table);
		free(two_holders_str);
		return error;
	}

	error = h_irs_parse(two_holders_table, two_holders_str, h_irs_build);
	if (error)
	{
		free(single_table);
		free(unique_holder_table);
		free(two_holders_str);
		free(two_holders_table);
		return error;
	}

	free(two_holders_str);

	do
	{
		fprintf(stdout, "%s", H_STRS_MENU);
		fprintf(stdout, GREEN("%s"), H_STRS_PROMPT);
		scanf(" %u", &op);

		switch (op)
		{
		case 1:
			h_menu_irs(single_table, unique_holder_table, two_holders_table);
			break;
		case 9:
			error = h_irs_write(single_table, H_PATH_SINGLE);
			if (error)
			{
				free(single_table);
				free(unique_holder_table);
				free(two_holders_table);
				return error;
			}
			error = h_irs_write(unique_holder_table, H_PATH_UNIQUE_HOLDER);
			if (error)
			{
				free(single_table);
				free(unique_holder_table);
				free(two_holders_table);
				return error;
			}
			error = h_irs_write(two_holders_table, H_PATH_TWO_HOLDERS);
			if (error)
			{
				free(single_table);
				free(unique_holder_table);
				free(two_holders_table);
				return error;
			}
			fprintf(stdout, GREEN("[!] Guardado com sucesso"));
			break;
		default:
			break;
		}
	} while (op != 0);

	free(single_table);
	free(unique_holder_table);
	free(two_holders_table);

	return NULL;
}

int main()
{
	s_error* error;

	error = main_menu();
	if (error)
	{
		h_error_print(error);
		h_error_free(error);
		return -1;
	}

	return 0;
}
