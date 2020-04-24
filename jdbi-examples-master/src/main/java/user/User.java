package user;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;
import java.time.LocalDate;

@AllArgsConstructor
@NoArgsConstructor
@Builder
@Data

public class User {

    public static enum Gender {
        FEMALE,
        MALE
    }
    private Long id;
    private String name;
    private String username;
    private String password;
    private String email;
    private LocalDate dob;
    private Gender gender;
    private boolean enabled;
}
