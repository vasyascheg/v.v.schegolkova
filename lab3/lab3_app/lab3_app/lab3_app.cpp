#include <string.h>
#include <tchar.h>
#include <stdio.h>

#include "sgx_urts.h"
#include "sgx_tseal.h"
#include "Enclave_LR3_u.h"

#define ENCLAVE_FILE _T("Enclave_LR3.signed.dll")

#define BUF_LEN 100 //размер буфера
//макетные данные, которые необходимо защитить, в виде таблицы
/*
const char table[6][41] = { "A126B858C7964D65436F69AAB24790DFB24AC378",
                            "AB6487CF4907624AB5C6B7C9AF4D7F93A5C6F790",
                            "0987C65B34D2457546A589B8631CBF7854807DD6",
                            "FF54698B988775C75676DD575FDF4657ADB564FC",
                            "5388F65D686231097B09C64A21147D5899865436",
                            "090807060505050404030B0C0D0A00F007043665" };

//функция запроса к этой таблице
void foo(char* buf, size_t len, size_t idx) {

    if (idx >= 0 && idx < 5) {
        const char* data_ptr = table[idx];
        memcpy(buf, data_ptr, strlen(data_ptr + 1));
    }
    else {
        //возврат нулевой строки, если такого индекса в таблице не найдено
        memset(buf, 0, strlen(table[0]));
    }
    return;
}
*/
int main()
{
    char buffer[BUF_LEN] = { 0 };
    //активация анклава
    sgx_enclave_id_t eid;
    sgx_status_t ret = SGX_SUCCESS;
    sgx_launch_token_t token = { 0 };
    int updated = 0; 
    //создаем анклав из библиотеки .dll
    ret = sgx_create_enclave(ENCLAVE_FILE, SGX_DEBUG_FLAG, &token, &updated, &eid, NULL);
    //проверка на ошибки при создании
    if (ret != SGX_SUCCESS) {
        printf("App: error %#x, faild to create enclave.\n", ret);
        return -1;
    }

    while (true)
    {
        printf("Input index to retrieve, or -1 to exit: \t");
        int idx = -1;
        scanf_s("%d", &idx); //кладет введеное число в idx
        if (idx < 0) {
            return 0;
        }
        // foo(buffer, BUF_LEN, idx)
        foo(eid ,buffer, BUF_LEN, idx); //id созданного анклава
        printf_s("%s\n==================\n\n", buffer);
    }
    if (SGX_SUCCESS != sgx_destroy_enclave(eid)) {
        return  -1;
    }
        
    return 0;
}