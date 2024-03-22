#define _CRT_SECURE_NO_WARNINGS 1
#define bool int
#define Max_Cars 5

/*Libraries*/
#include <stdio.h>
#include <stdlib.h>

//Stucture to store all information abou the car//
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

/*function for the menu for the showroom*/
void menu()
{
    //variables
    struct Car showroom[Max_Cars];
    int numCars = 0;
    int choice;
    //menu
    /*the do while loop around the menu will keep the user in a loop, always returning to the main 
    menu until the enter key 7 to exit the program*/
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
        reserveCar(showroom, numCars);
        break;
    case 4:
        viewAllCars(showroom, numCars);
        break;
    case 5:
        viewSpecificCar(showroom, numCars);
        break;
    case 6:
        modify(showroom, numCars);
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

/*function to add a car to the showroom*/
void addCar(struct Car showroom[], int *numCars)
{
    /*check if the showroom is full*/
    if(*numCars >= Max_Cars)
    {
        printf("This showromm is already full. You cannot add any more cars.\n");
        return;
    }

    /*adding variables to the new car*/
    struct Car newCar;
    printf("Please enter the regestration number of the car: ");
    scanf("%d", &newCar.regNumber);

    //check to see if the car is already in the showroom/ duplicate registration numbers//
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

    //check to see if the car has had too many previous owners//
    if(newCar.previousOwners > 3)
    {
        printf("This car has had too many previous owners.\nIt cannot be added to the showroom.\n");
        return;
    }

    //mark the car as available for sale//
    newCar.status = 0;

    //add the new car to the showroom//
    showroom[*numCars] = newCar;
    (*numCars)++;

    printf("This car has been successfully add to the showroom.\n");
}

/*function to sell a car in the showroom*/
void sellCar(struct Car showroom[], int *numCars)
{
    char sellReg[20];
    int foundCar = -1;

    //input the reg number of the car that will be sold//
    printf("Enter the registration number of the car being sold: ");
    scanf("%s", sellReg);

    //search the showroom for the car with the reg number entered//
    for(int i = 0; i < numCars; i++)
    {
        if(strcmp(sellReg, showroom[i].regNumber) == 0)
        {
            foundCar = i;
            break;
        }
    }

    //check if the car was found//
    if(foundCar == -1)
    {
        printf("The car with registration number %s is not in the showroom.\n", sellReg);
        return;
    }

    //check if the car has been reserved//
    if (showroom[foundCar].status == 0)
    {
        printf("The car with registration number %s is not available for sale at the moment.\n", sellReg);
        return;
    }

    //sell the car and remove it from the showroom//
    printf("The car with the registration number %s has been sold.\n", sellReg);

    //move the remaining cars in the showroom up one place to fill the gap//
    for (int i = foundCar; i < *numCars - i; i++)
    {
        showroom[i] = showroom[i + 1];
    }

    //lessen the number of cars in the showroom//
    *numCars--;

    //print that the car has been sold
    printf("The car with this registrationnumber has been sold and removed from the showroom.\n");
}

/*function to reserve and unreserve a car*/
void reserveCar(struct Car showroom[], int numCars)
{
    int select;
    //menu for the user to reserver or unresrves a car//
    printf("\nPlease select one of the following: !\n");
    orintf("1. Reserve a car\n");
    printf("2. Unreserve a car\n");
    printf("Enter your choice: ");
    scanf("%d", &select);

    switch(select)
    {
        case 1: 
        {
            //reserving a car//
            char resReg[20];
            int foundCar = 0;

            //asks the user to input the reg number of the car they would like to reserve//
            printf("Enter the registration number of the car you would like to reserve: ");
            scanf("%s", resReg);

            //search for the car with the reg number entered//
            for (int i = 0; i < numCars; i++)
            {
                if(strcmp(resReg, showroom[i].regNumber) == 0)
                {
                    foundCar = 1;
                    break;
                }
            }

            //check if the car was found in the showroom//
            if (!foundCar)
            {
                printf("The car with the registration number %s is not in the showroom.\n", resReg);
                return;
            }
            //check if it is already reserved//
            else if (showroom[foundCar].status == 1)
            {
                printf("The car wiht registration number %s is already reserved.\n");
                return;
            }
            else
            {
                //reserve the acr//
                showroom[foundCar].status = 1;
                printf("The car with the registration number %s has been reserved for you.\n");
            
            //taking payment for the deposit//
            int deposit;
                do 
                {
                //asks the user to input the deposit amount//
                printf("Please enter a deposit amount for the reservation: ");
                scanf("%d", &deposit);
                    //check if the deposit fits in the parameters//
                    if (deposit < 250 || deposit > 1000)
                    {
                    printf("The deposit amount must be between €250 and €1000>\n");
                    }
                }while (deposit > 250 || deposit < 1000);
            //print that the deposit was paid successfully//
            printf("Deposit of amount %d was paid successfully,\n", deposit);
            }
            break;
        }

        //unreserving a car//
        case 2:
        {
            char unResReg[20];
            int foundCar = 0;

            //asks the user to input the reg number of the car they would like to unreserve//
            printf("Enter the registration number of the car you would like to unreserve: ");
            scanf("%s", unResReg);

                //search for the car with the reg number entered//
                for (int i = 0; i < numCars; i++)
                {
                    if (strcmp(unResReg, showroom[i].regNumber) ==0)
                    {
                        foundCar = 1;
                        break;
                    }
                }

                //check if the car with reg number entered was found//
                if (!foundCar)
                {
                    printf("The car with the registration number %s is not in the showroom.\n", unResReg);
                    return;
                }
                //check if the car was already unreserved//
                else if (!showroom[foundCar].status)
                {
                    printf("The car with the registration number %s was not reserved.\n", unResReg);
                    return;
                }
                //unreserve the car//
                else
                {
                    showroom[foundCar].status = 0;
                    printf("The car with the registration number %s has been unreserved.\n", unResReg);
                }
            break;
        }
        //default print incorrect choice//
        default:
        printf("Incorrect choice entered.\n");
        break;
    }
    
}


/*function to view all cars*/
void viewAllCars(struct Car showroom[], int numCars)
{
    int pick;
    //menu for the user//
    printf("Please select one of the following options.\n");
    printf("1. View all cars in the showroom\n");
    printf("2. View all cars available for sale\n");
    printf("3. View all cars of a specific make and model\n");
    printf("4. View all cars of a specific color\n");
    scanf("%d", &pick);

    switch(pick)
    {
        //to view all cars in the showroom//
        case 1:
        printf("\nAll cars in the showroom");
        //prints all information about all cars in the showroom//
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
        //to view all cars available for sale//
        case 2:
        printf("\nAll cars available for sale");
        //prints all information about all cars available for sale//
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
        //to view all cars of specific make and model//
        case 3: 
        //asks user to inout the make and model of the car they wish to see//
        printf("\nPlease enter the Make and Model of the car you wish to view: ");
        char makeModel[50];
        scanf("%s", makeModel);
        //displays all information about cars with such make and model//
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
        //to view all cars of a specific color in the showroom//
        case 4: 
        //asks user to input the color of the car they wish to see//
        printf("\nPlease enter the color of the car you wish to view: ");
        char carColor[15];
        scanf("%s", carColor);
        //displays all information about cars with such color//
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
        //otherwise default print incorrect choice//
        default:
        printf("Incorrect Choice Entered\n");
        break;
    }
}

/*function to view a specific car*/
void viewSpecificCar(struct Car showroom[], int numCars)
{
    char searcgReg[20];
    int foundCar = -1;

    //asks the user to input the reg of the specific car they would like to view//
    printf("Enter the registration number of the car you wish to view: ");
    scanf("%s", searcgReg);

    //search for the car with the reg number entered//
    for (int i = 0; i < numCars; i++)
    {
        if(strcmp(searcgReg, showroom[i].regNumber) == 0)
        {
            foundCar = i;
            break;
        }
    }

    //check if the car was found in the showroom//
    if (foundCar == -1)
    {
        printf("\nThe car with the registration number %s is not in the showroom.\n", searcgReg);
    }
    else
    {
        //displayy all information if the car with reg entered is found//
        printf("Registration number: %d\n", showroom[foundCar].regNumber);
        printf("Make and Model: %s\n", showroom[foundCar].makeAndModel);
        printf("Color: %s\n", showroom[foundCar].color);
        printf("Previous Owners: %d\n", showroom[foundCar].previousOwners);
        printf("Modifications: %s\n", showroom[foundCar].mod);
        printf("Status: %d\n", showroom[foundCar].status);
    }
}

/*function to modify a car*/
void modify(struct Car showroom[], int numCars)
{
    char modReg[20];
    int foundCar = -1;

    //asks the user to input the reg number of the car they wish to modify//
    printf("Enter the registration number of the car you wish to modify: ");
    scanf("%s", modReg);

    //search for the car with the reg number entered//
    for (int i = 0; i < numCars; i++)
    {
        if (strcmp(modReg, showroom[i].regNumber) == 0)
        {
            foundCar = i; 
            break;
        }
    }

    //check if the car was found in the showroom//
    if (foundCar == -1)
    {
        printf("The car with the registration number %s is not in the shpwroom.\n", modReg);
        return;
    }
    //check if the car is reserved//
    else if (showroom[foundCar].status == 1)
    {
        printf("The car with the registration number %s is reserved and cannot be modified.\n", modReg);
        return;
    }
    //if the car is not reserved, the user can modify the car//
    else
    {
        //menu for the user to select what they would like to modify//
        printf("\nPlease select one of the following options to modify: \n");
        printf("1. Change the color of the car\n");
        printf("2. Change the wheels of the car\n");
        printf("3. Add a spoiler to the car\n");
        printf("Enter your choice: ");
        int decide;
        scanf("%d", &decide);

        switch (decide)
        {
            //changing the color of the car//
            case 1: 
            {   
                //asks the user to input the new color of the car//
                printf("Enter the new color of the car: ");
                scanf("%s", showroom[foundCar].color);
                printf("The color of the car with registration number %s has been changed to %s.\n", modReg, showroom[foundCar].color);
                break;
            }
            //changing the wheels of the car//
            case 2:
            {
                //asks the user to input the new wheels of the car//
                printf("Enter the new wheels of the car: ");
                scnaf("%s", showroom[foundCar].mod);
                printf("The wheels of the car with registration number %s have been changed to %s.\n", modReg, showroom[foundCar].mod);
                break;
            }
            case 3: 
            {
                //adds a spoiler to the car//
                printf("A spoiler has been added to the car with registration number %s.\n", modReg);
                break;
            }
            //default print incorrect choice//
            default:
            printf("Incorrect choice entered.\n");
            break;
        } 
    }
}
//function to exit the program//
void leaveProgram()
{
    //prints that the user has chosen to leave the showroom//
    printf("You have chosen to leave the showroom.");
    exit(0);
}