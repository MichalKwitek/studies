package worldsimulator;

import java.util.Random;

public class Plant extends Organism {
	
	public static final int GROW_CHANCE = 10;
	
    public Plant(char sprite, int initiative, int strength, String species, Coordinate coord, World world) {
		super(sprite, initiative, strength, species, coord, world);
		// TODO Auto-generated constructor stub
	}

    public Plant() {
		// TODO Auto-generated constructor stub
	}
    
	@Override
    public void action() {
		String message;
		Random rand = new Random();
        int growRoll = rand.nextInt(100);
        if (growRoll <= GROW_CHANCE) {
            Coordinate newbornCoord = findVoidSpace(getCoord());
            if (!newbornCoord.equals(getCoord())) {
                multiply(this, newbornCoord);
                message = String.format(getSpecies() + getID() + " z pola " + getCoord() + " rozprzestrzenia sie na pole " + newbornCoord + "\n");
                world.prompt(message);
            } else {
            	message = String.format(getSpecies() + getID() + " z pola " + getCoord() + " nie moze sie rozprzestrzenic - brak pustego miejsca w poblizu\n");
            	world.prompt(message);
            }
        }
    }

}
