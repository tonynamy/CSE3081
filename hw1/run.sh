clang++ -std=c++11 -Wl,-stack_size -Wl,0x10000000 main.cpp insertion_sort.cpp heap_sort.cpp quick_sort.cpp quick_sort_opt.cpp && ./a.out