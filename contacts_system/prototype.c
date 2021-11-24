#include <stdio.h>
#include <string.h>

#define FILE_PATH "./contacts.txt"
#define MAX_NAME_LEN 10
#define MAX_COMPANY_LEN 15
#define MAX_EMAIL_LEN 30
#define MAX_CONTACT_NUM 100
#define PHONE_NUM_LEN 8

int NUM_OF_DIGITS_OF_CONTACT_ID = -1;

struct Contact {
    char name[MAX_NAME_LEN];
    char company[MAX_COMPANY_LEN];
    int phone;
    char email[MAX_EMAIL_LEN];
} contacts[MAX_CONTACT_NUM];

/* print the headline of contacts in a beautified format */
void print_contact_headline() {
    printf("%-*s   %-*s   %-*s   %-*s   %-*s\n", NUM_OF_DIGITS_OF_CONTACT_ID,
           "No.", MAX_NAME_LEN, "Name", MAX_COMPANY_LEN, "Company",
           PHONE_NUM_LEN + 1, "Phone", MAX_EMAIL_LEN, "E-mail");
}

/* print a contact in a beautified format */
void print_contact(int id, char *name, char *company, int phone, char *email) {
    printf("%-*d   %-*s   %-*s   %-*d   %-*s\n", NUM_OF_DIGITS_OF_CONTACT_ID,
           id, MAX_NAME_LEN, name, MAX_COMPANY_LEN, company, PHONE_NUM_LEN + 1,
           phone, MAX_EMAIL_LEN, email);
}

/* read in all contacts from file */
void load_contacts() {
    // open in read mode and create if file not exists
    FILE *fp = fopen(FILE_PATH, "a+");

    if (getc(fp) == EOF) {
        printf("Detected empty contacts data.\n\n");
    } else {
        int i = 0;
        rewind(fp); // move the cursor back to the beginning of the file
        while (!feof(fp)) {
            fscanf(fp, "%s %s %d %s", &contacts[i].name, &contacts[i].company,
                   &contacts[i].phone, &contacts[i].email);
            i++;
        }
        printf("Successfully read in %d contact info.\n\n", i - 1);
    }
    fclose(fp);
}

/* get the number of saved contacts */
int get_contact_len() {
    int i;
    for (i = 0; i < MAX_CONTACT_NUM; i++) {
        struct Contact temp = contacts[i];
        if (temp.name[0] == 0 && temp.company[0] == 0 && temp.phone == 0 &&
            temp.email[0] == 0)
            break;
    }
    return i;
}

/* read a name from user input */
void input_name(char *msg, int contact_idx) {
    if (contact_idx >= MAX_CONTACT_NUM) {
        perror("Runtime error: contact index out of range.\n");
        exit(-1);
    }
    int invalid_input = 1;
    char temp[MAX_NAME_LEN];
    while (invalid_input) {
        printf("Please input the Name:      ");
        scanf("%s", temp);
        setbuf(stdin, NULL); // ignore extra characters in input string !!
    }
}

/* list all contacts */
void list_contacts() {
    int len = get_contact_len();
    if (len == 0) {
        printf("No contact info found.\n\n");
        return;
    }

    // calculate the number of digits of max allowed contacts id once
    if (NUM_OF_DIGITS_OF_CONTACT_ID == -1) {
        int tmp = MAX_CONTACT_NUM;
        NUM_OF_DIGITS_OF_CONTACT_ID = 0;
        while (tmp != 0) {
            tmp /= 10;
            ++NUM_OF_DIGITS_OF_CONTACT_ID;
        }
    }

    print_contact_headline();
    for (int i = 0; i < len; i++)
        print_contact(i + 1, contacts[i].name, contacts[i].company,
                      contacts[i].phone, contacts[i].email);
    printf("\n");
}

void add_new_contact() {
    if (get_contact_len() >= MAX_CONTACT_NUM) {
        printf("Memory full.\n");
        return;
    }
    int len = get_contact_len();
    printf("Please input the Name:      ");
    scanf("%s", contacts[len].name);
    setbuf(stdin, NULL); // ignore extra characters in input string !!
    printf("Please input the Company:   ");
    scanf("%s", contacts[len].company);
    setbuf(stdin, NULL); // ignore extra characters in input string !!
    printf("Please input the Phone:     ");
    scanf("%d", &(contacts[len].phone));
    setbuf(stdin, NULL); // ignore extra characters in input string !!
    printf("Please input the E-mail:    ");
    scanf("%s", contacts[len].email);
    setbuf(stdin, NULL); // ignore extra characters in input string !!

    printf("Contact added!\n\n");
}

void modify_contact() {
    printf("Please input the No. of the contact to modify: ");

    int id;
    scanf("%d", &id);
    setbuf(stdin, NULL); // ignore extra characters in input string !!
    id--;

    printf("Please input the Name:  ");
    scanf("%s", &contacts[id].name);
    setbuf(stdin, NULL); // ignore extra characters in input string !!
    printf("Please input the Company:  ");
    scanf("%s", &contacts[id].company);
    setbuf(stdin, NULL); // ignore extra characters in input string !!
    printf("Please input the Phone:  ");
    scanf("%d", &contacts[id].phone);
    setbuf(stdin, NULL); // ignore extra characters in input string !!
    printf("Please input the E-mail:  ");
    scanf("%s", &contacts[id].email);
    setbuf(stdin, NULL); // ignore extra characters in input string !!

    printf("Contact updated!\n\n");
}

void delete_contact() {
    printf("Please input the No. of the contact to delete: ");

    int id;
    scanf("%d", &id);
    setbuf(stdin, NULL); // ignore extra characters in input string !!
    id--;

    int len = get_contact_len();
    for (int i = id; i < len - 1; i++) {
        contacts[i] = contacts[i + 1];
    }
    strcpy(contacts[len - 1].name, "");
    strcpy(contacts[len - 1].company, "");
    contacts[len - 1].phone = 0;
    strcpy(contacts[len - 1].email, "");

    printf("Contact deleted!\n\n");
}

void search_contact() {
    printf("Please input the name of the contact to search: ");

    char name[MAX_NAME_LEN];
    scanf("%s", name);
    setbuf(stdin, NULL); // ignore extra characters in input string !!

    int has_found = 0; // flag: whether find the contact info
    int len = get_contact_len();
    for (int i = 0; i < len; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            printf("Contact found:\n");
            printf("%d   %s   %s   %d   %s\n\n", i + 1, contacts[i].name,
                   contacts[i].company, contacts[i].phone, contacts[i].email);
            has_found = 1;
            break;
        }
    }
    if (has_found == 0)
        printf("Contact not found!\n\n");
}

void save_contacts() {
    // clear file content and write file
    FILE *fp = fopen(FILE_PATH, "w");
    int len = get_contact_len();
    for (int i = 0; i < len; i++) {
        struct Contact temp = contacts[i];
        fprintf(fp, "%s %s %d %s\n", temp.name, temp.company, temp.phone,
                temp.email);
    }
    fclose(fp);
    printf("Bye\n");
}

char input_cmd() {
    printf("Please input\n"
           "\tl - show all contacts\n"
           "\ta - add a new contact\n"
           "\tm - modify a contact\n"
           "\td - delete a contact\n"
           "\ts - search a contact by name\n"
           "\tq - quit the program\n");
    char input;
    scanf("%c", &input);
    setbuf(stdin, NULL); // ignore extra characters in input string !!
    return input;
}

int main() {
    printf("Welcome to Coffee Contacts!\n");
    load_contacts();

    while (1) {
        char input = input_cmd();
        int will_quit = 0; // flag: whether quit the program !!

        switch (input) {
        case 'l': { /* list all contact info */
            list_contacts();
            break;
        }
        case 'a': { /* add a new contact */
            add_new_contact();
            break;
        }
        case 'm': { /* modify a contact info */
            modify_contact();
            break;
        }
        case 'd': { /* delete a contact info */
            delete_contact();
            break;
        }
        case 's': { /* search a contact info by name */
            search_contact();
            break;
        }
        case 'q': { /* quit the program */
            will_quit = 1;
            break;
        }
        default: {
            printf("Illegal input\n");
            break;
        }
        }

        // save the updated contacts data to file
        if (will_quit) {
            save_contacts();
            break;
        }
    }

    return 0;
}
