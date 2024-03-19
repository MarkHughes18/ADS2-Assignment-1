#define _CRT_SECURE_NO_WARNINGS 1
#define bool int
#define Max_Cars 5

/*Libraries*/
#include <stdio.h>
#include <stdlib.h>

//Stucture template for car part of the linked list
struct Car
{
    int regNumber[10];
    char makeAndModel[50];
    char color[15];
    int previousOwners;
    bool status;
    int deposit;
    char mod[50];
    struct Car* next;
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
void leaveProgram(); // exit the program

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
    struct Car showroom[Max_Cars];
    int numCars = 0;
    int choice;
    do{
    printf("\nThis is the showroom menu. Please select one of the following: \n");
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
        addCar(showroom, &numCars);
        break;
    case 2:
        sellCar(showroom, &numCars);
        break;
    case 3:
        reserveCar();
        break;
    case 4:
        viewAllCars(showroom, numCars);
        break;
    case 5:
        viewSpecificCar(showroom, numCars);
        break;
    case 6:
        modify();
        break;
    case 7:
        leaveProgram();
        break;
    default:
        printf("Invalid choice\n");
        break;
    }
    }while(choice !=7);

    
}

/*method to add a car*/
void addCar(struct Car showroom[], int *numCars)
{
    //*check if the showroom is full*//
    if(*numCars >= Max_Cars)
    {
        printf("This showromm is already full. You cannot add any more cars.\n");
        return;
    }

    struct Car newCar;
    printf("Please enter the regestration number of the car: ");
    scanf("%d", &newCar.regNumber);

    for(int i = 0; 0 < *numCars; i++)
    {
        if(strcmp(newCar.regNumber, showroom[i].regNumber) == 0)
        {
            printf("A car with this registration number is already in the showroom.\n");
            return;
        }
    }

    printf("Enter the make and model of the car: ");
    scanf("%s", newCar.makeAndModel);
    printf("Enter the color of the car: ");
    scanf("%s", newCar.color);
    printf("Enter the number of previous owners of the car: ");
    scanf("%d", &newCar.previousOwners);
    printf("Enter if this car has any modifications: ");
    scanf("%d", &newCar.mod);

    if(newCar.previousOwners > 3)
    {
        printf("This car has had too many previous owners.\nIt cannot be added to the showroom.\n");
        return;
    }

    newCar.status = 0;

    showroom[*numCars] = newCar;
    (*numCars)++;

    printf("This car has been successfully add to the showroom.\n");
}

/*method to sell a car*/
void sellCar(struct Car showroom[], int *numCars)
{
    char sellReg[20];
    int foundCar = -1;

    printf("Enter the registration number of the car being sold: ");
    scanf("%s", sellReg);

    for(int i = 0; i < numCars; i++)
    {
        if(strcmp(sellReg, showroom[i].regNumber) == 0)
        {
            foundCar = i;
            break;
        }
    }

    if(foundCar == -1)
    {
        printf("The car with registration number %s is not in the showroom.\n", sellReg);
        return;
    }

    if (showroom[foundCar].status == 0)
    {
        printf("The car with registration number %s is not available for sale at the moment.\n", sellReg);
        return;
    }

    printf("The car with the registration number %s has been sold.\n", sellReg);

    for (int i = foundCar; i < *numCars - i; i++)
    {
        showroom[i] = showroom[i + 1];
    }

    *numCars--;

    printf("the car with this registrationnumber has been removed from the showroom.\n");
}

/*method to reserve a car*/
void reserveCar()
{

}

/*method to view all cars*/
void viewAllCars(struct Car showroom[], int numCars)
{
    int pick;
    printf("Please select one of the following options.\n");
    printf("1. View all cars in the showroom\n");
    printf("2. View all cars available for sale\n");
    printf("3. View all cars of a specific make and model\n");
    printf("4. View all cars of a specific color\n");
    scanf("%d", &pick);

    switch(pick)
    {
        case 1:
        printf("\nAll cars in the showroom");
            for (int i = 0; i < numCars; i++)
            {
                printf("Registration number: %d\n", showroom[i].regNumber);
                printf("Make and Model: %s\n", showroom[i].makeAndModel);
                printf("Color: %s\n", showroom[i].color);
                printf("Previous Owners: %d\n", showroom[i].previousOwners);
                printf("Modifications: %s\n", showroom[i].mod);
                printf("Status: %d\n", showroom[i].status);
            }
        break;
        case 2:
        printf("\nAll cars available for sale");
            for (int i = 0; i < numCars; i++)
            {
                if (showroom[i].status == 1)
                {
                    printf("Registration number: %d\n", showroom[i].regNumber);
                    printf("Make and Model: %s\n", showroom[i].makeAndModel);
                    printf("Color: %s\n", showroom[i].color);
                    printf("Previous Owners: %d\n", showroom[i].previousOwners);
                    printf("Modifications: %s\n", showroom[i].mod);
                    printf("Status: %d\n", showroom[i].status);
                }
            }
        break;
        case 3: 
        printf("\nPlease enter the Make and Model of the car you wish to view: ");
        char makeModel[50];
        scanf("%s", makeModel);
        printf("\nAll cars of the make and model %s", makeModel);
            for (int i = 0; i < numCars; i++)
            {
                if (strcmp(makeModel, showroom[i].makeAndModel) == 0)
                {
                    printf("Registration number: %d\n", showroom[i].regNumber);
                    printf("Make and Model: %s\n", showroom[i].makeAndModel);
                    printf("Color: %s\n", showroom[i].color);
                    printf("Previous Owners: %d\n", showroom[i].previousOwners);
                    printf("Modifications: %s\n", showroom[i].mod);
                    printf("Status: %d\n", showroom[i].status);
                }
            }
        break;
        case 4: 
        printf("\nPlease enter the color of the car you wish to view: ");
        char carColor[15];
        scanf("%s", carColor);
        printf("\nAll cars of color %s", carColor);
            for (int i = 0; i < numCars; i++)
            {
                if (strcmp(carColor, showroom[i].color) == 0)
                {
                    printf("Registration number: %d\n", showroom[i].regNumber);
                    printf("Make and Model: %s\n", showroom[i].makeAndModel);
                    printf("Color: %s\n", showroom[i].color);
                    printf("Previous Owners: %d\n", showroom[i].previousOwners);
                    printf("Modifications: %s\n", showroom[i].mod);
                    printf("Status: %d\n", showroom[i].status);
                }
            }
        break;
        default:
        printf("Incorrect Choice Entered\n");
        break;
    }
}

/*method to view a specific car*/
void viewSpecificCar(struct Car showroom[], int numCars)
{
    char searcgReg[20];
    int foundCar = -1;

    printf("Enter the registration number of the car you wish to view: ");
    scanf("%s", searcgReg);

    for (int i = 0; i < numCars; i++)
    {
        if(strcmp(searcgReg, showroom[i].regNumber) == 0)
        {
            foundCar = i;
            break;
        }
    }

    if (foundCar == -1)
    {
        printf("\nThe car with the registration number %s is not in the showroom.\n", searcgReg);
    }
    else
    {
        printf("Registration number: %d\n", showroom[foundCar].regNumber);
        printf("Make and Model: %s\n", showroom[foundCar].makeAndModel);
        printf("Color: %s\n", showroom[foundCar].color);
        printf("Previous Owners: %d\n", showroom[foundCar].previousOwners);
        printf("Modifications: %s\n", showroom[foundCar].mod);
        printf("Status: %d\n", showroom[foundCar].status);
    }
}

/*method to modify a car*/
void modify()
{

}

void leaveProgram()
{
    printf("You have chosen to leave the showroom.");
    exit(0);
}