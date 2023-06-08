#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define MAGIC_FIELD "m"
#define MIN_VERSION 17
#define MAX_VERSION 109
#define MIN_SECTIONS 6
#define MAX_SECTIONS 18
#define VALID_TYPES  {85, 87, 39, 36, 12, 50, 92}


#pragma pack(push, 1)
typedef struct fileHeaderSection
{
    char name[9];
    short type;
    int offset;
    int size;
}fileHeaderSection_t;

typedef struct fileHeader
{
    short version;
    unsigned char numberOfSections;
    fileHeaderSection_t sectionContent[18];
    char magicNumber[2];
    short headerSize;
}fileHeader_t;

#pragma pack(pop)

int parseFile(const char *path, fileHeader_t *fileData)
{
    const short validTypes[] = VALID_TYPES;
    const int numberOfValidTypes = sizeof(validTypes) / sizeof(validTypes[0]);
    int isTypeValid = 0;
    int currentFile = 0;
    currentFile = open(path, O_RDONLY);
    if (currentFile == -1)
    {
        // perror("ERROR\nfailed to open file\n");
        return -1;
    }
    off_t fileSize = 0;
    fileSize = lseek(currentFile, 0, SEEK_END);
    if (fileSize < sizeof(fileHeader_t))
    {
        // printf("ERROR\nfile too small\n");
        close(currentFile);
        return -1;
    }

    lseek(currentFile, -1, SEEK_END);
    if ((read(currentFile, fileData->magicNumber, sizeof(char)) != 1))
    {
        // printf("ERROR\nwrong magic\n");
        close(currentFile);
        return -2;
    }
    fileData->magicNumber[1]='\0';
    if (strcmp(fileData->magicNumber, "m") != 0)
    {
        // printf("ERROR\nwrong magic\n");
        close(currentFile);
        return -2;
    }
    lseek(currentFile, -3, SEEK_END);
    read(currentFile, &fileData->headerSize, 2);
    lseek(currentFile, -(off_t)fileData->headerSize, SEEK_END);

    if ((read(currentFile, &fileData->version, 2) != 2) || (fileData->version < MIN_VERSION) || (fileData->version > MAX_VERSION))
    {
        // printf("ERROR\nwrong version\n");
        close(currentFile);
        return -3;
    }

    if ((read(currentFile, &fileData->numberOfSections, 1) != 1) || (fileData->numberOfSections < MIN_SECTIONS) || (fileData->numberOfSections > MAX_SECTIONS))
    {
        // printf("ERROR\nwrong sect_nr\n");
        close(currentFile);
        return -4;
    }
    for (int i = 0; i < fileData->numberOfSections; i++)
    {
        read(currentFile, fileData->sectionContent[i].name, 8);
        read(currentFile, &fileData->sectionContent[i].type, 2);
        read(currentFile, &fileData->sectionContent[i].offset, 4);
        read(currentFile, &fileData->sectionContent[i].size, 4);

        fileData->sectionContent[i].name[8]='\0';
        isTypeValid = 0;
        for (int j = 0; j < numberOfValidTypes; j++)
        {
            if (fileData->sectionContent[i].type == validTypes[j])
            {
                
                isTypeValid = 1;
                break;
            }
        }
        if (isTypeValid == 0)
        {
            // printf("ERROR\nwrong sect_types\n");
            close(currentFile);
            return -5;
        }
    }
    close(currentFile);
    return 0;
}

int findAll(char *path)
{
    fileHeader_t fileData;

    fileData.headerSize=0;
    fileData.numberOfSections=0;
    fileData.version=0;
    strcpy(fileData.magicNumber,"\0");
    for (int k = 0; k < fileData.numberOfSections; k++)
    {
        strcpy(fileData.sectionContent[k].name,"\0");
        fileData.sectionContent[k].offset=0;
        fileData.sectionContent[k].size=0;
        fileData.sectionContent[k].type=0;
    }
     
    int ok=0;
    int fileOK=1;
    ok=parseFile(path,&fileData);
    if(ok!=0)
    {
        return -1;
    }
    for (int i = 0; i < fileData.numberOfSections; i++)
    {
       if(fileData.sectionContent->size>1290)
       {
         fileOK=0;
         break;
       }
    }
    return fileOK;
}

int findAllFiles(char *path)
{
    DIR *directory = NULL;
    directory = opendir(path);
    if (NULL == directory)
    {
        return -1;
    }
    char absolutePath[1106] = "";
    struct dirent *directoryEntry = NULL;
    int ok = 0;
    while ((directoryEntry = readdir(directory)) != NULL)
    {
        if (strcmp(directoryEntry->d_name, ".") != 0 && strcmp(directoryEntry->d_name, "..") != 0)
        {
            ok = -3;
            strcpy(absolutePath, path);
            strcat(absolutePath, "/");
            strcat(absolutePath, directoryEntry->d_name);
            ok = findAll(absolutePath);
            if (ok == 1)
            {
                printf("%s\n", absolutePath);
            }
            findAllFiles(absolutePath);
        }
    }
    closedir(directory);
    return 0;
}

void deallocate_memory(void *ptr)
{
    ptr = NULL;
    free(ptr);
}
int extractFromFile(const char *path, int sectionNumber, int lineNumber)
{
    fileHeader_t fileData;

    fileData.headerSize=0;
    fileData.numberOfSections=0;
    fileData.version=0;
    strcpy(fileData.magicNumber,"\0");
    for (int k = 0; k < fileData.numberOfSections; k++)
    {
        strcpy(fileData.sectionContent[k].name,"\0");
        fileData.sectionContent[k].offset=0;
        fileData.sectionContent[k].size=0;
        fileData.sectionContent[k].type=0;
    }

    int printEntries = 0;
    printEntries = parseFile(path, &fileData);
    if (printEntries != 0)
    {
        printf("ERROR\ninvalid file");
        return -1;
    }
    int currentFile = 0;
    currentFile = open(path, O_RDONLY);
    if (currentFile == -1)
    {
        // perror("ERROR\nfailed to open file\n");
        return -1;
    }
    lseek(currentFile, fileData.sectionContent[sectionNumber - 1].offset, SEEK_SET);
    char *sectionContent = (char *)malloc(fileData.sectionContent[sectionNumber - 1].size);
    if (sectionContent == NULL)
    {

        close(currentFile);
        return -1;
    }
    read(currentFile, sectionContent, fileData.sectionContent[sectionNumber - 1].size);
    char *lineSeparator = "\x0A";
    char *linesContent = (char *)malloc(fileData.sectionContent[sectionNumber - 1].size * sizeof(char));
    if (linesContent == NULL)
    {
        deallocate_memory(sectionContent);
        close(currentFile);
        return -1;
    }
    char *linePointerSeparator = strtok(sectionContent, lineSeparator);
    int numberOfLines = 1;
    while ((linePointerSeparator != NULL) && (numberOfLines <= lineNumber))
    {
        linesContent = linePointerSeparator;
        numberOfLines++;
        linePointerSeparator = strtok(NULL, lineSeparator);
    }
    // printf("%d\n", numberOfLines);
    char *extractedLine = NULL;
    // printf("%d\n",lineNumber);
     if (lineNumber < 1 || linesContent == NULL || strlen(linesContent) == 0)
    {
        printf("ERROR\ninvalid line\n");

        deallocate_memory(linesContent);
        deallocate_memory(sectionContent);

        close(currentFile);
        return -1;
    }
    extractedLine = linesContent;
     if (extractedLine == NULL || strlen(extractedLine)==0)
    {
        deallocate_memory(linesContent);
        deallocate_memory(sectionContent);
        close(currentFile);
        return -1;
    }
    for (int j = strlen(extractedLine) - 1; j >= 0; j--)
    {
        printf("%c", extractedLine[j]);
    }
    printf("\n");
    deallocate_memory(extractedLine);
    deallocate_memory(linesContent);
    deallocate_memory(sectionContent);
    close(currentFile);
    return 0;
}
int hasPermission(const char *path)
{
    struct stat info;
    if (stat(path, &info) != 0)
    {
        return 0;
    }
    uid_t currentOwner = getuid();
    if (currentOwner != info.st_uid)
    {
        return 0;
    }
    if ((info.st_mode & S_IXUSR) == S_IXUSR)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int startsWith(char *str, char *prefix)
{
    return strncmp(str, prefix, strlen(prefix)) == 0;
}

void listDirectoryContentsSimple(const char *path)
{
    DIR *directory = NULL;
    directory = opendir(path);
    if (NULL == directory)
    {
        perror("ERROR\ninvalid directory path\n");
        return;
    }
    struct dirent *directoryEntry = NULL;
    printf("SUCCESS\n");
    while ((directoryEntry = readdir(directory)) != NULL)
    {
        if (strcmp(directoryEntry->d_name, ".") != 0 && strcmp(directoryEntry->d_name, "..") != 0)
        {
            printf("%s/%s\n", path, directoryEntry->d_name);
        }
    }
    closedir(directory);
}

void listDirectoryContentsSimpleRecursion(char *path)
{
    DIR *directory = NULL;
    directory = opendir(path);
    if (NULL == directory)
    {
        perror("ERROR\ninvalid directory path\n");
        return;
    }
    char absolutePath[1106] = "";
    struct dirent *directoryEntry = NULL;

    while ((directoryEntry = readdir(directory)) != NULL)
    {
        if (strcmp(directoryEntry->d_name, ".") != 0 && strcmp(directoryEntry->d_name, "..") != 0)
        {
            printf("%s/%s\n", path, directoryEntry->d_name);

            strcpy(absolutePath, path);
            strcat(absolutePath, "/");
            strcat(absolutePath, directoryEntry->d_name);

            listDirectoryContentsSimpleRecursion(absolutePath);
        }
    }
    closedir(directory);
}

void listDirectoryContentsSimpleFilter(const char *path, int permissionFilteringOptions, char *nameFilteringOption)
{
    DIR *directory = NULL;
    char absolutePath[1106] = "";
    directory = opendir(path);
    if (NULL == directory)
    {
        perror("ERROR\ninvalid directory path\n");
        return;
    }
    struct dirent *directoryEntry = NULL;
    printf("SUCCESS\n");
    while ((directoryEntry = readdir(directory)) != NULL)
    {
        if (strcmp(directoryEntry->d_name, ".") != 0 && strcmp(directoryEntry->d_name, "..") != 0)
        {
            strcpy(absolutePath, path);
            strcat(absolutePath, "/");
            strcat(absolutePath, directoryEntry->d_name);
            if (permissionFilteringOptions == 1 && nameFilteringOption != NULL)
            {
                if (hasPermission(absolutePath) && startsWith(directoryEntry->d_name, nameFilteringOption))
                {
                    printf("%s/%s\n", path, directoryEntry->d_name);
                }
            }
            else if (permissionFilteringOptions == 1)
            {
                if (hasPermission(absolutePath))
                {
                    printf("%s/%s\n", path, directoryEntry->d_name);
                }
            }
            else if (nameFilteringOption != NULL)
            {
                if (startsWith(directoryEntry->d_name, nameFilteringOption))
                {
                    printf("%s/%s\n", path, directoryEntry->d_name);
                }
            }
        }
    }
    closedir(directory);
}

void listDirectoryContentsSimpleRecursionFilter(const char *path, int permissionFilteringOptions, char *nameFilteringOption)
{
    DIR *directory = NULL;
    directory = opendir(path);
    if (NULL == directory)
    {
        perror("ERROR\ninvalid directory path\n");
        return;
    }
    char absolutePath[1106] = "";
    struct dirent *directoryEntry = NULL;

    while ((directoryEntry = readdir(directory)) != NULL)
    {
        if (strcmp(directoryEntry->d_name, ".") != 0 && strcmp(directoryEntry->d_name, "..") != 0)
        {

            strcpy(absolutePath, path);
            strcat(absolutePath, "/");
            strcat(absolutePath, directoryEntry->d_name);

            if (permissionFilteringOptions == 1 && nameFilteringOption != NULL)
            {
                if (hasPermission(absolutePath) && startsWith(directoryEntry->d_name, nameFilteringOption))
                {
                    printf("%s/%s\n", path, directoryEntry->d_name);
                }
            }
            else if (permissionFilteringOptions == 1)
            {
                if (hasPermission(absolutePath))
                {
                    printf("%s/%s\n", path, directoryEntry->d_name);
                }
            }
            else if (nameFilteringOption != NULL)
            {
                if (startsWith(directoryEntry->d_name, nameFilteringOption))
                {
                    printf("%s/%s\n", path, directoryEntry->d_name);
                }
            }

            listDirectoryContentsSimpleRecursion(absolutePath);
        }
    }
    closedir(directory);
}

int main(int argc, char **argv)
{
    int recursiveOption = 0;
    int listOption = 0;
    char *path = NULL;
    char *nameFilteringOption = NULL;
    int permissionFilteringOptions = 0;
    int parseOption = 0;
    int extractOption = 0;
    int lineNumber = 0;
    int sectionNumber = 0;
    int filterFindAllOption = 0;

    fileHeader_t fileData;
    fileData.headerSize=0;
    fileData.numberOfSections=0;
    fileData.version=0;
    strcpy(fileData.magicNumber,"\0");
    for (int k = 0; k < fileData.numberOfSections; k++)
    {
        strcpy(fileData.sectionContent[k].name,"\0");
        fileData.sectionContent[k].offset=0;
        fileData.sectionContent[k].size=0;
        fileData.sectionContent[k].type=0;
    }

    if (argc >= 2)
    {
        if (strcmp(argv[1], "variant") == 0)
        {
            printf("24212\n");
        }
        for (int i = 1; i < argc; i++)
        {
            if (strcmp(argv[i], "list") == 0)
            {
                listOption = 1;
            }
            if (strncmp(argv[i], "line=", 5) == 0)
            {
                lineNumber = atoi(argv[i] + 5);
            }
            if (strncmp(argv[i], "section=", 8) == 0)
            {
                sectionNumber = atoi(argv[i] + 8);
            }
            if (strcmp(argv[i], "findall") == 0)
            {
                filterFindAllOption = 1;
            }
            if (strcmp(argv[i], "recursive") == 0)
            {
                recursiveOption = 1;
            }
            if (strcmp(argv[i], "extract") == 0)
            {
                extractOption = 1;
            }

            if (strncmp(argv[i], "path=", 5) == 0)
            {
                path = argv[i] + 5;
            }

            if (strncmp(argv[i], "name_starts_with=", 17) == 0)
            {
                nameFilteringOption = argv[i] + 17;
            }

            if (strcmp(argv[i], "has_perm_execute") == 0)
            {
                permissionFilteringOptions = 1;
            }

            if (strcmp(argv[i], "parse") == 0)
            {
                parseOption = 1;
            }
        }
        if (NULL == path && (listOption == 1 || parseOption == 1))
        {
            printf("ERROR\ninvalid directory path\n");
        }
        if (listOption == 1)
        {
            if (recursiveOption == 1)
            {
                printf("SUCCESS\n");
                if ((permissionFilteringOptions == 1) || (nameFilteringOption != NULL))
                {
                    listDirectoryContentsSimpleRecursionFilter(path, permissionFilteringOptions, nameFilteringOption);
                }
                else
                {
                    listDirectoryContentsSimpleRecursion(path);
                }
            }
            else
            {
                if ((permissionFilteringOptions == 1) || (nameFilteringOption != NULL))
                {
                    listDirectoryContentsSimpleFilter(path, permissionFilteringOptions, nameFilteringOption);
                }
                else
                {
                    listDirectoryContentsSimple(path);
                }
            }
        }
        if (extractOption == 1)
        {
            printf("SUCCESS\n");
            extractFromFile(path, sectionNumber, lineNumber);
        }
        if (parseOption == 1)
        {
            int ok = 0;
            ok = parseFile(path, &fileData);
            if(ok==0)
            {
                printf("SUCCESS\n");
                printf("version=%d\n", (int)fileData.version);
                printf("nr_sections=%d\n", (int)fileData.numberOfSections);
                for (int k = 0; k < fileData.numberOfSections; k++)
                {
                    printf("section%d: %s %d %d\n", k + 1, fileData.sectionContent[k].name, (int)fileData.sectionContent[k].type, fileData.sectionContent[k].size);
                }
            }else{
                if(ok==-1)
                {
                    printf("ERROR\nfailed to open file\n");
                }
                 if(ok==-2)
                {
                    printf("ERROR\nwrong magic\n");
                }
                 if(ok==-3)
                {
                    printf("ERROR\nwrong version\n");
                }
                 if(ok==-4)
                {
                    printf("ERROR\nwrong sect_nr\n");
                }
                 if(ok==-5)
                {
                    printf("ERROR\nwrong sect_types\n");
                }
            }
            }
        
        if (filterFindAllOption)
        {
            printf("SUCCESS\n");
            findAllFiles(path);
        }
    }
    
    return 0;
}