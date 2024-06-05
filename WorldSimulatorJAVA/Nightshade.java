package worldsimulator;

public class Nightshade extends Plant {
	
	public Nightshade() {
        // potrzebne do konstruktora Sosnowsky
    }
	
    public Nightshade(World w, Coordinate c) {
    	strength = Species.NIGHTSHADE.getStrength();
        initiative = Species.NIGHTSHADE.getInitiative();
        species = Species.NIGHTSHADE.getName();
        sprite = Species.NIGHTSHADE.getSprite();
        age = 0;
        world = w;
        coord = c;
        dead = false;
        world.addOrganism(this);
    }

    public Nightshade(World w, Coordinate c, int s, int a) {
    	strength = s;
    	initiative = Species.NIGHTSHADE.getInitiative();
        species = Species.NIGHTSHADE.getName();
        sprite = Species.NIGHTSHADE.getSprite();
        age = a;
        world = w;
        coord = c;
        dead = false;
        world.addOrganism(this);
    }
    
    @Override
    public boolean isPoisonous(Organism attacker) {
    	String message = String.format(attacker.getSpecies() + attacker.getID() + " zjada " + getSpecies() + getID() + " na polu " + getCoord() + " i umiera");
        world.prompt(message);
    	attacker.kill();
        return true;
    }

}
