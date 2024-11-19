#include "main.h"

#define MAX_NAME 70
#define MAX_NAME 70
#define MAX_NAME 70

int isBusExists(struct Bus **result, int count, const unsigned int bus_namber) {
    if (!result)
        return 0;
    
    for (int i = 0; i < count; i++)
        if ((*result)[i].number == bus_namber) 
            return 1;

    return 0;
}

void printBus(struct Bus *bus, int number) {
    for (int i = 0; i < number; i++){
        printf("Bus: %d\n", bus[i].number);
        struct BusStop *temp = bus[i].start;
        while (temp) {
            printf("%s->", temp->name);
            temp = temp->next;
        }
        printf("\n");
    }
}

void freeBus(struct Bus *bus, int number) {
    for (int i = 0; i < number; i++){
        struct BusStop *temp = bus[i].start;
        while (temp) {
            struct BusStop *next = temp->next;
            free(temp);
            temp = next;
        }
    }   
    free(bus);
}

enum Errors AddBusStop(struct Bus *result, struct BusStop* bus_stop) {
    if (!result || !bus_stop)
        return INVALID_INPUT;
    
    if (result->start->time_departure > bus_stop->time_arrival){
        bus_stop->next = result->start;
        result->start = bus_stop;
        return OK;
    }

    struct BusStop* temp = result->start;
    while (temp->next && temp->next->time_departure < bus_stop->time_arrival)
        temp = temp->next;
    bus_stop->next = temp->next;
    temp->next = bus_stop;

    return OK;
}

enum Errors AddBus(struct Bus **result, int *count, const unsigned int bus_namber, struct BusStop* bus_stop) {
    if (!(*result)){
        *result = malloc(sizeof(struct Bus));
        if (!*result)
            return INVALID_MEMORY;
        (*result)->number = bus_namber;
        (*result)->start = bus_stop;
        *count = 1;

    }
    else if (!isBusExists(result, *count, bus_namber))
    {
        struct Bus *temp = NULL;
        temp = (struct Bus *)realloc(*result, (*count + 1) * sizeof(struct Bus));
        if (!temp)
            return INVALID_MEMORY;
        (*result) = temp;
        (*result)[*count].number = bus_namber;
        (*result)[*count].start = bus_stop;
        (*count)++;
    }
    else{
        for (int i = 0; i < *count; i++)
            if ((*result)[i].number == bus_namber){
                if (AddBusStop(&(*result)[i], bus_stop) != OK)
                    return INVALID_MEMORY;
            }
    }

    return OK;
}

int is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int is_valid_date(int year, int month, int day) {
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month == 1 && is_leap_year(year))
        days_in_month[1] = 29;

    if (day < 1 || day > days_in_month[month])
        return 0;

    return 1;
}

enum Errors is_valid_time(struct tm tm) {
    if (tm.tm_mon < 0 || tm.tm_mon > 11)
        return INVALID_INPUT;
    if (tm.tm_mday < 1 || tm.tm_mday > 31)
        return INVALID_INPUT;
    if (!is_valid_date(tm.tm_year, tm.tm_mon, tm.tm_mday)) 
        return INVALID_INPUT;
    if (tm.tm_hour < 0 || tm.tm_hour > 23)
        return INVALID_INPUT;
    if (tm.tm_min < 0 || tm.tm_min > 59)
        return INVALID_INPUT;
    if (tm.tm_sec < 0 || tm.tm_sec > 59)
        return INVALID_INPUT;

    return OK;
}

enum Errors ParseStopFile(const char *filename, struct Bus **result, int *count) {
    if (!filename)
        return INVALID_INPUT;
    FILE *file = fopen(filename, "r");
    if (!file)
        return ERROR_OPEN_FILE;
    unsigned int bus_namber = 0;
    struct tm tm1 = {0}, tm2 = {0};
    int marker = 0;
    while (!feof(file)) {
        if (fscanf(file, "%u %d.%d.%d %d:%d:%d %d.%d.%d %d:%d:%d %i\n", &bus_namber, &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year, &tm1.tm_hour, &tm1.tm_min, &tm1.tm_sec, &tm2.tm_mday, &tm2.tm_mon, &tm2.tm_year, &tm2.tm_hour, &tm2.tm_min, &tm2.tm_sec, &marker) != 14)
            break;
        if (is_valid_time(tm1) != OK || is_valid_time(tm2) != OK)
            return INVALID_INPUT;
        struct BusStop* bus_stop = malloc(sizeof(struct BusStop));
        if (!bus_stop)
            return INVALID_MEMORY;
        bus_stop->time_arrival = mktime(&tm1);
        bus_stop->time_departure = mktime(&tm2);
        bus_stop->flag = marker;
        bus_stop->next = NULL;
        strcpy(bus_stop->name, filename);
        if (AddBus(result, count, bus_namber, bus_stop) != OK) 
            return INVALID_MEMORY;
    }
    return OK;
}

int countRoutes(struct BusStop *stop) {
    int count = 0;
    while (stop != NULL) {
        count++;
        stop = stop->next;
    }
    return count;
}

time_t totalTravelTime(struct BusStop *stop) {
    time_t total = 0;
    while (stop != NULL) {
        total += difftime(stop->time_departure, stop->time_arrival);
        stop = stop->next;
    }
    return total;
}

struct BusStop* findLongestStop(struct BusStop *stop) {
    struct BusStop *longest = stop;
    while (stop != NULL) {
        if (difftime(stop->time_departure, stop->time_arrival) > difftime(longest->time_departure, longest->time_arrival)) {
            longest = stop;
        }
        stop = stop->next;
    }
    return longest;
}

struct BusStop* findShortestStop(struct BusStop *stop) {
    struct BusStop *shortest = stop;
    while (stop != NULL) {
        if (difftime(stop->time_departure, stop->time_arrival) < difftime(shortest->time_departure, shortest->time_arrival)) {
            shortest = stop;
        }
        stop = stop->next;
    }
    return shortest;
}

struct BusStop* findLongestIdleTime(struct BusStop *stop) {
    struct BusStop *longest = stop;
    while (stop != NULL) {
        if (difftime(stop->time_departure, stop->time_arrival) > difftime(longest->time_departure, longest->time_arrival)) {
            longest = stop;
        }
        stop = stop->next;
    }
    return longest;
}

struct Bus* findBusWithRoutes(struct Bus *buses, int count, int flag) {
    struct Bus *RoutesBus = &buses[0];
    int Routes = countRoutes(buses[0].start);
    for (int i = 1; i < count; i++) {
        int currentRoutes = countRoutes(buses[i].start);
        if (flag == 0) {
            if (currentRoutes > Routes) {
                Routes = currentRoutes;
                RoutesBus = &buses[i];
            }
        }
        else {
            if (currentRoutes < Routes) {
                Routes = currentRoutes;
                RoutesBus = &buses[i];
            }
        }
        
    }
    return RoutesBus;
}

struct Bus* findBusWithTravelTime(struct Bus *buses, int count, int flag) {
    struct Bus *TravelTimeBus = &buses[0];
    time_t TravelTime = totalTravelTime(buses[0].start);
    for (int i = 1; i < count; i++) {
        time_t currentTravelTime = totalTravelTime(buses[i].start);
        if (flag == 0) {
            if (currentTravelTime > TravelTime) {
                TravelTime = currentTravelTime;
                TravelTimeBus = &buses[i];
            }
        }
        else {
            if (currentTravelTime < TravelTime) {
                TravelTime = currentTravelTime;
                TravelTimeBus = &buses[i];
            }
        }
        
    }
    return TravelTimeBus;
}

struct Bus* findBusWithStop(struct Bus *buses, int count, int flag) {
    struct Bus *StopBus = &buses[0];
    struct BusStop *Stop = NULL;
    if (flag == 0)
        Stop = findLongestStop(buses[0].start);
    else 
        Stop = findShortestStop(buses[0].start);
    for (int i = 1; i < count; i++) {
        if (flag == 0) {
            struct BusStop *currentStop = findLongestStop(buses[i].start);
            if (difftime(currentStop->time_departure, currentStop->time_arrival) > difftime(Stop->time_departure, Stop->time_arrival)) {
                Stop = currentStop;
                StopBus = &buses[i];
            }    
        }
        else {
            struct BusStop *currentStop = findShortestStop(buses[i].start);
            if (difftime(currentStop->time_departure, currentStop->time_arrival) < difftime(Stop->time_departure, Stop->time_arrival)) {
                Stop = currentStop;
                StopBus = &buses[i];
            }
        }
    }
    return StopBus;
}

struct Bus* findBusWithLongestIdleTime(struct Bus *buses, int count) {
    struct Bus *longestIdleTimeBus = &buses[0];
    struct BusStop *longestIdleTime = findLongestIdleTime(buses[0].start);
    for (int i = 1; i < count; i++) {
        struct BusStop *currentLongestIdleTime = findLongestIdleTime(buses[i].start);
        if (difftime(currentLongestIdleTime->time_departure, currentLongestIdleTime->time_arrival) > difftime(longestIdleTime->time_departure, longestIdleTime->time_arrival)) {
            longestIdleTime = currentLongestIdleTime;
            longestIdleTimeBus = &buses[i];
        }
    }
    return longestIdleTimeBus;
}

enum Errors UserMain(struct Bus *buses, int count) {
    if (buses == NULL || count <= 0) {
        return INVALID_INPUT;
    }

    int choice;
    do {
        printf("Enter a number:\n");
        printf("1. Bus with the most routes\n");
        printf("2. Bus with the fewest routes\n");
        printf("3. Bus with the longest route\n");
        printf("4. Bus with the shortest route\n");
        printf("5. Bus with the longest stop\n");
        printf("6. Bus with the shortest stop\n");
        printf("7. Bus with the longest idle time\n");
        printf("0. Exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        struct Bus *resultBus = NULL;
        switch (choice) {
            case 1:
                resultBus = findBusWithRoutes(buses, count, 0);
                break;
            case 2:
                resultBus = findBusWithRoutes(buses, count, 1);
                break;
            case 3:
                resultBus = findBusWithTravelTime(buses, count, 0);
                break;
            case 4:
                resultBus = findBusWithTravelTime(buses, count, 1);
                break;
            case 5:
                resultBus = findBusWithStop(buses, count, 0);
                break;
            case 6:
                resultBus = findBusWithStop(buses, count, 1);
                break;
            case 7:
                resultBus = findBusWithLongestIdleTime(buses, count);
                break;
            case 0:
                break;
            default:
                printf("Error Invalid choice.\n");
                continue;
        }

        if (resultBus != NULL) {
            printf("Number bus: %d\n", resultBus->number);
        }
    } while (choice != 0);

    return OK;
}
