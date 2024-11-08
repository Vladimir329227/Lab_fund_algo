#include "main.h"


enum Errors createAddress(Address *addr, const char *city, const char *street, int houseNumber, const char *building, int apartmentNumber, const char *index) {
    if (createString(city, &addr->city) != OK || createString(street, &addr->street) != OK ||\
     createString(building, &addr->building) != OK || createString(index, &addr->index) != OK){
        deleteAddress(addr);
        return INVALID_MEMORY;
     }
    addr->houseNumber = houseNumber;
    addr->apartmentNumber = apartmentNumber;
    return OK;
}

enum Errors deleteAddress(Address *addr) {
    if (!addr)
        return INVALID_INPUT;
    deleteString(&addr->city);
    deleteString(&addr->street);
    deleteString(&addr->building);
    deleteString(&addr->index);
    return OK;
}

enum Errors createMail(Mail *mail, const Address *recipient, float weight, const char *postalID, const char *creationTime, const char *deliveryTime) {
    if (!mail || !recipient || !postalID || !creationTime || !deliveryTime)
        return INVALID_INPUT;
    mail->recipient = *recipient;
    mail->weight = weight;
    if (createString(postalID, &mail->postalID) != OK || createString(creationTime, &mail->creationTime) != OK || createString(deliveryTime, &mail->deliveryTime) != OK){
        deleteMail(mail);
        return INVALID_MEMORY;
    }
    return OK;
}

enum Errors deleteMail(Mail *mail) {
    if (!mail)
        return INVALID_INPUT;
    deleteAddress(&mail->recipient);
    deleteString(&mail->postalID);
    deleteString(&mail->creationTime);
    deleteString(&mail->deliveryTime);
    return OK;
}

enum Errors initPost(Post *post, const Address *currentAddress) {
    if (!post || !currentAddress)
        return INVALID_INPUT;
    post->currentAddress = (Address *)malloc(sizeof(Address));
    if (post->currentAddress == NULL) {
        deletePost(post);
        return INVALID_MEMORY;
    }
    *post->currentAddress = *currentAddress;
    post->mailCount = 0;
    post->mailCapacity = 10;
    post->mails = (Mail *)malloc(post->mailCapacity * sizeof(Mail));
    if (post->mails == NULL) {
        deletePost(post);
        return INVALID_MEMORY;
    }
    return OK;
}

enum Errors deletePost(Post *post) {
    if (!post)
        return INVALID_INPUT;
    for (int i = 0; i < post->mailCount; i++) {
        deleteMail(&post->mails[i]);
    }
    free(post->mails);
    deleteAddress(post->currentAddress);
    free(post->currentAddress);
    return OK;
}

enum Errors addMail(Post *post, const Mail *mail) {
    if (!mail || !post)
        return INVALID_INPUT;
    Mail* t = NULL;
    if (post->mailCount >= post->mailCapacity) {
        post->mailCapacity *= 2;
        t = (Mail *)realloc(post->mails, post->mailCapacity * sizeof(Mail));
        if (t == NULL){
            deletePost(post);
            return INVALID_MEMORY;
        }
        post->mails = t;
    }
    post->mails[post->mailCount] = *mail;
    post->mailCount++;
    return OK;
}

enum Errors removeMail(Post *post, int index) {
    if (index < 0 || index >= post->mailCount) {
        return INVALID_INPUT;
    }
    deleteMail(&post->mails[index]);
    for (int i = index; i < post->mailCount - 1; i++) {
        post->mails[i] = post->mails[i + 1];
    }
    post->mailCount--;
    return OK;
}

int compareMails(const void *a, const void *b) {
    Mail *mailA = (Mail *)a;
    Mail *mailB = (Mail *)b;
    int indexCompare = strcmp(mailA->recipient.index.data, mailB->recipient.index.data);
    if (indexCompare != 0) {
        return indexCompare;
    }
    return strcmp(mailA->postalID.data, mailB->postalID.data);
}

enum Errors sortMails(Post *post) {
    if (!post)
        return INVALID_INPUT;
    qsort(post->mails, post->mailCount, sizeof(Mail), compareMails);
    return OK;
}

Mail *findMailByID(Post *post, const char *postalID) {
    for (int i = 0; i < post->mailCount; i++) {
        if (strcmp(post->mails[i].postalID.data, postalID) == 0) {
            return &post->mails[i];
        }
    }
    return NULL;
}

int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(int month, int year) {
    if (month == 2) {
        return isLeapYear(year) ? 29 : 28;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    } else {
        return 31;
    }
}

int parseTime(const char *timeStr, struct tm *time) {
    if (sscanf(timeStr, "%2d:%2d:%4d/%2d:%2d:%2d", &time->tm_mday, &time->tm_mon, &time->tm_year, &time->tm_hour, &time->tm_min, &time->tm_sec) != 6) {
        return 1;
    }
    time->tm_mon -= 1;
    time->tm_year -= 1900;
    return 0;
}

int compareTimes(const struct tm *time1, const struct tm *time2) {
    if (time1->tm_year != time2->tm_year) {
        return time1->tm_year - time2->tm_year;
    }
    if (time1->tm_mon != time2->tm_mon) {
        return time1->tm_mon - time2->tm_mon;
    }
    if (time1->tm_mday != time2->tm_mday) {
        return time1->tm_mday - time2->tm_mday;
    }
    if (time1->tm_hour != time2->tm_hour) {
        return time1->tm_hour - time2->tm_hour;
    }
    if (time1->tm_min != time2->tm_min) {
        return time1->tm_min - time2->tm_min;
    }
    return time1->tm_sec - time2->tm_sec;
}

enum Errors interactiveDialog(Post *post) {
    if (!post)
        return INVALID_INPUT;
    int choice;
    enum Errors err = OK;
    do {
        printf("1. Add Mail\n");
        printf("2. Remove Mail\n");
        printf("3. Find Mail by ID\n");
        printf("4. List Delivered Mails\n");
        printf("5. List Overdue Mails\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                Address recipient;
                char city[100], street[100], building[100], index[7];
                int houseNumber, apartmentNumber;
                float weight;
                char postalID[15], creationTime[20], deliveryTime[20];

                printf("Enter recipient city: ");
                scanf("%s", city);
                printf("Enter recipient street: ");
                scanf("%s", street);
                printf("Enter recipient house number: ");
                scanf("%d", &houseNumber);
                printf("Enter recipient building: ");
                scanf("%s", building);
                printf("Enter recipient apartment number: ");
                scanf("%d", &apartmentNumber);
                printf("Enter recipient index: ");
                scanf("%s", index);
                printf("Enter weight: ");
                scanf("%f", &weight);
                printf("Enter postal ID: ");
                scanf("%s", postalID);
                printf("Enter creation time (dd:MM:yyyy/hh:mm:ss): ");
                scanf("%s", creationTime);
                printf("Enter delivery time (dd:MM:yyyy/hh:mm:ss): ");
                scanf("%s", deliveryTime);

                err = createAddress(&recipient, city, street, houseNumber, building, apartmentNumber, index);
                if (err != OK) {
                    return err;
                }
                Mail newMail;
                err = createMail(&newMail, &recipient, weight, postalID, creationTime, deliveryTime);
                if (err != OK) {
                    return err;
                }
                err = addMail(post, &newMail);
                if (err != OK) {
                    return err;
                }
                sortMails(post);
                break;
            }
            case 2: {
                char postalID[15];
                printf("Enter postal ID to remove: ");
                scanf("%s", postalID);
                Mail *mail = findMailByID(post, postalID);
                if (mail != NULL) {
                    int index = mail - post->mails;
                    err = removeMail(post, index);
                    if (err != OK) 
                        return err;
                } else {
                    printf("Mail not found\n");
                }
                break;
            }
            case 3: {
                char postalID[15];
                printf("Enter postal ID to find: ");
                scanf("%s", postalID);
                Mail *mail = findMailByID(post, postalID);
                if (mail != NULL) {
                    printf("Mail found:\n");
                    printf("Recipient: %s, %s, %d, %s, %d, %s\n", mail->recipient.city.data, mail->recipient.street.data, mail->recipient.houseNumber, mail->recipient.building.data, mail->recipient.apartmentNumber, mail->recipient.index.data);
                    printf("Weight: %.2f\n", mail->weight);
                    printf("Postal ID: %s\n", mail->postalID.data);
                    printf("Creation Time: %s\n", mail->creationTime.data);
                    printf("Delivery Time: %s\n", mail->deliveryTime.data);
                } else {
                    printf("Mail not found\n");
                }
                break;
            }
            case 4: {
                printf("Delivered Mails:\n");
                for (int i = 0; i < post->mailCount; i++) {
                    struct tm currentTime;
                    time_t now = time(NULL);
                    localtime_r(&now, &currentTime);
                    struct tm deliveryTime;
                    if (parseTime(post->mails[i].deliveryTime.data, &deliveryTime) == 0 && compareTimes(&currentTime, &deliveryTime) >= 0) {
                        printf("Recipient: %s, %s, %d, %s, %d, %s\n", post->mails[i].recipient.city.data, post->mails[i].recipient.street.data, post->mails[i].recipient.houseNumber, post->mails[i].recipient.building.data, post->mails[i].recipient.apartmentNumber, post->mails[i].recipient.index.data);
                        printf("Weight: %.2f\n", post->mails[i].weight);
                        printf("Postal ID: %s\n", post->mails[i].postalID.data);
                        printf("Creation Time: %s\n", post->mails[i].creationTime.data);
                        printf("Delivery Time: %s\n", post->mails[i].deliveryTime.data);
                    }
                }
                break;
            }
            case 5: {
                printf("Overdue Mails:\n");
                for (int i = 0; i < post->mailCount; i++) {
                    struct tm currentTime;
                    time_t now = time(NULL);
                    localtime_r(&now, &currentTime);
                    struct tm deliveryTime;
                    if (parseTime(post->mails[i].deliveryTime.data, &deliveryTime) == 0 && compareTimes(&currentTime, &deliveryTime) > 0) {
                        printf("Recipient: %s, %s, %d, %s, %d, %s\n", post->mails[i].recipient.city.data, post->mails[i].recipient.street.data, post->mails[i].recipient.houseNumber, post->mails[i].recipient.building.data, post->mails[i].recipient.apartmentNumber, post->mails[i].recipient.index.data);
                        printf("Weight: %.2f\n", post->mails[i].weight);
                        printf("Postal ID: %s\n", post->mails[i].postalID.data);
                        printf("Creation Time: %s\n", post->mails[i].creationTime.data);
                        printf("Delivery Time: %s\n", post->mails[i].deliveryTime.data);
                    }
                }
                break;
            }
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 6);
    
    return OK;
}