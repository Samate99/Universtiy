package book;

import book.model.Book;
import com.github.javafaker.Faker;

import java.time.ZoneId;
import java.util.Locale;

public class BookGenerator {
    private Faker faker;

    public BookGenerator(Locale loc) {
        faker = new Faker(loc);
    }

    public Book generate() {

        java.util.Date date;
        date=faker.date().birthday();
        java.time.LocalDate localDate = date.toInstant().atZone(ZoneId.systemDefault()).toLocalDate();

         Book egy=Book.builder()
                .isbn13(faker.code().isbn13())
                .title(faker.book().title())
                .publisher(faker.book().publisher())
                .author(faker.book().author())
                .publicationDate(localDate)
                .pages(faker.number().numberBetween(400,600))
                .format(faker.options().option(Book.Format.class))
                .available(faker.bool().bool())
                .build();
        return egy;
    }
}
