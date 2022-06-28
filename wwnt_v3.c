#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <net/if.h>

void f1()
{
    struct addrinfo hints = {0}, *addrs;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;

    int rval = getaddrinfo("ifconfig.me", "80", &hints, &addrs);
    if (rval != 0)
    {
        fprintf(stderr,"getaddrinfo failed: %s\n", gai_strerror(rval));
        return 1;
    }

    int s = socket(addrs->ai_family, addrs->ai_socktype, addrs->ai_protocol);
    if (s == -1)
    {
        perror("socket failed");
        return 1;
    }
    rval = connect(s, addrs->ai_addr, addrs->ai_addrlen);


    char cmd[] = "GET / HTTP/1.1\nHost: ifconfig.me\n\n";
    rval = send(s, cmd, strlen(cmd), 0);
    if (rval == -1)
    {
        perror("send failed");
        return 1;
    }

    char buf[1000] = {0};
    rval = recv(s, buf, sizeof(buf), 0);
    if (rval == -1)
    {
        perror("recv failed");
        return 1;
    }

    char *start = buf, *end;
    end = strchr(start, '\n');
    if (!strncmp(start, "HTTP/1.1 200 OK", end - start - 1))
    {
        while (!(end[1] == '\r' && end[2] == '\n'))
        {
            start = end + 2;
            end = strchr(start, '\n');
        }
        start = end + 3;
        end = strchr(start, '\n');
        if (end) *end = 0;
        printf("%s\n", start);
    }
    else
    {
        printf("request failed\n");
    }

    close(s);
    freeaddrinfo(addrs);
}

void f2()
{
    unsigned int max_interfaces = 255;
    char ifname[IFNAMSIZ];
    char prev_ifname[IFNAMSIZ];

    for (unsigned int if_id=1; if_id<max_interfaces; if_id++)
    {
        if_indextoname(if_id, ifname);
        if  (ifname[1] == '\1'){
            continue;
        }
       else if(strcmp(ifname, prev_ifname) == 0)
        {
            break;
        }
        else
        {
            printf("%d: %s\n", if_id, ifname);
            snprintf(prev_ifname, sizeof(prev_ifname), "%s", ifname);
        }
    }    

}

int main(int args, char *argv[])
{
    while(1)
    {
        char op;
        printf("\n\n\t White Wolf Network Toolkit\n\n\n");
        printf("\n\n\t Written by TIRATORE\n\n\n");


        printf("1. Get External IP\n");
        printf("2. Get Interfaces List\n");
        printf("3. Restart Interfaces(TODO)\n");
        printf("4. Exit\n\n\n");
        printf("Enter your choice: ");        		
        
        scanf(" %c", &op);

        switch (op)
        {
        case '1':
            f1();
            break;
        case '2':
            f2();
            break;
        case '3':
            printf("TODO\n");
            break;
        case '4':
            break;
        default:
            printf("Invalid Input\n");
            break;
        if (op == "4")
        {
            break;
        }
        }
    }
    return 0;
}