#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int id;
    char title[50];
    char author[50];
    int quantity;
};

void addBook() {
    struct Book b;
    FILE *fp = fopen("library.txt", "ab");

    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Book ID: ");
    scanf("%d", &b.id);

    printf("Enter Book Title: ");
    scanf("%s", b.title);

    printf("Enter Book Author: ");
    scanf("%s", b.author);

    printf("Enter Quantity: ");
    scanf("%d", &b.quantity);

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);

    printf("\nBook added successfully!\n");
}

void displayBooks() {
    struct Book b;
    FILE *fp = fopen("library.txt", "rb");

    if (!fp) {
        printf("\nNo books found!\n");
        return;
    }

    printf("\n--- Library Books List ---\n");

    while (fread(&b, sizeof(b), 1, fp)) {
        printf("ID: %d | Title: %s | Author: %s | Quantity: %d\n",
               b.id, b.title, b.author, b.quantity);
    }

    fclose(fp);
}

void searchBook() {
    int id, found = 0;
    struct Book b;
    FILE *fp = fopen("library.txt", "rb");

    if (!fp) {
        printf("\nNo books found!\n");
        return;
    }

    printf("\nEnter Book ID to search: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.id == id) {
            printf("\n--- Book Found ---\n");
            printf("ID: %d\nTitle: %s\nAuthor: %s\nQuantity: %d\n",
                   b.id, b.title, b.author, b.quantity);

            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nBook not found!\n");

    fclose(fp);
}

void updateBook() {
    int id, found = 0;
    struct Book b;
    FILE *fp = fopen("library.txt", "rb+");

    if (!fp) {
        printf("\nNo books found!\n");
        return;
    }

    printf("\nEnter Book ID to update quantity: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.id == id) {
            printf("\nEnter new quantity: ");
            scanf("%d", &b.quantity);

            fseek(fp, -sizeof(b), SEEK_CUR);
            fwrite(&b, sizeof(b), 1, fp);

            printf("\nBook quantity updated!\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nBook not found!\n");

    fclose(fp);
}

void deleteBook() {
    int id, found = 0;
    struct Book b;

    FILE *fp = fopen("library.txt", "rb");
    FILE *temp = fopen("temp.txt", "wb");

    if (!fp) {
        printf("\nNo books found!\n");
        return;
    }

    printf("\nEnter Book ID to delete: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.id == id) {
            found = 1;
            continue;
        }
        fwrite(&b, sizeof(b), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("library.txt");
    rename("temp.txt", "library.txt");

    if (found)
        printf("\nBook deleted successfully!\n");
    else
        printf("\nBook not found!\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n--- Library Management System ---\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Search Book\n");
        printf("4. Update Book Quantity\n");
        printf("5. Delete Book\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: updateBook(); break;
            case 5: deleteBook(); break;
            case 6: exit(0);
            default: printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}