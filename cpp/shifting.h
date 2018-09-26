#ifndef SHIFTING_FUNS
#define SHIFTING_FUNS

bool combine(int a, int b, int *result);
bool can_shift_left(int (&array)[16]);
bool can_shift_right(int (&array)[16]);
bool can_shift_up(int (&array)[16]);
bool can_shift_down(int (&array)[16]);
bool shift_left(int (&array)[16]);
bool shift_right(int (&array)[16]);
bool shift_up(int (&array)[16]);
bool shift_down(int (&array)[16]);

#endif
