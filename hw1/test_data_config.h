#pragma once

#define INPUT_FILE_NAME_0 "ENTIRELY_RANDOM_65536.binary"
#define INPUT_FILE_NAME_1 "ENTIRELY_RANDOM_1024.binary"
#define INPUT_FILE_NAME_2 "ENTIRELY_RANDOM_1048576.binary"

#define SORTED_INPUT_FILE_NAME_0 "ENTIRELY_RANDOM_32_sorted.binary"
#define SORTED_INPUT_FILE_NAME_1 "ENTIRELY_RANDOM_1024_sorted.binary"
#define SORTED_INPUT_FILE_NAME_2 "ENTIRELY_RANDOM_1048576_sorted.binary"

int test_cases_sorting = 16;
char test_data_file_sorting[48][128] = {
    // "ENTIRELY_RANDOM_1024.binary",
    // "ENTIRELY_RANDOM_2048.binary",
    // "ENTIRELY_RANDOM_4096.binary",
    // "ENTIRELY_RANDOM_8192.binary",
    // "ENTIRELY_RANDOM_16384.binary",
    // "ENTIRELY_RANDOM_32768.binary",
    // "ENTIRELY_RANDOM_65536.binary",
    // "ENTIRELY_RANDOM_131072.binary",
    // "ENTIRELY_RANDOM_262144.binary",
    // "ENTIRELY_RANDOM_524288.binary",
    // "ENTIRELY_RANDOM_1048576.binary",
    // "ENTIRELY_RANDOM_2097152.binary",
    // "ENTIRELY_RANDOM_4194304.binary",
    // "ENTIRELY_RANDOM_8388608.binary",
    // "ENTIRELY_RANDOM_16777216.binary",
    // "ENTIRELY_RANDOM_33554432.binary",
    // "DESCENDING_1024.binary",
    // "DESCENDING_2048.binary",
    // "DESCENDING_4096.binary",
    // "DESCENDING_8192.binary",
    // "DESCENDING_16384.binary",
    // "DESCENDING_32768.binary",
    // "DESCENDING_65536.binary",
    // "DESCENDING_131072.binary",
    // "DESCENDING_262144.binary",
    // "DESCENDING_524288.binary",
    // "DESCENDING_1048576.binary",
    // "DESCENDING_2097152.binary",
    // "DESCENDING_4194304.binary",
    // "DESCENDING_8388608.binary",
    // "DESCENDING_16777216.binary",
    // "DESCENDING_33554432.binary",
    "FEW_SWAPS_1024.binary",
    "FEW_SWAPS_2048.binary",
    "FEW_SWAPS_4096.binary",
    "FEW_SWAPS_8192.binary",
    "FEW_SWAPS_16384.binary",
    "FEW_SWAPS_32768.binary",
    "FEW_SWAPS_65536.binary",
    "FEW_SWAPS_131072.binary",
    "FEW_SWAPS_262144.binary",
    "FEW_SWAPS_524288.binary",
    "FEW_SWAPS_1048576.binary",
    "FEW_SWAPS_2097152.binary",
    "FEW_SWAPS_4194304.binary",
    "FEW_SWAPS_8388608.binary",
    "FEW_SWAPS_16777216.binary",
    "FEW_SWAPS_33554432.binary",
};
// char test_data_file_sorting[24][128] = {"ENTIRELY_RANDOM_1024.binary", "ENTIRELY_RANDOM_2048.binary", "ENTIRELY_RANDOM_4096.binary", "ENTIRELY_RANDOM_8192.binary", "ENTIRELY_RANDOM_16384.binary", "ENTIRELY_RANDOM_32768.binary", "ENTIRELY_RANDOM_65536.binary", "ENTIRELY_RANDOM_131072.binary", "DESCENDING_1024.binary", "DESCENDING_2048.binary", "DESCENDING_4096.binary", "DESCENDING_8192.binary", "DESCENDING_16384.binary", "DESCENDING_32768.binary", "DESCENDING_65536.binary", "DESCENDING_131072.binary", "FEW_SWAPS_1024.binary", "FEW_SWAPS_2048.binary", "FEW_SWAPS_4096.binary", "FEW_SWAPS_8192.binary", "FEW_SWAPS_16384.binary", "FEW_SWAPS_32768.binary", "FEW_SWAPS_65536.binary", "FEW_SWAPS_131072.binary"};
char test_data_file_sorted[16][128] = {SORTED_INPUT_FILE_NAME_0, SORTED_INPUT_FILE_NAME_1, SORTED_INPUT_FILE_NAME_2};
