#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STAFF 100
#define MAX_CUSTOMERS 100

struct Staff {
  char name[50];
  char post[50];
  int id;
};

struct Customer {
  int id;
  char name[50];
  int room_number;
  char room_category[50];
};

struct Staff staffList[MAX_STAFF];
struct Customer customerList[MAX_CUSTOMERS];

int staffCount = 0;
int customerCount = 0;

void displayMainMenu();
void addStaff();
void searchStaff();
void deleteStaff();
void checkRoomAvailability();
void addCustomer();
void searchCustomer();
void generateBill();
void displayRoomCategories();
void saveDataToFile();
void loadDataFromFile();

int main() {
  loadDataFromFile();

  int choice;

  do {
    displayMainMenu();
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
      addStaff();
      break;
    case 2:
      searchStaff();
      break;
    case 3:
      deleteStaff();
      break;
    case 4:
      addCustomer();
      break;
    case 5:
      searchCustomer();
      break;
    case 6:
      checkRoomAvailability();
      break;
    case 7:
      generateBill();
      break;
    case 8:
      saveDataToFile();
      printf("Exiting...\n");
      break;
    default:
      printf("Invalid choice. Please try again.\n");
    }
  } while (choice != 8);
  return 0;
}

void displayMainMenu() {
  printf("\n===== Hotel Management System =====\n");
  printf("1. Add Staff\n");
  printf("2. Search Staff\n");
  printf("3. Delete Staff\n");
  printf("4. Add Customer\n");
  printf("5. Search Customer\n");
  printf("6. Check Room Availability\n");
  printf("7. Generate Bill\n");
  printf("8. Save & Exit\n");
}

void addStaff() {
  int numStaffs;
  printf("How many staffs to add? ");
  scanf("%d", &numStaffs);
  for (int i = 0; i < numStaffs; i++) {
    if (staffCount >= MAX_STAFF) {
      printf("Cannot add more staff. Staff list is full.\n");
      return;
    }

    struct Staff newStaff;
    int newStaffID;
    printf("Enter staff name: ");
    scanf("%s", newStaff.name);
    printf("Enter staff post: ");
    scanf("%s", newStaff.post);
    printf("Enter staff ID: ");
    scanf("%d", &newStaffID);

    // Checking if staff ID already exists
    for (int j = 0; j < staffCount; j++) {
      if (newStaffID == staffList[j].id) {
        printf(
            "Staff with ID %d already exists. Please choose a different ID.\n",
            newStaffID);
        printf("Enter another ID: ");
        scanf("%d", &newStaffID);
      }
    }

    newStaff.id = newStaffID;
    staffList[staffCount++] = newStaff;
    printf("Staff added successfully.\n");
  }
}

void searchStaff() {
  if (staffCount == 0) {
    printf("No staff records available.\n");
    return;
  }

  int searchID;
  printf("Enter staff ID to search: ");
  scanf("%d", &searchID);

  for (int i = 0; i < staffCount; i++) {
    if (staffList[i].id == searchID) {
      printf("Staff found:\n");
      printf("Name: %s\n", staffList[i].name);
      printf("Post: %s\n", staffList[i].post);
      printf("ID: %d\n", staffList[i].id);
      return;
    }
  }

  printf("Staff with ID %d not found.\n", searchID);
}

void deleteStaff() {
  if (staffCount == 0) {
    printf("No staff records available.\n");
    return;
  }

  int deleteID;
  printf("Enter staff ID to delete: ");
  scanf("%d", &deleteID);

  for (int i = 0; i < staffCount; i++) {
    if (staffList[i].id == deleteID) {
      for (int j = i; j < staffCount - 1; j++) {
        staffList[j] = staffList[j + 1];
      }
      staffCount--;
      printf("Staff with ID %d deleted successfully.\n", deleteID);
      return;
    }
  }

  printf("Staff with ID %d not found.\n", deleteID);
}

void checkRoomAvailability() {
  int roomNumber;
  printf("Enter room number to check availability: ");
  scanf("%d", &roomNumber);
  // Checking if the room is occupied
  for (int i = 0; i < customerCount; i++) {
    if (roomNumber == customerList[i].room_number) {
      printf("Room number %d is occupied by customer %s.\n", roomNumber,
             customerList[i].name);
      return;
    }
  }
  printf("Room number %d is available.\n", roomNumber);
}

void addCustomer() {
  if (customerCount >= MAX_CUSTOMERS) {
    printf("Cannot add more customers. Customer list is full.\n");
    return;
  }
  struct Customer newCustomer;
  int newCustomerID;
  printf("Enter customer ID: ");
  scanf("%d", &newCustomerID);

  for (int i = 0; i < customerCount; i++) {
    if (newCustomerID == customerList[i].id) {
      printf(
          "Customer with ID %d already exists. Please choose a different ID.\n",
          newCustomerID);
      printf("Enter another ID: ");
      scanf("%d", &newCustomerID);
      i = -1;
    }
  }
  newCustomer.id = newCustomerID;

  printf("Enter customer name: ");
  scanf("%s", newCustomer.name);

  printf("Choose room category: \n");
  displayRoomCategories();
  scanf("%s", newCustomer.room_category);

  printf("Enter room number: ");
  scanf("%d", &newCustomer.room_number);

  // Checking if the chosen room number is already occupied
  for (int i = 0; i < customerCount; i++) {
    if (newCustomer.room_number == customerList[i].room_number) {
      printf("Room number %d is already occupied. Please choose a different "
             "room number.\n",
             newCustomer.room_number);
      printf("Enter another room number: ");
      scanf("%d", &newCustomer.room_number);
      i = -1; // Reset loop to check new room number against all occupied rooms
    }
  }

  customerList[customerCount++] = newCustomer;
  printf("Customer added successfully.\n");
}

void searchCustomer() {
  if (customerCount == 0) {
    printf("No customer records available.\n");
    return;
  }

  int searchID;
  printf("Enter customer ID to search: ");
  scanf("%d", &searchID);

  for (int i = 0; i < customerCount; i++) {
    if (customerList[i].id == searchID) {
      printf("Customer found with ID: %d\n", customerList[i].id);
      printf("Name: %s\n", customerList[i].name);
      printf("Room Number: %d\n", customerList[i].room_number);
      return;
    }
  }

  printf("Customer with ID %d not found.\n", searchID);
}

void generateBill() {
  int i, n;
  float price[100], discount;
  float c = 0, totalAmount;
  printf("How many items?");
  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    printf("Enter the price of item %d:", i + 1);
    scanf("%f", &price[i]);
    c = c + price[i];
  }
  printf("Enter the discount amount");
  scanf("%f", &discount);
  printf("Generating bill...\n");
  totalAmount = c - discount;
  printf("Total amount: %f\n", totalAmount);
}

void displayRoomCategories() {
  printf("1. VIP\n");
  printf("2. Single Bed\n");
  printf("3. Double Bed\n");
}

void saveDataToFile() {
  FILE *file = fopen("hotel_data.txt", "w");
  if (file == NULL) {
    printf("Error opening file for writing.\n");
    return;
  }
  fprintf(file, "%d\n", staffCount);
  for (int i = 0; i < staffCount; i++) {
    fprintf(file, "%s %s %d\n", staffList[i].name, staffList[i].post,
            staffList[i].id);
  }
  fprintf(file, "%d\n", customerCount);
  for (int i = 0; i < customerCount; i++) {
    fprintf(file, "%d %s %d %s\n", customerList[i].id, customerList[i].name,
            customerList[i].room_number, customerList[i].room_category);
  }

  fclose(file);
}
void loadDataFromFile() {

  FILE *file = fopen("hotel_data.txt", "r");
  if (file == NULL) {
    printf("No existing data found. Starting with empty records.\n");
    return;
  }
  fscanf(file, "%d", &staffCount);
  for (int i = 0; i < staffCount; i++) {
    fscanf(file, "%s %s %d", staffList[i].name, staffList[i].post,
           &staffList[i].id);
  }
  fscanf(file, "%d", &customerCount);
  for (int i = 0; i < customerCount; i++) {
    fscanf(file, "%d %s %d %s", &customerList[i].id, customerList[i].name,
           &customerList[i].room_number, customerList[i].room_category);
  }

  fclose(file);
}