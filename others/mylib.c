int convert(int x, int old_base, int new_base) {
    int x_dec = 0;   // x in decimal system
    int res = 0;     // convertion result
    int is_neg = 0;  // whether x in negative

    if (x < 0) {
        is_neg = 1;
        x = -x;
    }

    for (int i = 0; x > 0; ++i) {
        x_dec += (x % 10) * (int)pow(old_base, i);
        x /= 10;
    }

    for (int i = 0; x_dec > 0; ++i) {
        res += (x_dec % new_base) * (int)pow(10, i);
        x_dec /= new_base;
    }

    return is_neg ? -res: res;
}
