#ifndef _UNION_FIND_H
#define _UNION_FIND_H

void fast_find(ifstream& f, int* arr, int length);
void fast_union(ifstream& f, int* arr, int length);
void weighted_fast_union(ifstream& f, int* arr, int* v, int length);
void heighted_fast_union(ifstream& f, int* arr, int* h, int length);
void weighted_fast_union_half_path_compression(ifstream& f, int* arr, int* v, int length);
void weighted_fast_union_full_path_compression(ifstream& f, int* arr, int* v, int length);


#endif /* _UNION_FIND_H */