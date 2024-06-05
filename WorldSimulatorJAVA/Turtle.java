package worldsimulator;

import java.util.Random;

public class Turtle extends Animal {
	
	private static final int MOVE_CHANCE = 25;
	private static final int DEFLECT_STRENGTH = 5;

	public Turtle(World w, Coordinate c) {
		strength = Species.TURTLE.getStrength();
        initiative = Species.TURTLE.getInitiative();
        species = Species.TURTLE.getName();
        sprite = Species.TURTLE.getSprite();
        age = 0;
        world = w;
        coord = c;
        dead = false;
        world.addOrganism(this);
    }

    public Turtle(World w, Coordinate c, int s, int a) {
    	strength = s;
    	initiative = Species.TURTLE.getInitiative();
        species = Species.TURTLE.getName();
        sprite = Species.TURTLE.getSprite();
        age = a;
        world = w;
        coord = c;
        dead = false;
        world.addOrganism(this);
    }

    @Override
    public void action() {
    	String message;
        Random rand = new Random();
        int movementRoll = rand.nextInt(100);
        if (movementRoll > MOVE_CHANCE) {
        	message = String.format(getSpecies() + getID() + " pozostaje na polu " + getCoord() + "\n");
            world.prompt(message);
        	return;
        }
        Coordinate newCoord = findSpace();
        Organism opponent = world.findOrganismByCoordinate(newCoord);
        message = String.format(getSpecies() + getID() + " przechodzi z pola " + getCoord() + " na pole " + newCoord);
        world.prompt(message);
        if (opponent == null) {
        	message = String.format(" ");
            world.prompt(message);
        	setCoord(newCoord);
        } else {
            collision(this, opponent);
        }
    }

    @Override
    public boolean hasDeflectedAttack(Organism attacker) {
    	String message;
        if (attacker.getStrength() < DEFLECT_STRENGTH) {
        	message = String.format(getSpecies() + getID() + " odbija atak " + attacker.getSpecies() + attacker.getID() + " na polu " + getCoord());
        	world.prompt(message);
        	message = String.format(attacker.getSpecies() + attacker.getID() + " wraca na pole " + attacker.getCoord() + "\n");
            world.prompt(message);
        	return true;
        } else {
            return false;
        }
    }
    
}
