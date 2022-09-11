
#ifndef _INCLUDE_DATA_WARNINGS_H_
#define _INCLUDE_DATA_WARNINGS_H_

// Container status type
typedef struct {
    bool filled_warning;
    bool temperature_warning;
    bool humidity_warning;
    bool position_warning;
} t_warnings;

#endif // _INCLUDE_DATA_WARNINGS_H_
