package worldsimulator;

import java.util.Random;

public class Sosnowsky extends Nightshade {
	
	public Sosnowsky(World w, Coordinate c) {
		strength = Species.SOSNOWSKY.getStrength();
        initiative = Species.SOSNOWSKY.getInitiative();
        species = Species.SOSNOWSKY.getName();
        sprite = Species.SOSNOWSKY.getSprite();
        age = 0;
        world = w;
        coord = c;
        dead = false;
        world.addOrganism(this);
    }

    public Sosnowsky(World w, Coordinate c, int s, int a) {
    	strength = s;
    	initiative = Species.SOSNOWSKY.getInitiative();
        species = Species.SOSNOWSKY.getName();
        sprite = Species.SOSNOWSKY.getSprite();
        age = a;
        world = w;
        coord = c;
        dead = false;
        world.addOrganism(this);
    }

    @Override
    public void action() {
    	String message;
        killAnimals();
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
    
    private void killAnimal(boolean killed, Coordinate coord) {
    	Organism org = world.findOrganismByCoordinate(coord);
        if (org instanceof Animal) {
            killed = true;
            String message = String.format(org.getSpecies() + org.getID() + " z pola " + org.getCoord() + " ginie zatruty przez " + this.getSpecies() + this.getID() + " z pola " + this.getCoord());
            world.prompt(message);
            org.kill();
        }
    }

    private void killAnimals() {
        boolean killed = false;
        Coordinate newCoord = new Coordinate(getCoord());
        newCoord.x += 1;
        killAnimal(killed, newCoord);
        newCoord.y -= 1;
        killAnimal(killed, newCoord);
        newCoord.x -= 1;
        killAnimal(killed, newCoord);
        newCoord.x -= 1;
        killAnimal(killed, newCoord);
        newCoord.y += 1;
        killAnimal(killed, newCoord);
        newCoord.y += 1;
        killAnimal(killed, newCoord);
        newCoord.x += 1;
        killAnimal(killed, newCoord);
        newCoord.x += 1;
        killAnimal(killed, newCoord);
        if (killed) {
        	String message = String.format("\n");
        	world.prompt(message);
        }
    }

}
