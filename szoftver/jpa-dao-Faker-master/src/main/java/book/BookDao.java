package book;

import book.model.Book;
import com.google.inject.persist.Transactional;
import jpa.GenericJpaDao;

import javax.persistence.NoResultException;
import java.util.Optional;

public class BookDao extends GenericJpaDao<Book> {
    @Transactional
    public Optional<Book> findByIsbn13(String isbn13) {
        try {
            return Optional.of(entityManager.createQuery("SELECT x FROM Book x  WHERE x.valtozo = :valtozo", Book.class)
                    .setParameter("valtozo", isbn13)
                    .getSingleResult());
        } catch (NoResultException e) {
            return Optional.empty();
        }
    }
}
