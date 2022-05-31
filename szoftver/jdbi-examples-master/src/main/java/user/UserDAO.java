package user;

import org.jdbi.v3.sqlobject.config.RegisterBeanMapper;
import org.jdbi.v3.sqlobject.customizer.Bind;
import org.jdbi.v3.sqlobject.customizer.BindBean;
import org.jdbi.v3.sqlobject.statement.GetGeneratedKeys;
import org.jdbi.v3.sqlobject.statement.SqlCall;
import org.jdbi.v3.sqlobject.statement.SqlQuery;
import org.jdbi.v3.sqlobject.statement.SqlUpdate;

import java.util.List;
import java.util.Optional;


@RegisterBeanMapper(User.class)
public interface UserDAO {
    @SqlUpdate("""
        CREATE TABLE user (
            id IDENTITY PRIMARY KEY,
            username VARCHAR NOT NULL,
            password VARCHAR NOT NULL,
            name VARCHAR NOT NULL,
            email VARCHAR NOT NULL,
            gender VARCHAR NOT NULL,
            dob DATE NOT NULL,
            enabled BOOLEAN NOT NULL
        )
        """
    )
    void createTable();

    @SqlUpdate("INSERT INTO user VALUES (NULL, :username, :password, :name, :email, :gender, :dob, :enabled)")
    @GetGeneratedKeys
    Long insert(@BindBean User user);
    @SqlQuery("SELECT * FROM user WHERE id = :id")
    Optional<User> findById(@Bind("id") long id);
    @SqlQuery("SELECT * FROM user WHERE username = :username")
    Optional<User> findByUsername(@Bind("username") String username);
    @SqlCall("DELETE FROM user WHERE id = :id")
    void delete(@BindBean User user);
    @SqlQuery("SELECT * FROM user ORDER BY id")
    List<User> list();
}