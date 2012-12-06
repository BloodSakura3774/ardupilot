
#ifndef __AP_HAL_AVR_CONSOLE_DRIVER_H__
#define __AP_HAL_AVR_CONSOLE_DRIVER_H__

#include <stdlib.h>

#include <AP_HAL.h>
#include "AP_HAL_AVR_Namespace.h"

class AP_HAL_AVR::AVRConsoleDriver : public AP_HAL::ConsoleDriver {
public:
    AVRConsoleDriver();
    void init(void* baseuartdriver);
    void backend_open();
    void backend_close();
    size_t backend_read(uint8_t *data, size_t len);
    size_t backend_write(const uint8_t *data, size_t len);

    /* Implementations of BetterStream virtual methods */
    void print_P(const prog_char_t *s);
    void println_P(const prog_char_t *s);
    void printf(const char *s, ...)
            __attribute__ ((format(__printf__, 2, 3)));
    void _printf_P(const prog_char *s, ...)
            __attribute__ ((format(__printf__, 2, 3)));

    /* Implementations of Stream virtual methods */
    int16_t available();
    int16_t txspace();
    int16_t read();
    int16_t peek();

    /* Implementations of Print virtual methods */
    size_t write(uint8_t c);
private:
    struct Buffer {
        /* public methods:*/
        bool allocate(uint16_t size);
        bool push(uint8_t b);
        int16_t  pop();
        int16_t  peek();

        uint16_t bytes_free();
        uint16_t bytes_used();
    private:
        uint16_t _head, _tail; /* Head and tail indicies */
        uint16_t _mask;       /* Buffer size mask for index wrap */
        uint8_t *_bytes;      /* Pointer to allocated buffer */
    };

    Buffer _txbuf;
    Buffer _rxbuf;

    AP_HAL::UARTDriver* _base_uart;
    bool _user_backend;
};

#endif // __AP_HAL_AVR_CONSOLE_DRIVER_H__

