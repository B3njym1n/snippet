#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <winsock2.h>
#include <stdio.h>
#include <string.h>
#include <ws2tcpip.h>

// #pragma comment(lib, “ws2_32.lib”) useless besides visualstudio

void get_msg_text(DWORD,char **);

int main(int argc, char** argv)
{
    struct addrinfo     *ps_address;
    void                *pv_address;
    char                *nc_error;
    DWORD                dw_error;
    struct addrinfo       s_hints;
    char                 ac_ipstr[INET6_ADDRSTRLEN];
    struct sockaddr_in  *ps_ipv4;
    struct sockaddr_in6 *ps_ipv6;
    char                *pc_ipver;
    struct addrinfo     *ps_res;
    int                 i_status;
    WSADATA s_wsaData;

    if (argc != 2)
    {
        fprintf(stderr,"usage: showip hostname\n");

        return 1;
    }
/*                                                                            */
/* Initialize Winsock and request version 2.2:                                */
/*                                                                            */
    if ((i_status = WSAStartup(MAKEWORD(2,2), &s_wsaData)) != 0) {
        dw_error = (DWORD)i_status;
        get_msg_text(dw_error,
                    &nc_error);
        fprintf(stderr,"WSAStartup failed with code %d.\n",i_status);
        fprintf(stderr,"%s\n",nc_error);
        LocalFree(nc_error);

        return 2;
    }

/*                                                                            */
/* Verify that version 2.2 is available:                                      */
/*                                                                            */
    if (LOBYTE(s_wsaData.wVersion) < 2 ||
       HIBYTE(s_wsaData.wVersion) < 2)
    {
        fprintf(stderr,"Version 2.2 of Winsock is not available.\n");
        WSACleanup();

        return 3;
    }

/*                                                                            */
/* Set the desired IP address characteristics:                                */
/*                                                                            */
    memset(&s_hints,0,sizeof(s_hints));
    s_hints.ai_family   = AF_UNSPEC;   // AF_INET or AF_INET6 to force version
    s_hints.ai_socktype = SOCK_STREAM; // Streaming socket

/*                                                                            */
/* Request the list of matching IP addresses for the specified host:          */
/*                                                                            */
    i_status = getaddrinfo(argv[1],NULL,&s_hints,&ps_res);

    if (i_status != 0)
    {
        dw_error = (DWORD)WSAGetLastError();
        get_msg_text(dw_error,
                    &nc_error);
        fprintf(stderr,"getaddrinfo failed with code %ld.\n",dw_error);
        fprintf(stderr,"%s\n",nc_error);
        LocalFree(nc_error);
        WSACleanup();

        return 4;
    }
/*                                                                            */
/* Print out the list of IP addresses:                                        */
/*                                                                            */
   printf("IP addresses for %s:\n\n",argv[1]);

   for (ps_address = ps_res ;
        ps_address != NULL ;
        ps_address = ps_address->ai_next)
    {
    /* Get the pointer to the address itself (different fields in IPv4 and IPv6): */
        if (ps_address->ai_family == AF_INET) // IPv4
        {
            ps_ipv4 = (struct sockaddr_in *)ps_address->ai_addr;
            pv_address = &(ps_ipv4->sin_addr);
            pc_ipver = "IPv4";
        }
        else // IPv6
        {
            ps_ipv6 = (struct sockaddr_in6 *)ps_address->ai_addr;
            pv_address = &(ps_ipv6->sin6_addr);
            pc_ipver = "IPv6";
        }
    /* Convert the IP to a string and print it:                                   */
        inet_ntop(ps_address->ai_family,pv_address,ac_ipstr,sizeof(ac_ipstr));

        printf("  %s: %s\n",pc_ipver,ac_ipstr);
    }
    WSACleanup();

/*                                                                            */
/* Free the list of addresses:                                                */
/*                                                                            */
    freeaddrinfo(ps_res);
    return 0;
}

/*                                                                            */
/******************************************************************************/
/*                                                                            */
/* Get Error Message Text:                                                    */
/*                                                                            */
void get_msg_text
(
   DWORD    dw_error, /* in   - Error code                                    */
   char  **pnc_msg    /* out  - Error message                                 */
)
{
   DWORD dw_flags;
/*                                                                            */
/* Set message options:                                                       */
/*                                                                            */
   dw_flags = FORMAT_MESSAGE_ALLOCATE_BUFFER
            | FORMAT_MESSAGE_FROM_SYSTEM
            | FORMAT_MESSAGE_IGNORE_INSERTS;
/*                                                                            */
/* Create the message string:                                                 */
/*                                                                            */
   FormatMessage(dw_flags,NULL,dw_error,LANG_SYSTEM_DEFAULT,(LPTSTR)pnc_msg,0,
                 NULL);
}