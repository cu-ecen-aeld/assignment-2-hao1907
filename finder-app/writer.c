#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <syslog.h>

int main(int argc, char *argv[]) {
    //open connection to syslog
    openlog("writer", LOG_PID, LOG_USER);
    
    if(argc != 3) {
        syslog(LOG_ERR, "Invalid number of arguments: %d ( expected 2)", argc - 1);
        fprintf(stderr, "Error: Invalid number of arguments \n");
        fprintf(stderr, "Usage: %s <writefile> <string>\n", argv[0]);
        closelog();
        return 1;
    }

    const char* writefile = argv[1];
    const char* writestr = argv[2];

    //write the log debug about writing file
    syslog(LOG_DEBUG, "Writing %s to file: %s",writestr, writefile);
    //Open the file for writing
    FILE *file = fopen(writefile, "w");
    if(file ==NULL){
        syslog(LOG_ERR, "Error opening file %s (%s)", writefile, strerror(errno));
        fprintf(stderr, "Error: Failed to open file %s (%s)\n", writefile, strerror(errno));
        closelog();
        return 1;
    }

    //Write the string to the file
    if(fputs(writestr, file) == EOF){
        syslog(LOG_ERR, "Error writing %s to file %s (%s)", writestr, writefile, strerror(errno));
        fprintf(stderr, "Error: Failed to write %s to file %s (%s)\n", writestr, writefile, strerror(errno));
        fclose(file);
        closelog();
        return 1;
    }

    //Close the file
    if(fclose(file) != 0){
        syslog(LOG_ERR, "Error closing file %s (%s)", writefile, strerror(errno));
        fprintf(stderr, "Error: Failed to close file %s (%s)\n", writefile, strerror(errno));
        closelog();
        return 1;
    } else {
        syslog(LOG_DEBUG, "Successfully wrote %s to file %s", writestr, writefile);
        printf("Successfully wrote %s to file %s\n", writestr, writefile);
        closelog();
        return 0;
    }
}