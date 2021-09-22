//Stefan Tcaciuc 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//student

struct student {
    char *name;
    char initial;
    char *surname;
    int year;
    char *courseName;
    char group;
    int average;
};

struct list_node {
    int data_type;
    void *data;
    struct list_node *next;
};

enum type {
    INT,
    STRING,
    CHAR,
    STUDENT
};

struct list_node *new_node(void *data, int type) {
    struct list_node *new_node = malloc(sizeof(struct list_node));

    new_node->data_type = type;
    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}


//struct student *new_student() {
//    struct student *new_student = malloc(sizeof(struct student));
//    scanf("%s", new_student->name);
//    scanf("(%c)", &new_student->initial);
//    scanf("%s", new_student->surname);
//    scanf("%d", &new_student->year);
//    scanf("%s", new_student->courseName);
//    scanf("%c", &new_student->group);
//    scanf("%d", &new_student->average);
//    return new_student;
//}

int f_scanf(FILE *FILE, const char *format, struct list_node head) {
    struct list_node *cursor = head.next;

    int hold;
    int dataCounter = 0;
    int index = 0;
    char d_hold_array[10];
    char s_hold_array[10];

    while (format[index] != '\0') {             //while not end of line
        if (format[index] == '%') {                 //check format string for % if not go to else statement
            char scenario = format[index + 1];          //check the data time of next index
            switch (scenario) {                         //switch to scenario that matches the datatype
                case 'd':                               //intiget scenario
                    cursor->data_type = INT;
                    index++;
                    int i = 0;
                    while ((hold >= '0') &&
                           (hold <= '9')) {               //while between 0 and 9 get char and append it to array
                        hold = fgetc(FILE);
                        d_hold_array[i] = (char) hold;
                        i++;
                    }
                    ungetc(hold, stdin);                            //put back the last char in the buffer
                    int hold_int = atoi(d_hold_array);                //parse to  appropriate data type
                    printf("%d", hold_int);                 //test string
                    index++;
//inc index++
                    dataCounter++;
                    *(int *) cursor->data = hold_int;               //set date to pointer
                    break;

                case 's':                                   //string scenario
                    cursor->data_type = STRING;             //set datatype to string
                    index++;
                    int g = 0;
                    while (hold != ' ') {                   //while there is no space in string
                        hold = fgetc(FILE);                     //getchar
                        if (hold == ' ') { break; }             //if character is space break
                        s_hold_array[g] = hold;                //append characters to array
                        g++;
                    }
                    ungetc(hold, stdin);                // put back the space in the buffer

                    s_hold_array[g] = '\0';
                    printf("%s", s_hold_array);         //test print statement
                    index++;
                    dataCounter++;
                    strcpy(cursor->data, s_hold_array);        //segmentation fault here not sure why
                    break;

                case 'c':                                       //char case
                    cursor->data_type = CHAR;                   //set datatype to char
                    index++;
                    hold = fgetc(FILE);                         //get char
                    printf("%c", hold);                     //test print
                    index++;
                    dataCounter++;
                    *(char *) cursor->data = hold;                  //saet hold as the data for char
                    ungetc(hold, stdin);                    //put back the char in the buffer

                    break;
            }

        } else if (format[index] != '%') {
            hold = fgetc(FILE);

            if (format[index] == hold) {
                dataCounter++;                              //right here its skipping an format index and ive used the
                // debugger and spent soo much time but i coudnt find the problem
                index++;
            } else {
                return dataCounter;
            }

        }

    }

    return dataCounter;
}

int main(int argc, char *argv[]) {

    struct student *s = malloc(sizeof(struct student));
    struct list_node head;
    struct list_node *cursor;
    struct list_node *name = new_node(s->name, STRING);
    struct list_node *initial = new_node(&s->initial, CHAR);                //nodes for each of the parameters
    struct list_node *surname = new_node(s->surname, STRING);
    struct list_node *year = new_node(&s->year, INT);
    struct list_node *courseName = new_node(s->courseName, STRING);
    struct list_node *group = new_node(&s->group, CHAR);
    struct list_node *average = new_node(&s->average, INT);


    head.next = name;
    name->next = initial;
    initial->next = surname;
    surname->next = year;               //manually linking the nodes
    year->next = courseName;
    courseName->next = group;
    group->next = average;

    char format[] = "%s (%c) %s %d %s %c %d";
    FILE *FILE;

    if (argc < 2) {
        return 0;
    }
    FILE = fopen(argv[1], "r");         //open file
    if (!FILE) {
        printf("Source file cannot be found");          //make sure file exists
    }
    while (FILE != EOF) {

        f_scanf(FILE, format, head);         //while not end of file use costom f_scanf function
    }


    cursor = head.next;
    struct list_node *student = new_node(s, STUDENT);
    head.next = student;                                                                    //student gets added to database
    while (cursor != NULL) {
        printf("%s %c %s %d %s %c %d\n", ((struct student *) cursor->data)->name,
               ((struct student *) cursor->data)->initial, ((struct student *) cursor->data)->surname,
               ((struct student *) cursor->data)->year,
               ((struct student *) cursor->data)->courseName,          //print out the student
               ((struct student *) cursor->data)->group, ((struct student *) cursor->data)->average);
        cursor = cursor->next;
    }

    fclose(FILE);   //close file
}
