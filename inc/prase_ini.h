#ifndef __PRASE_INI_H__
#define __PRASE_INI_H__

struct ini_parameter {
    const char* name;
    const char* value;
    struct ini_parameter* next;
};
struct ini_section {
    const char* name;
    struct ini_parameter* parameters;
    struct ini_section* next;
};
struct ini {
    struct ini_parameter* parameters;
    struct ini_section* section;
    char* st; // string table
};

struct ini* ini_read(const char* filename);
int prase_write(struct ini* ini,const char* filename);
int prase_free(struct ini* ini);

#endif //!__PRASE_INI_H__
