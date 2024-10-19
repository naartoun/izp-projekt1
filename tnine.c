#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_CONTACTS 100    // Maximal value of contacts to be read.

int is_found = 0;           //Variable determining whether suitable contact has been found.

//Structure holding contact name and number.
struct contact_t {
    char name[101];
    char number[101];
};

//Function to load from stdin to contact_t structure.
int load_stdin(struct contact_t database[]) {
    char new_line[200];     //Array to preload data to from stdin.
    int line_count = 1;
    int arg_index = 0;

    //Reading new line using fgets.
    while ((fgets(new_line, sizeof(new_line), stdin) != NULL) && (line_count <= 2 * MAX_CONTACTS)) {
        //Checks if the line is within length boundary.
        if (strlen(new_line) > 101) {
            return 1000;
            break;
        }
        //Copies read values into .name/.number section in contact database.
        else {
            if (line_count % 2 == 1) {
                new_line[strcspn(new_line, "\n")] = '\0';
                strncpy(database[arg_index].name, new_line, strlen(new_line));
                database[arg_index].name[strlen(database[arg_index].name)] = '\0';      //Adding \0 to the end of the string to prevent errors.
            }
            else if (line_count % 2 == 0) {
                new_line[strcspn(new_line, "\n")] = '\0';
                strncpy(database[arg_index].number, new_line, strlen(new_line));
                database[arg_index].number[strlen(database[arg_index].number)] = '\0';  //Adding \0 to the end of the string to prevent errors.
            }

            if (line_count % 2 == 0) arg_index++;
            line_count++;
        }
    }
    printf("Line count: %d\n", line_count);
    return arg_index;   //Returns contact count.
}

//Method to turn .name element into a number.
void convert_to_number(struct contact_t current_contact, char name_to_number[]) {
    for (int char_pos = 0; char_pos < (int)strlen(current_contact.name); char_pos++) {
        switch (tolower(current_contact.name[char_pos]))
        {
            case 'a': case 'b': case 'c':
                name_to_number[char_pos] = '2';
                break;
            case 'd': case 'e': case 'f':
                name_to_number[char_pos] = '3';
                break;
            case 'g': case 'h': case 'i':
                name_to_number[char_pos] = '4';
                break;
            case 'j': case 'k': case 'l':
                name_to_number[char_pos] = '5';
                break;
            case 'm': case 'n': case 'o':
                name_to_number[char_pos] = '6';
                break;
            case 'p': case 'q': case 'r': case 's':
                name_to_number[char_pos] = '7';
                break;
            case 't': case 'u': case 'v':
                name_to_number[char_pos] = '8';
                break;
            case 'w': case 'x': case 'y': case 'z':
                name_to_number[char_pos] = '9';
                break;
            default:
                name_to_number[char_pos] = current_contact.name[char_pos];
                break;
        }
    }
    
    name_to_number[strlen(current_contact.name)] = '\0';    //Adding \0 to the end of the string to prevent errors.
}

//Function to find split string within .name/.number.
int split_string_finder(char search_input[], char array_to_search[]) {
    int srch_index = 0;
    int arr_index = 0;
    
    while ((arr_index < (int)strlen(array_to_search)) && (srch_index < (int)strlen(search_input))) {
        if (search_input[srch_index] == array_to_search[arr_index]) {
            srch_index++;
        }
        arr_index++;
    }

    if (srch_index == (int)strlen(search_input)) return 1;
    else return 0;
}

//Main function.
int main(int argc, char *argv[]) {
    //Setting variables.
    struct contact_t all_contacts[MAX_CONTACTS];
    int contact_count = load_stdin(all_contacts);
    printf("Contact count: %d\n", contact_count);
    if (contact_count == 1000) {
        printf("Invalid data, error code 1000\n");
    }
    else {
        //If argc < 2 program outputs whole seznam.txt.
        if (argc < 2) {
            for (int cont_index = 0; cont_index < contact_count; cont_index++) {
            printf("%s, %s\n", all_contacts[cont_index].name, all_contacts[cont_index].number);
            }
        }
        //If argc == 2 program searches for string within given contacts.
        else if (argc == 2) {
            char *search_input = argv[1];

            for (int cont_index = 0; cont_index < contact_count; cont_index++) {
                if (strstr(all_contacts[cont_index].number, search_input) != NULL) {
                    printf("%s, %s\n", all_contacts[cont_index].name, all_contacts[cont_index].number);
                    is_found = 1;   //Global variable is_found is set to 1.
                }
                else {
                    char current_contact_to_number[strlen(all_contacts[cont_index].name)];
                    
                    //Converting name to number using previously declared method.
                    convert_to_number(all_contacts[cont_index], current_contact_to_number);

                    if (strstr(current_contact_to_number, search_input) != NULL) {
                        printf("%s, %s\n", all_contacts[cont_index].name, all_contacts[cont_index].number);
                        is_found = 1;   //Global variable is_found is set to 1.
                    }
                }
            }
        
            if (is_found == 0) printf("Not found\n");
        }
        //If argc == 3 and argv[1] == "-s" program searches for split string within given contacts.
        else if ((argc == 3) && (strcmp(argv[1], "-s") == 0)) {
            char *search_input = argv[2];

            for (int cont_index = 0; cont_index < contact_count; cont_index++) {
                if (split_string_finder(search_input, all_contacts[cont_index].number) == 1) {
                    printf("%s, %s\n", all_contacts[cont_index].name, all_contacts[cont_index].number);
                    is_found = 1;   //Global variable is_found is set to 1.
                }
                else {
                    char current_contact_to_number[strlen(all_contacts[cont_index].name)];

                    //Converting name to number using previously declared method.
                    convert_to_number(all_contacts[cont_index], current_contact_to_number);

                    if (split_string_finder(search_input, current_contact_to_number) == 1) {
                        printf("%s, %s\n", all_contacts[cont_index].name, all_contacts[cont_index].number);
                        is_found = 1;   //Global variable is_found is set to 1.
                    }
                }
            }
        
            if (is_found == 0) printf("Not found\n");
        }
        else printf("Invalid argument count\n");
    }

    return 0;
}