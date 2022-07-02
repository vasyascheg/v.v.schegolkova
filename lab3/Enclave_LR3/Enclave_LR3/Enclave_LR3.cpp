#include "Enclave_LR3_t.h"
#include <string.h>
#include <stdio.h>
#include "sgx_trts.h"

const char table[6][41] = { "A126B858C7964D65436F69AAB24790DFB24AC378",  //40 символов + скрытый символ /0
                            "AB6487CF4907624AB5C6B7C9AF4D7F93A5C6F790",
                            "0987C65B34D2457546A589B8631CBF7854807DD6",
                            "FF54698B988775C75676DD575FDF4657ADB564FC",
                            "5388F65D686231097B09C64A21147D5899865436",
                            "090807060505050404030B0C0D0A00F007043665" };

//функция запроса к этой таблице
void foo(char* buf, size_t len, size_t idx) {

    if (idx >= 0 && idx < 5) { //ограничение индекса строки <5
        const char* data_ptr = table[idx];
        memcpy(buf, data_ptr, strlen(data_ptr + 1));
    }
    else {
        //возврат нулевой строки, если такого индекса в таблице не найдено
        memset(buf, 0, strlen(table[0])); 
    }
    return;
}