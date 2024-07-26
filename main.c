#include <stdio.h>
#include <stdlib.h>

#include "Collector.h"

typedef struct books_ {
    char book_name[70];
    unsigned int bood_id;
    char isbn[13];
} books_t;

typedef struct author_ {
    char first_name[40];
    char last_name[40];
    unsigned int author_id;
    books_t *books;
} author_t;

void fill_struct_db(void) {
    struct_db_t *st_db = (struct_db_t *) calloc(1, sizeof(struct_db_t));

    static field_info_t author_fields[] = {
        FIELD_INFO(author_t, first_name, CHAR, 0),
        FIELD_INFO(author_t, last_name, CHAR, 0),
        FIELD_INFO(author_t, author_id, UINT32, 0),
        FIELD_INFO(author_t, books, OBJ_PTR, 0)
    };

    REG_STRUCT(st_db, author_t, author_fields);

}

int main(void) {

    fill_struct_db();



}
