package pkg;

import org.tinylog.Logger;

public class Main {

    public  static void main(String[] args)  {
        Logger.error("this is an Error message");
        Logger.warn("This is a Warn message");
        Logger.info("This is a info message");
        Logger.debug("This is a DEBUG message");
        Logger.trace("This is a Trace message");
        Logger.info("User's name is {}" , System.getProperty("user.name"));
        //Logger.info("User's name is " + System.getProperty("user.name"));
        Logger.error(new RuntimeException("Oops"),"something is wrong");

    }
}
