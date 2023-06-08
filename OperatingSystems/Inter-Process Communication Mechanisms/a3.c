#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define TESTER_REQUEST_PIPE "REQ_PIPE_24212"
#define TESTER_RESPONSE_PIPE "RESP_PIPE_24212"
#define MAX_BUFFER_SIZE 250
int JSG_VARIANT = 24212;

int U_REQ_PIPE, T_RESP_PIPE;
char reqMESSAGEresp[MAX_BUFFER_SIZE];

int shmFd;
void *shmPtr;
const char *shmName = "/yO4pstV";
size_t shmSize = 4217434;
mode_t shmPerm = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;

const char *R_err = "ERROR$";
const char *R_succ = "SUCCESS$";
const char *R_createSHM = "CREATE_SHM$";
const char *R_writeSHM = "WRITE_TO_SHM$";
const char *R_mmFile = "MAP_FILE$";
const char *R_readFileOff = "READ_FROM_FILE_OFFSET$";
const char *R_readFileSec = "READ_FROM_FILE_SECTION$";
const char *R_readLogicalSpace = "READ_FROM_LOGICAL_SPACE$";
const char *R_ping = "PING$";
const char *R_pong = "PONG$";
const char *R_connect = "CONNECT$";

const char *T_err = "ERROR";
const char *T_succ = "SUCCESS";
const char *T_createSHM = "CREATE_SHM";
const char *T_writeSHM = "WRITE_TO_SHM";
const char *T_mmFile = "MAP_FILE";
const char *T_readFileOff = "READ_FROM_FILE_OFFSET";
const char *T_readFileSec = "READ_FROM_FILE_SECTION";
const char *T_readLogicalSpace = "READ_FROM_LOGICAL_SPACE";
const char *T_ping = "PING";
const char *T_exit = "EXIT";

unsigned int offset;
unsigned int value;
unsigned int readFileoffset;
unsigned int readFilebytes;
int fileSize;
unsigned int SHMbyteCount;

void *fileOFFPtr;
char *fileOFFmem;

void handleFirstReq()
{

    if(-1 == write(T_RESP_PIPE, R_ping, strlen(R_ping))){
        exit(-1);
    };
    if(-1 == write(T_RESP_PIPE, R_pong, strlen(R_pong))){
        exit(-1);
    };
    if(-1 == write(T_RESP_PIPE, &JSG_VARIANT, sizeof(int))){
        exit(-1);
    };
}

void handleSecondReq()
{
    shmFd = shm_open(shmName, O_CREAT | O_RDWR, shmPerm);
    if(-1 == read(U_REQ_PIPE, &SHMbyteCount, sizeof(unsigned int))){
        exit(-1);
    };
    if(-1 == write(T_RESP_PIPE, R_createSHM, strlen(R_createSHM))){
        exit(-1);
    };
    shmSize = SHMbyteCount;

    if (shmFd < 0)
    {
        write(T_RESP_PIPE, R_err, strlen(R_err));
        exit(-1);
    }
    else
    {
        if (-1 == ftruncate(shmFd, shmSize))
        {
            write(T_RESP_PIPE, R_err, strlen(R_err));
            exit(-1);
        }
        shmPtr = mmap(NULL, shmSize, PROT_READ | PROT_WRITE, MAP_SHARED, shmFd, 0);
        if (MAP_FAILED == shmPtr)
        {
            write(T_RESP_PIPE, R_err, strlen(R_err));
            exit(-1);
        }

        if(-1 == write(T_RESP_PIPE, R_succ, strlen(R_succ))){
        exit(-1);
    };
    }
}

void handleThirdReq()
{

    if(-1 == read(U_REQ_PIPE, &offset, sizeof(unsigned int))){
        exit(-1);
    };
    if(-1 == read(U_REQ_PIPE, &value, sizeof(unsigned int))){
        exit(-1);
    };
    if(-1 == write(T_RESP_PIPE, R_writeSHM, strlen(R_writeSHM))){
        exit(-1);
    };

    if (shmPtr != NULL && offset > 0 && (offset + sizeof(value) < shmSize))
    {
        memcpy(shmPtr + offset, &value, sizeof(unsigned int));
        if(-1 == write(T_RESP_PIPE, R_succ, strlen(R_succ))){
        exit(-1);
    };
    }
    else
    {
        write(T_RESP_PIPE, R_err, strlen(R_err));
        exit(-1);
    }
}

void handleFourthReq()
{

    char fileName[MAX_BUFFER_SIZE];
    if(-1 == read(U_REQ_PIPE, &fileName, MAX_BUFFER_SIZE)){
        exit(-1);
    };

    if(-1 == write(T_RESP_PIPE, R_mmFile, strlen(R_mmFile))){
        exit(-1);
    };

    int i = 0;
    while (fileName[i] != '$')
    {
        i++;
    }
    fileName[i] = '\0';
    int fileD = open(fileName, O_RDONLY);
    if (-1 == fileD)
    {
        write(T_RESP_PIPE, R_err, strlen(R_err));
        exit(-1);
    }
    else
    {
        struct stat statFile = {};

        if (stat(fileName, &statFile) == 0)
        {
            fileSize = statFile.st_size;
        }
        fileOFFPtr = mmap(0, fileSize, PROT_READ, MAP_SHARED, fileD, 0);
        if (fileOFFPtr != NULL)
        {
            if(-1 == write(T_RESP_PIPE, R_succ, strlen(R_succ))){
        exit(-1);
    };
        }
        else
        {
            write(T_RESP_PIPE, R_err, strlen(R_err));
            exit(-1);
        }
    }
}

void handleFifthReq()
{

    if(-1 == read(U_REQ_PIPE, &readFileoffset, sizeof(unsigned int))){
        exit(-1);
    };
    if( -1 == read(U_REQ_PIPE, &readFilebytes, sizeof(unsigned int))){
        exit(-1);
    };
    if(-1 == write(T_RESP_PIPE, R_readFileOff, strlen(R_readFileOff))){
        exit(-1);
    };

    if (NULL != fileOFFPtr && readFileoffset > 0 && (readFileoffset + sizeof(readFilebytes)) < fileSize)
    {
        memcpy(fileOFFmem, fileOFFPtr + readFileoffset, readFilebytes);
       if(-1 == write(T_RESP_PIPE, R_succ, strlen(R_succ))){
        exit(-1);
    };
    }
    else
    {
        write(T_RESP_PIPE, R_err, strlen(R_err));
        exit(-1);
    }
}

void handleSixthReq()
{
    write(T_RESP_PIPE, R_readFileSec, strlen(R_readFileSec));
    write(T_RESP_PIPE, R_err, strlen(R_err));
    exit(-1);
}

void handleSeventhReq()
{
    write(T_RESP_PIPE, R_readLogicalSpace, strlen(R_readLogicalSpace));
    write(T_RESP_PIPE, R_err, strlen(R_err));
    exit(-1);
}

int main(int argc, char **argv)
{
    if (mkfifo(TESTER_RESPONSE_PIPE, 0777) < 0)
    {
        printf("ERROR\ncan't create the response pipe\n");
        return -1;
    }

    U_REQ_PIPE = open(TESTER_REQUEST_PIPE, O_RDONLY);
    if (U_REQ_PIPE < 0)
    {
        printf("ERROR\ncannot open the request pipe\n");
        return -1;
    }
    T_RESP_PIPE = open(TESTER_RESPONSE_PIPE, O_WRONLY);
    if (T_RESP_PIPE < 0)
    {
        printf("ERROR\ncan't open the response pipe\n");
        return -1;
    }
    if(-1 == write(T_RESP_PIPE, R_connect, strlen(R_connect))){
        exit(-1);
    };
    printf("%s\n", T_succ);

    char outMsg[MAX_BUFFER_SIZE];
    char buff[1];
    char readCHARByte = '\0';
    int size = 0;
    while (read(U_REQ_PIPE, buff, sizeof(buff)))
    {
        readCHARByte = buff[0];
        outMsg[size] = buff[0];
        size++;
        if (readCHARByte == '$')
        {
            break;
        }
    }
    outMsg[size - 1] = '\0';
    strcpy(reqMESSAGEresp, outMsg);
    reqMESSAGEresp[size - 1] = '\0';

    while (strstr(reqMESSAGEresp, T_exit) == NULL)
    {
        if (strstr(reqMESSAGEresp, T_ping) != NULL)
        {
            handleFirstReq();
        }
        if (strstr(reqMESSAGEresp, T_createSHM) != NULL)
        {
            handleSecondReq();
        }
        if (strstr(reqMESSAGEresp, T_writeSHM) != NULL)
        {
            handleThirdReq();
        }
        if (strstr(reqMESSAGEresp, T_mmFile) != NULL)
        {
            handleFourthReq();
        }
        if (strstr(reqMESSAGEresp, T_readFileOff) != NULL)
        {
            handleFifthReq();
        }
        if (strstr(reqMESSAGEresp, T_readFileSec) != NULL)
        {
            handleSixthReq();
        }
        if (strstr(reqMESSAGEresp, T_readLogicalSpace) != NULL)
        {
            handleSeventhReq();
        }

        size = 0;
        while (read(U_REQ_PIPE, buff, sizeof(buff)) > 0)
        {
            readCHARByte = buff[0];
            outMsg[size] = buff[0];
            size++;

            if (readCHARByte == '$')
            {
                break;
            }
        }
        outMsg[size - 1] = '\0';
        strcpy(reqMESSAGEresp, outMsg);
        reqMESSAGEresp[size - 1] = '\0';
    }

    close(T_RESP_PIPE);
    close(U_REQ_PIPE);
    munmap(shmPtr, shmSize);
    munmap(fileOFFPtr, fileSize);

    return 0;
}