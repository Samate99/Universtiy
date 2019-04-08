public class ExorTitkosito {

    
    public ExorTitkosito(String kulcsSzoveg,
            java.io.InputStream bejovoCsatorna,
            java.io.OutputStream kimenoCsatorna)
            throws java.io.IOException {

        byte [] kulcs = kulcsSzoveg.getBytes();
        byte [] buffer = new byte[256];
        int kulcsIndex = 0;
        int olvasottBajtok = 0;

        while((olvasottBajtok =
                bejovoCsatorna.read(buffer)) != -1) {
    
            for(int i=0; i<olvasottBajtok; ++i) {

                
                buffer[i] = (byte)(buffer[i] ^ kulcs[kulcsIndex]);
                kulcsIndex = (kulcsIndex+1) % kulcs.length;
               
            }

            kimenoCsatorna.write(buffer, 0, olvasottBajtok);
            
        }       
    }   
    public static void main(String[] args) {       
        try {          
            new ExorTitkosito(args[0], System.in, System.out);
           
        } catch(java.io.IOException e) {
          
            e.printStackTrace();            
        }        
    }

   
