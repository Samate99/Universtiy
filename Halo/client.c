#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFSIZE 1024
#define PORT_NO 25565


int main(int argc, char *argv[] ){ // arg count, arg vector

  

   int fd;	                       // socket endpt	
   struct sockaddr_in server;	     // socket name (addr) of server 
   struct sockaddr_in client;	     // socket name of client 
   int server_size;                // length of the socket addr. server 
   int client_size;                // length of the socket addr. client 
   int bytes;    	                 // length of buffer 
   int rcvsize;                    // received bytes
   int trnmsize;                   // transmitted bytes
   int err;                        // error code
   int ip;												 // ip address
   char on;                        // 
   char buffer[100];                  // datagram dat buffer area
   char server_addr[16];           // server address
   char var[100];
   char s[INET6_ADDRSTRLEN];

   
   on                     = 1;   
   server.sin_family      = AF_INET;
   server.sin_addr.s_addr = inet_addr("127.0.0.1");
   server.sin_port        = htons(PORT_NO);
   server_size            = sizeof server;
   client_size            = sizeof client;
	
    //Socket keszites
   fd = socket(AF_INET, SOCK_STREAM, 0 );           //csatlakozások
   //printf("Creating socket! \n");
   if ( fd < 0 ) {
      //printf("Socket creation error\n");          //Hiba esetén 
      exit(1);
      }

   // beallitasok 
   setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof on);
   setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (char *)&on, sizeof on);

   //csatlakozas
   err = connect( fd, (struct sockaddr *) &server, server_size);
if ( err < 0 ) {
      printf("Nem sikerült csatlakozni a szerverhez\n");    //Connection error eseten
      printf("Próbld meg később\n");                //tereloszoveg
	exit(1); //csatlakozasi hiba eseten kilep itt.
      }
   printf("Sikeres csatlakozás a szerverhez!\n");            //sikeres csatlakozás
   
       recv(fd,buffer,100,0);                         
	if(strncmp(buffer, "vrn",4)==0)               //Varunk mert meg nem csatlakozott a masik player
        {
		printf("Várakozás az ellenfelre !\n");			
		
	}
   	if(strncmp(buffer, "skr",4)==0)  //beert a masik jatekos 
        {
		printf("A játék elindult, ellenfél kezd\n");	
		
	}
    
int player1_Elso=1, player1_Masodik = 1 , player2_Elso=1, player2_Masodik=1, dobot_szam=0; 
    while(1){
        recv(fd, buffer, 100, 0 );
        
       
        //Ezt az uzenetet az kapja meg aki az uj jatek eseten nem a vege-t írta be hanem az ujra reszt a masik jatekos pedig a veget   
	if(strncmp(buffer, "vege",4)==0)
        {
		printf("Vége az ellenfél sajnos ma már nem szeretne több játékot\n");
        printf("Köszönjük a játékot\n");
		close(fd);            
		break;
		
	}
       
        if(strncmp(buffer, "Vesztettél", 10) == 0)    
		{
		printf("Vesztettél az ellenfél átlépte a 49. mezőt!\n");  
		recv(fd,buffer,100,0);              
		if(strncmp(buffer,"vege",4)==0)                                     
		{
			printf("Vége az ellenfél sajnos ma már nem szeretne több játékot\n");  
                        printf("Köszönjük a játékot\n");
			close(fd);         //vege a kapcsolatnak .
			exit(0); //kilep a program
		}
		else if(strncmp(buffer,"ujgame",6)==0){  
		  printf("Az ellenfél szeretne új játékot\n");	         
          printf("Szeretnél új játékot kezdeni,vagy vége mára ?( ujra,vege):");    
		while(1)                              
				{
					fgets(buffer,100,stdin);
					if(strncmp(buffer, "ujra",4)==0)
					{
						send(fd, buffer, 100, 0);
		        			break;
					}
					if(strncmp(buffer, "vege",4)==0)
					{
						send(fd, "vege", 100, 0); 
                        
                        printf("Nem szeretnél új jatekot kezdeni !\n"); 
                        printf("Köszönjük a játékot\n");
						close(fd);
		    				exit(0);
					}
				printf("Rossz választ adtál meg kérlek válassz e kettő szó közűl : ujra,vege \n"); 
				}
				continue;		   
            	}
        }        
	//Megerkezdtünk a feladjuk reszhez 
        if(strncmp(buffer, "Feladta",7)==0)              
        {  
			printf("Nyertél az ellenfél feladta a játékod !\n");  
 
		   		recv(fd,buffer,100,0);      //feladasi eset
			
				if(strncmp(buffer,"vege",4)==0)    
				{
				printf("Vége az ellenfél sajnos ma már nem szeretne több játékot\n");  // Ha a vesztes nem akar ujat jatszani ezt az uzenetet kapja a gyoztes
                                printf("Köszönjük a játékot!\n");

				close(fd);

            			exit(0);
				}
				else if(strncmp(buffer,"ujgame",6)==0)
					{
					printf("Az ellenfél szeretne új játékot\n");   //Ha új jatekot akar a vesztes
            				printf("Szeretnél új játékot kezdeni,vagy mára vége?( ujra),(vege)\n");   //Itt dont a gyoztes hogy jatszanak ujat vagy sem
					while(1)
					{
						fgets(buffer,100,stdin);
						if(strncmp(buffer, "ujra",4)==0)
						{
							send(fd, buffer, 100, 0);
							break;
						}
						if(strncmp(buffer, "vege",4)==0)
						{
                                              printf("Nem szeretnél új jatekot kezdeni !\n");  //Zaró uzenet. Itt a jatek lezarul
                                              printf("Köszönjük a játékot!\n");
							send(fd, "vege", 100, 0);
							close(fd);
			    				exit(0);
						}
					printf("Rossz választ adtál meg kérlek válassz e kettő szó közűl :  ujra,vege \n");
					}
				continue;            				
				}    
         }        
	//lépés
	printf("%s", buffer);    
                  //if()				{
			//	printf("Az ellenfél nem szeretne több játékot\n");
			//	else if()
			//		{
   printf("+--------------------------------------------------------------------------------+\n");
   printf("|      Kérlek válassz bábút (elso) (masodik)                                     |\n");
   printf("|      Kérlek ha az egyik bábúd átlépte a 49es célt használd a másik bábúd !     |\n");
   printf("|      Ha meguntad a játékot egyszerűen csak használd a 'feladom' parancsot !    |\n");
   printf("+--------------------------------------------------------------------------------+\n");

				
	while (1)
	{	fgets(buffer,100,stdin);		
 		
		if(strncmp(buffer, "elso",4)==0)         //Valaszthatunk babuk kozul vagy feladhatjuk 
			break;
		if(strncmp(buffer, "masodik",7)==0)
			break;
		if(strncmp(buffer, "feladom",7)==0)
			break;
		printf("Rossz választ adtál meg kérlek válassz e három szó közűl : elso , masodik , feladom\n");
	}
	
	send(fd, buffer, 100, 0);
	recv(fd, buffer, 100, 0 );
	printf("\n--------------------\n");
        if(strncmp(buffer, "Feladtad",8)==0)
        { 
	       printf("Feladtad a játékot tehát  vesztettél\n");  //vesztes resz
               printf("Szeretnél új játékot kezdeni,vagy mára vége?( ujra),(vege)\n");
				while(1)
				{
					fgets(buffer,100,stdin);
					if(strncmp(buffer, "ujra",4)==0)  //Ha ujat akar a vesztes
					{
						send(fd, buffer, 100, 0);
		        			break;
					}
					if(strncmp(buffer, "vege",4)==0)   //Ha nem akar ujat a vesztes 
					{
                                             printf("Nem szeretnél új jatekot kezdeni !\n");
                                              printf("Köszönjük a játékot\n");   //Zaro uzene
						send(fd, "vege", 100, 0);
						close(fd);
		    				exit(0);
					}
				printf("Rossz választ adtál meg kérlek válassz e kettő szó közűl :  ujra,vege :");
				}
				continue;		
         }       
         if((strncmp(buffer, "Nyertél",7) == 0))
		{
                    	printf("Gratulálunk ! Te  Nyerted meg a jatekot ! \n");		
           	    	printf("Szeretnél új játékot kezdeni,vagy mára vége?( ujra) (vege):");
           		while(1)
				{
					fgets(buffer,100,stdin);   
					if(strncmp(buffer, "ujra",4)==0) // uj jatekot akar 
					{
						send(fd, buffer, 100, 0);
		        			break;
					}
					if(strncmp(buffer, "vege",4)==0)  //nem szeretne 
					{
                                              printf("Nem szeretnél új jatekot kezdeni !\n"); 
                                              printf("Köszönjük a játékot\n"); 
						send(fd, "vege", 100, 0);
						close(fd);
		    				exit(0);
					}
				printf("Rossz választ adtál meg kérlek válassz e kettő szó közűl :  ujra,vege \n");
				}
				continue; //uj valaszt kell megadni lehetoleg most megfelelot
                    
                }
		
		printf("%s", buffer);  //A babuk helyzete Sajat és ellenfel is
		printf("\n-----------------\nKör vége\n");  // 
           }
exit(0);
}
