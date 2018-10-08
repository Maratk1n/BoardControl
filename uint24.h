#ifndef UINT24_H
#define UINT24_H

#include <QMetaType>

class uint24
{
public:
    uint32_t data;
    uint24(){
        data = 0;
    }
    uint24(const uint24 &instanse){
        data = instanse.data;
    }
    ~uint24(){}
    operator uint32_t () const {
        return data;
    }
    uint24& operator=(uint32_t data) {
        this->data = data;
        return *this;
    }
};

Q_DECLARE_METATYPE(uint24)


#endif // UINT24_H
