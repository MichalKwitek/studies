package worldsimulator;

import java.util.List;
import java.util.Random;

public class Antilope extends Animal {
	
    private static final int RUN_CHANCE = 50;

    public Antilope(World w, Coordinate c) {
        strength = Species.ANTILOPE.getStrength();
        initiative = Species.ANTILOPE.getInitiative();
        species = Species.ANTILOPE.getName();
        sprite = Species.ANTILOPE.getSprite();
        age = 0;
        world = w;
        coord = c;
        dead = false;
        world.addOrganism(this);
    }

    public Antilope(World w, Coordinate c, int s, int a) {
    	strength = s;
    	initiative = Species.ANTILOPE.getInitiative();
        species = Species.ANTILOPE.getName();
        sprite = Species.ANTILOPE.getSprite();
        age = a;
        world = w;
        coord = c;
        dead = false;
        world.addOrganism(this);
    }

    @Override
    public void action() {
    	String message;
        Coordinate oldCoord = new Coordinate(getCoord());
        Coordinate newCoord = new Coordinate(oldCoord);
        List<Coordinate> coordinates = world.getAdjacentTiles(newCoord);
        Random rand = new Random();
        if (coordinates.size() > 0) {
        	int rolledValue = rand.nextInt(coordinates.size());
            newCoord = coordinates.get(rolledValue);
            coordinates = world.getAdjacentTiles(newCoord);
            if (coordinates.size() > 0) {
            	newCoord = oldCoord;
            	while (newCoord.equals(oldCoord)) {
            	rolledValue = rand.nextInt(coordinates.size());
                newCoord = coordinates.get(rolledValue);
            	}
            }
        }

        Organism opponent = world.findOrganismByCoordinate(newCoord);
        message = String.format(getSpecies() + getID() + " przechodzi z pola " + oldCoord + " na pole " + newCoord);
        world.prompt(message);
        if (opponent == null) {
        	message = String.format("\n");
        	world.prompt(message);
            setCoord(newCoord);
        } else {
            collision(this, opponent);
        }
    }

    @Override
	public boolean ranAway(Organism attacker) {
    	String message;
        Random rand = new Random();
        int runRoll = rand.nextInt(100);
        if (runRoll < RUN_CHANCE) {
            Coordinate newCoord = findVoidSpace(getCoord());
            if (!newCoord.equals(getCoord())) {
                attacker.setCoord(getCoord());
                message = String.format(getSpecies() + getID() + " uciekla przed " + attacker.getSpecies() + attacker.getID() + " z pola " + getCoord() + " na pole " + newCoord + "\n");
                world.prompt(message);
                setCoord(newCoord);
                return true;
            } else {
            	message = String.format(getSpecies() + getID() + "Nie moze uciec - brak pustego miejsca w poblizu\n");
                world.prompt(message);
            	return false;
            }
        } else {
            return false;
        }
    }
}
