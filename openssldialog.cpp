#include "openssldialog.h"
#include "ui_openssldialog.h"
#include <string.h>
#include <openssl/objects.h>
#include <openssl/rsa.h>

void hexDump(const char* buf, int len)
{
    if (len < 1 || buf == NULL) return;

    const char *hexChars = "0123456789ABCDEF";
    int i = 0;
    char c = 0x00;
    char str_print_able[17];
    char str_hex_buffer[16 * 3 + 1];

    for (i = 0; i < (len / 16) * 16; i += 16)
    {
        int j = 0;
        for (j = 0; j < 16; j++)
        {
            c = buf[i + j];

            // hex
            int z = j * 3;
            str_hex_buffer[z++] = hexChars[(c >> 4) & 0x0F];
            str_hex_buffer[z++] = hexChars[c & 0x0F];
            str_hex_buffer[z++] = (j < 10 && !((j + 1) % 8)) ? '_' : ' ';

            // string with space repalced
            if (c < 32 || c == '\0' || c == '\t' || c == '\r' || c == '\n' || c == '\b')
                str_print_able[j] = '.';
            else
                str_print_able[j] = c;
        }
        str_hex_buffer[16 * 3] = 0x00;
        str_print_able[j] = 0x00;

        printf("%04x  %s %s\n", i, str_hex_buffer, str_print_able);
    }

    // 处理剩下的不够16字节长度的部分
    int leftSize = len % 16;
    if (leftSize < 1) return;
    int j = 0;
    int pos = i;
    for (; i < len; i++)
    {
        c = buf[i];

        // hex
        int z = j * 3;
        str_hex_buffer[z++] = hexChars[(c >> 4) & 0x0F];
        str_hex_buffer[z++] = hexChars[c & 0x0F];
        str_hex_buffer[z++] = ' ';

        // string with space repalced
        if (c < 32 || c == '\0' || c == '\t' || c == '\r' || c == '\n' || c == '\b')
            str_print_able[j] = '.';
        else
            str_print_able[j] = c;
        j++;
    }
    str_hex_buffer[leftSize * 3] = 0x00;
    str_print_able[j] = 0x00;

    for (j = leftSize; j < 16; j++)
    {
        int z = j * 3;
        str_hex_buffer[z++] = ' ';
        str_hex_buffer[z++] = ' ';
        str_hex_buffer[z++] = ' ';
    }
    str_hex_buffer[16 * 3] = 0x00;
    printf("%04x  %s %s\n", pos, str_hex_buffer, str_print_able);
}

OpensslDialog::OpensslDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpensslDialog)
{
    ui->setupUi(this);
}

OpensslDialog::~OpensslDialog()
{
    delete ui;
}

void OpensslDialog::on_pushButton_genRsa_clicked()
{
    int ret;
    RSA *r;
    unsigned int i, bits = 1024, signlen, datalen, alg, nid;
    unsigned long e = RSA_3;
    BIGNUM *bne;
    unsigned char data[100], signret[200];
    bne = BN_new();
    ret = BN_set_word(bne, e);
    r = RSA_new();
    ret = RSA_generate_key_ex(r, bits, bne, NULL);
    char * p = NULL;
    if (ret != 1)
    {
        printf("RSA_generate_key_ex err!\n");
        return ;
    }
    for (i = 0; i < 100; i++)
        memset(&data[i], i + 1, 1);
    printf("please select digest alg: \n");
    printf("1.NID_md5\n");
    printf("2.NID_sha\n");
    printf("3.NID_sha1\n");
    printf("4.NID_md5_sha1\n");
//    scanf("%d", &alg);
    alg = 3;
    if (alg == 1)
    {
        datalen = 55;
        nid = NID_md5;
    }
    else if (alg == 2)
    {
        datalen = 55;
        nid = NID_sha;
    }
    else if (alg == 3)
    {
        datalen = 55;
        nid = NID_sha1;
    }
    else if (alg == 4)
    {
        datalen = 36;
        nid = NID_md5_sha1;
    }
    ret = RSA_sign(nid, data, datalen, signret, &signlen, r);
    if (ret != 1)
    {
        printf("RSA_sign err!\n");
        RSA_free(r);
        return ;
    }
    hexDump((const char*)signret, signlen);
    ret = RSA_verify(nid, data, datalen, signret, signlen, r);
    if (ret != 1)
    {
        printf("RSA_verify err!\n");
        RSA_free(r);
        return ;
    }
    RSA_free(r);
    printf("test ok!\n");
    return ;
}
