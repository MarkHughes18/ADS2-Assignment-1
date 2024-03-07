#define _CRT_SECURE_NO_WARNINGS 1
#define bool int

/*Libraries*/
#include <stdio.h>
#include <stdlib.h>

//Stucture template for car part of the linked list
struct Car
{
    int regNumber;
    char makeAndModel;
    char color;
    int previousOwners;
    bool status;
    int deposit;
};

//Stucture template for one node
struct LinearNode
{
    struct Car *element;
    struct LinearNode *next;
};

// Function prototypes
void addCar(); //add a new car to the showroom
void sellCar();//remove a car from the showroom
void reserveCar();//reserve/unreserve a car from the showroom
void viewAllCars();//view all care in the showroom
void viewSpecificCar();//view a specific car in the showroom
void menu();//menu for the user
void modify();//modify a car in the showroom

// Global Variables
struct LinearNode *front = NULL; //front of the list

struct LinearNode *last = NULL; //pointer to last node in the list



/*main method*/
int main()
{
    menu();

    return 0;
}

/*method for menu*/
void menu()
{
    int choice;
    printf("1. Add a car\n");
    printf("2. Sell a car\n");
    printf("3. Reserve a car\n");
    printf("4. View all cars\n");
    printf("5. View a specific car\n");
    printf("6. Modify a car\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        addCar();
        break;
    case 2:
        sellCar();
        break;
    case 3:
        reserveCar();
        break;
    case 4:
        viewAllCars();
        break;
    case 5:
        viewSpecificCar();
        break;
    case 6:
        modify();
        break;
    case 7:
        exit(0);
        break;
    default:
        printf("Invalid choice\n");
        break;
    }

    return 0;
}

/*method to add a car*/
void addCar()
{

}

/*method to sell a car*/
void sellCar()
{

}

/*method to reserve a car*/
void reserveCar()
{

}

/*method to view all cars*/
void viewAllCars()
{

}

/*method to view a specific car*/
void viewSpecificCar()
{

}

/*method to modify a car*/
void modify()
{

}