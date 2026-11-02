#pragma once

#define noreturn [[__noreturn__]]
#define in_section(s) [[gnu::used, gnu::section(s)]]

// See scripts/auto_headers.py.
#define public
