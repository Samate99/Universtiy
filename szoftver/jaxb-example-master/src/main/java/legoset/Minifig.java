package legoset;

import lombok.Data;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlValue;

@XmlAccessorType(XmlAccessType.FIELD)
@Data

public class Minifig {
    @XmlValue
    private String name;

    @XmlAttribute
    private int count;

    public Minifig(String name, int count){
        this.name = name;
        this.count = count;
    }

}
