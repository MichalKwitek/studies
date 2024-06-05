package worldsimulator;

public class Guarana extends Plant {
	
	private static final int STRENGTH_INCREASE = 3;

	public Guarana(World w, Coordinate c) {
		strength = Species.GUARANA.getStrength();
        initiative = Species.GUARANA.getInitiative();
        species = Species.GUARANA.getName();
        sprite = Species.GUARANA.getSprite();
        age = 0;
        world = w;
        coord = c;
        dead = false;
        world.addOrganism(this);
    }

    public Guarana(World w, Coordinate c, int s, int a) {
    	strength = s;
    	initiative = Species.GUARANA.getInitiative();
        species = Species.GUARANA.getName();
        sprite = Species.GUARANA.getSprite();
        age = a;
        world = w;
        coord = c;
        dead = false;
        world.addOrganism(this);
    }

    public boolean hasIncreasedStrength(Organism attacker) {
        attacker.setStrength(attacker.getStrength() + STRENGTH_INCREASE);
        String message = String.format(attacker.getSpecies() + attacker.getID() + " zwieksza swoja sile o " + STRENGTH_INCREASE + "\n");
        world.prompt(message);
        return true;
    }

}
