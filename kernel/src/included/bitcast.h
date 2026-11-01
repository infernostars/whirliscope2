#pragma once

#define bitcast(type, value) \
    (((union { typeof(value) src; type dst; }){ .src = (value) }).dst)