#include <iostream>  
#include <list>  
#include <queue>
#include <unistd.h> 
#include "product.h"
#include "processScheduler.h"
#include "threadManager.h"

using namespace std;

void makeOrder(int option){
    // Create products based on the order
    list<Product> order;
    switch (option) {
        case 1:
            order = {Product("Croissant",20), Product("Cinnamon roll",14), Product("Tea",5)};
            break;
        case 2:
            order = {Product("Cheese bread",17), Product("Chocolate brownie",34), Product("Juice",7)};
            break;            
        case 3:
            order = {Product("Baguette",11), Product("Multigrain bread",23), Product("Sourdough loaf",10), Product("Juice",7)};
            break;  
        case 4:
            order = {Product("Bagel",36), Product("Muffin",15), Product("Napoleons",4), Product("Coffee",9)};
            break;   
    }

    // Create order
    cout << "\nCREATE PROCESSES:\n\n";
    ProcessScheduler scheduler;
    size_t index = 1;
    for (Product producto : order){
        Process pt(index, producto.getProductName(),producto.getReadinessTime());
        scheduler.addProcess(pt);
        index++;
    }

    //Show time slice
    cout << "\nTIME SLICE: " << scheduler.getTimeSlice() << " seconds \n";

    // Run Process Scheduler (PS)
    cout << "\nPROCESS SCHEDULER:\n\n";
    scheduler.runScheduler();

    //End PS
    cout << "\nTHE ORDER HAS BEEN COMPLETED.\n";
}

void stockUp(){

  // Create a list of ingredients
    vector<string> truck = {"flour", "sugar", "yeast","butter", "eggs", "vanilla","chocolate chips", 
                            "brown sugar", "nuts","milk", "cocoa powder", "baking powder"};

    cout << "\nInventory of ingredients requiring restocking:\n";
    for (size_t i = 0; i < truck.size(); ++i) {
        cout << truck[i];
        if (i != truck.size() - 1) {
            cout << ", ";
        } else {
            cout << ".\n\n";
        }
    }
    cout<<endl;

    // Create ThreadManager Object
    cout << "-------------------START THE STORAGE OF PRODUCTS-------------------\n\n";
    ThreadManager thM;
    
    // Create threads and pass the truck vector
    for (int i = 0; i < 3; ++i) {
        thM.createThread(truck);
    }

    // Start the scheduler
    thM.startScheduler();
     
    // Terminate threads
    thM.terminateThreads();

    cout << "\n\n-------------------THE PRODUCTS HAVE BEEN STORED.-------------------\n\n";
}

void showLogo(){

     string logo = R"(
##################################################################################
  ____            _                              ____            _                
 |  _ \          | |                            |  _ \          | |               
 | |_) |   __ _  | | __   ___   _ __   _   _    | |_) |  _   _  | |_    ___   ___ 
 |  _ <   / _` | | |/ /  / _ \ | '__| | | | |   |  _ <  | | | | | __|  / _ \ / __|
 | |_) | | (_| | |   <  |  __/ | |    | |_| |   | |_) | | |_| | | |_  |  __/ \__ \
 |____/   \__,_| |_|\_\  \___| |_|     \__, |   |____/   \__, |  \__|  \___| |___/
                                        __/ |             __/ |                   
                                       |___/             |___/      
##################################################################################
    )";
        
    cout << logo << "\n";
}

void orderMenu(){
    int choice;

    while (true) {
        cout << "\n";
        cout << " *----------------------------------------------------------------------------------*\n";
        cout << " |                                      MENU                                        |\n";
        cout << " *----------------------------------------------------------------------------------*\n";
        cout << " |         #1: MORNING BLISS COMBO         |        #2: SAVORY DELIGHT COMBO        |\n"; 
        cout << " |             - Croissant                 |            - Cheese bread              |\n"; 
        cout << " |             - Cinnamon roll             |            - Chocolate brownie         |\n"; 
        cout << " |             - Tea                       |            - Juice                     |\n"; 
        cout << " *-----------------------------------------|----------------------------------------*\n";
        cout << " |         #3: ARTISAN BREAD COMBO         |       #4: BRUNCH BONANZA COMBO         |\n"; 
        cout << " |             - Baguette                  |           - Bagel                      |\n"; 
        cout << " |             - Multigrain bread          |           - Muffin                     |\n"; 
        cout << " |             - Sourdough loaf            |           - Napoleons                  |\n"; 
        cout << " |             - Juice                     |           - Coffee                     |\n"; 
        cout << " *----------------------------------------------------------------------------------*\n";
        cout << " *                                    #5: EXIT                                      *\n";
        cout << " *----------------------------------------------------------------------------------*\n";
        cout << "\nENTER YOUR CHOICE (1-5): ";
        cin >> choice;

        switch (choice) {
            case 1:
                makeOrder(choice);
                break;
            case 2:
                makeOrder(choice);
                break;            
            case 3:
                makeOrder(choice);
                break;  
            case 4:
                makeOrder(choice);
                break;   
            case 5:
                return;     
            default:
                cout << "\nInvalid choice. Please try again.\n\n";
                cin.clear();             
                cin.ignore(10000, '\n'); 
        }
    }
}

// Run program
int main()
{
    // Display Bakery's Logo
    showLogo();

    // Display menu
    int choice;
    while (true) {
        cout << "PLEASE SELECT AN OPTION:\n";
        cout << "1. MAKE AN ORDER\n";
        cout << "2. RESTOCK INGREDIENTS\n";
        cout << "2. EXIT\n\n";
        cout << "ENTER YOUR CHOICE (1-3): ";
        cin >> choice;

        switch (choice) {
            case 1:
                orderMenu();
                break;
            case 2:
                stockUp();
                break;
            case 3:
                stockUp();
                return 0;
            default:
                cout << "\nInvalid choice. Please try again.\n\n";
                cin.clear();             
                cin.ignore(10000, '\n'); 
                break;
        }
    }
}
