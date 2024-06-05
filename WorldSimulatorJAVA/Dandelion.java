package worldsimulator;

import java.util.Random;

public class Dandelion extends Plant {
    

    public Dandelion(World w, Coordinate c) {
    	strength = Species.DANDELION.getStrength();
        initiative = Species.DANDELION.getInitiative();
        species = Species.DANDELION.getName();
        sprite = Species.DANDELION.getSprite();
        age = 0;
        world = w;
        coord = c;
        dead = false;
        world.addOrganism(this);
    }

    public Dandelion(World w, Coordinate c, int s, int a) {
    	strength = s;
    	initiative = Species.DANDELION.getInitiative();
        species = Species.DANDELION.getName();
        sprite = Species.DANDELION.getSprite();
        age = a;
        world = w;
        coord = c;
        dead = false;
        world.addOrganism(this);
    }

    @Override
    public void action() {
    	String message;
        boolean grew = false;
        int growTimes = 0;
        Random rand = new Random();
        while (growTimes < 3) {
            int growRoll = rand.nextInt(100);
            if (growRoll <= GROW_CHANCE) {
                grew = true;
                Coordinate newbornCoord = findVoidSpace(getCoord());
                if (!newbornCoord.equals(getCoord())) {
                    multiply(this, newbornCoord);
                    message = String.format(getSpecies() + getID() + " z pola " + getCoord() + " rozprzestrzenia sie na pole " + newbornCoord);
                    world.prompt(message);
                } else {
                	message = String.format(getSpecies() + getID() + " z pola " + getCoord() + " nie moze sie rozprzestrzenic - brak pustego miejsca w poblizu");
                	world.prompt(message);
                }
            }
            growTimes++;
        }
        if (grew) {
        	message = String.format(" ");
        	world.prompt(message);
        }
    }
}
