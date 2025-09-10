#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Product {
    int id;
    char name[20];
    float price;
    int quantity;
};

struct Product inventory[4] = {
    {1, "shampoo", 30.00, 100},
    {2, "soap", 20.00, 100},
    {3, "comb", 15.00, 200},
    {4, "brush", 10.00, 200}
};

struct Product cart[4];

struct Product getProductDetail(int id);
void showMenu();
void Checkout(int count);
void showInventory();
void showCart(int count);
int UpdateQuantity(int id, int qty);

int main() {
    int option, id, qty, count = 0;

    while (1) {
        showMenu();

        scanf("%d", &option);

        switch (option) {
            case 1: 
                while (1) {
                    showInventory(); 

                    printf("Please enter product ID: ");
                    scanf("%d", &id);

                    struct Product p = getProductDetail(id);

                    if (p.id == 0) {
                        printf("Invalid product ID. Please enter a valid ID.\n");
                        continue;
                    }

                    printf("%d - %s - %.2f - %d\n", p.id, p.name, p.price, p.quantity);
                    printf("Please enter product quantity: ");
                    scanf("%d", &qty);

                   
                    if (UpdateQuantity(id, qty) == -1) {
                        printf("Invalid quantity. Please try again.\n");
                        continue;
                    }

                   
                    cart[count].id = p.id;
                    strcpy(cart[count].name, p.name);
                    cart[count].price = p.price;
                    cart[count].quantity = qty;

                    printf("%d - %s - %.2f - %d added to cart.\n", cart[count].id,
                           cart[count].name, cart[count].price, cart[count].quantity);

                    count++;

                    printf("Do you want to add more product? (1: Yes, 0: No): ");
                    scanf("%d", &option);

                    if (option == 1) {
                        continue;
                    } else {
                        break;
                    }
                }
                break;

            case 2:
                showCart(count);

                printf("(1) Go to main menu\n(0) Checkout\n");
                scanf("%d", &option);

                if (option == 0) {
                    Checkout(count);
                    printf("Thank you for visiting.\n");
                    return 0;
                }
                break;

            case 3: 
                Checkout(count);
                printf("Thank you for visiting.\n");
                return 0;

            case 4: // Exit
                return 0;

            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    }
}

struct Product getProductDetail(int id) {
    for (int i = 0; i < 4; i++) {
        if (inventory[i].id == id) {
            return inventory[i];
        }
    }

    struct Product p = {0, "", 0.0, 0};
    return p;
}

void showInventory() {
    printf("\n-------------------- INVENTORY --------------------\n");
    printf("PRODUCT ID\tPRODUCT NAME\tUNIT PRICE\tQUANTITY\n");

    for (int i = 0; i < 4; i++) {
        printf("\t%d\t\t%s\t\t%.2f\t\t%d\n",
               inventory[i].id, inventory[i].name, inventory[i].price, inventory[i].quantity);
    }
}

void showMenu() {
    printf("\nPlease select your option:\n");
    printf("1. Purchase Product\n");
    printf("2. Show cart\n");
    printf("3. Checkout\n");
    printf("4. Exit\n");
}

void showCart(int count) {
    printf("\n------------------------ CART -----------------------------\n");
    printf("PRODUCT ID\tPRODUCT NAME\tUNIT PRICE\tQUANTITY\n");

    for (int i = 0; i < count; i++) {
        printf("\t%d\t\t%s\t\t%.2f\t\t%d\n",
               cart[i].id, cart[i].name, cart[i].price, cart[i].quantity);
    }
}

void Checkout(int count) {
    float SubTotalPrice = 0.0;

    printf("\n------------------------ CHECKOUT -----------------------------\n");
    printf("PRODUCT ID\tPRODUCT NAME\tUNIT PRICE\tQUANTITY\tTOTAL AMOUNT\n");

    for (int i = 0; i < count; i++) {
        float totalAmount = cart[i].price * cart[i].quantity;
        printf("\t%d\t\t%s\t\t%.2f\t\t%d\t\t%.2f\n",
               cart[i].id, cart[i].name, cart[i].price, cart[i].quantity, totalAmount);
        SubTotalPrice += totalAmount;
    }

    printf("--------------------------------------------------------------\n");
    printf("Subtotal amount: %.2f\n", SubTotalPrice);
    printf("--------------------------------------------------------------\n");
}

int UpdateQuantity(int id, int qty) {
    for (int i = 0; i < 4; i++) {
        if (inventory[i].id == id) {
           
            if (inventory[i].quantity < qty) {
                printf("Not enough stock available.\n");
                return -1; 
            }
            inventory[i].quantity -= qty;
            return inventory[i].quantity;
        }
    }
    return -1;
}
