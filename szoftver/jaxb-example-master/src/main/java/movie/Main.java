package movie;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.math.BigDecimal;
import java.net.URL;
import java.time.Year;
import java.util.List;

import jaxb.JAXBHelper;

public class Main {

    public static void main(String[] args) throws Exception {
        Movie movie = new Movie();
        movie.setTitle("Shrek");
        movie.setYear(Year.of(2001));
        movie.setRating(new BigDecimal("7.8"));
        movie.setVotes(587180);
        movie.setGenres(List.of("animation", "adventure", "comedy"));
        movie.setUrl(new URL("https://www.imdb.com/title/tt0126029/"));

        JAXBHelper.toXML(movie, System.out);

        JAXBHelper.toXML(movie, new FileOutputStream("movie.xml"));
        System.out.println(JAXBHelper.fromXML(Movie.class, new FileInputStream("movie.xml")));
    }

}