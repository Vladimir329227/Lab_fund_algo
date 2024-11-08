#ifndef MAIN_H_FLAG
#define MAIN_H_FLAG
#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

enum Errors
{
    OK,
    INVALID_MEMORY,
    INVALID_INPUT,
    ERROR_OPEN_FILE,
};

typedef struct {
    char *data;
    int length;
} String;

enum Errors createString(const char *str, String *new_str);

enum Errors deleteString(String *str);

int compareStrings(const String *str1, const String *str2);

int areStringsEqual(const String *str1, const String *str2);

enum Errors copyString(String *dest, const String *src);

enum Errors cloneString(const String *src, String **newString);

enum Errors concatStrings(String *dest, const String *src);

enum Errors printString(const String *str);

typedef struct {
    String city;
    String street;
    int houseNumber;
    String building;
    int apartmentNumber;
    String index;
} Address;

typedef struct {
    Address recipient;
    float weight;
    String postalID;
    String creationTime;
    String deliveryTime;
} Mail;

typedef struct {
    Address *currentAddress;
    Mail *mails;
    int mailCount;
    int mailCapacity;
} Post;

enum Errors interactiveDialog(Post *post);

enum Errors createAddress(Address *addr, const char *city, const char *street, int houseNumber, const char *building, int apartmentNumber, const char *index);

enum Errors createMail(Mail *mail, const Address *recipient, float weight, const char *postalID, const char *creationTime, const char *deliveryTime);

enum Errors initPost(Post *post, const Address *currentAddress);

enum Errors addMail(Post *post, const Mail *mail);

enum Errors removeMail(Post *post, int index);

enum Errors deleteAddress(Address *addr);

enum Errors deleteMail(Mail *mail);

enum Errors deletePost(Post *post);


#endif