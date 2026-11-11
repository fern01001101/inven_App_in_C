// inventory application

/* 
=== Main Menu ===
    1. Scanner / Calculator
    2. Inventory
    3. Exit
    Select transaction: 


=== Scanner / Calculator ===

    Input product codes -> 1) Add & Quantity 2) Void & Quantity 3) Get total & Show Summary 4) Return

    Print receipt


=== Inventory ===
    1. Add product
    2. Search product
    3. View all products
    4. Update product
    5. Delete product
    6. Back to main menu
    Select transaction: 

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct {

    int barcode;
    char name[50];
    float price;
    int quantity;

} Product;

Product products[100];

int productCount = 0;

void clearBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

int findProduct_name(char name[50]) {

    for(int i = 0; i < productCount; i++) {
        if(strcmp(products[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int findProduct_barcode(int barcode) {

    for(int i = 0; i < productCount; i++) {
        if(products[i].barcode == barcode) {
            return i;
        }
    }
    return -1;
}

void inputString(char *str, int size) {
    if(fgets(str, size, stdin) != NULL) {
        str[strcspn(str, "\n")] = '\0';
        int length = strlen(str);
        for(int i = 0; i < length; i++){
            if(str[i] == ' '){
                str[i] = '_';
            }
        }
    }
}

void inputInteger(int *num) {
    while(scanf("%d", num) != 1) {
        printf("Invalid input!\nInput: ");
        clearBuffer();
    }
    clearBuffer();
}

void inputFloat(float *num) {
    while(scanf("%f", num) != 1) {
        printf("Invalid input!\nInput: ");
        clearBuffer();
    }
    clearBuffer();
}

void loadData() {

    FILE *file;

    file = fopen("inventory.txt", "r");

    if(file == NULL) {
        return;
    }

    while(fscanf(file, "%d %50s %f %d", 
            &products[productCount].barcode,
            products[productCount].name,
            &products[productCount].price,
            &products[productCount].quantity) == 4) {

                productCount++;
    }

    fclose(file);
}

void saveData() {

    FILE *file;

    file = fopen("inventory.txt", "w");

    for(int i = 0; i < productCount; i++) {
        fprintf(file, "%d %s %f %d\n", 
                products[i].barcode,
                products[i].name,
                products[i].price,
                products[i].quantity);
    }
    
    fclose(file);

}

void edit_addData(int index) {
    Product editProduct;

    
    printf("Product name: ");
    inputString(editProduct.name, sizeof(editProduct.name));

    while(1){
        printf("Barcode: ");
        inputInteger(&editProduct.barcode);
        if(editProduct.barcode <= 0 || editProduct.barcode > 999999999){
            printf("Invalid input\n");
        }else{
            break;
        }
    }

    while(1){
        printf("Price: ");
        inputFloat(&editProduct.price);
        if(editProduct.price <= 0){
            printf("Invalid input\n");
        }else{
            break;
        }
    }

    while(1){
        printf("Quantity: ");
        inputInteger(&editProduct.quantity);
        if(editProduct.quantity <= 0){
            printf("Invalid input\n");
        }else{
            break;
        }
    }

    products[index] = editProduct;

    saveData();
}

void deleteData() {

    int choice = 0;
    char name[50];
    int barcode = 0;
    int index = 0;
    int sindex = 0;
    bool run = true;

    while(run) {
        printf("1. Search by name\n2. Search by barcode\n3. Back to menu\n");
        do {
            printf("Select transaction: ");
            inputInteger(&choice);
            if(choice != 1 && choice !=2 && choice != 3) {
                printf("Invalid input!\n");
            }
        } while(choice != 1 && choice !=2 && choice != 3);

        switch(choice) {

            case 1: {
                printf("Type in name: ");
                inputString(name, sizeof(name));
                index = findProduct_name(name);
                if(index == -1) {
                    printf("Product does not exist\n");
                } else {
                    sindex = index;
                    for(int i = index; i < (productCount-1); i++) {
                        products[sindex] = products[sindex + 1];
                        sindex += 1;
                    }
                    productCount -= 1;
                    saveData();
                    printf("Item deleted\n");
                }
                break;
            }

            case 2: {
                printf("Type in barcode: ");
                inputInteger(&barcode);
                index = findProduct_barcode(barcode);
                if(index == -1) {
                    printf("Product does not exist\n");
                } else {
                    sindex = index;
                    for(int i = index; i < (productCount-1); i++) {
                        products[sindex] = products[sindex + 1];
                        sindex += 1;
                    }
                    productCount -= 1;
                    saveData();
                    printf("Item deleted\n");
                }
                break;
            }

            case 3:
                run = false;
                break;
        }
    }
}


void addProduct() {

    edit_addData(productCount++);
    printf("Product saved!\n");

}

void searchProduct() {

    int choice = 0;
    char name[50];
    int barcode = 0;
    int index = 0;


    while(1) {
        printf("1. Search by name\n2. Search by barcode\n3. Back to menu\n");
        do {
            printf("Select transaction: ");
            inputInteger(&choice);
            if(choice != 1 && choice !=2 && choice != 3) {
                printf("Invalid input!\n");
            }
        } while(choice != 1 && choice !=2 && choice != 3);

        if(choice == 1) {
            printf("Type in name: ");
            inputString(name, sizeof(name));
            index = findProduct_name(name);
            if(index == -1) {
                printf("Product does not exist\n");
            } else {
                printf("Barcode: %d, Name: %s, Price: %.2f, Quantity: %d\n",
                        products[index].barcode,
                        products[index].name,
                        products[index].price,
                        products[index].quantity);
            }
        } else if(choice == 2) {
            printf("Type in barcode: ");
            inputInteger(&barcode);
            index = findProduct_barcode(barcode);
            if(index == -1) {
                printf("Product does not exist\n");
            } else {
                printf("Barcode: %d, Name: %s, Price: %.2f, Quantity: %d\n",
                        products[index].barcode,
                        products[index].name,
                        products[index].price,
                        products[index].quantity);
            }
        } else if(choice == 3 ) {
            break;
        }
    }

}

void viewAll() {

    for(int i = 0; i < productCount; i++) {
        printf("Barcode: %d, Name: %s, Price: %.2f, Quantity: %d\n",
                products[i].barcode,
                products[i].name,
                products[i].price,
                products[i].quantity);

    }
}

void updateProduct() {
    Product updateProduct;
    int choice = 0;
    char name[50];
    int barcode = 0;
    int index = 0;
    bool run = true;

    while(run) {
        printf("1. Search by name\n2. Search by barcode\n3. Back to menu\n");
        do {
            printf("Select transaction: ");
            inputInteger(&choice);
            if(choice != 1 && choice !=2 && choice != 3) {
                printf("Invalid input!\n");
            }
        } while(choice != 1 && choice !=2 && choice != 3);

        switch(choice) {
            case 1: {
                printf("Type in name: ");
                inputString(name, sizeof(name));
                index = findProduct_name(name);
                if(index == -1) {
                    printf("Product does not exist\n");
                } else {
                    edit_addData(index);
                    printf("Product updated!\n");
                }
                break;
            }

            case 2: {
                printf("Type in barcode: ");
                inputInteger(&barcode);
                index = findProduct_barcode(barcode);
                if(index == -1) {
                    printf("Product does not exist\n");
                } else {
                    edit_addData(index);
                    printf("Product updated!\n");
                }
                break;
            }

            case 3:
            run = false;
            break;
        }
    }
}

void showMenu_Inventory() {
    int choice = 0;
    bool run = true;

    while(run) {
        printf("=== Inventory ===\n");
        printf("1. Add product\n");
        printf("2. Search product\n");
        printf("3. View all products\n");
        printf("4. Update product\n");
        printf("5. Delete product\n");
        printf("6. Back to main menu\n");

        do {
            printf("Select transaction: ");
            inputInteger(&choice);
            if(choice < 1 || choice > 6) {
                printf("Invalid input!\n");
            }
        } while(choice < 1 || choice > 6);

        switch(choice) {
            case 1: addProduct();
            break;
            case 2: searchProduct();
            break;
            case 3: viewAll();
            break;
            case 4: updateProduct();
            break;
            case 5: deleteData();
            break;
            case 6:
            run = false;
            break;
        }
    }
}

Product tempProduct[100];

float scanItem() {

    float total = 0;
    int quantity = 0;
    int barcode = 0;
    int index = 0;

    printf("Scan item/Type barcode: ");
    inputInteger(&barcode);
    index = findProduct_barcode(barcode);
    if(index == -1 || products[index].quantity < 1) {
        printf("Out of stock or product doesn't exist\n");
        return -1;
    }
    while(1) {
        printf("Quantity: ");
        inputInteger(&quantity);
        if(quantity <= 0){
            printf("Invalid input\n");
        }else if(quantity > tempProduct[index].quantity) {
            printf("Insufficient item in stock\n");
        }else{
            break;
        }
    }
    total += (quantity * tempProduct[index].price);
    tempProduct[index].quantity -= quantity;

    return total;  
}

float voidItem() {

    float total = 0;
    int barcode = 0;
    int index = 0;
    int quantity = 0;

    printf("Void item/Type barcode: ");
    inputInteger(&barcode);
    index = findProduct_barcode(barcode);
    if(index == -1){
        printf("Invalid input or product doesn't exist\n");
        return -1;
    }
    if(tempProduct[index].quantity == products[index].quantity){
        printf("Item not scanned\n");
        return -1;
    }

    while(1) {
        printf("Quantity: ");
        inputInteger(&quantity);
        if(quantity <= 0){
            printf("Invalid input\n");
        }else if((quantity + tempProduct[index].quantity) > products[index].quantity) {
            printf("Void quantity exceeded\n");
        }else{
            break;
        }
    }

    total += (quantity * tempProduct[index].price);
    tempProduct[index].quantity += quantity;
    return total;
}

void showMenu_Scanner() {

    for(int i = 0; i < productCount; i++) {
        tempProduct[i] = products[i];
    }

    int choice = 0;
    float total = 0;
    int result = 0;
    bool run = true;

    printf("=== Scanner Menu ===\n");

    while(run) {
        printf("1. Scan item\n2. Void item\n3. Complete transaction\n4. Back\nSelect transaction: ");
        inputInteger(&choice);

        switch(choice) {
            case 1:
            result = scanItem();
            if(result == -1) {
                //do nothing
            }else {
                total += result;
            }
            break;

            case 2:
            if(total == 0){
                printf("No item to void\n");
            }else{
                result = voidItem();
                if(result == -1) {
                    //do nothing
                } else{
                    total -= result;
                }
            }
            break;

            case 3:
            if(total > 0) {
                printf("Transaction complete. Please pay %.2f pesos\n", total);
                printf("=== Receipt ===\n");
                for(int i = 0; i < productCount; i++){
                    if(products[i].quantity != tempProduct[i].quantity){
                        printf("Item: %s Price: %.2f Quantity: %d Subtotal: %.2f\n",
                            tempProduct[i].name,
                            tempProduct[i].price,
                            (products[i].quantity-tempProduct[i].quantity),
                            (tempProduct[i].price*((products[i].quantity-tempProduct[i].quantity))));
                    }
                }
                printf("Total: %.2f\n", total);
            }else{
                printf("No transaction\n");
            }
            run = false;
            break;

            case 4:
            run = false;
            break;

            default:
            printf("Invalid input\n");
        }
    }

    if(choice == 3) {
        for(int i = 0; i < productCount; i++) {
            products[i] = tempProduct[i];
        }
        saveData();
    }
}


int main() {
    loadData();
    bool run = true;
    int choice = 0;

    while(run) {
        printf("=== Main Menu ===\n");
        printf("1. Item Scanner / Calculator\n2. Inventory\n3. Exit\nSelect transaction: ");
        inputInteger(&choice);

        switch(choice) {
            case 1:
            showMenu_Scanner();
            break;
            case 2:
            showMenu_Inventory();
            break;
            case 3:
            run = false;
            printf("Exiting program..\n");
            break;
            default:
            printf("Invalid input!\n");
        }
    }

    return 0;
}