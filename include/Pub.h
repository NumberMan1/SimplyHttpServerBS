#ifndef PUB_H
#define PUB_H

using size_t = unsigned long;

const char *get_mime_type(const char *name);
int get_line(int sock, char *buf, int size);
int hexit(char c);//16进制转10进制
void strencode(char* to, size_t tosize, const char* from);//编码
void strdecode(char *to, char *from);//解码



#endif // !PUB_H