#include <Security/Authorization.h> 
#include <Security/AuthorizationTags.h> 

int read (long,StringPtr,int); 
int write (long,StringPtr,int); 

int main(int argc, char* argv[]) { 
    OSStatus myStatus; 
    AuthorizationRef myAuthorizationRef; 

    myStatus = AuthorizationCreate(
        NULL,
        kAuthorizationEmptyEnvironment,
        kAuthorizationFlagDefaults,
        &myAuthorizationRef); 

    if (myStatus != errAuthorizationSuccess) 
        return myStatus; 

    do 
    { 
        { 
          AuthorizationItem myItems = {kAuthorizationRightExecute, 0, NULL, 0}; 
          AuthorizationRights myRights = {1, &myItems}; 
          AuthorizationFlags myFlags =
              kAuthorizationFlagDefaults | 
              kAuthorizationFlagInteractionAllowed | 
              kAuthorizationFlagPreAuthorize | 
              kAuthorizationFlagExtendRights;

          myStatus = AuthorizationCopyRights(
              myAuthorizationRef, &myRights, NULL, myFlags, NULL ); 
        }

        if (myStatus != errAuthorizationSuccess)
            break;
 
        { 
            FILE *myCommunicationsPipe = NULL; 
            unsigned char myReadBuffer[128]; 

            myStatus = AuthorizationExecuteWithPrivileges(
                myAuthorizationRef,
                argv[1],
                kAuthorizationFlagDefaults,
                &argv[2],
                &myCommunicationsPipe); 

            if (myStatus == errAuthorizationSuccess) 
                for(;;) 
                { 
                    int bytesRead = read(fileno(myCommunicationsPipe), myReadBuffer, sizeof(myReadBuffer)); 
                    if (bytesRead < 1) break; 
                    write(fileno(stdout), myReadBuffer, bytesRead); 
                } 
        } 
    } while (0); 
    
    AuthorizationFree(myAuthorizationRef, kAuthorizationFlagDefaults); 

    if (myStatus)
        printf("Status: %ld\n", myStatus); 

    return myStatus; 
} 
