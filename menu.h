#include <stdio.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#define MAX_BIKES 10

struct Bike {
    int id;
    char brand[20];
    char model[20];
    float price;
    int rented;
};

struct Rental {
    int bikeId;
    char renterName[50];
    time_t startTime;
    time_t endTime;
};

struct Bike bikes[MAX_BIKES];
struct Rental rentals[MAX_BIKES];
int numBikes = 0;
int numRentals = 0;

void addBike();
void rentBike();
void returnBike();
void displayBikes();
void saveBikeToFile(struct Bike bike);

void addBike() {
    if (numBikes == MAX_BIKES) {
        printf("Maximum number of bikes reached.\n");
        getch();// Holding screen
        mainMenu();// Recursively call the main menu
        return;
    }

    struct Bike newBike;

    printf("Enter Bike ID: ");
    scanf("%d", &newBike.id);

    printf("Enter Brand: ");
    scanf("%s", newBike.brand);

    printf("Enter Model: ");
    scanf("%s", newBike.model);

    printf("Enter Price per Hour: ");
    scanf("%f", &newBike.price);

    printf("Bike added successfully.\n");

    newBike.rented = 0;

    bikes[numBikes] = newBike;
    numBikes++;

    // Save bike information to file
    saveBikeToFile(newBike);

    getch();

    mainMenu();
}

void saveBikeToFile(struct Bike bike) {
    FILE *file = fopen("bikes.txt", "a");

    if (file != NULL) {
        fprintf(file, "%d %s %s %.2f\n", bike.id, bike.brand, bike.model, bike.price);

        fclose(file);
        getch();
        mainMenu();
    } else {
        printf("Error: Unable to open file for writing.\n");
        getch();
        mainMenu();
    }
}



void rentBike() {
    int bikeId;
    char renterName[50];

    printf("Enter Bike ID: ");
    scanf("%d", &bikeId);

    int bikeIndex = -1;

    for (int i = 0; i < numBikes; i++) {
        if (bikes[i].id == bikeId) {
            bikeIndex = i;
            break;
        }
    }

    if (bikeIndex == -1) {
        printf("Bike not found.\n");
        getch();
        mainMenu();
        return;
    }

    if (bikes[bikeIndex].rented) {
        printf("Bike is already rented.\n");
        getch();
        mainMenu();
        return;
    }

    printf("Enter Renter Name: ");
    scanf("%s", renterName);

    struct Rental newRental;
    newRental.bikeId = bikeId;
    strcpy(newRental.renterName, renterName);

    time(&newRental.startTime); // Get the current time as the start time

    rentals[numRentals] = newRental;
    numRentals++;

    bikes[bikeIndex].rented = 1;

    printf("Bike rented successfully.\n");
    // Recursively call the main menu
    getch();
    mainMenu();
}

void returnBike() {
    int bikeId;

    printf("Enter Bike ID: ");
    scanf("%d", &bikeId);

    int bikeIndex = -1;

    for (int i = 0; i < numBikes; i++) {
        if (bikes[i].id == bikeId) {
            bikeIndex = i;
            break;
        }
    }

    if (bikeIndex == -1) {
        printf("Bike not found.\n");
        getch();
        mainMenu();
        return;
    }

    if (!bikes[bikeIndex].rented) {
        printf("Bike is not rented.\n");
        getch();
        mainMenu();
        return;
    }

    for (int i = 0; i < numRentals; i++) {
        if (rentals[i].bikeId == bikeId) {
            time_t currentTime;
            time(&currentTime); // Get the current time as the end time

            double rentingTime = difftime(currentTime, rentals[i].startTime);
            double rentingHours = rentingTime / 3600.0;
            double rentalCost = bikes[bikeIndex].price * rentingHours;

            printf("Bike returned by %s\n", rentals[i].renterName);
            printf("Renting time: %.2f hours\n", rentingHours);
            printf("Rental cost: $%.2f\n", rentalCost);

            for (int j = i; j < numRentals - 1; j++) {
                rentals[j] = rentals[j + 1];
            }

            numRentals--;
            bikes[bikeIndex].rented = 0;
            return;
        }
    }

    printf("Error: Rental record not found.\n");
    printf("\n\n\n\t\t\t\tPress any key to continue...");
    getch();

    // Recursively call the main menu
    mainMenu();
}

void displayBikes() {
    FILE *file = fopen("bikes.txt", "r");

    if (file != NULL) {
        struct Bike bike;

        while (fscanf(file, "%d %s %s %f\n", &bike.id, bike.brand, bike.model, &bike.price) == 4) {
            printf("Bike ID: %d\n", bike.id);
            printf("Brand: %s\n", bike.brand);
            printf("Model: %s\n", bike.model);
            printf("Price per Hour: %.2f\n", bike.price);
            printf("------------------------------\n");
        }

        fclose(file);
    } else {
        printf("Error: Unable to open file for reading.\n");
    }
    printf("\n\n\n\t\t\t\tPress any key to continue...");
    getch();
    // Recursively call the main menu
    mainMenu();
}

void mainMenu() {
    int choice;
    system("cls");
    printf("\t===============================================\n");
    printf("\t\t ****** BIKE RENTAL SYSTEM ****** \t\t\n");
    printf("\t===============================================\n");
    printf("\t\t MAIN MENU: \t\t\t\n");
    printf("\t===============================================\n");
    printf("\t\t 1. Add Bike \t\t\n");
    printf("\t===============================================\n");
    printf("\t\t 2. Rent Bike \t\t\n");
    printf("\t===============================================\n");
    printf("\t\t 3. Return Bike \t\t\n");
    printf("\t===============================================\n");
    printf("\t\t 4. Display Available Bikes \t\t\n");
    printf("\t===============================================\n");
    printf("\t\t 5. Exit \t\t\n");
    printf("\t===============================================\n");
    printf("\t\t Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            addBike();
            break;
        case 2:
            rentBike();
            break;
        case 3:
            returnBike();
            break;
        case 4:
            displayBikes();
            break;
        case 5:
            printf("Thank you for using the bike rental system.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");

            getch();// Holding screen
            mainMenu();// Recursively call the main menu
            system("cls");
    }
}

