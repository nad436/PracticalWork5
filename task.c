#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char data[256];
} Item;

void process_items(size_t count) {
    size_t total_size = count * sizeof(Item);
    
    printf("[*] Requested count: %zu\n", count);
    printf("[*] Calculated total_size: %zu bytes (0x%zX)\n", total_size, total_size);

    Item* array = (Item*)malloc(total_size);
    if (!array) {
        printf("[!] Malloc failed!\n");
        return;
    }
    printf("[*] Buffer allocated at: %p\n", (void*)array);

    printf("[*] Writing data to buffer...\n");
    for (size_t i = 0; i < count; i++) {
        memset(array[i].data, 'A', sizeof(Item));
        
        if (i == 2) { 
            printf("[*] Stopping loop early after corrupting adjacent heap structures.\n");
            break; 
        }
    }

    printf("[*] Attempting to free buffer...\n");
    free(array);
    printf("[+] Done!\n");
}

int main() {
    size_t malicious_count = 72057594037927937ULL; 

    process_items(malicious_count);

    return 0;
}
