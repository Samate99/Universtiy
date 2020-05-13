package book;


import com.google.inject.Guice;
import com.google.inject.Injector;
import guice.PersistenceModule;
import java.util.Locale;


public class Main {
    public static void main(String[] args) {
        Injector injector = Guice.createInjector(new PersistenceModule("test"));
        BookDao bookDao = injector.getInstance(BookDao.class);
        BookGenerator gen = new BookGenerator(new Locale("hu"));


        for (int i = 0; i < 600; i++) {
            bookDao.persist(gen.generate());
        }
        bookDao.findAll()
                .stream()
                .forEach(System.out::println);


    }
}
