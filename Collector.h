#include <assert.h>
#include <string.h>

#define MAX_STRUCTURE_NAME_SIZE 128
#define MAX_FIELD_NAME_SIZE 128

typedef struct _struct_db_rec_ struct_db_rec_t;
typedef struct _field_info_ field_info_t;
typedef struct _struct_db_ struct_db_t;

typedef enum{
    UINT8,
    UINT32,
    INT32,
    CHAR,
    OBJ_PTR,
    FLOAT,
    DOUBLE,
    OBJ_STRUCT
} data_type_t;

#define OFFSETOF(struct_name, fld_name) \
    (unsigned int)&(((struct_name *)0)->fld_name)

#define FIELD_SIZE(struct_name, fld_name) \
    sizeof(((struct_name *)0)->fld_name)

struct _struct_db_ {
    struct_db_rec_t *head;
    struct_db_rec_t *tail;
    unsigned int count;
};

struct _struct_db_rec_ {
    struct_db_rec_t *next;
    char struct_name[MAX_STRUCTURE_NAME_SIZE];
    unsigned int ds_size;
    unsigned int n_fields;
    field_info_t *fields;
};

struct _field_info_ {
    char fname[MAX_FIELD_NAME_SIZE];
    unsigned int size;
    unsigned int offset;
    data_type_t *dtype;
    char nested_str_name[MAX_STRUCTURE_NAME_SIZE];
};

void print_structure_record(struct_db_rec_t *struct_rec);

void print_structure_db(struct_db_t *struct_db);

int add_structure_to_struct_db(struct_db_t *struct_db, struct_db_rec_t *struct_rec);

#define FIELD_INFO(struct_name, fld_name, dtype, nested_struct_name) \
    {#fld_name, FIELD_SIZE(struct_name, fld_name),            \
    OFFSETOF(struct_name, fld_name), dtype, #nested_struct_name}


#define REG_STRUCT(struct_db, st_name, fields_arr)                                      \
    do{                                                                                 \
        struct_db_rec_t *rec = (struct_db_rec_t *) calloc(1, sizeof(struct_db_rec_t));  \
        strncpy(rec->struct_name, #st_name, MAX_STRUCTURE_NAME_SIZE);                   \
        rec->ds_size = sizeof(st_name);                                                 \
        rec->n_fields = sizeof(fields_arr)/sizeof(field_info_t);                        \
        rec->fields = fields_arr;                                                       \
        if(add_structure_to_struct_db(struct_db, rec)){                                 \
            assert(0);                                                                  \
        }                                                                               \
    }while(0);
