package worldsimulator;

public enum Species {
    
	WOLF('W', "Wolf", 9, 5), 
	SHEEP('S', "Sheep", 4, 4), 
	ANTILOPE('A', "Antilope", 4, 4), 
	TURTLE('T', "Turtle", 2, 1), 
	FOX('F', "Fox", 3, 7), 
	GRASS('g', "Grass", 0, 0), 
	DANDELION('d', "Dandelion", 0, 0), 
	GUARANA('x', "Guarana", 0, 0), 
	NIGHTSHADE('n', "Nightshade", 99, 0), 
	SOSNOWSKY('s', "Sosnowsky", 10, 0), 
	HUMAN('H', "Human", 5, 4);
	
    private final char sprite;
    private final String name;
    private final int strength;
    private final int initiative;

    private Species(char sprite, String name, int strength, int initiative) {
        this.sprite = sprite;
        this.name = name;
        this.strength = strength;
        this.initiative = initiative;
    }

    public char getSprite() {
        return sprite;
    }

    public String getName() {
        return name;
    }
    
    public int getStrength() {
        return strength;
    }
    
    public int getInitiative() {
        return initiative;
    }
    
    public static int getSpeciesOrder(char sprite) {
        switch (sprite) {
            case 'W':
                return WOLF.ordinal(); // Return the ordinal value of the enum constant
            case 'S':
                return SHEEP.ordinal();
            case 'A':
                return ANTILOPE.ordinal();
            case 'T':
                return TURTLE.ordinal();
            case 'F':
                return FOX.ordinal();
            case 'g':
                return GRASS.ordinal();
            case 'd':
                return DANDELION.ordinal();
            case 'x':
                return GUARANA.ordinal();
            case 'n':
                return NIGHTSHADE.ordinal();
            case 's':
                return SOSNOWSKY.ordinal();
            default:
                throw new IllegalArgumentException("Invalid sprite character: " + sprite);
        }
    }
    
    public static Species fromName(String name) {
        for (Species species : Species.values()) {
            if (species.getName() == name) {
                return species;
            }
        }
        throw new IllegalArgumentException("Invalid name: " + name);
    }
    
    public static Species fromSprite(char sprite) {
        for (Species species : Species.values()) {
            if (species.getSprite() == sprite) {
                return species;
            }
        }
        throw new IllegalArgumentException("Invalid sprite character: " + sprite);
    }
    
    public static Species fromOrdinal(int ordinal) {
        for (Species species : Species.values()) {
            if (species.ordinal() == ordinal) {
                return species;
            }
        }
        throw new IllegalArgumentException("Invalid ordinal number: " + ordinal);
    }
}
