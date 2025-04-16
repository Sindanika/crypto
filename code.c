#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Caesar Cipher
void caesar_encode(char *message, int rotation, char *encoded_output) {
    int pos = 0;
    while (message[pos] != '\0') {
        if (isalpha(message[pos])) {
            int rotation_base = isupper(message[pos]) ? 65 : 97;
            encoded_output[pos] = ((message[pos] - rotation_base + rotation) % 26) + rotation_base;
        } else {
            encoded_output[pos] = message[pos];
        }
        pos++;
    }
    encoded_output[pos] = '\0';
}

void caesar_decode(char *encoded_message, int rotation, char *decoded_output) {
    caesar_encode(encoded_message, -rotation, decoded_output);
}

// Atbash Cipher
void atbash_encode(char *message, char *encoded_output) {
    int pos = 0;
    while (message[pos] != '\0') {
        if (isalpha(message[pos])) {
            encoded_output[pos] = islower(message[pos]) ? 
                             219 - message[pos] : 
                             155 - message[pos];
        } else {
            encoded_output[pos] = message[pos];
        }
        pos++;
    }
    encoded_output[pos] = '\0';
}

void atbash_decode(char *encoded_message, char *decoded_output) {
    atbash_encode(encoded_message, decoded_output);
}

// Augustus Cipher
void augustus_encode(char *message, char *encoded_output) {
    caesar_encode(message, 1, encoded_output);
}

void augustus_decode(char *encoded_message, char *decoded_output) {
    caesar_decode(encoded_message, 1, decoded_output);
}

// Affine Cipher
int modular_inverse(int num, int modulus) {
    num = num % modulus;
    for (int x = 1; x < modulus; x++) {
        if ((num * x) % modulus == 1) {
            return x;
        }
    }
    return 1;
}

void affine_encode(char *message, int multiplier, int adder, char *encoded_output) {
    int pos = 0;
    while (message[pos] != '\0') {
        if (isalpha(message[pos])) {
            int rotation_base = isupper(message[pos]) ? 65 : 97;
            encoded_output[pos] = ((multiplier * (message[pos] - rotation_base) + adder) % 26) + rotation_base;
        } else {
            encoded_output[pos] = message[pos];
        }
        pos++;
    }
    encoded_output[pos] = '\0';
}

void affine_decode(char *encoded_message, int multiplier, int adder, char *decoded_output) {
    int pos = 0;
    int mult_inverse = modular_inverse(multiplier, 26);
    
    while (encoded_message[pos] != '\0') {
        if (isalpha(encoded_message[pos])) {
            int rotation_base = isupper(encoded_message[pos]) ? 65 : 97;
            int value = (mult_inverse * ((encoded_message[pos] - rotation_base - adder) % 26 + 26)) % 26;
            decoded_output[pos] = value + rotation_base;
        } else {
            decoded_output[pos] = encoded_message[pos];
        }
        pos++;
    }
    decoded_output[pos] = '\0';
}

// Vigenère Cipher
void vigenere_encode(char *message, char *secret_key, char *encoded_output) {
    int pos = 0, key_pos = 0;
    int key_length = strlen(secret_key);
    
    while (message[pos] != '\0') {
        if (isalpha(message[pos])) {
            int rotation_base = isupper(message[pos]) ? 65 : 97;
            int key_offset = tolower(secret_key[key_pos % key_length]) - 'a';
            encoded_output[pos] = ((tolower(message[pos]) - 'a' + key_offset) % 26) + rotation_base;
            key_pos++;
        } else {
            encoded_output[pos] = message[pos];
        }
        pos++;
    }
    encoded_output[pos] = '\0';
}

void vigenere_decode(char *encoded_message, char *secret_key, char *decoded_output) {
    int pos = 0, key_pos = 0;
    int key_length = strlen(secret_key);
    
    while (encoded_message[pos] != '\0') {
        if (isalpha(encoded_message[pos])) {
            int rotation_base = isupper(encoded_message[pos]) ? 65 : 97;
            int key_offset = tolower(secret_key[key_pos % key_length]) - 'a';
            decoded_output[pos] = ((tolower(encoded_message[pos]) - 'a' - key_offset + 26) % 26) + rotation_base;
            key_pos++;
        } else {
            decoded_output[pos] = encoded_message[pos];
        }
        pos++;
    }
    decoded_output[pos] = '\0';
}

// Gronsfeld Cipher
void gronsfeld_encode(char *message, char *numeric_key, char *encoded_output) {
    int pos = 0, key_pos = 0;
    int key_length = strlen(numeric_key);
    
    while (message[pos] != '\0') {
        if (isalpha(message[pos])) {
            int rotation_base = isupper(message[pos]) ? 65 : 97;
            int key_offset = numeric_key[key_pos % key_length] - '0';
            encoded_output[pos] = ((tolower(message[pos]) - 'a' + key_offset) % 26) + rotation_base;
            key_pos++;
        } else {
            encoded_output[pos] = message[pos];
        }
        pos++;
    }
    encoded_output[pos] = '\0';
}

void gronsfeld_decode(char *encoded_message, char *numeric_key, char *decoded_output) {
    int pos = 0, key_pos = 0;
    int key_length = strlen(numeric_key);
    
    while (encoded_message[pos] != '\0') {
        if (isalpha(encoded_message[pos])) {
            int rotation_base = isupper(encoded_message[pos]) ? 65 : 97;
            int key_offset = numeric_key[key_pos % key_length] - '0';
            decoded_output[pos] = ((tolower(encoded_message[pos]) - 'a' - key_offset + 26) % 26) + rotation_base;
            key_pos++;
        } else {
            decoded_output[pos] = encoded_message[pos];
        }
        pos++;
    }
    decoded_output[pos] = '\0';
}

// Beaufort Cipher
void beaufort_encode(char *message, char *secret_key, char *encoded_output) {
    int pos = 0, key_pos = 0;
    int key_length = strlen(secret_key);
    
    while (message[pos] != '\0') {
        if (isalpha(message[pos])) {
            int rotation_base = 97;  // Always using lowercase for simplicity
            int msg_val = tolower(message[pos]) - 'a';
            int key_val = tolower(secret_key[key_pos % key_length]) - 'a';
            encoded_output[pos] = ((key_val - msg_val + 26) % 26) + rotation_base;
            key_pos++;
        } else {
            encoded_output[pos] = message[pos];
        }
        pos++;
    }
    encoded_output[pos] = '\0';
}

void beaufort_decode(char *encoded_message, char *secret_key, char *decoded_output) {
    beaufort_encode(encoded_message, secret_key, decoded_output); // Beaufort is its own inverse
}

// Autokey Cipher
void autokey_encode(char *message, char *seed_key, char *encoded_output) {
    int pos = 0;
    int key_length = strlen(seed_key);
    char *complete_key = (char *)malloc(strlen(message) + key_length + 1);
    
    strcpy(complete_key, seed_key);
    
    while (message[pos] != '\0') {
        if (isalpha(message[pos])) {
            int rotation_base = isupper(message[pos]) ? 65 : 97;
            int key_offset;
            
            if (pos < key_length) {
                key_offset = tolower(seed_key[pos]) - 'a';
            } else {
                key_offset = tolower(message[pos - key_length]) - 'a';
            }
            
            encoded_output[pos] = ((tolower(message[pos]) - 'a' + key_offset) % 26) + rotation_base;
        } else {
            encoded_output[pos] = message[pos];
        }
        pos++;
    }
    encoded_output[pos] = '\0';
    free(complete_key);
}

void autokey_decode(char *encoded_message, char *seed_key, char *decoded_output) {
    int pos = 0;
    int key_length = strlen(seed_key);
    
    while (encoded_message[pos] != '\0') {
        if (isalpha(encoded_message[pos])) {
            int rotation_base = isupper(encoded_message[pos]) ? 65 : 97;
            int key_offset;
            
            if (pos < key_length) {
                key_offset = tolower(seed_key[pos]) - 'a';
            } else {
                key_offset = tolower(decoded_output[pos - key_length]) - 'a';
            }
            
            decoded_output[pos] = ((tolower(encoded_message[pos]) - 'a' - key_offset + 26) % 26) + rotation_base;
        } else {
            decoded_output[pos] = encoded_message[pos];
        }
        pos++;
    }
    decoded_output[pos] = '\0';
}

// Hill Cipher (2x2 matrix)
void matrix_multiply(int key_matrix[2][2], int vector[2], int result_vector[2]) {
    result_vector[0] = (key_matrix[0][0] * vector[0] + key_matrix[0][1] * vector[1]) % 26;
    result_vector[1] = (key_matrix[1][0] * vector[0] + key_matrix[1][1] * vector[1]) % 26;
}

int matrix_det(int matrix[2][2]) {
    return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
}

void matrix_inverse(int matrix[2][2], int inverse_matrix[2][2]) {
    int det = matrix_det(matrix) % 26;
    if (det < 0) det += 26;
    
    int det_inv = modular_inverse(det, 26);
    
    inverse_matrix[0][0] = (matrix[1][1] * det_inv) % 26;
    inverse_matrix[0][1] = ((-matrix[0][1] + 26) * det_inv) % 26;
    inverse_matrix[1][0] = ((-matrix[1][0] + 26) * det_inv) % 26;
    inverse_matrix[1][1] = (matrix[0][0] * det_inv) % 26;
}

void hill_encode(char *message, int key_values[4], char *encoded_output) {
    int key_matrix[2][2] = {
        {key_values[0], key_values[1]},
        {key_values[2], key_values[3]}
    };
    
    // Preprocess message (remove non-alphabetic characters and convert to lowercase)
    char clean_message[1000];
    int clean_pos = 0;
    for (int pos = 0; message[pos] != '\0'; pos++) {
        if (isalpha(message[pos])) {
            clean_message[clean_pos++] = tolower(message[pos]);
        }
    }
    clean_message[clean_pos] = '\0';
    
    // Padding with x, if length is odd
    if (strlen(clean_message) % 2 != 0) {
        strcat(clean_message, "x");
    }
    
    int msg_length = strlen(clean_message);
    clean_pos = 0;
    
    for (int pos = 0; pos < msg_length; pos += 2) {
        int vector[2] = {clean_message[pos] - 'a', clean_message[pos+1] - 'a'};
        int result_vector[2];
        
        matrix_multiply(key_matrix, vector, result_vector);
        
        encoded_output[clean_pos++] = result_vector[0] + 'a';
        encoded_output[clean_pos++] = result_vector[1] + 'a';
    }
    
    encoded_output[clean_pos] = '\0';
}

void hill_decode(char *encoded_message, int key_values[4], char *decoded_output) {
    int key_matrix[2][2] = {
        {key_values[0], key_values[1]},
        {key_values[2], key_values[3]}
    };
    
    int inverse_matrix[2][2];
    matrix_inverse(key_matrix, inverse_matrix);
    
    int msg_length = strlen(encoded_message);
    int decoded_pos = 0;
    
    for (int pos = 0; pos < msg_length; pos += 2) {
        int vector[2] = {encoded_message[pos] - 'a', encoded_message[pos+1] - 'a'};
        int result_vector[2];
        
        matrix_multiply(inverse_matrix, vector, result_vector);
        
        decoded_output[decoded_pos++] = result_vector[0] + 'a';
        decoded_output[decoded_pos++] = result_vector[1] + 'a';
    }
    
    decoded_output[decoded_pos] = '\0';
}

// Rail Fence Cipher
void rail_fence_encode(char *message, int rails_count, char *encoded_output) {
    int msg_length = strlen(message);
    
    char fence[rails_count][msg_length];
    for (int rail = 0; rail < rails_count; rail++) {
        for (int col = 0; col < msg_length; col++) {
            fence[rail][col] = '\0';
        }
    }
    
    int current_rail = 0;
    int direction_down = 0;
    
    for (int col = 0; col < msg_length; col++) {
        fence[current_rail][col] = message[col];
        
        if (current_rail == 0 || current_rail == rails_count - 1) {
            direction_down = !direction_down;
        }
        
        current_rail += direction_down ? 1 : -1;
    }
    
    // Reading cipher text from rail matrix
    int output_pos = 0;
    for (int rail = 0; rail < rails_count; rail++) {
        for (int col = 0; col < msg_length; col++) {
            if (fence[rail][col] != '\0') {
                encoded_output[output_pos++] = fence[rail][col];
            }
        }
    }
    encoded_output[output_pos] = '\0';
}

void rail_fence_decode(char *encoded_message, int rails_count, char *decoded_output) {
    int msg_length = strlen(encoded_message);
    
    char fence[rails_count][msg_length];
    for (int rail = 0; rail < rails_count; rail++) {
        for (int col = 0; col < msg_length; col++) {
            fence[rail][col] = '\0';
        }
    }
    
    int current_rail = 0;
    int direction_down = 0;
    
    for (int col = 0; col < msg_length; col++) {
        fence[current_rail][col] = '*';
        
        if (current_rail == 0 || current_rail == rails_count - 1) {
            direction_down = !direction_down;
        }
        
        current_rail += direction_down ? 1 : -1;
    }
    
    int input_pos = 0;
    for (int rail = 0; rail < rails_count; rail++) {
        for (int col = 0; col < msg_length; col++) {
            if (fence[rail][col] == '*') {
                fence[rail][col] = encoded_message[input_pos++];
            }
        }
    }
    
    // Reading the decoded message
    current_rail = 0;
    direction_down = 0;
    input_pos = 0;
    
    for (int col = 0; col < msg_length; col++) {
        decoded_output[col] = fence[current_rail][col];
        
        if (current_rail == 0 || current_rail == rails_count - 1) {
            direction_down = !direction_down;
        }
        
        current_rail += direction_down ? 1 : -1;
    }
    
    decoded_output[msg_length] = '\0';
}

// Ngram Cipher
void ngram_encode(char *message, int chunk_size, char *encoded_output) {
    int msg_length = strlen(message);
    int output_pos = 0;
    
    //Removes plain spaces
    char clean_message[1000];
    int clean_pos = 0;
    
    for (int pos = 0; pos < msg_length; pos++) {
        if (isalpha(message[pos])) {
            clean_message[clean_pos++] = toupper(message[pos]);
        }
    }
    clean_message[clean_pos] = '\0';
    
    // Padding with 'X' if length is not divisible by chunk_size
    while (clean_pos % chunk_size != 0) {
        clean_message[clean_pos++] = 'X';
    }
    clean_message[clean_pos] = '\0';
    
    for (int pos = 0; pos < clean_pos; pos += chunk_size) {
        int offset = 5; // Fixed shift value for easiness
        
        for (int j = 0; j < chunk_size; j++) {
            encoded_output[output_pos++] = ((clean_message[pos + j] - 'A' + offset) % 26) + 'A';
        }
        
        if (pos + chunk_size < clean_pos) {
            encoded_output[output_pos++] = ' ';
        }
    }
    
    encoded_output[output_pos] = '\0';
}

void ngram_decode(char *encoded_message, int chunk_size, char *decoded_output) {
    // Removing spaces
    char clean_encoded[1000];
    int clean_pos = 0;
    
    for (int pos = 0; encoded_message[pos] != '\0'; pos++) {
        if (encoded_message[pos] != ' ') {
            clean_encoded[clean_pos++] = encoded_message[pos];
        }
    }
    clean_encoded[clean_pos] = '\0';
    
    int output_pos = 0;
    
    for (int pos = 0; pos < clean_pos; pos += chunk_size) {
        int offset = 5; // Same fixed shift value 
        
        for (int j = 0; j < chunk_size && (pos + j) < clean_pos; j++) {
            decoded_output[output_pos++] = ((clean_encoded[pos + j] - 'A' - offset + 26) % 26) + 'A';
        }
    }
    
    decoded_output[output_pos] = '\0';
}

// Route Cipher
void route_encode(char *message, int rows_count, char *encoded_output) {
    int msg_length = strlen(message);
    int cols_count = (msg_length + rows_count - 1) / rows_count; 
    
    char grid[rows_count][cols_count];
    int pos = 0;
    
    for (int row = 0; row < rows_count; row++) {
        for (int col = 0; col < cols_count; col++) {
            if (pos < msg_length) {
                grid[row][col] = message[pos++];
            } else {
                grid[row][col] = 'x';  
            }
        }
    }
    
    pos = 0;
    for (int col = 0; col < cols_count; col++) {
        for (int row = 0; row < rows_count; row++) {
            encoded_output[pos++] = grid[row][col];
        }
    }
    
    encoded_output[pos] = '\0';
}

void route_decode(char *encoded_message, int rows_count, char *decoded_output) {
    int msg_length = strlen(encoded_message);
    int cols_count = (msg_length + rows_count - 1) / rows_count;
    
    char grid[rows_count][cols_count];
    int pos = 0;
    
    for (int col = 0; col < cols_count; col++) {
        for (int row = 0; row < rows_count; row++) {
            grid[row][col] = encoded_message[pos++];
        }
    }
    
    pos = 0;
    for (int row = 0; row < rows_count; row++) {
        for (int col = 0; col < cols_count; col++) {
            decoded_output[pos++] = grid[row][col];
        }
    }
    
    decoded_output[msg_length] = '\0';
}

// Myszkowski Cipher 
void myszkowski_encode(char *message, char *key_word, char *encoded_output) {
    int key_length = strlen(key_word);
    int msg_length = strlen(message);
    
    int key_order[key_length];
    for (int i = 0; i < key_length; i++) {
        key_order[i] = i;
    }
    
    // Sorting based on key
    for (int i = 0; i < key_length - 1; i++) {
        for (int j = i + 1; j < key_length; j++) {
            if (key_word[key_order[i]] > key_word[key_order[j]]) {
                int temp = key_order[i];
                key_order[i] = key_order[j];
                key_order[j] = temp;
            }
        }
    }
    
    // Create the column grid
    int rows_count = (msg_length + key_length - 1) / key_length;
    char grid[rows_count][key_length];
    
    // Filling the grid
    int pos = 0;
    for (int row = 0; row < rows_count; row++) {
        for (int col = 0; col < key_length; col++) {
            if (pos < msg_length) {
                grid[row][col] = message[pos++];
            } else {
                grid[row][col] = 'x';  // Padding
            }
        }
    }
    
    // Reading from the columns as per key order
    pos = 0;
    for (int col_idx = 0; col_idx < key_length; col_idx++) {
        for (int row = 0; row < rows_count; row++) {
            encoded_output[pos++] = grid[row][key_order[col_idx]];
        }
    }
    
    encoded_output[pos] = '\0';
}

void myszkowski_decode(char *encoded_message, char *key_word, char *decoded_output) {
    int key_length = strlen(key_word);
    int msg_length = strlen(encoded_message);
    int rows_count = (msg_length + key_length - 1) / key_length;
    
    int key_order[key_length];
    for (int i = 0; i < key_length; i++) {
        key_order[i] = i;
    }
    
    // Sorting based on the key
    for (int i = 0; i < key_length - 1; i++) {
        for (int j = i + 1; j < key_length; j++) {
            if (key_word[key_order[i]] > key_word[key_order[j]]) {
                int temp = key_order[i];
                key_order[i] = key_order[j];
                key_order[j] = temp;
            }
        }
    }
    
    char grid[rows_count][key_length];
    
    // To fill the grid with the ciphertext with respect to the key order
    int pos = 0;
    for (int col_idx = 0; col_idx < key_length; col_idx++) {
        for (int row = 0; row < rows_count; row++) {
            grid[row][key_order[col_idx]] = encoded_message[pos++];
        }
    }
    
    pos = 0;
    for (int row = 0; row < rows_count; row++) {
        for (int col = 0; col < key_length; col++) {
            if (pos < msg_length) {
                decoded_output[pos++] = grid[row][col];
            }
        }
    }
    
    decoded_output[msg_length] = '\0';
}

int main() {
    char message[1000];
    char encoded_output[1000];
    char decoded_output[1000];
    int choice, rotation, multiplier, adder, rails_count, chunk_size;
    char secret_key[100];
    int hill_keys[4];
    
    printf("Choose Cipher Algorithm:\n");
    printf("1. Caesar Cipher\n");
    printf("2. Atbash Cipher\n");
    printf("3. Augustus Cipher\n");
    printf("4. Affine Cipher\n");
    printf("5. Vigenère Cipher\n");
    printf("6. Gronsfeld Cipher\n");
    printf("7. Beaufort Cipher\n");
    printf("8. Autokey Cipher\n");
    printf("9. Hill Cipher\n");
    printf("10. Rail Fence Cipher\n");
    printf("11. Ngram Cipher\n");
    printf("12. Route Cipher\n");
    printf("13. Myszkowski Cipher\n");
    
    printf("Enter the number of the cipher you want to use: ");
    scanf("%d", &choice);
    getchar();  
    
    printf("Enter the message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';  
    
    switch (choice) {
        case 1:
            printf("Enter the rotation value for Caesar Cipher: ");
            scanf("%d", &rotation);
            caesar_encode(message, rotation, encoded_output);
            caesar_decode(encoded_output, rotation, decoded_output);
            break;
        case 2:
            atbash_encode(message, encoded_output);
            atbash_decode(encoded_output, decoded_output);
            break;
        case 3:
            augustus_encode(message, encoded_output);
            augustus_decode(encoded_output, decoded_output);
            break;
        case 4:
            printf("Enter the multiplier for Affine Cipher: ");
            scanf("%d", &multiplier);
            printf("Enter the additive constant for Affine Cipher: ");
            scanf("%d", &adder);
            affine_encode(message, multiplier, adder, encoded_output);
            affine_decode(encoded_output, multiplier, adder, decoded_output);
            break;
        case 5:
            printf("Enter the key for Vigenère Cipher: ");
            scanf("%s", secret_key);
            vigenere_encode(message, secret_key, encoded_output);
            vigenere_decode(encoded_output, secret_key, decoded_output);
            break;
        case 6:
            printf("Enter the key for Gronsfeld Cipher (digits only): ");
            scanf("%s", secret_key);
            gronsfeld_encode(message, secret_key, encoded_output);
            gronsfeld_decode(encoded_output, secret_key, decoded_output);
            break;
        case 7:
            printf("Enter the key for Beaufort Cipher: ");
            scanf("%s", secret_key);
            beaufort_encode(message, secret_key, encoded_output);
            beaufort_decode(encoded_output, secret_key, decoded_output);
            break;
        case 8:
            printf("Enter the key for Autokey Cipher: ");
            scanf("%s", secret_key);
            autokey_encode(message, secret_key, encoded_output);
            autokey_decode(encoded_output, secret_key, decoded_output);
            break;
        case 9:
            printf("Enter the 4 keys for Hill Cipher as a list (e.g. 5 8 17 3): ");
            scanf("%d %d %d %d", &hill_keys[0], &hill_keys[1], &hill_keys[2], &hill_keys[3]);
            hill_encode(message, hill_keys, encoded_output);
            hill_decode(encoded_output, hill_keys, decoded_output);
            break;
        case 10:
            printf("Enter the number of rails for Rail Fence Cipher: ");
            scanf("%d", &rails_count);
            rail_fence_encode(message, rails_count, encoded_output);
            rail_fence_decode(encoded_output, rails_count, decoded_output);
            break;
        case 11:
            printf("Enter the value of n for Ngram Cipher: ");
            scanf("%d", &chunk_size);
            ngram_encode(message, chunk_size, encoded_output);
            ngram_decode(encoded_output, chunk_size, decoded_output);
            break;
        case 12:
            printf("Enter the size of the matrix for Route Cipher: ");
            scanf("%d", &rails_count);
            route_encode(message, rails_count, encoded_output);
            route_decode(encoded_output, rails_count, decoded_output);
            break;
        case 13:
            printf("Enter the key for Myszkowski Cipher: ");
            scanf("%s", secret_key);
            myszkowski_encode(message, secret_key, encoded_output);
            myszkowski_decode(encoded_output, secret_key, decoded_output);
            break;
        default:
            printf("Invalid choice!\n");
            return 1;
    }
    
    printf("Encrypted: %s\n", encoded_output);
    printf("Decrypted: %s\n", decoded_output);
    
    return 0;
}
