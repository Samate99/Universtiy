#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h> 

#define BUFSIZE 1024                      // buffer size
#define PORT_NO 25565                  // port number

int main(int argc, char *argv[] ){ // arg count, arg vector

   //Deklaraciok
   int fd, fd2;	        	           // socket endpoint
   int fdc1;                        // socket endpoint
   struct sockaddr_in server;      	// socket name (addr) of server
   struct sockaddr_in client;	     	// socket name of client
   struct sockaddr_in client2;
   int server_size;                	// length of the socket addr. server
   int client_size;                	// length of the socket addr. client
   int client2_size;
   int bytes;		           			// length of buffer
   int ip;
   int err;                        // error code
   char on;                        // sockopt option
   char buffer[100];
   int fdc2;
   char s[INET6_ADDRSTRLEN];   
   
   on                     = 1;   
   bytes                  = BUFSIZE;
   server.sin_family      = AF_INET;
   server.sin_addr.s_addr = INADDR_ANY;
   server.sin_port        = htons(PORT_NO);
   server_size            = sizeof server;
   client_size            = sizeof client;	 


// Maga a socket 
   fd = socket(AF_INET, SOCK_STREAM, 0 );   
   if ( fd < 0 ) {                      
      exit(1);              
      }   	


   setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof on); 
   setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (char *)&on, sizeof on);  


	
   err = bind( fd, (struct sockaddr *) &server, server_size);  
   err = listen( fd, 2);
   printf("+-------------------------------+\n");
   printf("|      A szerver elkészült!     |\n");
   printf("+-------------------------------+\n");
   printf("Várakozás a jatekosokra \n");

		fdc1 = accept(fd, (struct sockaddr *) &client, &client_size);
		send(fdc1,"vrn",100,0);   //Nem csatlakoztak meg a kliensek 
		fdc2 = accept(fd, (struct sockaddr *) &client, &client_size);
		printf("Kliensek csatlakoztak a játék  Hamarosan elkezdődik!\n"); // MIndjart kezdunk 
		send(fdc2,"skr",100,0); 

    srand ( time(NULL) );
    int j11=1,j12=1,j21=1,j22=1;  // 11 ,12 a client egy elso es masodik babujanak utvonala a j21 ,j22 a client ketto elso es masodik babujanak helye
    int n;                                // megjelenik az N ami a random szamunk vagyis maga a dobókocka
    int indul = 0;                
    int temp;    //ezzel van megoldva hogy ne mindig ugyanaz a jatekos kezdjen 
    while(1){

        	if(indul==1)  //continue 
          	 {        
			
	    j11=1,j12=1,j21=1,j22=1; //resetelodnek a statok
	    temp = fdc1;  //itt cserelem meg a playereket , ha ujra indul akkor ezzel van megoldva hogy ne mindig ugyanaz jatszon
            fdc1 = fdc2;
            fdc2 = temp;
           	 }
            indul = 0;
	// jatekos 1
	//elküldi a helyzetét az első játékosnak
	   n = rand() %6 +1; // dobott szam
           sprintf(buffer,"Saját bábuid pozíciója: [%d] [%d]\nEllenfél bábuinak pozíciója: [%d] [%d]\ndobott szám: {%d}\n",j11,j12,j21,j22,n);
	//szerver kérdése hogy melyik bábut választa az első játékos vagy feladta e 
          	send(fdc1, buffer, 100, 0); //Buffer tartalmat elkuldni a szerver
              //válaszol a játékos
            recv(fdc1, buffer, 100, 0 );  //visszakapja
                     
         
	  //ha feladommal válaszolt elküldi az adatot a játékosnak és az ellenfélnek
           if(strncmp(buffer, "feladom",7)==0)
           {	 	
		//feladta üzenet a győztesnek
                send(fdc2, "Feladta", 100, 0);
		//feladtad üzenet az a "feladónak"
                send(fdc1, "Feladtad", 100, 0);
                //uj jatek resz
		recv(fdc1, buffer, 100, 0 );
		//ha egyes játékos nem akar uj játékot
		if(strncmp(buffer,"vege",4)==0)
			{
				send(fdc2, "vege", 100, 0); 
				break; 
			}
		//ha egyes játékos akar uj játékot
                if(strncmp(buffer,"ujra",4)==0)  
			{				
				send(fdc2,"ujgame",100,0);
			}
		

		//kettes akare e uj játékot
                recv(fdc2, buffer, 100, 0 );
		if(strncmp(buffer,"vege",4)==0)
		{
             	 send(fdc1, "vege", 100, 0);
		break; 
		}
                 if(strncmp(buffer,"ujra",4)==0)
                {
			indul = 1;
                   	 
                   	 continue; //ujrakezdodik 
		}                
                  
            }
         
		//lépés a bábuval
          if(strncmp(buffer,"elso",4)==0 && j11<49)
		{
			j11+=n; //lepes alap esetben
			if(j11==j21 && j21<49)   //utesek
			j21=1; 
			if(j11==j22 && j22<49)
			j22=1;
			
		}
        else if(strncmp(buffer,"elso",4)==0 && j11>49)
					{
			j12+=n;  //lepes ha az elso babu beert 
			if(j12==j21 && j21<49)  // utesek
				j21=1;
			if(j12==j22 && j22<49)
				j22=1;
			}
		if(strncmp(buffer,"masodik",7)==0 && j12<49)
		{
			j12+=n;  //lepes masodik alap esetben
			if(j12==j21 && j21<49)
				j21=1;         //utesek
			if(j12==j22 && j22<49)
				j22=1;
			
		}        
		else if(strncmp(buffer,"masodik",7)==0 && j12>49)
        {	        j11+=n; //lepes ha a masodik babu beert
			if(j11==j21 && j21<49)  //utesek
			j21=1;
			if(j11==j22 && j22<49)
			j22=1;
			
			}
         //ha nyert az első játékos
          if(j11>49 && j12>49)
		{
                	              
                	send(fdc1, "Nyertél", 100, 0);			
              		send(fdc2, "Vesztettél", 100, 0);                
              		//akarnake új játékot
			recv(fdc1, buffer, 100, 0 );        
			//ha az elso játékos nem akar uj játékot
			if(strncmp(buffer,"vege",4)==0)
			{
				send(fdc2, "vege", 100, 0);
				break;
			}
			//ha elso játékos akar uj játékot
               		 if(strncmp(buffer,"ujra",4)==0)
			{				
				send(fdc2,"ujgame",100,0);
			}
		

			//masodik akare e uj játékot
                	recv(fdc2, buffer, 100, 0 );
			if(strncmp(buffer,"vege",4)==0)
			{
             			 send(fdc1, "vege", 100, 0);
				 break;
			}
                 	if(strncmp(buffer,"ujra",4)==0)
               		{
				indul = 1;                   		 
                   	 	continue;
			}
              }
// lépés utáni poziciok	
sprintf(buffer,"Saját bábuid pozíciója: [%d] [%d]\nEllenfél bábuinak pozíciója: [%d] [%d]\n",j11,j12,j21,j22); 
send(fdc1, buffer, 100, 0); 

//masodik jatekos esete
n = rand() %6 +1;	
sprintf(buffer,"Saját bábuid pozíciója: [%d] [%d]\nEllenfél bábuinak pozíciója: [%d] [%d]\ndobott szám: {%d}\n",j21,j22,j11,j12,n);  
send(fdc2, buffer, 100, 0);

recv(fdc2, buffer, 100, 0 );
          if(strncmp(buffer, "feladom",7)==0)
          	 {
			
                	send(fdc1, "Feladta", 100, 0);
               	 	send(fdc2, "Feladtad", 100, 0);
                	//akare a kettes új játékot
			recv(fdc2, buffer, 100, 0 );
			//ha nem
			if(strncmp(buffer,"vege",4)==0)
				{
             				 send(fdc1, "vege", 100, 0);
					break; //kilep a ciklusbol
				}
			//ha igen
                	if(strncmp(buffer,"ujra",4)==0)
				{
				  send(fdc1,"ujgame",100,0);
				}
			
              		recv(fdc1, buffer, 100, 0 );
			//ha a másik játékos nem akar
			if(strncmp(buffer,"vege",4)==0)
				{
             	 			send(fdc2, "vege", 100, 0);
					break; //kilep a ciklusbol
				}
			//ha akar
                 	if(strncmp(buffer,"ujra",4)==0)
               			{
					indul = 1;                    			
                    			continue; //ujrainditja 
				}         	 
           	 }
//lépés 2es
if(strncmp(buffer,"elso",4)==0 && j21<49)
		{
			j21+=n; //lepes 
			if(j21==j11 && j11<49)  //utesek
			j11=1;
			if(j21==j12 && j12<49)
			j12=1;
			
		}		
		else if(strncmp(buffer,"elso",4)==0 && j21>49)
					{
			j22+=n;  //lepes ha az elso babu mar beert es az okos elsot irt
			if(j22==j11 && j11<49)
			j11=1;
			if(j22==j12 && j12<49)
			j12=1;
			
			}
					
if(strncmp(buffer,"masodik",7)==0 && j22<49)
		{
			j22+=n;  //lepes
			if(j22==j11 && j11<49)  //utesek
			j11=1;
			if(j22==j12 && j12<49)
			j12=1;
						
		}  
			else if(strncmp(buffer,"masodik",7)==0 && j22>49)  
					{
			j21+=n;
			if(j21==j11 && j11<49)  //lepes ha a masodik babu beert de megis beeírja hogy masodik
			j11=1;  //utesek
			if(j21==j12 && j12<49)
			j12=1;
			
			}
//nyert-e
if(j21>49 && j22>49)
		{
            		           		
              		send(fdc2, "Nyertél", 100, 0);			
              		send(fdc1, "Vesztettél", 100, 0);
			//Kettes eseteben ujra jatszas
			recv(fdc2, buffer, 100, 0 );
			//ha no
			if(strncmp(buffer,"vege",4)==0)
				{
             				 send(fdc1, "vege", 100, 0);
					break; //kilep a ciklusbol
				}
			//ha yes
                	if(strncmp(buffer,"ujra",4)==0)
				{
				  send(fdc1,"ujgame",100,0);
				}
			
              		recv(fdc1, buffer, 100, 0 );
			// a másik játékos nem akar
			if(strncmp(buffer,"vege",4)==0)
				{
             	 			send(fdc2, "vege", 100, 0);
					break; //kilep a ciklusbol
				}
			// akar
                 	if(strncmp(buffer,"ujra",4)==0)
               			{
					indul = 1;                    			
                    			continue; // ujra inditja
				}               
          	  
           	 }
sprintf(buffer,"Saját bábuid pozíciója: [%d] [%d]\nEllenfél bábuinak pozíciója: [%d] [%d]\n",j21,j22,j11,j12);
send(fdc2, buffer, 100, 0);  //elkuldni az adatokat a kliensnek

    }
   printf("+------------------------------------------+\n");
   printf("|    A jateknak vege !                     |\n");
   printf("|    Sikeres kapcsolatbontás a kliensekkel |\n");
   printf("|    Program vege                          |\n");
   printf("+------------------------------------------+\n");
//ha vege a jateknak ez az utolso uzenetek amelyeket a server.c ír ki
close(fdc1); //bezarja a kapcsolatokat
close(fdc2); 
exit(0); //leall
   }
