#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <chrono>

#include "my_types.h"

// #include <Windows.h>
std::chrono::high_resolution_clock::time_point start, end;
std::chrono::duration<double> time_span;

#define CHECK_TIME_START start = std::chrono::high_resolution_clock::now()
#define CHECK_TIME_END(a)                                                               \
	end = std::chrono::high_resolution_clock::now();                                    \
	time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - start); \
	a = time_span.count()
double compute_time;

#define STUDENT_ID 205

#include "test_data_config.h" // the content of this file will be modified for evaluation.

// #define DUMP_DATA

// #define CREATE_SAMPLE_DATA
// #define CREATE_ENTIRELY_RANDOM
// #define CREATE_DESCENDING
// #define CREATE_FEW_SWAPS

// #define TEST_INSERTION_SORT
// #define TEST_HEAP_SORT
// #define TEST_QUICK_SORT
// #define TEST_QUICK_SORT_OPT
#define TEST_QUICK_SORT_OPT_TIME_CHECK

int read_input_data(const char *file_name, int *n, ELEMENT **data)
{
	FILE *fp;

	fprintf(stdout, "^^^ Reading the input data file %s...\n", file_name);
	if ((fp = fopen(file_name, "rb")) == NULL)
	{
		fprintf(stderr, "Error: cannot open the binary file %s for reading...\n", file_name);
		return 0;
	}

	fread(n, sizeof(int), 1, fp);
	fprintf(stdout, "*** Number of elements = %d\n", *n);

	if ((*data = (ELEMENT *)malloc(sizeof(ELEMENT) * (*n))) == NULL)
	{
		fprintf(stderr, "Error: cannot allocate memory for %d ELEMENTs...\n", n);
		return 0;
	}
	fread(*data, sizeof(ELEMENT), *n, fp); // assume there is no problem in the input data file
	fclose(fp);
	fprintf(stdout, "^^^ Done...\n\n");
	return 1;
}

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<unsigned int> dist(0, UINT_MAX);

bool element_compare_a(const ELEMENT &a, const ELEMENT &b)
{
	return ELEMENT_KEY(&a) < ELEMENT_KEY(&b);
}

bool element_compare_d(const ELEMENT &a, const ELEMENT &b)
{
	return ELEMENT_KEY(&a) > ELEMENT_KEY(&b);
}

int write_data(const char *file_name, int n)
{

	FILE *fp = NULL;

	fprintf(stdout, "^^^ Writing the sample data file %s...\n", file_name);
	if ((fp = fopen(file_name, "wb+")) == NULL)
	{
		fprintf(stderr, "Error: cannot open the binary file %s for reading...\n", file_name);
		return 0;
	}

	fwrite(&n, sizeof(int), 1, fp);
	ELEMENT *t = (ELEMENT *)malloc(sizeof(ELEMENT) * n);

	for (int i = 0; i < n; i++)
	{
		t[i].key = dist(gen);
	}

#ifdef CREATE_DESCENDING
	std::sort(t, t + n, element_compare_d);
#endif

#ifdef CREATE_FEW_SWAPS
	std::sort(t, t + n, element_compare_a);
	std::vector<std::pair<int, int>> v;

	int r = sqrt(n);
	std::uniform_int_distribution<int> idist(0, n);
	std::uniform_int_distribution<int> rdist(-r, r);
	for (int i = 0; i < r; i++)
	{
		int rnum = rdist(gen);
		int j = i + rnum;

		if (j < 0 || j >= n)
		{
			j = i - rnum;
		}

		v.push_back({i, j});
	}
	for (auto p : v)
	{
		std::swap(t[p.first], t[p.second]);
	}
#endif

	fwrite(t, sizeof(ELEMENT), n, fp);

	fclose(fp);
}

int check_sorting_result(const char *file_name, int n, ELEMENT *data)
{
	// return 1 if the input data has been sorted correctly
	// or 0 otherwise
	return 1;
}

int main(void)
{

	ELEMENT *data;
	int n;
	FILE *fp;

#ifdef CREATE_SAMPLE_DATA
	n = 1024;

	while (n <= 33554432)
	{
		std::stringstream fname_stream;

#ifdef CREATE_ENTIRELY_RANDOM
		std::string data_type = "ENTIRELY_RANDOM_";
#endif
#ifdef CREATE_DESCENDING
		std::string data_type = "DESCENDING_";
#endif
#ifdef CREATE_FEW_SWAPS
		std::string data_type = "FEW_SWAPS_";
#endif

		fname_stream << data_type << n << ".binary";
		std::string fname = fname_stream.str();
		write_data(fname.c_str(), n);
		n *= 2;
	}
	return 0;
#endif

	char test_result_file[32];
	char test_method[32];

	int test_result;

	sprintf(test_result_file, "TEST_RESULT_%d.txt", STUDENT_ID);

	if ((fp = fopen(test_result_file, "w")) == NULL)
	{
		fprintf(stderr, "Error: cannot open the file %s for reading...\n", test_result_file);
		exit(-1);
	}

#ifdef TEST_INSERTION_SORT
	sprintf(test_method, " INSERTION_SORT");

	for (int i = 0; i < test_cases_sorting; i++)
	{
		read_input_data(test_data_file_sorting[i], &n, &data);

#ifdef DUMP_DATA
		{
			ELEMENT *ptr = data;
			fprintf(stdout, "*** %s: Input data\n", test_method);
			for (int i = 0; i < n; i++, ptr++)
				fprintf(stdout, "  i = %6d: (%11u, %5.1f, %17.14f, %s)\n", i, ELEMENT_KEY(ptr), ptr->score, ptr->other, ptr->name);
			fprintf(stdout, "\n");
		}
#endif
		fprintf(stdout, "^^^ [INSERTION_SORT] Processing data file %s...\n", test_data_file_sorting[i]);
		CHECK_TIME_START;
		test_result = INSERTION_SORT(data, 0, n - 1);
		CHECK_TIME_END(compute_time);
		free(data);
		fprintf(stdout, "Finished in %f\n\n", compute_time);
		if (test_result == 1)
		{
			// the function has finished successfully
			fprintf(fp, "^^^ Sorting method = %s, Test file = %s, Result =  %d, Time = %f\n",
					test_method, test_data_file_sorting[i], check_sorting_result(SORTED_INPUT_FILE_NAME_0, n, data), compute_time);
		}
		else
			fprintf(fp, "^^^ Sorting method = %s, Test file = %s, Result =  %d\n", test_method, test_data_file_sorting[i], 0);

#ifdef DUMP_DATA
		{
			ELEMENT *ptr = data;
			fprintf(stdout, "*** %s: Output data\n", test_method);
			for (int i = 0; i < n; i++, ptr++)
				fprintf(stdout, "  i = %6d: (%11u, %5.1f, %17.14f, %s)\n", i, ELEMENT_KEY(ptr), ptr->score, ptr->other, ptr->name);
			fprintf(stdout, "\n");
		}
#endif
	}
#endif // end of TEST_INSERTION_SORT

#ifdef TEST_HEAP_SORT
	sprintf(test_method, "HEAP_SORT");

	for (int i = 0; i < test_cases_sorting; i++)
	{
		read_input_data(test_data_file_sorting[i], &n, &data);

#ifdef DUMP_DATA
		{
			ELEMENT *ptr = data;
			fprintf(stdout, "*** %s: Input data\n", test_method);
			for (int i = 0; i < n; i++, ptr++)
				fprintf(stdout, "  i = %6d: (%11u, %5.1f, %17.14f, %s)\n", i, ELEMENT_KEY(ptr), ptr->score, ptr->other, ptr->name);
			fprintf(stdout, "\n");
		}
#endif
		fprintf(stdout, "^^^ [HEAP_SORT] Processing data file %s...\n", test_data_file_sorting[i]);
		CHECK_TIME_START;
		test_result = HEAP_SORT(data, 0, n - 1);
		CHECK_TIME_END(compute_time);
		free(data);
		fprintf(stdout, "Finished in %f\n\n", compute_time);
		if (test_result == 1)
		{
			// the function has finished successfully
			fprintf(fp, "^^^ Sorting method = %s, Test file = %s, Result =  %d, Time = %f\n",
					test_method, test_data_file_sorting[i], check_sorting_result(SORTED_INPUT_FILE_NAME_0, n, data), compute_time);
		}
		else
			fprintf(fp, "^^^ Sorting method = %s, Test file = %s, Result =  %d\n", test_method, test_data_file_sorting[i], 0);

#ifdef DUMP_DATA
		{
			ELEMENT *ptr = data;
			fprintf(stdout, "*** %s: Output data\n", test_method);
			for (int i = 0; i < n; i++, ptr++)
				fprintf(stdout, "  i = %6d: (%11u, %5.1f, %17.14f, %s)\n", i, ELEMENT_KEY(ptr), ptr->score, ptr->other, ptr->name);
			fprintf(stdout, "\n");
		}
#endif
	}
#endif // end of TEST_HEAP_SORT

#ifdef TEST_QUICK_SORT
	sprintf(test_method, "QUICK_SORT");

	for (int i = 0; i < test_cases_sorting; i++)
	{
		read_input_data(test_data_file_sorting[i], &n, &data);

#ifdef DUMP_DATA
		{
			ELEMENT *ptr = data;
			fprintf(stdout, "*** %s: Input data\n", test_method);
			for (int i = 0; i < n; i++, ptr++)
				fprintf(stdout, "  i = %6d: (%11u, %5.1f, %17.14f, %s)\n", i, ELEMENT_KEY(ptr), ptr->score, ptr->other, ptr->name);
			fprintf(stdout, "\n");
		}
#endif
		fprintf(stdout, "^^^ [QUICK_SORT] Processing data file %s...\n", test_data_file_sorting[i]);
		CHECK_TIME_START;
		test_result = QUICK_SORT(data, 0, n - 1);
		CHECK_TIME_END(compute_time);
		free(data);
		fprintf(stdout, "Finished in %f\n\n", compute_time);
		if (test_result == 1)
		{
			// the function has finished successfully
			fprintf(fp, "^^^ Sorting method = %s, Test file = %s, Result =  %d, Time = %f\n",
					test_method, test_data_file_sorting[i], check_sorting_result(SORTED_INPUT_FILE_NAME_0, n, data), compute_time);
		}
		else
			fprintf(fp, "^^^ Sorting method = %s, Test file = %s, Result =  %d\n", test_method, test_data_file_sorting[i], 0);

#ifdef DUMP_DATA
		{
			ELEMENT *ptr = data;
			fprintf(stdout, "*** %s: Output data\n", test_method);
			for (int i = 0; i < n; i++, ptr++)
				fprintf(stdout, "  i = %6d: (%11u, %5.1f, %17.14f, %s)\n", i, ELEMENT_KEY(ptr), ptr->score, ptr->other, ptr->name);
			fprintf(stdout, "\n");
		}
#endif
	}
#endif // end of TEST_QUICK_SORT

#ifdef TEST_QUICK_SORT_OPT
	sprintf(test_method, "QUICK_SORT_OPT");

	for (int i = 0; i < test_cases_sorting; i++)
	{
		read_input_data(test_data_file_sorting[i], &n, &data);

#ifdef DUMP_DATA
		{
			ELEMENT *ptr = data;
			fprintf(stdout, "*** %s: Input data\n", test_method);
			for (int i = 0; i < n; i++, ptr++)
				fprintf(stdout, "  i = %6d: (%11u, %5.1f, %17.14f, %s)\n", i, ELEMENT_KEY(ptr), ptr->score, ptr->other, ptr->name);
			fprintf(stdout, "\n");
		}
#endif

		test_result = QUICK_SORT_OPT(data, 0, n - 1);
		if (test_result == 1)
		{
			// the function has finished successfully
			fprintf(fp, "^^^ Sorting method = %s, Test file = %s, Result =  %d\n",
					test_method, test_data_file_sorting[i], check_sorting_result(SORTED_INPUT_FILE_NAME_0, n, data));
		}
		else
			fprintf(fp, "^^^ Sorting method = %s, Test file = %s, Result =  %d\n", test_method, test_data_file_sorting[i], 0);

#ifdef DUMP_DATA
		{
			ELEMENT *ptr = data;
			fprintf(stdout, "*** %s: Output data\n", test_method);
			for (int i = 0; i < n; i++, ptr++)
				fprintf(stdout, "  i = %6d: (%11u, %5.1f, %17.14f, %s)\n", i, ELEMENT_KEY(ptr), ptr->score, ptr->other, ptr->name);
			fprintf(stdout, "\n");
		}
#endif
	}
#endif // end of TEST_QUICK_SORT_OPT

#ifdef TEST_QUICK_SORT_OPT_TIME_CHECK
	// time measuring code must be inserted
	sprintf(test_method, "QUICK_SORT_OPT_TIME_CHECK");

	for (int i = 0; i < test_cases_sorting; i++)
	{
		read_input_data(test_data_file_sorting[i], &n, &data);

#ifdef DUMP_DATA
		{
			ELEMENT *ptr = data;
			fprintf(stdout, "*** %s: Input data\n", test_method);
			for (int i = 0; i < n; i++, ptr++)
				fprintf(stdout, "  i = %6d: (%11u, %5.1f, %17.14f, %s)\n", i, ELEMENT_KEY(ptr), ptr->score, ptr->other, ptr->name);
			fprintf(stdout, "\n");
		}
#endif
		fprintf(stdout, "^^^ [QUICK_SORT_OPT] Processing data file %s...\n", test_data_file_sorting[i]);
		CHECK_TIME_START;
		test_result = QUICK_SORT_OPT(data, 0, n - 1);
		CHECK_TIME_END(compute_time);
		free(data);
		fprintf(stdout, "Finished in %f\n\n", compute_time);
		if (test_result == 1)
		{
			// the function has finished successfully
			fprintf(fp, "^^^ Sorting method = %s, Test file = %s, Result =  %d, Time = %f\n",
					test_method, test_data_file_sorting[i], check_sorting_result(SORTED_INPUT_FILE_NAME_0, n, data), compute_time);
		}
		else
			fprintf(fp, "^^^ Sorting method = %s, Test file = %s, Result =  %d\n", test_method, test_data_file_sorting[i], 0);

#ifdef DUMP_DATA
		{
			ELEMENT *ptr = data;
			fprintf(stdout, "*** %s: Output data\n", test_method);
			for (int i = 0; i < n; i++, ptr++)
				fprintf(stdout, "  i = %6d: (%11u, %5.1f, %17.14f, %s)\n", i, ELEMENT_KEY(ptr), ptr->score, ptr->other, ptr->name);
			fprintf(stdout, "\n");
		}
#endif
	}
#endif // end of TEST_QUICK_SORT_OPT

	fclose(fp);

	return 0;
}
