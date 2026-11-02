void prepare(char string[]) {
    string[0] = '0';
    string[1] = 'x';
}


public char* format_uptr(uptr ptr, char string[]) {
    prepare(string);

    constexpr char hex_chars[] = "0123456789abcdef";
    constexpr u8 CHAR_COUNT = sizeof(uptr) * 2;

    for (int i = CHAR_COUNT - 1; i >= 0; i--) {
        string[i+2] = hex_chars[ptr & 0xF];
        ptr >>= 4;
    }

    string[CHAR_COUNT+2] = '\0';
    return string;
}

public char* format_u64(u64 a, char string[]) {
    prepare(string);

    constexpr char hex_chars[] = "0123456789abcdef";
    constexpr u8 CHAR_COUNT = 16;

    for (int i = CHAR_COUNT - 1; i >= 0; i--) {
        string[i+2] = hex_chars[a & 0xF];
        a >>= 4;
    }

    string[CHAR_COUNT+2] = '\0';
    return string;
}
