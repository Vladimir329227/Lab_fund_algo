#include "main.h"

unsigned long hash(const char *str) {
    unsigned long hash = 0;
    while (*str != '\0') {
        if ( hash > ULONG_MAX / 62 - (*str - '0') - 10)
            hash = 1;

        if (isdigit(*str))
            hash = hash * 62 + (*str - '0');
        else if (isupper(*str))
            hash = hash * 62 + (*str - 'A' + 10);
        else if (islower(*str))
            hash = hash * 62 + (*str - 'a' + 36);
        str++;
    }
    return hash;
}

enum Errors rebuild_table(HashTable *ht) {
    int new_size = ht->size * 2;
    Node **new_table = (Node **)calloc(new_size, sizeof(Node *));
    if (!new_table)
        return INVALID_MEMORY;

    for (int i = 0; i < ht->size; i++) {
        Node *node = ht->table[i];
        while (node) {
            Node *next = node->next;
            unsigned long new_index = node->hash % new_size;
            node->next = new_table[new_index];
            new_table[new_index] = node;
            node = next;
        }
    }

    free(ht->table);
    ht->table = new_table;
    ht->size = new_size;

    return OK;
}

enum Errors create_node(const char *def_name, const char *value, Node** node, unsigned long hash) {
    if (!def_name || !value || !node)
        return INVALID_INPUT;
    *node = (Node *)malloc(sizeof(Node));
    if (!*node)
        return INVALID_MEMORY;
    (*node)->def_name = strdup(def_name);
    (*node)->value = strdup(value);
    (*node)->next = NULL;
    (*node)->hash = hash;
    return OK;
}

enum Errors insert(HashTable *ht, const char *def_name, const char *value) {
    if (!def_name || !value || !ht)
        return INVALID_INPUT;
    unsigned long index = hash(def_name);
    Node *node;
    if (create_node(def_name, value, &node, index) != OK)
        return INVALID_MEMORY;
    node->next = ht->table[index % ht->size];
    ht->table[index % ht->size] = node;
    char *newline = strchr(node->value, '\n');
    if (newline)
        *newline = '\0';
    
    ht->count++;
    if (ht->count > ht->size) {
        if (rebuild_table(ht) != OK) 
            return INVALID_MEMORY;
    }
    return OK;
}


char* search(HashTable *ht, const char *def_name) {
    unsigned long index = hash(def_name);
    Node *node = ht->table[index % ht->size];
    while (node) {
        if (strcmp(node->def_name, def_name) == 0) {
            return node->value;
        }
        node = node->next;
    }
    return NULL;
}

enum Errors free_table(HashTable *ht) {
    if (!ht)
        return INVALID_INPUT;
    for (int i = 0; i < HASH_SIZE; i++) {
        Node *node = ht->table[i];
        while (node) {
            Node *temp = node;
            node = node->next;
            free(temp->def_name);
            free(temp->value);
            free(temp);
        }
    }
    free(ht->table);
    return OK;
}

enum Errors process_file(const char *filename) {
    if (!filename)
        return INVALID_INPUT;
    FILE *file = fopen(filename, "r");
    if (!file)
        return ERROR_OPEN_FILE;

    HashTable ht = {0};
    ht.size = HASH_SIZE;
    ht.table = (Node **)calloc(ht.size, sizeof(Node *));
    if (!ht.table) {
        fclose(file);
        return INVALID_MEMORY;
    }

    char line[LINE_SIZE];
    while (fgets(line, sizeof(line), file)) {
        char *ptr = line;
        while (ptr[0] == ' ' || ptr[0] == '\t')
            ptr++;

        if (strncmp(ptr, "#define", 7) == 0) {
            char def_name[LINE_SIZE];
            char value[LINE_SIZE];
            if (sscanf(ptr, "#define %s %[^\n]", def_name, value) == 2) {
                value[strlen(value)-1] = '\0';
                if (insert(&ht, def_name, value) != OK) {
                    free_table(&ht);
                    fclose(file);
                    return INVALID_MEMORY;
                }
                printf("#define %s %s\n", def_name, value);
            }
        }
    }

    rewind(file);
    char buffer[LINE_SIZE];
    while (fgets(line, sizeof(line), file)) {
        char *ptr = line;
        while (ptr[0] == ' ' || ptr[0] == '\t')
            ptr++;
        if (strncmp(ptr, "#define", 7) != 0) {
            const char *delimiters = " \t\n\r()!+-/*[].,;:";
            char *token = strpbrk(ptr, delimiters);
            while (token) {
                sprintf(buffer, "%.*s", (int)(token - ptr), ptr);
                char *value = search(&ht, buffer);
                if (value) {
                    printf("%s%c", value, *token);
                } else {
                    printf("%.*s%c", (int)(token - ptr), ptr, *token);
                }
                ptr = token + 1;
                token = strpbrk(ptr, delimiters);
            }
            printf("%s", ptr);

        }
    }

    free_table(&ht);
    fclose(file);
    return OK;
}
