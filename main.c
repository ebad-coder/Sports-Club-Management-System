// Project Name  : Sports Club Management System


// HEADER FILES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/*******************************************************************************************/


// STRUCTURE TO STORE EVERY BOOKING DETAILS
struct Booking
{
    int booking_id;
    char name[50];
    char phone_number[20];
    char court_name[20];
    char day[20];
    char timing[15];
    struct Booking* next;
};
/*******************************************************************************************/


// FUNCTION PROTOTYPES:
void print_menu();
void about_club();
void view_all_bookings(struct Booking*);
void get_string_input(char*, int);
void print_string_array(char* [], int);
void save_to_file(struct Booking*);
void free_memory(struct Booking*);
void wait_for_enter();
int check_id_exists(struct Booking*, int);
int is_available(struct Booking*, struct Booking*);
int get_int_input();
struct Booking* book_court(struct Booking*);
struct Booking* check_booking(struct Booking*);
struct Booking* cancel_booking(struct Booking*);
struct Booking* check_availability(struct Booking*);
struct Booking* edit_booking(struct Booking*, struct Booking*);
struct Booking* perform_booking(struct Booking*, struct Booking*);
struct Booking* load_from_file(struct Booking*);
/*******************************************************************************************/


// PROGRAM EXECUTION STARTS FROM HERE
int main()
{
    struct Booking* head = NULL;
    srand(time(NULL));
    head = load_from_file(head);

    while (1)
    {
        printf("\n\n\n==================================================================\n");
        printf("------------ WELCOME TO SPORTS CLUB MANAGEMENT SYSTEM ------------\n");
        printf("==================================================================\n\n");

        print_menu();
        printf("Enter your choice: ");
        int choice = get_int_input();

        switch (choice) {
            case 1:
                about_club();
                break;

            case 2:
                head = book_court(head);
                break;

            case 3:
                head = check_booking(head);
                break;

            case 4:
                head = cancel_booking(head);
                break;

            case 5:
                head = check_availability(head);
                break;
            
            case 6:
                view_all_bookings(head);
                break;

            case 7:
                printf("\nThanks for using our management system. See you soon :)");
                save_to_file(head);
                free_memory(head);
                return 0;

            default:
                printf("\nPlease enter a valid option [1-7] next time. Press ENTER to continue...");
                wait_for_enter();
                break;
        }
    }
}
/*******************************************************************************************/


// THIS FUNCTIONS PRINTS THE MAIN MENU TO THE USER
void print_menu()
{
    printf("Menu:\n");
    printf("------------------------------\n");
    printf("1. About our club\n");
    printf("2. Book our court\n");
    printf("3. View your booking\n");
    printf("4. Cancel your booking\n");
    printf("5. Check court availability\n");
    printf("6. View all bookings\n");
    printf("7. Exit\n");
    printf("------------------------------\n");
}
/*******************************************************************************************/


// THIS FUNCTION PRINTS THE DETAILS OF THE SPORTS CLUB
void about_club()
{
    printf("\n\n\n==================================================================\n");
    printf("--------------------- ABOUT OUR SPORTS CLUB ----------------------\n");
    printf("==================================================================\n\n");

    printf("Welcome to our Sports Club, a premier destination for sports enthusiasts and fitness lovers. Established with the vision of promoting a healthy and active lifestyle, our club provides world-class facilities for a variety of sports, including tennis, badminton, football, cricket, basketball, hockey and more. We take pride in fostering a community built on teamwork, discipline, and sportsmanship, where players of all levels can develop their skills and enjoy the spirit of competition. At our Sports Club, we believe that fitness should be both fun and fulfilling. Our mission is to create an environment where every member feels motivated, valued, and inspired to achieve their personal goals. Whether you are here to compete, train, or simply stay active, our club offers the perfect blend of professionalism, passion, and community spirit. Join us and be part of a dynamic sports family that celebrates excellence and the joy of an active lifestyle.");

    printf("\n\nContact: 03123456789\n");
    printf("Email:   sportsclub123@gmail.com\n");
    printf("Website: www.sportsclub.com\n\n");

    printf("Press ENTER to return to menu...");
    wait_for_enter();
}
/*******************************************************************************************/


// THIS FUNCTION BOOKS AN AVAILABLE COURT FOR THE USER'S ENTERED DETAILS
struct Booking* book_court(struct Booking* head)
{
    printf("\n\n\n==================================================================\n");
    printf("----------------- BOOK A COURT AT OUR SPORTS CLUB ----------------\n");
    printf("==================================================================\n\n");

    struct Booking record;

    printf("Please enter your full name: ");
    get_string_input(record.name, 50);

    printf("\nPlease enter your phone number: ");
    get_string_input(record.phone_number, 20);

    char* courts[] = {"Cricket", "Football", "Basketball", "Tennis", "Badminton", "Boxing", "Hockey", "Volleyball", "Table Tennis"};
    printf("\nSelect the court you want to book:\n");
    print_string_array(courts, 9);
    printf("Enter your choice: ");
    int choice = get_int_input();

    if (choice > 0 && choice <= 9) {
        strcpy(record.court_name, courts[choice - 1]);
    }
    else {
        printf("\n\nPlease select a valid option [1-9] next time. Press ENTER to return to menu...");
        wait_for_enter();
        return head;
    }

    printf("\nSelect The Day You Would Like To Reserve The Court For:\n");
    char* days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    print_string_array(days, 7);
    printf("Enter Your Choice: ");
    int day_choice = get_int_input();

    if (day_choice > 0 && day_choice <= 7) {
        strcpy(record.day, days[day_choice - 1]);
    }
    else {
        printf("\n\nPlease select a valid option [1-7] next time. Press ENTER to return to menu..");
        wait_for_enter();
        return head;
    }

    printf("\nSelect Your Timings:\n");
    char* timings[] = {"Morning", "Afternoon", "Evening", "Night"};
    print_string_array(timings, 4);
    printf("Enter Your Choice: ");
    int timing_choice = get_int_input();
    
    if (timing_choice > 0 && timing_choice <= 4) {
        strcpy(record.timing, timings[timing_choice - 1]);
    }
    else {
        printf("\n\nPlease select a valid option [1-4] next time. Press ENTER to return to menu..");
        wait_for_enter();
        return head;
    }
    
    if (is_available(&record, head)) {
        head = perform_booking(&record, head);
    }
    else {
        printf("\n\nOops! The court you desired is not available at your desired timings. Please try again later.");
        printf("\nPress ENTER to return to menu...");
        wait_for_enter();
    }

    return head;
}
/*******************************************************************************************/


// THIS FUNCTION CHECKS THE BOOKING FOR THE BOOKING ID ENTERED BY THE USER
struct Booking* check_booking(struct Booking* head)
{
    printf("\n\n\n==================================================================\n");
    printf("-------------- CHECK YOUR BOOKING AT OUR SPORTS CLUB -------------\n");
    printf("==================================================================\n\n");

    printf("Please enter your booking ID: ");
    int check_id = get_int_input();

    struct Booking* record = head;
    int found = 0;
    
    while (record) {
        if (record->booking_id == check_id) {
            printf("\n\nRecord founded:");
            printf("\nName: %s", record->name);
            printf("\nContact: %s", record->phone_number);
            printf("\nCourt: %s", record->court_name);
            printf("\nDay: %s", record->day);
            printf("\nTiming: %s", record->timing);
            found = 1;
            break;
        }
        record = record->next;
    }

    if (!found) {
        printf("\n\nError: Record not found. Please enter correct booking ID.");
        printf("\nIf you have lost your booking ID, then please contact on 03123456789 for help.");
    }
    else {
        printf("\n\nDo you wish to edit your booking [Y/N]: ");
        char wish[20];
        get_string_input(wish, 20);

        if (wish[0] == 'Y' || wish[0] == 'y') {
            head = edit_booking(record, head);
        }
    }
    
    printf("\nPress ENTER to return to menu...");
    wait_for_enter();
    return head;
}
/*******************************************************************************************/


// THIS FUNCTION CANCELS THE BOOKING FOR THE BOOKING ID ENTERED BY THE USER
struct Booking* cancel_booking(struct Booking* head)
{
    printf("\n\n\n==================================================================\n");
    printf("------------- CANCEL YOUR BOOKING AT OUR SPORTS CLUB -------------\n");
    printf("==================================================================\n\n");
    
    printf("Please Enter Your Booking ID: ");
    int check_id = get_int_input();
    
    int found = 0;
    struct Booking* node_to_remove = head;
    struct Booking* record = head;
    
    if (head && head->booking_id == check_id) {
        node_to_remove = head;
        found = 1;
    }
    else {
        while (record && record->next) {
            if (record->next->booking_id == check_id) {
                node_to_remove = record->next;
                found = 1;
                break;
            }
            record = record->next;      
        }
    }

    if (found == 1) {
        printf("\n\nAre you sure you want to cancel your booking? [Y/N]: ");
        char wish[20];
        get_string_input(wish, 20);
        int cancel = (wish[0] == 'Y' || wish[0] == 'y') ? 1 : 0;

        if (cancel) {
            if (node_to_remove == head) {
                head = head->next;
            }
            else {
                record->next = node_to_remove->next;
            }
            free(node_to_remove);
            printf("\n\nYour booking has been successfully cancelled.");
        }
        else {
            printf("\n\nThe cancellation process has been stopped.");
        }
    }
    else {
        printf("\n\nError: Record not found. Please enter correct booking ID..!");
        printf("\nIf you have lost your booking ID, then please contact on 03123456789 for help.");
    }

    printf("\nPress ENTER to return to menu...");
    wait_for_enter();
    return head;
}
/*******************************************************************************************/


// THIS FUNCTION CHECKS THE AVAILABILITY OF A COURT AT USER'S ENTERED TIMINGS
struct Booking* check_availability(struct Booking* head)
{
    printf("\n\n\n==================================================================\n");
    printf("--------- CHECK A COURT'S AVAILABILITY AT OUR SPORTS CLUB --------\n");
    printf("==================================================================\n\n");
    
    struct Booking record;

    char* courts[] = {"Cricket", "Football", "Basketball", "Tennis", "Badminton", "Boxing", "Hockey", "Volleyball", "Table Tennis"};
    printf("Select the court you want to check:\n");
    print_string_array(courts, 9);
    printf("Enter your choice: ");
    int choice = get_int_input();

    if (choice > 0 && choice <= 9) {
        strcpy(record.court_name, courts[choice - 1]);
    }
    else {
        printf("\n\nPlease select a valid option [1-9] next time. Press ENTER to return to menu..");
        wait_for_enter();
        return head;
    }
    
    printf("\nSelect the day you would like to check for:\n");
    char* days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    print_string_array(days, 7);
    printf("Enter your choice: ");
    int day_choice = get_int_input();

    if (day_choice > 0 && day_choice <= 7) {
        strcpy(record.day, days[day_choice - 1]);
    }
    else {
        printf("\n\nPlease select a valid option [1-7] next time. Press ENTER to return to menu..");
        wait_for_enter();
        return head;
    }

    printf("\nSelect the timings you want to check for:\n");
    char* timings[] = {"Morning", "Afternoon", "Evening", "Night"};
    print_string_array(timings, 4);
    printf("Enter your choice: ");
    int timing_choice = get_int_input();
    
    if (timing_choice > 0 && timing_choice <= 4) {
        strcpy(record.timing, timings[timing_choice - 1]);
    }
    else {
        printf("\n\nPlease select a valid option [1-4] next time. Press ENTER to return to menu..");
        wait_for_enter();
        return head;
    }

    if (!is_available(&record, head)) {
        printf("\n\nSorry, the court is not available at the given timings. Press ENTER to return to menu...");
        wait_for_enter();
        return head;
    }
    
    printf("\n\nThe court is available at the given timings. Do you wish to book the court? [Y/N]: ");
    char wish[20];
    get_string_input(wish, 20);

    if (wish[0] == 'Y' || wish[0] == 'y') {
        printf("\nEnter your full name: ");
        get_string_input(record.name, 50);

        printf("\nEnter your phone number: ");
        get_string_input(record.phone_number, 20);

        head = perform_booking(&record, head);
    }

    return head;
}
/*******************************************************************************************/


// THIS IS AN ADMINISTRATIVE FUNCTION FOR DISPLAYING ALL THE BOOKINGS OF THE CLUB
void view_all_bookings(struct Booking* head)
{
    printf("\n\n\n==================================================================\n");
    printf("-------------- VIEW ALL BOOKINGS AT OUR SPORTS CLUB --------------\n");
    printf("==================================================================\n\n");
    
    char password[] = "839493";
    char pin[20];

    printf("Enter administrative PIN: ");
    get_string_input(pin, 20);

    if (strcmp(password, pin) != 0) {
        printf("\nEntered PIN is incorrect. Press ENTER to return to menu...");
        wait_for_enter();
        return;
    }

    struct Booking* record = head;
    int total_bookings = 0;

    printf("\n------------------------------------------------------------------------------------------------------\n");
    printf("| %-6s | %-30s | %-15s | %-12s | %-10s | %-10s |\n", "ID", "Name", "Contact", "Court", "Day", "Timings");
    printf("------------------------------------------------------------------------------------------------------\n");

    while (record)
    {
        printf("| %-6d | %-30s | %-15s | %-12s | %-10s | %-10s |\n", record->booking_id, record->name, record->phone_number, record->court_name, record->day, record->timing);
        ++total_bookings;
        record = record->next;
    }

    printf("------------------------------------------------------------------------------------------------------\n");

    printf("\nTotal Bookings: %d", total_bookings);
    printf("\nPress ENTER to return to menu...");
    wait_for_enter();
}
/*******************************************************************************************/


// THIS FUNCTION EDITS THE USER BOOKING. IT CHANGES THE COURTS AND THE TIMINGS FOR THE USERS BOOKING.
struct Booking* edit_booking(struct Booking* record, struct Booking* head)
{
    struct Booking temp;
    char* courts[] = {"Cricket", "Football", "Basketball", "Tennis", "Badminton", "Boxing", "Hockey", "Volleyball", "Table Tennis"};
    printf("\nSelect your new court:\n");
    print_string_array(courts, 9);
    printf("Enter your choice: ");
    int choice = get_int_input();

    if (choice > 0 && choice <= 9) {
        strcpy(temp.court_name, courts[choice - 1]);
    }
    else {
        printf("\n\nPlease select a valid option [1-9] next time. Press ENTER to return to menu..");
        wait_for_enter();
        return head;
    }
    
    printf("\nSelect your new booking day:\n");
    char* days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    print_string_array(days, 7);
    printf("Enter your choice: ");
    int day_choice = get_int_input();

    if (day_choice > 0 && day_choice <= 7) {
        strcpy(temp.day, days[day_choice - 1]);
    }
    else {
        printf("\n\nPlease select a valid option [1-7] next time. Press ENTER to return to menu..");
        wait_for_enter();
        return head;
    }

    printf("\nSelect your new booking timings:\n");
    char* timings[] = {"Morning", "Afternoon", "Evening", "Night"};
    print_string_array(timings, 4);
    printf("Enter your choice: ");
    int timing_choice = get_int_input();
    
    if (timing_choice > 0 && timing_choice <= 4) {
        strcpy(temp.timing, timings[timing_choice - 1]);
    }
    else {
        printf("\n\nPlease select a valid option [1-4] next time. Press ENTER to return to menu..");
        wait_for_enter();
        return head;
    }

    if (is_available(&temp, head)) {
        strcpy(record->court_name, temp.court_name);
        strcpy(record->day, temp.day);
        strcpy(record->timing, temp.timing);
        printf("\n\nYour booking has been successfully updated.");
    }
    else {
        printf("\n\nOops! The court you desired is not available at the given timings. Your booking will remain unchanged.");
    }

    return head;
}
/*******************************************************************************************/


// THIS IS A HELPER FUNCTION FOR BOOKING A COURT AS IT SAVES THE USER'S ENTERED DETAILS INTO THE LINKED LIST 
struct Booking* perform_booking(struct Booking* record, struct Booking* head)
{
    struct Booking* node = malloc(sizeof(struct Booking));
    *node = *record;

    int new_id;
    do {
        new_id = (rand() % 9000) + 1000;
    } while (check_id_exists(head, new_id) == 1);
    node->booking_id = new_id;

    node->next = head;
    head = node;

    printf("\n\nCourt booked successfully.");
    printf("\nYour booking ID is %d.", node->booking_id);
    printf("\nPLEASE REMEMBER THIS ID FOR LATER USE");
    printf("\nPress ENTER to return to menu...");
    wait_for_enter();
    return head;
}
/*******************************************************************************************/


// THIS IS A HELPER FUNCTION FOR CHECKING COURT AVAILABILITY
int is_available(struct Booking* record, struct Booking* head)
{
    struct Booking* temp = head;

    while (temp) {
        if ((strcmp(temp->court_name, record->court_name) == 0) && (strcmp(temp->day, record->day) == 0) && (strcmp(temp->timing, record->timing) == 0)) {
            return 0;
        }
        temp = temp->next;
    }

    return 1;
}
/*******************************************************************************************/


// THIS IS A HELPER FUNCTION THAT CHECKS WHETHER A BOOKING ID IS UNIQUE OR NOT
int check_id_exists(struct Booking* head, int id)
{
    struct Booking* temp = head;
    int temp_id;
    
    while (temp) {
        if (temp->booking_id == id) {
            return 1;
        }
        temp = temp->next;
    }
    
    return 0;
}
/*******************************************************************************************/


// THIS IS A HELPER FUNCTION THAT TAKES ONLY AN INTEGER AS INPUT FROM THE USER
int get_int_input()
{
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);
    return atoi(buffer);
}
/*******************************************************************************************/


// THIS IS A HELPER FUNCTION THAT TAKES A STRING AS INPUT FROM THE USER
void get_string_input(char *str, int size)
{
    fgets(str, size, stdin);
    str[strcspn(str, "\n")] = 0;
}
/*******************************************************************************************/


// THIS IS A HELPER FUNCTION TO PRINT AN ARRAY OF STRINGS.
void print_string_array(char* arr[], int n)
{
    for (int i = 0; i < n; ++i) {
        printf("%d. %s\n", i+1, arr[i]);
    }
}
/*******************************************************************************************/


// THIS FUNCTION READS THE DATA FROM THE FILE AND CREATES A LINKED LIST TO HOLD IT
struct Booking* load_from_file(struct Booking* head)
{
    FILE* my_file = fopen("booking.txt", "r");

    if (my_file == NULL) {
        printf("\n\nError: Could not open file. Please try again later...");
        return head;
    }

    struct Booking temp;
    while (fscanf(my_file, "%d | %49[^|] | %19[^|] | %19[^|] | %19[^|] | %14[^\n]", &temp.booking_id, temp.name, temp.phone_number, temp.court_name, temp.day, temp.timing) == 6) {
        struct Booking* node = malloc(sizeof(struct Booking));
        *node = temp;
        node->next = head;
        head = node;
    }

    fclose(my_file);
    return head;
}
/*******************************************************************************************/


// THIS FUNCTION SAVES THE ENTIRE LINKED LIST DATA TO THE FILE
void save_to_file(struct Booking* head)
{
    FILE* my_file = fopen("booking.txt", "w");

    if (my_file == NULL) {
        printf("\n\nError: Could not open file. Please try again later...");
        return;
    }

    struct Booking* temp = head;

    while (temp) {
        fprintf(my_file, "%d | %s | %s | %s | %s | %s\n", temp->booking_id, temp->name, temp->phone_number, temp->court_name, temp->day, temp->timing);
        temp = temp->next;
    }

    fclose(my_file);
}
/*******************************************************************************************/


// THIS FUNCTION CLEANS THE MEMORY WHICH WAS USED BY LINKED LIST TO STORE ALL THE BOOKINGS.
void free_memory(struct Booking* head)
{
    struct Booking* temp;
    while (head)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}
/*******************************************************************************************/


// THIS IS A HELPER FUNCTION TO PAUSE THE SCREEN
void wait_for_enter()
{
    int c;
    while ((c = getchar()) != '\n');
}
/*******************************************************************************************/