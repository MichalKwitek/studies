package worldsimulator;

public enum Directions {
    NORTH(0), EAST(1), SOUTH(2), WEST(3), NORTH_EAST(4), NORTH_WEST(5), SOUTH_EAST(6), SOUTH_WEST(7);

    private final int dirNumber;

    private Directions(int dirNumber) {
        this.dirNumber = dirNumber;
    }

    public int getDirNumber() {
        return dirNumber;
    }
    
    // Method to get Directions enum constant based on rolled value
    public static Directions fromInt(int rolledValue) {
        switch (rolledValue) {
            case 0:
                return NORTH;
            case 1:
                return EAST;
            case 2:
                return SOUTH;
            case 3:
                return WEST;
            case 4:
                return NORTH_EAST;
            case 5:
                return NORTH_WEST;
            case 6:
                return SOUTH_EAST;
            case 7:
                return SOUTH_WEST;
            default:
                throw new IllegalArgumentException("Invalid rolled value: " + rolledValue);
        }
    }

}
